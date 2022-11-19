#include <common.h>
#include <file_transfer.h>

#define IPSERVER "127.0.0.1"
#define ID "CLIENT=> "

#define LENUSERINPUT 1024

struct command {
  CommandType type;
  int npaths;
  char** paths;
};

struct command* userinputtocommand(char[LENUSERINPUT]);

void printcommand(struct command*);

void PwdCommand(int);
void CdLocalCommand(char*);
void CdCommand(int, char*);
void LsLocalCommand(char*);
void LsCommand(int);
void GetCommand(int, char*);
void PutCommand(int, char*);
void LmkdirCommand(char*);
void MkdirLocalCommand(int, char*);
void DeleteCommand(int, char*);
void DeleteLocalCommand(char*);
