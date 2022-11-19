#ifndef SERVER_INCLUDE_COMMANDS_H_
#define SERVER_INCLUDE_COMMANDS_H_

#include <common.h>

void PwdCommand(struct Packet *, int, char *);
void CdCommand(struct Packet *, int, char *);
void LsCommand(struct Packet *, int, char *);
void GetCommand(struct Packet *, int);
void PutCommand(struct Packet *, int);
void MkdirCommand(struct Packet *, int);
void DeleteCommand(struct Packet *, int);

#endif