#include <client_command.h>

int main(int argc, char *argv[])
{
	// BEGIN: initialization
	struct sockaddr_in server_socket;
	int socket_file_description_client, x;
	size_t size_sockaddr = sizeof(struct sockaddr),
		   size_packet = sizeof(struct Packet);
	short int connection_id;

	if ((x = socket_file_description_client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		throwErrorAndExit("socket()", x);

	memset((char *)&server_socket, 0, sizeof(struct sockaddr_in));
	server_socket.sin_family = AF_INET;
	server_socket.sin_addr.s_addr = inet_addr(IPSERVER);
	server_socket.sin_port = htons(SERVER_PORT);

	if ((x = connect(socket_file_description_client, (struct sockaddr *)&server_socket, size_sockaddr)) < 0)
		throwErrorAndExit("connect()", x);

	printf(ID
		   "FTP Client started up. Attempting communication with server @ "
		   "%s:%d...\n\n",
		   IPSERVER, SERVER_PORT);
	// END: initialization

	struct command *cmd;
	char local_pwd[BUF_SIZE], pwd[BUF_SIZE];
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
		cmd = inputCommand(userinput);
		if (!cmd)
			continue;
		switch (cmd->type)
		{
		case kGet:
			if (cmd->npaths)
				GetCommand(socket_file_description_client, *cmd->paths);
			else
				fprintf(stderr, "Please enter a path.\n");
			break;
		case kPut:
			if (cmd->npaths)
				PutCommand(socket_file_description_client, *cmd->paths);
			else
				fprintf(stderr, "Please enter a path.\n");
			break;
		case kCd:
			if (cmd->npaths)
				CdCommand(socket_file_description_client, *cmd->paths);
			else
				fprintf(stderr, "Please enter a path.\n");
			break;
		case kLcd:
			if (cmd->npaths)
				CdLocalCommand(*cmd->paths);
			else
				fprintf(stderr, "Please enter a path.\n");
			break;
		case kDelete:
			if (cmd->npaths)
				DeleteCommand(socket_file_description_client, *cmd->paths);
			else
				fprintf(stderr, "Please enter a path.\n");
			break;
		case kLdelete:
			if (cmd->npaths)
				DeleteLocalCommand(*cmd->paths);
			else
				fprintf(stderr, "Please enter a path.\n");
			break;
		case kPwd:
			PwdCommand(socket_file_description_client);
			break;
		case kLpwd:
			if (!getcwd(local_pwd, sizeof local_pwd))
				throwErrorAndExit("getcwd()", 0);
			printf("%s\n", local_pwd);
			break;
		case kLs:
			LsCommand(socket_file_description_client);
			break;
		case kLls:
			if (!getcwd(local_pwd, sizeof local_pwd))
				throwErrorAndExit("getcwd()", 0);
			LsLocalCommand(local_pwd);
			break;
		case kMkdir:
			if (cmd->npaths)
				MkdirLocalCommand(socket_file_description_client, *cmd->paths);
			else
				fprintf(stderr, "Please enter a path.\n");
			break;
		case kLmkdir:
			if (cmd->npaths)
				LmkdirCommand(*cmd->paths);
			else
				fprintf(stderr, "Please enter a path.\n");
			break;
		case kExit:
			exit_flag = true;
			break;
		default:
			break;
			free(cmd);
		}
	}

	close(socket_file_description_client);
	printf(ID "has done.\n");
	fflush(stdout);

	return 0;
}
