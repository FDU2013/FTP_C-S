#include <common.h>

static size_t size_packet = sizeof(struct Packet);

void init_packet(struct Packet* p) { memset(p, 0, sizeof(struct Packet)); }

struct Packet* ntohp(struct Packet* np) {
  struct Packet* hp = (struct Packet*)malloc(size_packet);
  memset(hp, 0, size_packet);

  hp->connection_id = ntohs(np->connection_id);
  hp->type = ntohs(np->type);
  hp->command_type = ntohs(np->command_type);
  hp->datalen = ntohs(np->datalen);
  memcpy(hp->buffer, np->buffer, LENBUFFER);

  return hp;
}

struct Packet* htonp(struct Packet* hp) {
  struct Packet* np = (struct Packet*)malloc(size_packet);
  memset(np, 0, size_packet);

  np->connection_id = ntohs(hp->connection_id);
  np->type = ntohs(hp->type);
  np->command_type = ntohs(hp->command_type);
  np->datalen = ntohs(hp->datalen);
  memcpy(np->buffer, hp->buffer, LENBUFFER);

  return np;
}

void printpacket(struct Packet* p, int ptype) {
  if (!DEBUG) return;

  if (ptype)
    printf("HOST PACKET\n");
  else
    printf("NETWORK PACKET\n");

  printf("connection_id = %d\n", p->connection_id);
  printf("type = %d\n", p->type);
  printf("command_type = %d\n", p->command_type);
  printf("datalen = %d\n", p->datalen);
  printf("buffer = %s\n", p->buffer);

  fflush(stdout);
}

bool IsAsciiFile(char* filename) {
  int len = strlen(filename);
  if (len > 4 && strcmp(".txt", filename + len - 4)) {
    printf("(debug).txt file\n");
    return true;
  }
  printf("(debug)normal file\n");
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
