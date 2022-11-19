#include <common.h>

void InitPacket(struct Packet *p) { memset(p, 0, sizeof(struct Packet)); }

void ntoh_packet(struct Packet *netPacket) {
  netPacket->connection_id = ntohs(netPacket->connection_id);
  netPacket->type = ntohs(netPacket->type);
  netPacket->command_type = ntohs(netPacket->command_type);
  netPacket->data_size = ntohs(netPacket->data_size);
}

void hton_packet(struct Packet *hostPacket) {
  hostPacket->connection_id = htons(hostPacket->connection_id);
  hostPacket->type = htons(hostPacket->type);
  hostPacket->command_type = htons(hostPacket->command_type);
  hostPacket->data_size = htons(hostPacket->data_size);
}

/*列举常见的文件后缀，可以自行扩展*/
static const char *with_suffix[] = {
    ".gz",  ".rar",  ".exe",  ".bz2",  ".tar", ".xz",  ".Z",    ".rpm", ".zip",
    ".a",   ".so",   ".o",    ".jar",  ".dll", ".lib", ".deb",  ".I",   ".png",
    ".jpg", ".mp3",  ".mp4",  ".m4a",  ".flv", ".mkv", ".rmvb", ".avi", ".pcap",
    ".pdf", ".docx", ".xlsx", ".pptx", ".ram", ".mid", ".dwg",  NULL};

/*判断某个字符串是否拥有指定后缀*/
static bool StringHasSuffix(const char *str, const char *suffix) {
  int n, m, i = 0;
  char ch = '\0';
  if (str == NULL || suffix == NULL) {
    return false;
  }
  n = strlen(str);
  m = strlen(suffix);
  if (n < m) {
    return false;
  }
  for (i = m - 1; i >= 0; i--) {
    if (suffix[i] != str[n - m + i]) {
      return false;
    }
  }
  return true;
}

/*判断文件是否具有特殊后缀*/
static bool FileHasSpecSuffix(const char *fname) {
  const char **suffix = NULL;
  suffix = with_suffix;
  while (*suffix) {
    if (StringHasSuffix(fname, *suffix)) {
      return true;
    }
    suffix++;
  }
  return false;
}

/*判断文件是否具有特殊文件头*/
static bool FileHasSpecHeader(const char *fname) {
  FILE *fp = NULL;
  size_t len = 0;
  char buf[16] = {0};
  int i = 0;
  bool retval = false;
  if ((fp = fopen(fname, "r")) == NULL) {
    return false;
  }

  len = sizeof(buf) - 1;
  if (fgets(buf, len, fp) == NULL) {
    return false;
  }
  if (len < 4) {
    return false;
  }
#if defined(__linux__)
  // ELF header
  if (memcmp(buf, "\x7F\x45\x4C\x46", 4) == 0) {
    return true;
  }
#elif defined(_AIX)
  // executable binary
  if (memcmp(buf, "\x01\xDF\x00", 3) == 0) {
    return true;
  }
#elif defined(WIN32)
  // standard exe file, actually, won't go into this case
  if (memcmp(buf, "\x4D\x5A\x90\x00", 4) == 0) {
    return true;
  }
#endif
  if (memcmp(buf, "\x50\x4B\x03\x04", 4) == 0) {
    // maybe archive file, eg: jar zip rar sec.
    return true;
  }

  return false;
}

bool IsAsciiFile(char *filename) {
  if (FileHasSpecSuffix(filename)) {
    return true;
  } else if (FileHasSpecHeader(filename)) {
    return true;
  } else {
    return false;
  }
}

// bool IsAsciiFile(char* filename) {
//   int len = strlen(filename);
//   if (len > 4 && strcmp(".txt", filename + len - 4) == 0) {
//     // printf("(info).txt file, transfer by ascii mode\n");
//     return true;
//   }
//   // printf("(info)normal file, transfer by binary mode \n");
//   return false;
// }

FILE *ReadFileAuto(char *filename) {
  if (IsAsciiFile(filename)) {
    return fopen(filename, "r");
  } else {
    return fopen(filename, "rb");
  }
}
FILE *WriteFileAuto(char *filename) {
  if (IsAsciiFile(filename)) {
    return fopen(filename, "w");
  } else {
    return fopen(filename, "wb");
  }
}

void PrintPacket(struct Packet *packet) {
  printf("connection_id is %d\n", packet->connection_id);
  printf("type is %d\n", packet->type);
  printf("command_type is %d\n", packet->command_type);
  printf("data_size is %d\n", packet->data_size);
}