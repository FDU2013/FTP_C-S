#ifndef COMMON_H
#define COMMON_H

#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define DEBUG 1
#define SERVER_PORT 8888

#define throwErrorAndExit(error, message) \
  (perror("Error in: " #error "\n"), fprintf(stderr, "%d\n", message), exit(-1))
// #define throwErrorAndExit(e, x)   \
//   do {                            \
//     perror("Error in: " #e "\n"); \
//     fprintf(stderr, "%d\n", x);   \
//     exit(-1);                     \
//   } while (0)

typedef short PacketType;
enum { kRequest, kResponse, kData, kEnd, kError };

typedef short CommandType;
#define COMMAND_NUM 13
enum {
  kGet,
  kPut,
  kCd,
  kLcd,
  kDelete,
  kLdelete,
  kLs,
  kLls,
  kMkdir,
  kLmkdir,
  kPwd,
  kLpwd,
  kExit
};

#define PACKET_SIZE 512
#define BUF_SIZE                                              \
  (PACKET_SIZE - sizeof(short int) * 2 - sizeof(PacketType) - \
   sizeof(CommandType))

struct Packet {
  short connection_id;
  PacketType type;
  CommandType command_type;
  short data_size;
  char buf[BUF_SIZE];
};

void InitPacket(struct Packet *);
void ntoh_packet(struct Packet *);
void hton_packet(struct Packet *);

FILE *ReadFileAuto(char *filename);
FILE *WriteFileAuto(char *filename);

void PrintPacket(struct Packet *);

#endif
