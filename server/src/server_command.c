#include <server_command.h>

static size_t size_packet = sizeof(struct Packet);

struct client_info *client_info_alloc(int s, int c)
{
	struct client_info *ci = (struct client_info *)malloc(sizeof(struct client_info));
	ci->sfd = s;
	ci->cid = c;
	return ci;
}

void command_pwd(struct Packet *packet, int sfd_client, char *lpwd)
{
	packet->type = kData;
	strcpy(packet->buf, lpwd);
	sendPacket(packet, sfd_client);
}

void command_cd(struct Packet *packet, int sfd_client, char *message)
{
	packet->type = kResponse;
	strcpy(packet->buf, message);
	sendPacket(packet, sfd_client);
}

void command_ls(struct Packet *packet, int sfd_client, char *lpwd)
{
	packet->type = kData;
	DIR *d = opendir(lpwd);
	if (!d)
		throwErrorAndExit("opendir()", (int)d);
	struct dirent *e;
	while (e = readdir(d))
	{
		sprintf(packet->buf, "%s\t%s", e->d_type == 4 ? "DIR:" : e->d_type == 8 ? "FILE:"
																				: "UNDEF:",
				e->d_name);
		sendPacket(packet, sfd_client);
	}
	sendEndPacket(sfd_client);
}

void command_get(struct Packet *packet, int sfd_client)
{
	FILE *f = ReadFileAuto(packet->buf); // Yo!
	packet->type = kResponse;
	packet->command_type = GET;
	strcpy(packet->buf, f ? "File found; processing" : "Error opening file.");
	// printpacket(packet, HP);
	sendPacket(packet, sfd_client);
	if (f)
	{
		packet->type = kData;
		sendFile(sfd_client, f);
		fclose(f);
	}
	sendEndPacket(sfd_client);
}

void command_put(struct Packet *packet, int sfd_client)
{
	FILE *f = WriteFileAuto(packet->buf);
	packet->type = kResponse;
	packet->command_type = PUT;
	strcpy(packet->buf, f ? "Everything in order; processing" : "Error opening file for writing on server side.");
	// printpacket(packet, HP);
	sendPacket(packet, sfd_client);
	if (f)
	{
		receiveFile(sfd_client, f);
		fclose(f);
	}
}

void command_mkdir(struct Packet *packet, int sfd_client)
{
	char message[LENBUFFER];
	DIR *d = opendir(packet->buf);
	if (d)
	{
		strcpy(message, "already exists");
		closedir(d);
	}
	else if (mkdir(packet->buf, 0777) == -1)
	{
		fprintf(stderr, "Wrong path.\n");
		strcpy(message, "fail");
	}
	else
		strcpy(message, "success");

	packet->type = kResponse;
	strcpy(packet->buf, message);
	sendPacket(packet, sfd_client);
}
