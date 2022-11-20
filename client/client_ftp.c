#include <client_command.h>

int main(int argc, char *argv[]) {
  // BEGIN: initialization
  struct sockaddr_in server_socket;
  int socket_file_description_client, x;
  size_t size_sockaddr = sizeof(struct sockaddr),
         size_packet = sizeof(struct Packet);
  short int connection_id;

  if ((x = socket_file_description_client =
           socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    throwErrorAndExit("socket()", x);

  memset((char *)&server_socket, 0, sizeof(struct sockaddr_in));
  server_socket.sin_family = AF_INET;
  server_socket.sin_addr.s_addr = inet_addr(SERVER_IP);
  server_socket.sin_port = htons(SERVER_PORT);

  if ((x = connect(socket_file_description_client,
                   (struct sockaddr *)&server_socket, size_sockaddr)) < 0)
    throwErrorAndExit("connect()", x);

  printf(
      "Client=> FTP Client startup. Try to connect to server "
      "%s:(server_port)%d\n\n",
      SERVER_IP, SERVER_PORT);
  // END: initialization

  char input[INPUT_LENTH_MAX];
  char local_pwd[BUF_SIZE], pwd[BUF_SIZE];
  bool exit_flag = false;
  while (!exit_flag) {
    printf("Client> ");
    fgets(input, INPUT_LENTH_MAX, stdin);
    struct Command *cmd = InputCommand(input);
    if (!cmd) continue;
    switch (cmd->type) {
      case kGet:
        if (cmd->para_num)
          GetCommand(socket_file_description_client, *cmd->parameters);
        else
          fprintf(stderr, "No filename entered.\n");
        break;
      case kPut:
        if (cmd->para_num)
          PutCommand(socket_file_description_client, *cmd->parameters);
        else
          fprintf(stderr, "No filename entered.\n");
        break;
      case kCd:
        if (cmd->para_num)
          CdCommand(socket_file_description_client, *cmd->parameters);
        else
          fprintf(stderr, "No path entered.\n");
        break;
      case kLcd:
        if (cmd->para_num)
          CdLocalCommand(*cmd->parameters);
        else
          fprintf(stderr, "No path entered.\n");
        break;
      case kDelete:
        if (cmd->para_num)
          DeleteCommand(socket_file_description_client, *cmd->parameters);
        else
          fprintf(stderr, "No filename entered.\n");
        break;
      case kLdelete:
        if (cmd->para_num)
          DeleteLocalCommand(*cmd->parameters);
        else
          fprintf(stderr, "No filename entered.\n");
        break;
      case kPwd:
        PwdCommand(socket_file_description_client);
        break;
      case kLpwd:
        if (!getcwd(local_pwd, sizeof local_pwd)) {
          throwErrorAndExit("getcwd()", 0);
        }
        printf("%s\n", local_pwd);
        break;
      case kLs:
        LsCommand(socket_file_description_client);
        break;
      case kLls:
        if (!getcwd(local_pwd, sizeof local_pwd)) {
          throwErrorAndExit("getcwd()", 0);
        }
        LsLocalCommand(local_pwd);
        break;
      case kMkdir:
        if (cmd->para_num)
          MkdirLocalCommand(socket_file_description_client, *cmd->parameters);
        else
          fprintf(stderr, "No directory-name entered.\n");
        break;
      case kLmkdir:
        if (cmd->para_num)
          LmkdirCommand(*cmd->parameters);
        else
          fprintf(stderr, "No directory-name entered.\n");
        break;
      case kExit:
        exit_flag = true;
        break;
      default:
        break;
    }
    free(cmd);
  }
  close(socket_file_description_client);
  fflush(stdout);
  return 0;
}
