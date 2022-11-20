#ifndef COMMON_FILE_TRANSFER_H_  
#define COMMON_FILE_TRANSFER_H_

#include <common.h>
#include <sys/stat.h>

void SendPacket(struct Packet *packet, int socket_fd);
void RecvPacket(struct Packet *packet, int socket_fd);

void SendEndPacket(int socket_fd);
void sendErrorPacket(int socket_fd);

void SendFile(int, FILE *);
void ReceiveFile(int, FILE *);

#endif