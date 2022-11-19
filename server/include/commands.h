#ifndef SERVER_INCLUDE_COMMANDS_H_
#define SERVER_INCLUDE_COMMANDS_H_

#include <common.h>

void command_pwd(struct Packet *, int, char *);
void command_cd(struct Packet *, int, char *);
void command_ls(struct Packet *, int, char *);
void command_get(struct Packet *, int);
void command_put(struct Packet *, int);
void command_mkdir(struct Packet *, int);

#endif