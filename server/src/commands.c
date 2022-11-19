#include <commands.h>

void PwdCommand(struct Packet *packet, int sfd_client, char *lpwd) {
  packet->type = kData;
  strcpy(packet->buf, lpwd);
  sendPacket(packet, sfd_client);
}

void CdCommand(struct Packet *packet, int sfd_client, char *message) {
  packet->type = kResponse;
  strcpy(packet->buf, message);
  sendPacket(packet, sfd_client);
}

void LsCommand(struct Packet *packet, int sfd_client, char *lpwd) {
  packet->type = kData;
  DIR *d = opendir(lpwd);
  if (!d) throwErrorAndExit("opendir()", (int)d);
  struct dirent *e;
  while (e = readdir(d)) {
    sprintf(packet->buf, "%s\t%s",
            e->d_type == 4   ? "DIR:"
            : e->d_type == 8 ? "FILE:"
                             : "UNDEF:",
            e->d_name);
    sendPacket(packet, sfd_client);
  }
  sendEndPacket(sfd_client);
}

void GetCommand(struct Packet *packet, int sfd_client) {
  FILE *f = ReadFileAuto(packet->buf);  // Yo!
  packet->type = kResponse;
  packet->command_type = kGet;
  strcpy(packet->buf, f ? "File found; processing" : "Error opening file.");
  // printpacket(packet, HP);
  sendPacket(packet, sfd_client);
  if (f) {
    packet->type = kData;
    sendFile(sfd_client, f);
    fclose(f);
  }
  sendEndPacket(sfd_client);
}

void PutCommand(struct Packet *packet, int sfd_client) {
  FILE *f = WriteFileAuto(packet->buf);
  packet->type = kResponse;
  packet->command_type = kPut;
  strcpy(packet->buf, f ? "Everything in order; processing"
                        : "Error opening file for writing on server side.");
  // printpacket(packet, HP);
  sendPacket(packet, sfd_client);
  if (f) {
    receiveFile(sfd_client, f);
    fclose(f);
  }
}

void DeleteCommand(struct Packet *packet, int sfd_client) {
  char message[BUF_SIZE];
  FILE *f = fopen(packet->buf, "rb");
  if (!f) {
    fprintf(stderr, "File do not exist!\n");
    strcpy(message, "fail");
  } else {
    remove(packet->buf);
    strcpy(message, "success");
  }
  strcpy(packet->buf, message);
  sendPacket(packet, sfd_client);
}

void MkdirCommand(struct Packet *packet, int sfd_client) {
  char message[BUF_SIZE];
  DIR *d = opendir(packet->buf);
  if (d) {
    strcpy(message, "already exists");
    closedir(d);
  } else if (mkdir(packet->buf, 0777) == -1) {
    fprintf(stderr, "Wrong path.\n");
    strcpy(message, "fail");
  } else
    strcpy(message, "success");

  packet->type = kResponse;
  strcpy(packet->buf, message);
  sendPacket(packet, sfd_client);
}
