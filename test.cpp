#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string.h>


#define LEN 100


int main() {
    struct timeval timeout = {1, 0};
    fd_set fds;
    char name[LEN];
    char quit[] ={"quit\n"};
while(true){
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    //std::cout<<"-"<<std::endl;
    int ret = select(1, &fds, NULL, NULL, &timeout);
    if (ret == -1) {
        printf("Oops! Something wrong happened...\n");
    } else if (ret == 1) {
        fgets(name, LEN, stdin);
        std::cout<<"Nice to meet you "<<name<<"  "<<ret<<"  ";
    }
    if(strcmp(name,quit)==0) break;
    //std::cout<<"**"<<std::endl;
}    
    return 0;
}