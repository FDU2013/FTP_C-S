#include <common.h>
#include <file_transfer.h>
#include <sys/stat.h>

#define SERVER_IP "127.0.0.1"
#define TERMINAL_HEAD "Client=> "

#define INPUT_LENTH_MAX 512

struct Command {
  CommandType type;
  int para_num;
  char** parameters;
};

struct Command* InputCommand(char[INPUT_LENTH_MAX]);

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
