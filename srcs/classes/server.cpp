/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:44:37 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/16 00:17:29 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server() {}
server::~server() {}

void					server::setPassword(const std::string & pass) { this->password = pass; }
const std::string &		server::getPassword(void) const { return this->password; }


client*					server::findClientByFd(unsigned long Fd)
{
	std::vector<client *>::iterator	it = this->clients.begin();
	std::vector<client *>::iterator	ite = this->clients.end();

	for ( ; it != ite ; it++ ) {
		if ((*it)->getFd() == Fd)
			return (*it);
	}
	return (NULL);
}


int		server::acceptClient(int kq, struct kevent change_list)
{
	struct sockaddr_in	client_addr;	// new struct for addr info client
	int addrlen = sizeof(client_addr);	// size of struct for accept()
	int cfd;							// new client fd

	// Si personne ne souhaite se connecter, le fd du server etant non bloquant,
	// dans ce cas on continue pour repartir du haute de la boucle !
	if ((cfd = accept(this->sfd, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen)) == -1)
		exit_error("Accept error");

	/* #define EWOULDBLOCK		EAGAIN			Operation would block */
	if (errno == EWOULDBLOCK)
		return -1;

	// Ajouter mon nouveau client à ma liste d'evenement en lui precisant le cfd
	// le client fd sera set de maniere non bloquante avec cfd
	fcntl(cfd, F_SETFL, O_NONBLOCK);
	EV_SET(&change_list, cfd, EVFILT_READ, EV_ADD, 0, 0, 0);
	kevent(kq, &change_list, 1, NULL, 0, NULL);
	
	client	*new_client = new client(cfd);
	this->clients.push_back(new_client);	// Add client to server list

	// std::cout << "Client[" << cfd << "] accepted !" << std::endl;
	return (1);
}

void	server::recevMessage(char *buffer, struct kevent event_list[64], int i)
{
	bzero(buffer, 512);
	recv(event_list[i].ident, buffer, 512, 0);
	if (std::string(buffer) == "\n")
		return ;
	client*		temp = this->findClientByFd(event_list[i].ident);
	if (temp != NULL && temp->isAccepted() == false)
	{
		if (strstr(buffer, "PASS") && strstr(buffer, "NICK") && strstr(buffer, "USER"))
			temp->login(std::string(buffer), 'a');
		else if (strncmp(buffer, "PASS", 4) == 0)
			temp->login(std::string(buffer), 'p');
		else if (strncmp(buffer, "NICK", 4) == 0)
			temp->login(std::string(buffer), 'n');
		else if (strncmp(buffer, "USER", 4) == 0)
			temp->login(std::string(buffer), 'u');
		else
			send(temp->getFd(), "You need to login first: PASS, NICK, USER\r\n", 43, 0);
		std::cout << "Client[" << event_list[i].ident << "] sent message : "  << buffer;
	}
	return ;
	
	// Send client message to all clients that are connected
	// std::map<int, int>::iterator	it	= client.begin();
	// std::map<int, int>::iterator	ite	= client.end();
	// if (event_list[i].filter & EVFILT_WRITE)
	// {
	// 	//Boucle sur tous les clients a partir de notre map client
	// 	for ( ; it != ite ; it++)
	// 	{
	// 		// Verifie que le client ne s'envoie pas un message a lui meme
	// 		if ((unsigned long)it->first != event_list[i].ident && strcmp(buffer, "\n"))
	// 		{
	// 			send(it->first, "Client[", 8 ,0);
	// 			send(it->first, ft_itos(client.find(event_list[i].ident)->second), 4,0);
	// 			send(it->first, "] sent message : ", 18 ,0);
	// 			send(it->first, buffer, 1024, 0);
	// 		}
	// 	}
	// }
}
