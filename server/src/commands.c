#include <commands.h>

void PwdCommand(struct Packet *packet, int socketfd_client, char *lpwd) {
  packet->type = kData;
  strcpy(packet->buf, lpwd);
  SendPacket(packet, socketfd_client);
}

void CdCommand(struct Packet *packet, int socketfd_client, char *message) {
  packet->type = kResponse;
  // printf("mess:%s\n", message);
  strcpy(packet->buf, message);
  SendPacket(packet, socketfd_client);
}

void LsCommand(struct Packet *packet, int socketfd_client, char *lpwd) {
  packet->type = kData;
  DIR *this_dir = opendir(lpwd);
  if (!this_dir) throwErrorAndExit("ls()", (int)this_dir);
  struct dirent *this_dirent;
  while (this_dirent = readdir(this_dir)) {
    switch (this_dirent->d_type) {
      case DT_DIR:
        sprintf(packet->buf, "%s%s", "(Dir) ", this_dirent->d_name);
        break;
      case DT_REG:
        sprintf(packet->buf, "%s%s", "(File) ", this_dirent->d_name);
        break;
      case DT_UNKNOWN:
        sprintf(packet->buf, "%s%s", "(Unknown) ", this_dirent->d_name);
        break;
      default:
        sprintf(packet->buf, "%s%s", "(Other) ", this_dirent->d_name);
        break;
    }
    SendPacket(packet, socketfd_client);
  }
  closedir(this_dir);
  SendEndPacket(socketfd_client);
}

void GetCommand(struct Packet *packet, int socketfd_client) {
  FILE *file = ReadFileAuto(packet->buf);
  packet->type = kResponse;
  packet->command_type = kGet;
  strcpy(packet->buf, file ? "Getting:" : "(Server)Error opening file.");
  SendPacket(packet, socketfd_client);
  if (file) {
    packet->type = kData;
    SendFile(socketfd_client, file);
    fclose(file);
    SendEndPacket(socketfd_client);
  }
}

void PutCommand(struct Packet *packet, int socketfd_client) {
  FILE *file = WriteFileAuto(packet->buf);
  packet->type = kResponse;
  packet->command_type = kPut;
  strcpy(packet->buf, file ? "Everything in order; processing"
                           : "Error opening file for writing on server side.");
  // printpacket(packet, HP);
  SendPacket(packet, socketfd_client);
  if (file) {
    ReceiveFile(socketfd_client, file);
    fclose(file);
  }
}

void DeleteCommand(struct Packet *packet, int socketfd_client) {
  char message[BUF_SIZE];
  FILE *file = fopen(packet->buf, "rb");
  if (!file) {
    fprintf(stderr, "File do not exist!\n");
    strcpy(message, "fail");
  } else {
    remove(packet->buf);
    strcpy(message, "success");
  }
  packet->type = kResponse;
  // printf("mess:%s\n", message);
  strcpy(packet->buf, message);
  SendPacket(packet, socketfd_client);
}

void MkdirCommand(struct Packet *packet, int socketfd_client) {
  char message[BUF_SIZE];
  DIR *this_dir = opendir(packet->buf);
  if (this_dir) {
    strcpy(message, "already exists");
    closedir(this_dir);
  } else if (mkdir(packet->buf, 0777) == -1) {
    fprintf(stderr, "Wrong path.\n");
    strcpy(message, "fail");
  } else
    strcpy(message, "success");

  packet->type = kResponse;
  strcpy(packet->buf, message);
  SendPacket(packet, socketfd_client);
}
