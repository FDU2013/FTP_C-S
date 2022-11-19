#include <common.h>

void InitPacket(struct Packet* p) { memset(p, 0, sizeof(struct Packet)); }

void ntoh_packet(struct Packet* netPacket) {
  netPacket->connection_id = ntohs(netPacket->connection_id);
  netPacket->type = ntohs(netPacket->type);
  netPacket->command_type = ntohs(netPacket->command_type);
  netPacket->data_size = ntohs(netPacket->data_size);
}

void hton_packet(struct Packet* hostPacket) {
  hostPacket->connection_id = htons(hostPacket->connection_id);
  hostPacket->type = htons(hostPacket->type);
  hostPacket->command_type = htons(hostPacket->command_type);
  hostPacket->data_size = htons(hostPacket->data_size);
}

bool IsAsciiFile(char* filename) {
  int len = strlen(filename);
  if (len > 4 && strcmp(".txt", filename + len - 4) == 0) {
    // printf("(info).txt file, transfer by ascii mode\n");
    return true;
  }
  // printf("(info)normal file, transfer by binary mode \n");
  return false;
}

FILE* ReadFileAuto(char* filename) {
  if (IsAsciiFile(filename)) {
    return fopen(filename, "r");
  } else {
    return fopen(filename, "rb");
  }
}
FILE* WriteFileAuto(char* filename) {
  if (IsAsciiFile(filename)) {
    return fopen(filename, "w");
  } else {
    return fopen(filename, "wb");
  }
}
