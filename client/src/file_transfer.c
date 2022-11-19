#include <file_transfer.h>

static size_t size_packet = sizeof(struct Packet);

void SendPacket(struct Packet *packet, int socket_fd) {
  int expect;
  hton_packet(packet);
  if ((expect = send(socket_fd, packet, size_packet, 0)) != size_packet)
    throwErrorAndExit("SendPacket()", expect);
  ntoh_packet(packet);
}

void RecvPacket(struct Packet *packet, int socket_fd) {
  int expect;
  if ((expect = recv(socket_fd, packet, size_packet, 0)) <= 0)
    throwErrorAndExit("RecvPacket()", expect);
  ntoh_packet(packet);
}

void SendEndPacket(int socket_fd) {
  struct Packet *packet = malloc(size_packet);
  packet->type = kEnd;
  SendPacket(packet, socket_fd);
  free(packet);
}

void sendErrorPacket(int socket_fd) {
  struct Packet *packet = malloc(size_packet);
  packet->type = kError;
  SendPacket(packet, socket_fd);
  free(packet);
}

void SendFile(int socket_fd, FILE *file) {
  struct Packet *packet = malloc(size_packet);
  int cntBytes = 0, cntPacket = 0;
  packet->type = kData;
  // while循环里面每次send一个packet
  while (!feof(file)) {
    memset(packet->buf, 0, sizeof(char) * BUF_SIZE);
    packet->data_size = fread(packet->buf, 1, BUF_SIZE - 1, file);
    cntBytes += packet->data_size;
    cntPacket++;
    SendPacket(packet, socket_fd);
    //记得转换回去给while循环的下一个阶段用
  }
  fprintf(stderr, "%d byte(s) read.\n", cntBytes);
  fprintf(stderr, "%d data packet(s) sent.\n", cntPacket);
  fflush(stderr);
  free(packet);
}

void ReceiveFile(int socket_fd, FILE *file) {
  struct Packet *packet = malloc(size_packet);
  int cntBytes = 0, cntPacket = 0;
  RecvPacket(packet, socket_fd);
  // printpacket(hostPacket, HP);
  while (packet->type == kData) {
    cntBytes += fwrite(packet->buf, 1, packet->data_size, file);
    cntPacket++;
    RecvPacket(packet, socket_fd);
    // printpacket(hostPacket, HP);
  }
  fprintf(stderr, "%d data packet(s) received.\n",
          cntPacket);  // j decremented because the last packet is EOT.
  fprintf(stderr, "%d byte(s) written.\n", cntBytes);
  if (packet->type == kEnd)
    return;
  else {
    fprintf(stderr, "Error occured while downloading remote file.\n");
    exit(2);
  }
  fflush(stderr);
  free(packet);
}
