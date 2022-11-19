#include <server.h>

int main(void) {
  struct sockaddr_in server_sock, client_sock;
  int sockerfd_server, socketfd_client;
  InitSever(&server_sock, &sockerfd_server);
  short connection_id = 0;
  while (1) {
    ConnectClient(&client_sock, &sockerfd_server, &socketfd_client);
    struct ClientInfo client_info;
    client_info.socket_fd = socketfd_client;
    client_info.connection_id = ++connection_id;
    ServerWork(&client_info);
  }
  close(sockerfd_server);
  printf(TERMINAL_HEAD "Exit.\n");
  fflush(stdout);

  return 0;
}