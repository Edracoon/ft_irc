/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:27:23 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/10 16:05:58 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
 #include <sys/event.h>
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

struct kevent {
            uintptr_t  ident;        identifier for this event
            uint32_t   filter;       filter for event
            uint32_t   flags;        action flags for kqueue
            uint32_t   fflags;       filter flag value
            int64_t    data;         filter data value
            void       *udata;        opaque user data identifier
};


*************************************************************************** */

void	ft_recev_msg(int cfd, sockaddr_in client_addr)
{
	char				buffer[1024];

	while (1) {
	bzero(buffer, 1024);
	recv(cfd, buffer, 1024, 0);
	std::cout << "Message received by " << (client_addr.sin_addr.s_addr) << ": " << buffer << std::endl;
	}
}

int	main(int ac, char **av)
{
	int					sfd = 0; 						// socket server
	int					port;							// server port
	int					cfd;						// socket client -> accept()
	socklen_t			addrlen;						// sizeof la structure sockaddr_in
	struct sockaddr_in	server_addr, client_addr;		// structure, données pour bind(), accept(), etc

	// KQUEUE VARIABLES //
	struct kevent		change_list[64], event_list[64];
	int		kq, n_ev;

	if (ac != 2)
		exit_error("./server [PORT]");
	if(!(sfd = socket(AF_INET, SOCK_STREAM, 0)))
		exit_error("Socket Error");

	port = atoi(av[1]);
	addrlen = sizeof(server_addr);

	/* Remplire la structure pour donner les informations au bind */
	server_addr.sin_family			= AF_INET;				// famille ipv4
	server_addr.sin_port			= htons(port);			// port
	server_addr.sin_addr.s_addr		= htonl(INADDR_ANY);	// 0x00000000 pour accepter toutes les addresses

	/* Cast de la grande structure sockaddr_in avec une plus petite structure sockaddr */
	if (bind(sfd, (struct sockaddr *)&server_addr, addrlen) < 0)
		exit_error("Bind Error");

	if (listen(sfd, 5) < 0)
		exit_error("Lister Error: Failed set soket to passive socket");

	// Set structure kevent selon nos flags
	EV_SET(&change_list[0], sfd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
	EV_SET(&change_list[1], fileno(stdin), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);

	// initialiser kqueue
	if ((kq = kqueue()) == -1)
		exit_error("Kqueue failed");

	while (1)
	{
		n_ev = kevent(kq, change_list, 64, event_list, 64, NULL);
		if (n_ev < 0)
			exit_error("kevent failed");
		else if (n_ev > 0)
		{

			if (event_list[0].flags & EV_EOF)
				exit_error("kevent: EV_EOF");
	
			for (int fd = 0; fd < n_ev ; fd++)
			{
				// Handle kevent error
				if (event_list[fd].flags & EV_ERROR)
					exit_error("kevent: EV_ERROR");

				// Accept client
				if (event_list[fd].ident == sfd) /* Accept new clients */
				{
					if ((cfd = accept(sfd, (struct sockaddr *)&client_addr, &addrlen)) == -1)
						exit_error("Accept client error");
				}

				// Read client that are already accepted
				else if (event_list[fd].ident & EVFILT_READ) /* Read clients messages */
					ft_recev_msg(cfd, client_addr);
			}
		}
	}
}
