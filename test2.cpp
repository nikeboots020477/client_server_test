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
    struct timeval timeout = {7, 0};
    fd_set fds;
    char name[LEN];
    char quit[] ={"quit\n"};
  //int i=fputs( quit, stdout);
    FD_ZERO(&fds);
    FD_SET(1, &fds);
    printf("Hi. What is your name?\n");
    int ret = select(2, NULL, &fds,  NULL, &timeout);
    if (ret == -1) {
        printf("Oops! Something wrong happened...\n");
    } else if (ret == 0) {
        printf("Doesn't matter. You're too slow!\n");
    } else {
        
        int i = fputs( quit, stdout);
        
        //std::cout<<"Nice to meet you "<<name<<"  "<<ret<<"  "<<(strcmp(name,quit)==0);
    
}    
    return 0;
}