#ifndef COMMONS_H
#define COMMONS_H

#include <arpa/inet.h>
#include <stdbool.h>
/*
        for:
                htons()
                htonl()
                ntohs()
                inet_aton()
                inet_ntoa()
*/

#include <netinet/in.h>
/*
        for:
                inet_aton()
                inet_ntoa()
*/

#include <sys/types.h>
/*
        for:
                socket()
                bind()
                recvfrom()
                sendto()
                stat()
*/

#include <sys/socket.h>
/*
        for:
                socket()
                bind()
                recvfrom()
                sendto()
                inet_aton()
                inet_ntoa()
                AF_INET
                SOCK_DGRAM
*/

#include <errno.h>
/*
        for:
                return type of system calls
*/

#include <stdio.h>
/*
        for:
                printf()
                sprintf()
                fflush()
                perror()
*/

#include <stdlib.h>
/*
        for:
                exit()
                malloc()
*/

#include <string.h>
/*
        for:
                memset()
                strlen()
                strcpy()
*/

#include <unistd.h>
/*
        for:
                close()
                sleep()
                stat()
*/

#include <dirent.h>

#define DEBUG 1

// #define PORTSERVER 8487
#define SERVER_PORT 21
// #define CONTROLPORT PORTSERVER
// #define DATAPORT (PORTSERVER + 1)

// enum TYPE { REQU, DONE, INFO, TERM, DATA, EOT };
typedef short PacketType;
enum { kRequest, kResponse, kData, kEnd, kError };

#define throwErrorAndExit(e, x)   \
  do {                            \
    perror("ERROR IN: " #e "\n"); \
    fprintf(stderr, "%d\n", x);   \
    exit(-1);                     \
  } while (0)

// #define LENBUFFER \
//   504  // so as to make the whole packet well-rounded ( = 512 bytes)
// struct Packet {
//   short int conid;
//   short int type;
//   short int comid;
//   short int datalen;
//   char buffer[LENBUFFER];
// };

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

void InitPacket(struct Packet*);

struct Packet* ntoh_packet(struct Packet*);
struct Packet* hton_packet(struct Packet*);

// void printpacket(struct Packet*, int);
FILE* ReadFileAuto(char* filename);
FILE* WriteFileAuto(char* filename);

#define COMMAND_NUM 13
typedef short CommandType;
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

#endif
