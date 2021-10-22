#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

void    exit_error(std::string msg){
    std::cout << "Error" << std::endl << msg << std::endl;
    exit(1);
}

int    main(int ac, char **av) {
    int    sock;
    struct sockaddr_in    serv_addr;

    if (ac != 3)
        exit_error("Usage : ./client port message");
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        exit_error("Socket creation failed");
    
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(av[1]));

    if (inet_pton(AF_INET, "10.11.3.7", &serv_addr.sin_addr) < 0)
        exit_error("IP address convertion failed");
    if (connect(sock, reinterpret_cast< const struct sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0)
        exit_error("Connexion failed");
    if (send(sock, av[2], strlen(av[2]), 0) < 0)
        exit_error("Message not send");
    return (0);
}