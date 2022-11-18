#include <common.h>
#include <file_transfer.h>

#define IPSERVER "127.0.0.1"
#define ID "CLIENT=> "

#define LENUSERINPUT 1024

struct command {
  short int id;
  int npaths;
  char** paths;
};

struct command* userinputtocommand(char[LENUSERINPUT]);

void printcommand(struct command*);

void command_pwd(struct Packet*, struct Packet*, int);
void command_lcd(char*);
void command_cd(struct Packet*, struct Packet*, int, char*);
void command_lls(char*);
void command_ls(struct Packet*, struct Packet*, int);
void command_get(struct Packet*, struct Packet*, int, char*);
void command_put(struct Packet*, struct Packet*, int, char*);
void command_mget(struct Packet*, struct Packet*, int, int, char**);
void command_mput(struct Packet*, struct Packet*, int, int, char**);
void command_mgetwild(struct Packet*, struct Packet*, int);
void command_mputwild(struct Packet*, struct Packet*, int, char*);
void command_lmkdir(char*);
void command_mkdir(struct Packet*, struct Packet*, int, char*);
void command_rget(struct Packet*, struct Packet*, int);
void command_rput(struct Packet*, struct Packet*, int);
void command_delete(struct Packet*, struct Packet*, int, char*);
void command_ldelete(char*);
