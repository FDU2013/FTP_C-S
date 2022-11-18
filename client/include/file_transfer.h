#include <common.h>

#define extract_filename(filepath) ((strrchr(filepath, '/') != NULL) ? (strrchr(filepath, '/') + 1) : filepath)

void sendPacket(struct Packet* packet, int sfd);
void recvPacket(struct Packet* packet, int sfd);

void send_EOT(int sfd);
void send_TERM(int sfd);

void sendFile(int, FILE*);
void receiveFile(int, FILE*);

