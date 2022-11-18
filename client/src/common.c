#include <common.h>

static size_t size_packet = sizeof(struct Packet);

void InitPacket(struct Packet* p) { memset(p, 0, sizeof(struct Packet)); }

void ntoh_packet(struct Packet* netPacket){
  netPacket->connection_id = ntohs(netPacket->connection_id);
  netPacket->type = ntohs(netPacket->type);
  netPacket->command_type = ntohs(netPacket->command_type);
  netPacket->data_size = ntohs(netPacket->data_size);
}

void hton_packet(struct Packet* hostPacket){
  
  hostPacket->connection_id = ntohs(hostPacket->connection_id);
  hostPacket->type = ntohs(hostPacket->type);
  hostPacket->comid = ntohs(hostPacket->comid);
  hostPacket->data_size = ntohs(hostPacket->data_size);

}

// struct Packet* new_ntoh_packet(struct Packet* netPacket) {
//   struct Packet* hostPacket = (struct Packet*)malloc(size_packet);
//   memset(hostPacket, 0, size_packet);

//   hostPacket->connection_id = ntohs(netPacket->connection_id);
//   hostPacket->type = ntohs(netPacket->type);
//   hostPacket->command_type = ntohs(netPacket->command_type);
//   hostPacket->data_size = ntohs(netPacket->data_size);
//   memcpy(hostPacket->buffer, netPacket->buffer, BUF_SIZE);

//   return hostPacket;
// }

// struct Packet* new_hton_packet(struct Packet* hostPacket) {
//   struct Packet* netPacket = (struct Packet*)malloc(size_packet);
//   memset(netPacket, 0, size_packet);

//   netPacket->connection_id = ntohs(hostPacket->connection_id);
//   netPacket->type = ntohs(hostPacket->type);
//   netPacket->comid = ntohs(hostPacket->comid);
//   netPacket->data_size = ntohs(hostPacket->data_size);
//   memcpy(netPacket->buffer, hostPacket->buffer, LENBUFFER);

//   return netPacket;
// }

// void printpacket(struct Packet* p, int ptype) {
//   if (!DEBUG) return;

//   if (ptype)
//     printf("HOST PACKET\n");
//   else
//     printf("NETWORK PACKET\n");

//   printf("conid = %d\n", p->conid);
//   printf("type = %d\n", p->type);
//   printf("comid = %d\n", p->comid);
//   printf("datalen = %d\n", p->datalen);
//   printf("buffer = %s\n", p->buffer);

//   fflush(stdout);
// }

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
