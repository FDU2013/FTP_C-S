#include <file_transfer.h>
#include <server.h>

static size_t sockaddr_size = sizeof(struct sockaddr);

void InitSever(struct sockaddr_in *server_sock, int *sockerfd_server) {
  struct sockaddr_in sin_server;
  int expect;

  if ((expect = *sockerfd_server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) <
      0)
    throwErrorAndExit("socket()", expect);

  memset((char *)server_sock, 0, sizeof(struct sockaddr_in));
  server_sock->sin_family = AF_INET;
  server_sock->sin_port = htons(SERVER_PORT);
  server_sock->sin_addr.s_addr = htonl(INADDR_ANY);

  if ((expect = bind(*sockerfd_server, (struct sockaddr *)server_sock,
                     sockaddr_size)) < 0)
    throwErrorAndExit("bind()", expect);

  if ((expect = listen(*sockerfd_server, 1)) < 0)
    throwErrorAndExit("listen()", expect);

  printf(TERMINAL_HEAD
         "FTP Server started up @ local:%d. Waiting for client(s)...\n\n",
         SERVER_PORT);
}

void ConnectClient(struct sockaddr_in *client_sock, int *sockerfd_server,
                   int *socketfd_client) {
  int expect;
  if ((expect = (*socketfd_client) = accept(
           *sockerfd_server, (struct sockaddr *)client_sock, &sockaddr_size)) <
      0)
    throwErrorAndExit("accept()", expect);
  printf(TERMINAL_HEAD "Communication started with %s:%d\n",
         inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
  fflush(stdout);
}

void ServerWork(struct ClientInfo *client_info) {
  int socketfd_client, connection_id;
  struct Packet *packet = (struct Packet *)malloc(PACKET_SIZE);
  InitPacket(packet);
  char local_pwd[BUF_SIZE];
  socketfd_client = client_info->socket_fd;
  connection_id = client_info->connection_id;

  int flag;
  while (1) {
    if ((flag = recv(socketfd_client, packet, PACKET_SIZE, 0)) == 0) {
      fprintf(stderr, "Client is closed or terminated. Closing connection.\n");
      break;
    }
    ntoh_packet(packet);
    if (packet->type == kError) break;
    packet->connection_id = connection_id;
    if (packet->type == kRequest) {
      switch (packet->command_type) {
        case kPwd:
          if (!getcwd(local_pwd, sizeof local_pwd)) {
            throwErrorAndExit("getcwd()", 0);
          }
          PwdCommand(packet, socketfd_client, local_pwd);
          break;
        case kCd:
          if ((flag = chdir(packet->buf)) == -1) {
            fprintf(stderr, "Path wrong.\n");
          }
          CdCommand(packet, socketfd_client, flag == -1 ? "fail" : "success");
          break;
        case kMkdir:
          MkdirCommand(packet, socketfd_client);
          break;
        case kLs:
          if (!getcwd(local_pwd, sizeof local_pwd)) {
            throwErrorAndExit("getcwd()", 0);
          }
          LsCommand(packet, socketfd_client, local_pwd);
          break;
        case kGet:
          GetCommand(packet, socketfd_client);
          break;
        case kPut:
          PutCommand(packet, socketfd_client);
          break;
        case kDelete:
          DeleteCommand(packet, socketfd_client);
          break;
        default:
          fprintf(stderr, "Command type wrong.\n");
          break;
      }
    } else {
      fprintf(stderr, "Recieved abnormal request. Closing connection.\n");
      snedErrorPacket(socketfd_client);
      break;
    }
  }
  close(socketfd_client);
  fflush(stdout);
}