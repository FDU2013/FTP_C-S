#include <client_command.h>

static size_t size_packet = sizeof(struct Packet);

static const char commandlist[COMMAND_NUM][10] = {
    "get", "put",

    "cd", "lcd",

    "delete", "ldelete",

    "ls", "lls",

    "mkdir", "lmkdir",

    "pwd", "lpwd",

    "exit"}; // any change made here should also be \
				replicated accordingly in the COMMANDS \
				enum in commons.h

static void append_path(struct command *c, char *s)
{
  c->npaths++;
  char **temppaths = (char **)malloc(c->npaths * sizeof(char *));
  if (c->npaths > 1)
    memcpy(temppaths, c->paths, (c->npaths - 1) * sizeof(char *));

  char *temps = (char *)malloc((strlen(s) + 1) * sizeof(char));
  int i;
  for (i = 0; *(temps + i) = *(s + i) == ':' ? ' ' : *(s + i); i++)
    ;

  *(temppaths + c->npaths - 1) = temps;

  c->paths = temppaths;
}

struct command *userinputtocommand(char s[LENUSERINPUT])
{
  struct command *cmd = (struct command *)malloc(sizeof(struct command));
  cmd->type = -1;
  cmd->npaths = 0;
  cmd->paths = NULL;
  char *savestate;
  char *token;
  int i, j;
  for (i = 0;; i++, s = NULL)
  {
    token = strtok_r(s, " \t\n", &savestate);
    if (token == NULL)
      break;
    if (cmd->type == -1)
      for (j = 0; j < COMMAND_NUM; j++)
      {
        if (!strcmp(token, commandlist[j]))
        {
          cmd->type = j;
          break;
        }
      } // ommitting braces for the "for loop" here is \
			 disastrous because the else below gets \
			 associated with the "if inside the for loop". \
			 #BUGFIX
    else
      append_path(cmd, token);
  }
  if (cmd->type != -1)
    return cmd;
  else
  {
    fprintf(stderr, "Error parsing command\n");
    return NULL;
  }
}

// void printcommand(struct command *c)
// {
//   if (!DEBUG)
//     return;

//   printf("Printing contents of the above command...\n");
//   printf("id = %d\n", c->id);
//   printf("npaths = %d\n", c->npaths);
//   printf("paths =\n");
//   int i;
//   for (i = 0; i < c->npaths; i++)
//     printf("\t%s\n", c->paths[i]);
//   printf("\n");
// }

void PwdCommand(int sfd_client)
{
  struct Packet *packet = malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->connection_id = -1;
  packet->command_type = kPwd;
  sendPacket(packet, sfd_client);
  recvPacket(packet, sfd_client);
  if (packet->type == kData && packet->command_type == kPwd && strlen(packet->buf) > 0)
    printf("%s\n", packet->buf);
  else
    fprintf(stderr, "Error retrieving kResponsermation.\n");
  free(packet);
}

void CdCommand(int sfd_client, char *path)
{
  struct Packet *packet = malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->connection_id = -1;
  packet->command_type = kCd;
  strcpy(packet->buf, path);
  sendPacket(packet, sfd_client);
  recvPacket(packet, sfd_client);
  strcpy(packet->buf, path);
  if (packet->type == kResponse && packet->command_type == kCd && !strcmp(packet->buf, "success"))
    ;
  else
    fprintf(stderr, "Error executing command on the server.\n");

  free(packet);
}

void LsLocalCommand(char *lpwd)
{
  DIR *d = opendir(lpwd);
  if (!d)
    throwErrorAndExit("opendir()", (int)d);
  struct dirent *e;
  while (e = readdir(d))
    printf("%s\t%s\n",
           e->d_type == 4   ? "DIR:"
           : e->d_type == 8 ? "FILE:"
                            : "UNDEF",
           e->d_name);
  closedir(d);
}

void LsCommand(int sfd_client)
{

  struct Packet *packet = (struct Packet *)malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->connection_id = -1;
  packet->command_type = kLs;

  sendPacket(packet, sfd_client);
  // recvPacket(packet, sfd_client);
  int i = 0;
  while (packet->type != kEnd)
  {
    i++;
    printf("%d\n",i);
    if (packet->type == kData && packet->command_type == kLs && strlen(packet->buf))
      printf("%s\n", packet->buf);
    recvPacket(packet, sfd_client);
  }
  free(packet);
}

void GetCommand(int sfd_client, char *filename)
{
  FILE *f = WriteFileAuto(filename);
  if (!f)
  {
    fprintf(stderr, "File could not be opened for writing. Aborting...\n");
    return;
  }

  struct Packet *packet = malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->connection_id = -1;
  packet->command_type = kGet;
  strcpy(packet->buf, filename);

  sendPacket(packet, sfd_client);
  recvPacket(packet, sfd_client);
  if (packet->type == kResponse && packet->command_type == kGet && strlen(packet->buf))
  {
    printf("%s\n", packet->buf);
    receiveFile(sfd_client, f);
    fclose(f);
  }
  else
    fprintf(stderr, "Error getting remote file : <%s>\n", filename);
}

void PutCommand(int sfd_client, char *filename)
{
  FILE *f = ReadFileAuto(filename); // Yo!
  if (!f)
  {
    fprintf(stderr, "File could not be opened for reading. Aborting...\n");
    return;
  }

  struct Packet *packet = malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->connection_id = -1;
  packet->command_type = kPut;
  strcpy(packet->buf, filename);

  sendPacket(packet, sfd_client);
  recvPacket(packet, sfd_client);

  if (packet->type == kResponse && packet->command_type == kPut && strlen(packet->buf))
  {
    printf("%s\n", packet->buf);
    sendFile(sfd_client, f);
  }
  else
    fprintf(stderr, "Error sending file.\n");
  free(packet);
  fclose(f);
  send_EOT(sfd_client);
}

void MkdirLocalCommand(int sfd_client, char *dirname)
{
  struct Packet *packet = malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->connection_id = -1;
  packet->command_type = kMkdir;
  strcpy(packet->buf, dirname);

  sendPacket(packet, sfd_client);
  recvPacket(packet, sfd_client);

  if (packet->type == kResponse && packet->command_type == kMkdir)
  {
    if (!strcmp(packet->buf, "success"))
      printf("Created directory on server.\n");
    else if (!strcmp(packet->buf, "already exists"))
      printf("Directory already exitst on server.\n");
  }
  else
    fprintf(stderr, "Error executing command on the server.\n");
  free(packet);
}

void LmkdirCommand(char *dirname)
{
  DIR *d = opendir(dirname);
  if (d)
  {
    printf("Directory already exists.\n");
    closedir(d);
  }
  else if (mkdir(dirname, 0777) == -1)
    fprintf(stderr, "Error in creating directory.\n");
  else
    printf("Created directory.\n");
}

void CdLocalCommand(char *path)
{
  if (chdir(path) == -1)
    fprintf(stderr, "Wrong path : <%s>\n", path);
}

void DeleteCommand(int sfd_client, char *filename)
{
  struct Packet *packet = malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->connection_id = -1;
  packet->command_type = kDelete;
  strcpy(packet->buf, filename);

  sendPacket(packet, sfd_client);
  recvPacket(packet, sfd_client);

  if (packet->type == kResponse && packet->command_type == kDelete &&
      !strcmp(packet->buf, "success"))
    ;
  else
    fprintf(stderr, "Error executing command on the server.\n");
  free(packet);
}

void DeleteLocalCommand(char *filename) 
{
  FILE *f = fopen(filename,"rb");
  if(!f){
    fprintf(stderr, "File do not exist!\n");
  }
  else{
    remove(filename);
  }
}