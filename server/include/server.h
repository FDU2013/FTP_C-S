#ifndef SERVER_INCLUDE_SERVER_H_
#define SERVER_INCLUDE_SERVER_H_

#include <commands.h>
#include <sys/stat.h>
#include <time.h>

#define TERMINAL_HEAD "Server> "

struct ClientInfo {
  int socket_fd;
  int connection_id;
};

void InitSever(struct sockaddr_in *server_sock, int *sockerfd_server);
void ConnectClient(struct sockaddr_in *client_sock, int *sockerfd_server,
                   int *socketfd_client);
void ServerWork(struct ClientInfo *client_info);

#endif