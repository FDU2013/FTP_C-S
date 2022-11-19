#include <server_command.h>

size_t size_sockaddr = sizeof(struct sockaddr),
       size_packet = sizeof(struct Packet);

void *serve_client(void *);

int main(void)
{
  // BEGIN: initialization
  struct sockaddr_in sin_server, sin_client;
  int sockerfd_server, socketfd_client;
  int expect;
  short int connection_id = 0;

  if ((expect = sockerfd_server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) <
      0)
    throwErrorAndExit("socket()", expect);

  memset((char *)&sin_server, 0, sizeof(struct sockaddr_in));
  sin_server.sin_family = AF_INET;
  sin_server.sin_port = htons(PORTSERVER);
  sin_server.sin_addr.s_addr = htonl(INADDR_ANY);

  if ((expect = bind(sockerfd_server, (struct sockaddr *)&sin_server,
                     size_sockaddr)) < 0)
    throwErrorAndExit("bind()", expect);

  if ((expect = listen(sockerfd_server, 1)) < 0)
    throwErrorAndExit("listen()", expect);

  printf(ID "FTP Server started up @ local:%d. Waiting for client(s)...\n\n",
         PORTSERVER);
  // END: initialization

  while (1)
  {
    if ((expect = socketfd_client = accept(
             sockerfd_server, (struct sockaddr *)&sin_client, &size_sockaddr)) <
        0)
      throwErrorAndExit("accept()", expect);
    printf(ID "Communication started with %s:%d\n",
           inet_ntoa(sin_client.sin_addr), ntohs(sin_client.sin_port));
    fflush(stdout);

    struct client_info *ci =
        client_info_alloc(socketfd_client, connection_id++);
    serve_client(ci);
  }

  close(sockerfd_server);
  printf(ID "Done.\n");
  fflush(stdout);

  return 0;
}

void *serve_client(void *info)
{
  int sfd_client, connection_id, x;
  struct Packet *shp;
  char lpwd[LENBUFFER];
  struct client_info *ci = (struct client_info *)info;
  sfd_client = ci->sfd;
  connection_id = ci->cid;

  while (1)
  {

    if ((x = recv(sfd_client, shp, size_packet, 0)) == 0)
    {
      fprintf(stderr, "client closed/terminated. closing connection.\n");
      break;
    }

    ntoh_packet(shp);

    if (shp->type == TERM)
      break;

    if (shp->connection_id == -1)
      shp->connection_id = connection_id;

    if (shp->type == kRequest)
    {
      switch (shp->command_type)
      {
      case kPwd:
        if (!getcwd(lpwd, sizeof lpwd))
          throwErrorAndExit("getcwd()", 0);
        command_pwd(shp, sfd_client, lpwd);
        break;
      case kCd:
        if ((x = chdir(shp->buf)) == -1)
          fprintf(stderr, "Wrong path.\n");
        command_cd(shp, sfd_client, x == -1 ? "fail" : "success");
        break;
      case kMkdir:
        command_mkdir(shp, sfd_client);
        break;
      case kLs:
        if (!getcwd(lpwd, sizeof lpwd))
          throwErrorAndExit("getcwd()", 0);
        command_ls(shp, sfd_client, lpwd);
        break;
      case kGet:
        command_get(shp, sfd_client);
        break;
      case kPut:
        command_put(shp, sfd_client);
        break;
      default:
        // print error
        break;
      }
    }
    else
    {
      // show error, send TERM and break
      fprintf(stderr, "packet incomprihensible. closing connection.\n");
      snedErrorPacket(sfd_client);
      break;
    }
  }

  close(sfd_client);
  fflush(stdout);
}
