#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

#include <iostream>
#include <string.h>

//My IP address 192.168.0.10 
//Port 5050

int main(int argc, char *argv[]){

if(argc !=3){
    std::cerr<<"Need 2 args."<<std::endl;
    return 1;
}

int sock, Port;
struct sockaddr_in serv_addr;
struct sockaddr_in local_addr;

char *IP={argv[1]};
Port = atoi(argv[2]);

sock = socket(AF_INET, SOCK_STREAM, 0);

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(Port); 
serv_addr.sin_addr.s_addr = inet_addr(IP);

//int bind(int sockfd, struct sockaddr *addr, int addrlen);

if(connect(sock, (struct sockaddr *) & serv_addr, sizeof(serv_addr)) < 0){
    perror("connect");
    exit(2);
}

char msg[100]={};
char buf[sizeof(msg)];

char quit[] ={"quit\n"};
char str[20];


struct timeval timeout = {1, 0};
fd_set fds;

while(true){

    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    //std::cout<<"-"<<std::endl;
    int ret = select(1, &fds, NULL, NULL, &timeout);
    if (ret == -1) {
        printf("Oops! Something wrong happened...\n");
    } else if (ret == 1) {
        fgets(msg, sizeof(msg), stdin);
        std::cout<<"Massage send "<<msg<<"  "<<ret<<"  "<<std::endl;
        send(sock, msg, sizeof(msg), 0);
        
       // bytes_read = recv(sock, buf, sizeof(msg), 0);
        if(recv(sock, buf, sizeof(buf), 0)>0 )
        std::cout<<"Msg received"<<std::endl;
    }
    if(strcmp(msg,quit)==0) break;

    //std::cout<<"."<<"some shitttt"<<std::endl;
   /*  std::cout<<"."<<"some shitttt"<<std::endl;
       bytes_read = recv(sock, buf, sizeof(msg), 0);
        std::cout<<bytes_read<<std::endl;
         */
        //std::cout<<"receved "<<buf<<std::endl; 
}
//recv(sock, buf, sizeof(message), 0);
    
//std::cout<<buf;
close(sock);



return 0;    
}


