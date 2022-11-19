#include <common.h>
#include <file_transfer_functions.h>
#include <time.h>
/*
        for:
                ctime()
*/

#include <sys/stat.h>
/*
        for:
                stat()
*/

#define ID "SERVER=> "

struct client_info
{
  int sfd;
  int cid;
};

#define TERMINAL_HEAD "SERVER=> "

struct ServerInfo
{
  int socket_fd;
  int connection_id;
};

struct client_info *client_info_alloc(int, int);

void command_pwd(struct Packet *, int, char *);
void command_cd(struct Packet *, int, char *);
void command_ls(struct Packet *, int, char *);
void command_get(struct Packet *, int);
void command_put(struct Packet *, int);
void command_mkdir(struct Packet *, int);
