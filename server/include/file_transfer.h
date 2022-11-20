#include <common.h>
#include <sys/stat.h>

void SendPacket(struct Packet *packet, int socket_fd);
void RecvPacket(struct Packet *packet, int socket_fd);

void SendEndPacket(int socket_fd);
void snedErrorPacket(int socket_fd);

void SendFile(int, FILE *);
void ReceiveFile(int, FILE *);
