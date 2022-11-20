#ifndef CLIENT_INCLUDE_SERVER_H_
#define CLIENT_INCLUDE_SERVER_H_

#include <commands.h>

#define SERVER_IP "127.0.0.1"
#define TERMINAL_HEAD "Client=> "

void ConnectToServer(struct sockaddr_in* server_socket, int* socketfd_client);
void ClientWork(int socketfd_client);

#endif