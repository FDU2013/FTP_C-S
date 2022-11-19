#include <server_command.h>

static size_t size_packet = sizeof(struct Packet);

struct client_info *client_info_alloc(int s, int c)
{
	struct client_info *ci = (struct client_info *)malloc(sizeof(struct client_info));
	ci->sfd = s;
	ci->cid = c;
	return ci;
}

void command_pwd(struct Packet *shp, struct Packet *data, int sfd_client, char *lpwd)
{
	int x;
	shp->type = kData;
	strcpy(shp->buffer, lpwd);
	data = htonp(shp);
	if ((x = send(sfd_client, data, size_packet, 0)) != size_packet)
		throwErrorAndExit("send()", x);
}

void command_cd(struct Packet *shp, struct Packet *data, int sfd_client, char *message)
{
	int x;
	shp->type = kResponse;
	strcpy(shp->buffer, message);
	data = htonp(shp);
	if ((x = send(sfd_client, data, size_packet, 0)) != size_packet)
		throwErrorAndExit("send()", x);
}

void command_ls(struct Packet *shp, struct Packet *data, int sfd_client, char *lpwd)
{
	int x;
	shp->type = kData;
	DIR *d = opendir(lpwd);
	if (!d)
		throwErrorAndExit("opendir()", (int)d);
	struct dirent *e;
	while (e = readdir(d))
	{
		sprintf(shp->buffer, "%s\t%s", e->d_type == 4 ? "DIR:" : e->d_type == 8 ? "FILE:"
																				: "UNDEF:",
				e->d_name);
		data = htonp(shp);
		if ((x = send(sfd_client, data, size_packet, 0)) != size_packet)
			throwErrorAndExit("send()", x);
	}
	send_EOT(shp, data, sfd_client);
}

void command_get(struct Packet *shp, struct Packet *data, int sfd_client)
{
	int x;
	FILE *f = ReadFileAuto(shp->buffer); // Yo!
	shp->type = kResponse;
	shp->command_type = GET;
	strcpy(shp->buffer, f ? "File found; processing" : "Error opening file.");
	// printpacket(shp, HP);
	data = htonp(shp);
	if ((x = send(sfd_client, data, size_packet, 0)) != size_packet)
		throwErrorAndExit("send()", x);
	if (f)
	{
		shp->type = kData;
		send_file(shp, data, sfd_client, f);
		fclose(f);
	}
	send_EOT(shp, data, sfd_client);
}

void command_put(struct Packet *shp, struct Packet *data, int sfd_client)
{
	int x;
	FILE *f = WriteFileAuto(shp->buffer);
	shp->type = kResponse;
	shp->command_type = PUT;
	strcpy(shp->buffer, f ? "Everything in order; processing" : "Error opening file for writing on server side.");
	// printpacket(shp, HP);
	data = htonp(shp);
	if ((x = send(sfd_client, data, size_packet, 0)) != size_packet)
		throwErrorAndExit("send()", x);
	if (f)
	{
		receive_file(shp, data, sfd_client, f);
		fclose(f);
	}
}

void command_mkdir(struct Packet *shp, struct Packet *data, int sfd_client)
{
	char message[LENBUFFER];
	DIR *d = opendir(shp->buffer);
	if (d)
	{
		strcpy(message, "already exists");
		closedir(d);
	}
	else if (mkdir(shp->buffer, 0777) == -1)
	{
		fprintf(stderr, "Wrong path.\n");
		strcpy(message, "fail");
	}
	else
		strcpy(message, "success");
	int x;
	shp->type = kResponse;
	strcpy(shp->buffer, message);
	data = htonp(shp);
	if ((x = send(sfd_client, data, size_packet, 0)) != size_packet)
		throwErrorAndExit("send()", x);
}

void command_rget(struct Packet *shp, struct Packet *data, int sfd_client)
{
	static char lpwd[LENBUFFER];
	if (!getcwd(lpwd, sizeof lpwd))
		throwErrorAndExit("getcwd()", 0);
	int x;
	DIR *d = opendir(lpwd);
	if (!d)
		throwErrorAndExit("opendir()", (int)d);
	struct dirent *e;
	while (e = readdir(d))
		if (e->d_type == 4 && strcmp(e->d_name, ".") && strcmp(e->d_name, ".."))
		{
			shp->type = kRequest;
			shp->command_type = LMKDIR;
			strcpy(shp->buffer, e->d_name);
			data = htonp(shp);
			// fprintf(stderr, "LMKDIR: e->d_name = <%s>\n", e->d_name);
			// printpacket(shp, HP);
			if ((x = send(sfd_client, data, size_packet, 0)) != size_packet)
				throwErrorAndExit("send()", x);

			shp->type = kRequest;
			shp->command_type = LCD;
			strcpy(shp->buffer, e->d_name);
			data = htonp(shp);
			// fprintf(stderr, "LCD: e->d_name = <%s>\n", e->d_name);
			// printpacket(shp, HP);
			if ((x = send(sfd_client, data, size_packet, 0)) != size_packet)
				throwErrorAndExit("send()", x);
			if ((x = chdir(e->d_name)) == -1)
				throwErrorAndExit("chdir()", x);

			command_rget(shp, data, sfd_client);

			shp->type = kRequest;
			shp->command_type = LCD;
			strcpy(shp->buffer, "..");
			data = htonp(shp);
			// fprintf(stderr, "LCD: <..>\n");
			// printpacket(shp, HP);
			if ((x = send(sfd_client, data, size_packet, 0)) != size_packet)
				throwErrorAndExit("send()", x);
			if ((x = chdir("..")) == -1)
				throwErrorAndExit("chdir()", x);
		}
		else if (e->d_type == 8)
		{
			shp->type = kRequest;
			shp->command_type = GET;
			strcpy(shp->buffer, e->d_name);
			data = htonp(shp);
			// fprintf(stderr, "GET: e->d_name = <%s>\n", e->d_name);
			// printpacket(shp, HP);
			if ((x = send(sfd_client, data, size_packet, 0)) != size_packet)
				throwErrorAndExit("send()", x);
			if ((x = recv(sfd_client, data, size_packet, 0)) == 0)
				throwErrorAndExit("recv()", x);
			shp = ntohp(data);
			if (shp->type == kRequest && shp->command_type == GET)
				command_get(shp, data, sfd_client);
		}
	closedir(d);
}
