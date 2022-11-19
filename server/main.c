#include <server.h>

static size_t sockaddr_size = sizeof(struct sockaddr);
int main(void) {
  // BEGIN: initialization
  struct sockaddr_in server_sock, client_sock;
  int sockerfd_server, socketfd_client;
  InitSever(&server_sock, &sockerfd_server);
  // END: initialization
  short connection_id = 0;
  while (1) {
    ConnectClient(&client_sock, &sockerfd_server, &socketfd_client);
    struct ClientInfo client_info;
    client_info.socket_fd = socketfd_client;
    client_info.connection_id = ++connection_id;
    ServerWork(&client_info);
  }
  close(sockerfd_server);
  printf(TERMINAL_HEAD "Done.\n");
  fflush(stdout);

  return 0;
}