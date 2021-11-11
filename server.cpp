/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:27:23 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/11 13:45:48 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <map>
#include <sstream>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
 #include <sys/event.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	exit_error(std::string error)
{
	std::cout << "Error: "<< error << std::endl;
	exit(EXIT_FAILURE);
}

const char*	 ft_itos ( int Number )
{
	std::ostringstream	ss;
	ss << Number;
	return ss.str().c_str();
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

// Struct client pour renvoyer un message d'un client aux autres


int	main(int ac, char **av)
{
	int					id = 1;
	int					sfd = 0; 						// socket server
	int					port;							// server port
	int					cfd;							// socket client -> accept()
	socklen_t			addrlen;						// sizeof la structure sockaddr_in
	char				buffer[1024];
	struct sockaddr_in	server_addr, client_addr;		// structure, données pour bind(), accept(), etc

	std::map<int, int>	client;

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


	// KQUEUE VARIABLES //
	struct kevent		change_list, event_list[64];
	int		kq, n_ev;

	// initialiser kqueue
	if ((kq = kqueue()) == -1)
		exit_error("Kqueue failed");

	// Set structure kevent selon nos flags
	EV_SET(&change_list, sfd, EVFILT_READ, EV_ADD, 0, 0, 0);

	// Add ma queue
	kevent(kq, &change_list, 1, NULL, 0, NULL);

	while (1)
	{
		n_ev = kevent(kq, NULL, 0, event_list, 64, NULL);
		if (n_ev < 0)
			exit_error("kevent failed");
		else if (n_ev > 0)
		{
			
			// Boucler sur le nombre de nouveaux events
			for (int i = 0; i < n_ev ; i++)
			{
				// Handle kevent error
				if (event_list[i].flags & EV_ERROR)
					exit_error("kevent: EV_ERROR");

				// Client disconnect
				if (event_list[i].flags & EV_EOF)
				{
					std::cerr << "Client[" << event_list[i].ident << "] disconnected !" << std::endl;
					close(event_list[i].ident);
					client.erase(event_list[i].ident);
				}
				// Accept client
				else if (event_list[i].ident == sfd) /* Accept new clients */
				{
					if ((cfd = accept(sfd, (struct sockaddr *)&client_addr, &addrlen)) == -1)
						exit_error("Accept error");

					// Ajouter mon nouveau client à ma liste d'evenement en lui precisant le cfd
					EV_SET(&change_list, cfd, EVFILT_READ, EV_ADD, 0, 0, 0);
					kevent(kq, &change_list, 1, NULL, 0, NULL);
					
					client.insert(std::make_pair(cfd, id++));

					std::cout << "Client[" << cfd << "] accepted !" << std::endl;
				}

				// Read client that are already accepted
				else if (event_list[i].filter & EVFILT_READ) /* Read clients messages */
				{
					std::cout << "Client[" << event_list[i].ident << "] sent message : ";
					bzero(buffer, 1024);
					recv(event_list[i].ident, buffer, 1024, 0);
					std::cout << buffer;
					
					// Send client message to all clients that are connected
					std::map<int, int>::iterator	it	= client.begin();
					std::map<int, int>::iterator	ite	= client.end();
					if (event_list[i].filter & EVFILT_WRITE)
					{
						//Boucle sur tous les clients a partir de notre map client
						for ( ; it != ite ; it++)
						{
							// Verifie que le client ne s'envoie pas un message a lui meme
							if (it->first != event_list[i].ident)
							{
								send(it->first, "Client[", 8 ,0);
								send(it->first, ft_itos(event_list[i].ident), 8 ,0);
								send(it->first, "] sent message : ", 18 ,0);
								send(it->first, buffer, 1024, 0);
							}
						}
					}
				}

				// SERVER DISPLAY SYSTEM FONCTIONNE PAS POUR L'INSTANT
				// Write to clients that are connected
				// else if (event_list[i].filter == sfd) /* Read clients messages */
				// {
				// 	std::cout << "Message from server : ";
				// 	bzero(buffer, 1024);
				// 	read(sfd, buffer, 1024);
				// 	std::cout << "buffer = " << buffer << std::endl; 
				// 	send(event_list[i].ident, buffer, 1024, 0);
				// }
			}
		}
	}
}
