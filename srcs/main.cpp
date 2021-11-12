/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:27:23 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/12 16:14:50 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

int		accept_client(int sfd, int kq, struct kevent change_list, std::map<int, int>* client, int* id)
{
	struct sockaddr_in	client_addr;	// new struct for addr info client
	int addrlen = sizeof(client_addr);	// size of struct for accept()
	int cfd;							// new client fd

	// Si personne ne souhaite se connecter, le fd du server etant non bloquant,
	// dans ce cas on continue pour repartir du haute de la boucle !
	if ((cfd = accept(sfd, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen)) == -1)
		exit_error("Accept error");

	/* #define EWOULDBLOCK		EAGAIN			Operation would block */
	if (errno == EWOULDBLOCK)
		return -1;
	// Ajouter mon nouveau client à ma liste d'evenement en lui precisant le cfd
	// le client fd sera set de maniere non bloquante avec cfd
	fcntl(cfd, F_SETFL, O_NONBLOCK);
	EV_SET(&change_list, cfd, EVFILT_READ, EV_ADD, 0, 0, 0);
	kevent(kq, &change_list, 1, NULL, 0, NULL);

	client->insert(std::make_pair(cfd, *id));
	*id += 1;

	std::cout << "Client[" << cfd << "] accepted !" << std::endl;
	return (1);
}

void	recev_message(char *buffer, std::map<int, int> client, struct kevent event_list[64], int i)
{
	bzero(buffer, 1024);
	recv(event_list[i].ident, buffer, 1024, 0);
	if (strcmp(buffer, "\n"))
		std::cout << "Client[" << event_list[i].ident << "] sent message : "  << buffer;
	
	// Send client message to all clients that are connected
	std::map<int, int>::iterator	it	= client.begin();
	std::map<int, int>::iterator	ite	= client.end();
	if (event_list[i].filter & EVFILT_WRITE)
	{
		//Boucle sur tous les clients a partir de notre map client
		for ( ; it != ite ; it++)
		{
			// Verifie que le client ne s'envoie pas un message a lui meme
			if ((unsigned long)it->first != event_list[i].ident && strcmp(buffer, "\n"))
			{
				send(it->first, "Client[", 8 ,0);
				send(it->first, ft_itos(client.find(event_list[i].ident)->second), 4,0);
				send(it->first, "] sent message : ", 18 ,0);
				send(it->first, buffer, 1024, 0);
			}
		}
	}
}


int	main(int ac, char **av)
{
	int					id = 1;
	int					sfd = 0; 						// socket server
	int					port;							// server port
	socklen_t			addrlen;						// sizeof la structure sockaddr_in
	char				buffer[1024];
	struct sockaddr_in	server_addr;					// structure, données pour bind(), accept(), etc

	std::map<int, int>	client;

	if (ac != 2)
		exit_error("Usage ./server [PORT]");
	if(!(sfd = socket(AF_INET, SOCK_STREAM, 0)))
		exit_error("Socket Error");

	std::cout << "Server socket successfully created: " << sfd << std::endl;

	port = atoi(av[1]);
	addrlen = sizeof(server_addr);

	/* Remplire la structure pour donner les informations au bind */
	server_addr.sin_family			= AF_INET;				// famille ipv4
	server_addr.sin_port			= htons(port);			// port
	server_addr.sin_addr.s_addr		= htonl(INADDR_ANY);	// 0x00000000 pour accepter toutes les addresses

	/* Cast de la grande structure sockaddr_in avec une plus petite structure sockaddr */
	if (bind(sfd, (struct sockaddr *)&server_addr, addrlen) < 0)
		exit_error("Bind Error");
	std::cout << "Successfully binding server socket" << std::endl;
	
	// Rendre le fd du server non bloquant, ce qui va permettre d'eviter de bloquer
	// sur le accept dans la boucle si aucun client n'essaie de se connecter
	fcntl(sfd, F_SETFL, O_NONBLOCK);

	if (listen(sfd, 42) < 0)
		exit_error("Lister Error: Failed set soket to passive socket");

	std::cout << "Server listening for clients connexion" << std::endl;

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

		if ((n_ev = kevent(kq, NULL, 0, event_list, 64, NULL)) < 0 )
			exit_error("kevent failed");

		else if (n_ev > 0)
		{
			
			/* Boucler sur le nombre de nouveaux events */
			for (int i = 0; i < n_ev ; i++)
			{
				/* Handle kevent error */
				if (event_list[i].flags & EV_ERROR)
					exit_error("kevent: EV_ERROR");

				/* Client disconnect */
				if (event_list[i].flags & EV_EOF)
				{
					std::cerr << "Client[" << event_list[i].ident << "] disconnected !" << std::endl;
					close(event_list[i].ident);
					client.erase(event_list[i].ident);
				}

				/* Accept new clients */
				else if (event_list[i].ident == (unsigned long)sfd)
				{
					if (accept_client(sfd, kq, change_list, &client, &id))
						break ;
				}

				/* Read client messages that are already accepted */
				else if (event_list[i].filter & EVFILT_READ)
				{
					recev_message(buffer, client, event_list, i);
				}
			}
		}
	}
}
