/* simpleChatServer.c */
/* This server allows connection for ONLY two clients & lets
   them chat with each other */

#include"headers.h"
int main(int argc,char **argv)
{
        if(argc<2)
        {
                puts("input : server_executable port_number\n");
                return 0;
        }

        puts("creating server socket\n");
        int sfd;
        sfd=socket(AF_INET,SOCK_STREAM,0);
        if(sfd<0)
        {
                perror("socket");
                close(sfd);
                exit(0);
        }
        puts("server socket created succussfully\n");

        puts("setting option to avoid bind error");
        int val=1;
        if(setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val))==-1)
        {
                perror("setsockopt");
                exit(0);
        }
        puts("setsockopt success\n");

        puts("binding...\n");
        struct sockaddr_in saddr;
        saddr.sin_family=AF_INET;
        saddr.sin_addr.s_addr=inet_addr("0.0.0.0");
        saddr.sin_port=htons(atoi(argv[1]));
        socklen_t slen=sizeof(saddr);
        if(bind(sfd,(const struct sockaddr *)&saddr,sizeof(saddr))<0)
        {
                perror("bind\n");
                exit(0);
        }
        puts("bind success\n");

        puts("preparing connection queue\n");
        if(listen(sfd,1)<0)
        {
                perror("listen");
                close(sfd);
                return 0;
        }
        puts("listen success\n");

        struct sockaddr_in caddr1,caddr2;
        int cfd1,cfd2;
        socklen_t clen=sizeof(caddr1);

        puts("server waiting for connection from any 2 Clients ONLY...\n");
        cfd1=accept(sfd,(struct sockaddr *)&caddr1,&clen);
        if(cfd1<0)
        {
                perror("accept");
                close(sfd);
                return 0;
        }
        puts("server accepted connection from 1st client\n");

        puts("server waiting for connection from 2nd client...\n");
        cfd2=accept(sfd,(struct sockaddr *)&caddr2,&clen);
        if(cfd2<0)
        {
                perror("accept");
                close(sfd);
                return 0;
        }
        puts("server accepted connection from 2nd client\n");

        puts("Now 1st & 2nd clients can chat...\n");

        char buff1[100],buff2[100];

        if(fork()==0)
        {
                              // this process always should recv MSG from CLIENT1_CHILD
                // and then later it will send MSG to CLIENT2_PARENT.
                // use buff1 for recv ans send MSG
                while(1)
                {
                        recv(cfd1,buff1,sizeof(buff1),0);
                        send(cfd2,buff1,strlen(buff1)+1,0);
                }
        }
        else
        {
              
                // this process always should recv MSG from CLIENT2_CHILD
                // and then later it will send MSG to CLIENT1_PARENT.
                // use buff2 for recv ans send MSG

                while(1)
                {
                        recv(cfd2,buff1,sizeof(buff1),0);
                        send(cfd1,buff1,strlen(buff1)+1,0);
                }

        }


        puts("Server closing connection with Chat Clients");
        close(cfd1);
        close(cfd2);
        close(sfd);
}
