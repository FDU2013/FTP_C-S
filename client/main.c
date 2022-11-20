#include <client.h>

int main(int argc, char *argv[]) {
  struct sockaddr_in server_socket;
  int socketfd_client;
  ConnectToServer(&server_socket, &socketfd_client);
  ClientWork(socketfd_client);
  close(socketfd_client);
  fflush(stdout);
  return 0;
}
