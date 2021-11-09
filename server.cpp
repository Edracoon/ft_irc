#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void	exit_error(std::string error)
{
	std::cout << "Error: "<< error << std::endl;
	exit(EXIT_FAILURE);
}

/*
**	Server TCP / IP
** Socket()
** Bind()
** Listen()
** Accept()
** Write() / Read()  [communication server - client]
** Close()
*/

int	main(int ac, char **av)
{
	int					server_socket = 0; 	// socket server 
	int					port;				// server port
	int					new_socket;			// socket client -> accept()
	socklen_t			addrlen;			// sizeof la structure sockaddr_in
	struct sockaddr_in	t_sockaddr_in;		// structure, données pour bind(), accept(), etc
	char				buffer[1024];

	if (ac != 2)
		exit_error("./server [PORT]");
	if(!(server_socket = socket(AF_INET, SOCK_STREAM, 0)))
		exit_error("21: Socket Error");

	port = atoi(av[1]);
	addrlen = sizeof(t_sockaddr_in);

	/* Remplire la structure pour donner les informations au bind */
	t_sockaddr_in.sin_port				= port;			// port
	t_sockaddr_in.sin_addr.s_addr		= INADDR_ANY;	// n'importe quelle address ?
	t_sockaddr_in.sin_family			= AF_INET;		// famille ipv4

	/* Cast de la grande structure sockaddr_in avec une plus petite structure sockaddr */
	if (bind(server_socket, (struct sockaddr *)&t_sockaddr_in, addrlen) == -1)
		exit_error("25: Bind Error");


	// ==================================== micka et kevin part

	// if (listen(server_socket, 3) < 0)
	// 	exit_error("Failed set soket to passive socket");
	// while (1) {
	// 	new_socket = accept(server_socket, (struct sockaddr *)&t_sockaddr_in, &addrlen);
	// 	if (new_socket < 0)
	// 		exit_error("Accept client error");
	// 	recv(new_socket, buffer, 1024, 0);
	// 	std::cout << "Message received by " << (t_sockaddr_in.sin_addr.s_addr) << ": " << buffer << std::endl;
	// }

}