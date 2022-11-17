#include <commons.h>

static size_t size_packet = sizeof(struct packet);

void init_packet(struct packet* p)
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
		printf("\tHOST PACKET\n");
	else
		printf("\tNETWORK PACKET\n");
	
	printf("\tconid = %d\n", p->conid);
	printf("\ttype = %d\n", p->type);
	printf("\tcomid = %d\n", p->comid);
	printf("\tdatalen = %d\n", p->datalen);
	printf("\tbuffer = %s\n", p->buffer);
	
	fflush(stdout);
}

