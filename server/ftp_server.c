#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <fcntl.h>
 
#define N 256
 
typedef struct sockaddr SA;
 
void commd_ls(int);
void commd_get(int, char *);
void commd_put(int, char *);
 
int main(int arg, char *argv[])
{
    int ser_sockfd,cli_sockfd;
    struct sockaddr_in ser_addr,cli_addr;
    int ser_len, cli_len;
    char commd [N];
    bzero(commd,N);//��commd��ָ����ַ�����ǰN���ֽ���Ϊ0������'\0'
 
    if((ser_sockfd=socket(AF_INET, SOCK_STREAM, 0) ) < 0)
    {
        printf("Sokcet Error!\n");
        return -1;
    }
 
    bzero(&ser_addr,sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);//��TCP�����У��˴��������Զ���ȡip��ַ
                                                //�ڰ�ipʱ���Զ�ѡ��ip��ַ
    ser_addr.sin_port = htons ( 8989 );
    ser_len = sizeof(ser_addr);
    //��ip��ַ���׽��ְ�
    if((bind(ser_sockfd, (SA *)&ser_addr, ser_len)) < 0)
    {
        printf("Bind Error!\n");
        return -1;
    }
    //�������˼���
    if(listen(ser_sockfd, 5) < 0)
    {
        printf("Linsten Error!\n");
        return -1;
    }
 
    bzero(&cli_addr, sizeof(cli_addr));
    ser_len = sizeof(cli_addr);
 
    while(1)
    {
        printf("server_ftp>");
        //�������˽������Կͻ��˵����ӣ�����һ���׽��֣����׽���Ϊ�½���һ���������ͻ��˵ĵ�ַ����Ϣ����cli_addr��
        //ԭ�����׽����Դ��ڼ�����
        if((cli_sockfd=accept(ser_sockfd, (SA *)&cli_addr, &cli_len)) < 0)
        {
            printf("Accept Error!\n");
            exit(1);
        }
        //���׽��ֽ�������ʱ���׽��ְѽ��յ����ݷ����׽��ֻ������������û���������Ǹ��Ƶ��û���������Ȼ����read������ȡ
        //write����ͬ��
        if(read(cli_sockfd, commd, N) < 0)  //read������cli_sockfd�ж�ȡN���ֽ����ݷ���commd��
        {
            printf("Read Error!\n");
            exit(1);
        }
 
        printf("recvd [ %s ]\n",commd);
 
        if(strncmp(commd,"ls",2) == 0)
        {
            commd_ls(cli_sockfd);
        }else if(strncmp(commd,"get", 3) == 0 )
        {
            commd_get(cli_sockfd, commd+4);
        }else if(strncmp(commd, "put", 3) == 0)
        {
            commd_put(cli_sockfd, commd+4);
        }else
        {
            printf("Error!Command Error!\n");
        }
    }
 
    return 0;
}
 
void commd_ls(int sockfd)
{
    DIR * mydir =NULL;
    struct dirent *myitem = NULL;
    char commd[N] ;
    bzero(commd, N);
    //opendirΪĿ¼����������������open����
    //mydir�д������Ŀ¼����Ϣ���д�ѧϰ��
    if((mydir=opendir(".")) == NULL)
    {
        printf("OpenDir Error!\n");
        exit(1);
    }
 
    while((myitem = readdir(mydir)) != NULL)
    {
        if(sprintf(commd, myitem->d_name, N) < 0)
        {
            printf("Sprintf Error!\n");
            exit(1);
        }
 
        if(write(sockfd, commd, N) < 0 )
        {
            printf("Write Error!\n");
            exit(1);
        }
    }
 
    closedir(mydir);
    close(sockfd);
 
    return ;
}
 
void commd_get(int sockfd, char *filename)
{
    int fd, nbytes;
    char buffer[N];
    bzero(buffer, N);
 
    printf("get filename : [ %s ]\n",filename);
    if((fd=open(filename, O_RDONLY)) < 0)
    {
        printf("Open file Error!\n");
        buffer[0]='N';
        if(write(sockfd, buffer, N) <0)
        {
            printf("Write Error!At commd_get 1\n");
            exit(1);
        }
        return ;
    }
 
    buffer[0] = 'Y';    //�˴���ʾ���ļ���ȡ�ɹ�
    if(write(sockfd, buffer, N) <0)
    {
        printf("Write Error! At commd_get 2!\n");
        close(fd);
        exit(1);
    }
 
    while((nbytes=read(fd, buffer, N)) > 0)
    {
        if(write(sockfd, buffer, nbytes) < 0)
        {
            printf("Write Error! At commd_get 3!\n");
            close(fd);
            exit(1);
        }
    }
 
    close(fd);
    close(sockfd);
 
    return ;
}
 
void commd_put(int sockfd, char *filename)
{
    int fd, nbytes;
    char buffer[N];
    bzero(buffer, N);
 
    printf("get filename : [ %s ]\n",filename);
    if((fd=open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0)
    {
        printf("Open file Error!\n");
        return ;
    }
 
    while((nbytes=read(sockfd, buffer, N)) > 0)
    {
        if(write(fd, buffer, nbytes) < 0)
        {
            printf("Write Error! At commd_put 1!\n");
            close(fd);
            exit(1);
        }
    }
 
    close(fd);
    close(sockfd);
 
    return ;
}