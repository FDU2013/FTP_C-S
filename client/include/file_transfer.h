#include <common.h>

#define extract_filename(filepath) \
  ((strrchr(filepath, '/') != NULL) ? (strrchr(filepath, '/') + 1) : filepath)

void SendPacket(struct Packet *packet, int sfd);
void RecvPacket(struct Packet *packet, int sfd);

void SendEndPacket(int sfd);
void sendErrorPacket(int sfd);

void SendFile(int, FILE *);
void ReceiveFile(int, FILE *);
