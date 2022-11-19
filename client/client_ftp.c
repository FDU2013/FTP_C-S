#include <client_command.h>

int main(int argc, char *argv[])
{
	// BEGIN: initialization
	struct sockaddr_in sin_server;
	int sfd_client, x;
	size_t size_sockaddr = sizeof(struct sockaddr),
		   size_packet = sizeof(struct Packet);
	short int connection_id;

	if ((x = sfd_client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		throwErrorAndExit("socket()", x);

	memset((char *)&sin_server, 0, sizeof(struct sockaddr_in));
	sin_server.sin_family = AF_INET;
	sin_server.sin_addr.s_addr = inet_addr(IPSERVER);
	sin_server.sin_port = htons(SERVER_PORT);

	if ((x = connect(sfd_client, (struct sockaddr *)&sin_server, size_sockaddr)) <
		0)
		throwErrorAndExit("connect()", x);

	printf(ID
		   "FTP Client started up. Attempting communication with server @ "
		   "%s:%d...\n\n",
		   IPSERVER, SERVER_PORT);
	// END: initialization

	struct command *cmd;
	char lpwd[BUF_SIZE], pwd[BUF_SIZE];
	char userinput[LENUSERINPUT];
	bool exit_flag = false;
	while (!exit_flag)
	{
		printf("(ftp_client)> ");
		fgets(userinput, LENUSERINPUT, stdin); // in order to give \
					a filename with spaces, put ':' \
					instead of ' '. If a command needs \
					x paths, and y (y > x) paths are \
					provided, y - x paths will be \
					ignored.
		cmd = userinputtocommand(userinput);
		if (!cmd)
			continue;
		// printcommand(cmd);
		switch (cmd->type)
		{
		case kGet:
			if (cmd->npaths)
				GetCommand(sfd_client, *cmd->paths);
			else
				fprintf(stderr, "No path to file given.\n");
			break;
		case kPut:
			if (cmd->npaths)
				PutCommand(sfd_client, *cmd->paths);
			else
				fprintf(stderr, "No path to file given.\n");
			break;
		case kCd:
			if (cmd->npaths)
				CdCommand(sfd_client, *cmd->paths);
			else
				fprintf(stderr, "No path given.\n");
			break;
		case kLcd:
			if (cmd->npaths)
				CdLocalCommand(*cmd->paths);
			else
				fprintf(stderr, "No path given.\n");
			break;
		case kDelete:
			if (cmd->npaths)
				DeleteCommand(sfd_client, *cmd->paths);
			else
				fprintf(stderr, "No path to file given.\n");
			break;
		case kLdelete:
			if (cmd->npaths)
				DeleteLocalCommand(*cmd->paths);
			else
				fprintf(stderr, "No path to file given.\n");
			break;
		case kPwd:
			PwdCommand(sfd_client);
			break;
		case kLpwd:
			if (!getcwd(lpwd, sizeof lpwd))
				throwErrorAndExit("getcwd()", 0);
			printf("%s\n", lpwd);
			break;
		case kLs:
			LsCommand(sfd_client);
			break;
		case kLls:
			if (!getcwd(lpwd, sizeof lpwd))
				throwErrorAndExit("getcwd()", 0);
			LsLocalCommand(lpwd);
			break;
		case kMkdir:
			if (cmd->npaths)
				MkdirLocalCommand(sfd_client, *cmd->paths);
			else
				fprintf(stderr, "No path to directory given.\n");
			break;
		case kLmkdir:
			if (cmd->npaths)
				LmkdirCommand(*cmd->paths);
			else
				fprintf(stderr, "No path to directory given.\n");
			break;
		case kExit:
			exit_flag = true;
			break;
		default:
			// display error
			break;
			free(cmd);
		}
	}

	close(sfd_client);
	printf(ID "Done.\n");
	fflush(stdout);

	return 0;
}
