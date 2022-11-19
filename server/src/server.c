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
  struct Packet *shp = (struct Packet *)malloc(PACKET_SIZE);
  InitPacket(shp);
  char lpwd[BUF_SIZE];
  socketfd_client = client_info->socket_fd;
  connection_id = client_info->connection_id;

  int flag;
  while (1) {
    if ((flag = recv(socketfd_client, shp, PACKET_SIZE, 0)) == 0) {
      fprintf(stderr, "client closed/terminated. closing connection.\n");
      break;
    }

    ntoh_packet(shp);

    if (shp->type == kError) break;

    if (shp->connection_id == -1) shp->connection_id = connection_id;

    if (shp->type == kRequest) {
      switch (shp->command_type) {
        case kPwd:
          if (!getcwd(lpwd, sizeof lpwd)) throwErrorAndExit("getcwd()", 0);
          PwdCommand(shp, socketfd_client, lpwd);
          break;
        case kCd:
          if ((flag = chdir(shp->buf)) == -1) fprintf(stderr, "Wrong path.\n");
          CdCommand(shp, socketfd_client, flag == -1 ? "fail" : "success");
          break;
        case kMkdir:
          MkdirCommand(shp, socketfd_client);
          break;
        case kLs:
          if (!getcwd(lpwd, sizeof lpwd)) throwErrorAndExit("getcwd()", 0);
          LsCommand(shp, socketfd_client, lpwd);
          break;
        case kGet:
          GetCommand(shp, socketfd_client);
          break;
        case kPut:
          PutCommand(shp, socketfd_client);
          break;
        case kDelete:
          PutCommand(shp, socketfd_client);
          break;
        default:
          // print error
          break;
      }
    } else {
      // show error, send TERM and break
      fprintf(stderr, "packet incomprihensible. closing connection.\n");
      snedErrorPacket(socketfd_client);
      break;
    }
  }
  close(socketfd_client);
  fflush(stdout);
}