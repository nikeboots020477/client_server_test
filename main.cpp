#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <string.h>

#define PORT 5050

int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5050);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    char hostname[100];
    if(gethostname(hostname, sizeof(hostname)) < 0){
        perror("gethostname failed");
        exit(EXIT_FAILURE);
    }

    std::cout<<hostname;

    listen(listener, 1);
    std::cout << "Server listening on port " << PORT << "...\n";

    
    while(1){ 
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }
        std::cout << "Connection accepted...\n";
        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
            if(bytes_read <= 0) break;
            std::cout<<"Massage "<<buf<<std::endl;
            send(sock, buf, bytes_read, 0);
        }

        close(sock);
    }
    
    return 0;
}