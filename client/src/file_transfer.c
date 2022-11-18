#include <file_transfer.h>

static size_t size_packet = sizeof(struct Packet);

void sendPacket(struct Packet* packet, int sfd){
  int expect;
  htonp(packet);
  if ((expect = send(sfd, packet, size_packet, 0)) != size_packet)
    throwErrorAndExit("sendPacket()", expect);
  ntoh_packet(packet);

}

void recvPacket(struct Packet* packet, int sfd){
  int expect;
  if ((expect = recv(sfd, packet, size_packet, 0)) <= 0)
    throwErrorAndExit("recvPacket()", except);
  ntoh_packet(packet);
}

void send_EOT(int sfd) {
  struct Packet* packet = malloc(size_packet);
  packet->type = EOT;
  sendPacket(packet,sfd);
  free(packet);
}

void send_TERM(int sfd) {
  struct Packet* packet = malloc(size_packet);
  hostPacket->type = TERM;
  sendPacket(packet,sfd);
  free(packet);
}

void sendFile(int sfd, FILE* f) {
  struct Packet* packet = malloc(size_packet);
  int cntBytes = 0, cntPacket = 0;
  //while循环里面每次send一个packet
  while (!feof(f)) {
    memset(packet->buffer, 0, sizeof(char) * BUF_SIZE);
    packet->data_size = fread(hostPacket->buffer, 1, BUF_SIZE - 1, f);
    cntBytes += packet->data_size;
    cntPacket++;
    sendPacket(packet,sfd);
    //记得转换回去给while循环的下一个阶段用
  }
  fprintf(stderr, "%d byte(s) read.\n", cntBytes);
  fprintf(stderr, "%d data packet(s) sent.\n", cntPacket);
  fflush(stderr);
  free(packet);
}

void receiveFile(int sfd, FILE* f) {
  struct Packet* packet = malloc(size_packet);
  int cntBytes = 0, cntPacket = 0;
  recvPacket(packet,sfd);
  // printpacket(hostPacket, HP);
  while (hostPacket->type == DATA) {
    cntBytes += fwrite(hostPacket->buffer, 1, hostPacket->data_size, f);
    cntPacket++;
    recvPacket(packet,sfd);
    // printpacket(hostPacket, HP);
  }
  fprintf(stderr, "%d data packet(s) received.\n",cntPacket);  // j decremented because the last packet is EOT.
  fprintf(stderr, "%d byte(s) written.\n", i);
  if (packet->type == EOT)
    return;
  else {
    fprintf(stderr, "Error occured while downloading remote file.\n");
    exit(2);
  }
  fflush(stderr);
  free(packet);
}
