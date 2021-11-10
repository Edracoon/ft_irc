/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:27:23 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/10 12:22:45 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	exit_error(std::string error)
{
	std::cout << "Error: "<< error << std::endl;
	exit(EXIT_FAILURE);
}

/* ***************************************************************************

====================================
**	=== Server TCP / IP ===
**	Socket()
**	Bind()
**	Listen()
**	Accept()
**	Write() / Read() -> (server <--> client)
**	Close()
====================================

struct sockaddr_in
{
	__uint8_t       sin_len;							// unsigned char  0 - 255
	sa_family_t     sin_family;							// unsigned char  0 - 255
	in_port_t       sin_port;							// unsigned short 0	- 65535
	struct  in_addr sin_addr;		sin_addr.s_addr;	// unsigned int   (0xffffffff) address
	char            sin_zero[8];
};

[XSI] Structure used by kernel to store most addresses.
struct sockaddr
{
	__uint8_t       sa_len;         total length		// unsigned char
	sa_family_t     sa_family;      address family		// unsigned char
	char            sa_data[14];    addr value (actually larger)
};

struct in_addr
{
	in_addr_t s_addr;  base type for internet address
};

in_addr_t == uint32_t

*************************************************************************** */

int	main(int ac, char **av)
{
	int					sfd = 0; 						// socket server
	int					port;							// server port
	int					cfd = 0;						// socket client -> accept()
	socklen_t			addrlen;						// sizeof la structure sockaddr_in
	struct sockaddr_in	server_addr, client_addr;		// structure, données pour bind(), accept(), etc
	char				buffer[1024];

	if (ac != 2)
		exit_error("./server [PORT]");
	if(!(sfd = socket(AF_INET, SOCK_STREAM, 0)))
		exit_error("Socket Error");

	port = atoi(av[1]);
	addrlen = sizeof(server_addr);

	/* Remplire la structure pour donner les informations au bind */
	server_addr.sin_family			= AF_INET;				// famille ipv4
	server_addr.sin_port			= htons(port);			// port
	server_addr.sin_addr.s_addr		= htonl(INADDR_ANY);	// n'importe quelle address ?

	/* Cast de la grande structure sockaddr_in avec une plus petite structure sockaddr */
	if (bind(sfd, (struct sockaddr *)&server_addr, addrlen) == -1)
		exit_error("Bind Error");

	if (listen(sfd, 5) == -1)
		exit_error("Lister Error: Failed set soket to passive socket");

	// ==================================== micka et kevin part
	cfd = accept(sfd, (struct sockaddr *)&client_addr, &addrlen);
	if (cfd < 0)
			exit_error("Accept client error");
	while (1) {
		bzero(buffer, 1024);
		recv(cfd, buffer, 1024, 0);
		std::cout << "Message received by " << (client_addr.sin_addr.s_addr) << ": " << buffer << std::endl;
	}

}