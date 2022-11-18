#include <common.h>

// #define extract_filename(filepath) ((strrchr(filepath, '/') != NULL) ?
// (strrchr(filepath, '/') + 1) : filepath)

void send_EOT(struct Packet*, struct Packet*, int);
void send_TERM(struct Packet*, struct Packet*, int);

void send_file(struct Packet*, struct Packet*, int, FILE*);
void receive_file(struct Packet*, struct Packet*, int, FILE*);
