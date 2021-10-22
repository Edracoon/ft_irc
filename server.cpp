#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

void	exit_error2(std::string msg){
	std::cout << "Error" << std::endl << msg << std::endl;
	exit(1);
}

int	main(int ac, char **av)
{
	int	serv_fd, new_socket, rd;
	//int	opt_val = 1;
	int	addrlen;
	char buffer[1024] = {0};
	int port;
	struct sockaddr_in	address;

	if (ac != 2)
		exit_error2("Usage: ./client port");
	port = atoi(av[1]);
	serv_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (serv_fd == 0)
		exit_error2("Socket creation failed");
	// if (setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt_val, sizeof(opt_val)))
	//	 exit_error2("Failed attaching socket");
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	if ((bind(serv_fd, (struct sockaddr *)&address, sizeof(address))) < 0)
		exit_error2("Failed attaching socket to the port");
	if (listen(serv_fd, 3) < 0)
		exit_error2("Failed set soket to passive socket");
	addrlen = sizeof(address);
	while (1) {
		new_socket = accept(serv_fd, (struct sockaddr *)&address, (socklen_t *)&(addrlen));
		if (new_socket < 0)
			exit_error2("Failed to add client");
		rd = recv(new_socket, buffer, 1024, 0);
		std::cout << "Message received by " << (address.sin_addr.s_addr) << ": " << buffer << std::endl;
	}
}
