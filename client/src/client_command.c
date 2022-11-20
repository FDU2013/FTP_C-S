#include <client_command.h>
#include <common.h>
#include <file_transfer.h>

static int size_packet = sizeof(struct Packet);

#define COMMAND_LENTH_MAX 10
static const char all_commands[COMMAND_NUM][COMMAND_LENTH_MAX] = {
    "get",    "put",

    "cd",     "lcd",

    "delete", "ldelete",

    "ls",     "lls",

    "mkdir",  "lmkdir",

    "pwd",    "lpwd",

    "exit"};

static void AppendPath(struct Command *cmd, char *s) {
  cmd->para_num++;
  char **temp_paths = (char **)malloc(cmd->para_num * sizeof(char *));
  if (cmd->para_num > 1)
    memcpy(temp_paths, cmd->parameters, (cmd->para_num - 1) * sizeof(char *));

  char *temps = (char *)malloc((strlen(s) + 1) * sizeof(char));
  int i;
  for (i = 0; *(temps + i) = *(s + i) == ':' ? ' ' : *(s + i); i++) {
  }

  *(temp_paths + cmd->para_num - 1) = temps;

  cmd->parameters = temp_paths;
}

struct Command *InputCommand(char out[INPUT_LENTH_MAX]) {
  struct Command *cmd = (struct Command *)malloc(sizeof(struct Command));
  cmd->type = -1;
  cmd->para_num = 0;
  cmd->parameters = NULL;
  char *savestate;
  char *token;
  for (int i = 0;; i++, out = NULL) {
    token = strtok_r(out, " \t\n", &savestate);
    if (token == NULL) break;
    if (cmd->type == -1) {
      for (int j = 0; j < COMMAND_NUM; j++) {
        if (!strcmp(token, all_commands[j])) {
          cmd->type = j;
          break;
        }
      }
    } else {
      AppendPath(cmd, token);
    }
  }
  if (cmd->type != -1)
    return cmd;
  else {
    fprintf(stderr, "Error parsing command\n");
    return NULL;
  }
}

void PwdCommand(int socketfd_client) {
  struct Packet *packet = malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->command_type = kPwd;
  SendPacket(packet, socketfd_client);
  RecvPacket(packet, socketfd_client);
  if (packet->type == kData && packet->command_type == kPwd &&
      strlen(packet->buf) > 0)
    printf("%s\n", packet->buf);
  else
    fprintf(stderr, "Error retrieving kResponsermation.\n");
  free(packet);
}

void CdCommand(int socketfd_client, char *path) {
  struct Packet *packet = malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->command_type = kCd;
  strcpy(packet->buf, path);
  SendPacket(packet, socketfd_client);
  RecvPacket(packet, socketfd_client);
  if (packet->type == kResponse && packet->command_type == kCd &&
      !strcmp(packet->buf, "success"))
    ;
  else
    fprintf(stderr, "Error executing command on the server.\n");

  free(packet);
}

void LsLocalCommand(char *local_pwd) {
  DIR *local_dir = opendir(local_pwd);
  if (!local_dir) throwErrorAndExit("local_ls()", local_dir);
  struct dirent *this_dirent;
  int i = 0;
  while (this_dirent = readdir(local_dir)) {
    i++;
    if (i < 3) continue;
    switch (this_dirent->d_type) {
      case DT_DIR:
        printf("%s%s\n", "(Dir) ", this_dirent->d_name);
        break;
      case DT_REG:
        printf("%s%s\n", "(File) ", this_dirent->d_name);
        break;
      case DT_UNKNOWN:
        printf("%s%s\n", "(Unknown) ", this_dirent->d_name);
        break;
      default:
        printf("%s%s\n", "(Other) ", this_dirent->d_name);
        break;
    }
    //   printf("%s\t%s\n",
    //          this_dirent->d_type == 4   ? "DIR:"
    //          : this_dirent->d_type == 8 ? "FILE:"
    //                                     : "UNDEF",
    //          this_dirent->d_name);
    // }
  }
  closedir(local_dir);
}

void LsCommand(int socketfd_client) {
  struct Packet *packet = (struct Packet *)malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->command_type = kLs;

  SendPacket(packet, socketfd_client);
  // RecvPacket(packet, socketfd_client);
  while (packet->type != kEnd) {
    if (packet->type == kData && packet->command_type == kLs &&
        strlen(packet->buf))
      printf("%s\n", packet->buf);
    RecvPacket(packet, socketfd_client);
  }
  free(packet);
}

void GetCommand(int socketfd_client, char *filename) {
  // FILE *l_file = WriteFileAuto(filename);
  // if (!l_file) {
  //   fprintf(stderr, "Local file write failed.\n");
  //   return;
  // }
  struct Packet *packet = malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->command_type = kGet;
  strcpy(packet->buf, filename);

  SendPacket(packet, socketfd_client);
  RecvPacket(packet, socketfd_client);
  if (packet->type == kResponse && packet->command_type == kGet &&
      strlen(packet->buf)) {
    printf("%s\n", packet->buf);
    if (strcmp(packet->buf, "(Server)Error opening file.")) {
      char name[50] = "(copy)";
      if (!access(filename, 0)) {
        strcat(name, filename);
      } else {
        strcpy(name, filename);
      }
      FILE *l_file = WriteFileAuto(name);
      if (!l_file) {
        fprintf(stderr, "Local file write failed.\n");
        return;
      }
      ReceiveFile(socketfd_client, l_file);
      fclose(l_file);
    }
  } else
    fprintf(stderr, "Server does not allow getting or send illegal message .");
}

void PutCommand(int socketfd_client, char *filename) {
  FILE *l_file = ReadFileAuto(filename);  // Yo!
  if (!l_file) {
    fprintf(stderr, "Local file read failed.\n");
    return;
  }

  struct Packet *packet = malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->command_type = kPut;
  strcpy(packet->buf, filename);

  SendPacket(packet, socketfd_client);
  RecvPacket(packet, socketfd_client);

  if (packet->type == kResponse && packet->command_type == kPut &&
      strlen(packet->buf)) {
    printf("%s\n", packet->buf);
    SendFile(socketfd_client, l_file);
  } else
    fprintf(stderr, "Received illegal message from server.\n");
  free(packet);
  fclose(l_file);
  SendEndPacket(socketfd_client);
}

void MkdirLocalCommand(int socketfd_client, char *dirname) {
  struct Packet *packet = malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->command_type = kMkdir;
  strcpy(packet->buf, dirname);

  SendPacket(packet, socketfd_client);
  RecvPacket(packet, socketfd_client);

  if (packet->type == kResponse && packet->command_type == kMkdir) {
    if (!strcmp(packet->buf, "success"))
      printf("Created directory on server successfully.\n");
    else if (!strcmp(packet->buf, "already exists"))
      printf("Directory has already exitsted on server.\n");
  } else
    fprintf(stderr, "Received illegal message from server.\n");
  free(packet);
}

void LmkdirCommand(char *dirname) {
  DIR *l_dir = opendir(dirname);
  if (l_dir) {
    printf("Directory has already existed.\n");
    closedir(l_dir);
  } else if (mkdir(dirname, 0777) == -1)
    fprintf(stderr, "Error in creating directory.\n");
  else
    printf("Created directory.\n");
}

void CdLocalCommand(char *path) {
  if (chdir(path) == -1) fprintf(stderr, "Path is not valid : <%s>\n", path);
}

void DeleteCommand(int socketfd_client, char *filename) {
  struct Packet *packet = malloc(size_packet);
  InitPacket(packet);
  packet->type = kRequest;
  packet->command_type = kDelete;
  strcpy(packet->buf, filename);

  SendPacket(packet, socketfd_client);
  RecvPacket(packet, socketfd_client);

  if (packet->type == kResponse && packet->command_type == kDelete &&
      !strcmp(packet->buf, "success"))
    ;
  else
    fprintf(stderr, "Received illegal message from server.\n");
  free(packet);
}

void DeleteLocalCommand(char *filename) {
  FILE *l_file = fopen(filename, "rb");
  if (!l_file) {
    fprintf(stderr, "File does not exist!\n");
  } else {
    remove(filename);
  }
}