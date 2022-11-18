#include <commons.h>

static size_t size_packet = sizeof(struct packet);

void InitPacket(struct packet* p)
{
	memset(p, 0, sizeof(struct packet));
}

struct packet* ntohp(struct packet* np)
{
	struct packet* hp = (struct packet*) malloc(size_packet);
	memset(hp, 0, size_packet);
	
	hp->conid = ntohs(np->conid);
	hp->type = ntohs(np->type);
	hp->comid = ntohs(np->comid);
	hp->datalen = ntohs(np->datalen);
	memcpy(hp->buffer, np->buffer, LENBUFFER);
	
	return hp;	
}

struct packet* htonp(struct packet* hp)
{
	struct packet* np = (struct packet*) malloc(size_packet);
	memset(np, 0, size_packet);
	
	np->conid = ntohs(hp->conid);
	np->type = ntohs(hp->type);
	np->comid = ntohs(hp->comid);
	np->datalen = ntohs(hp->datalen);
	memcpy(np->buffer, hp->buffer, LENBUFFER);
	
	return np;
}

void printpacket(struct packet* p, int ptype)
{
	if(!DEBUG)
		return;
	
	if(ptype)
		printf("HOST PACKET\n");
	else
		printf("NETWORK PACKET\n");
	
	printf("conid = %d\n", p->conid);
	printf("type = %d\n", p->type);
	printf("comid = %d\n", p->comid);
	printf("datalen = %d\n", p->datalen);
	printf("buffer = %s\n", p->buffer);
	
	fflush(stdout);
}

