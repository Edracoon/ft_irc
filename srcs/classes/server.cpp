/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:44:37 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/25 15:23:31 by epfennig         ###   ########.fr       */
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

client*					server::findClientByName(std::string name)
{
	std::vector<client *>::iterator	it = this->clients.begin();
	std::vector<client *>::iterator	ite = this->clients.end();

	for ( ; it != ite ; it++ ) {
		if ((*it)->getNickname() == name)
			return (*it);
	}
	return (NULL);
}

channel*				server::findChannelByName(std::string name)
{
	std::vector<channel *>::iterator	it = this->channels.begin();
	std::vector<channel *>::iterator	ite = this->channels.end();

	for ( ; it != ite ; it++ ) {
		if ((*it)->getName() == name)
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

	std::cout << "Client[" << cfd << "] accepted !" << std::endl;
	return (1);
}

void	server::recevMessage(std::string buffer, struct kevent event_list[64], int i)
{
	client*		curr_client = this->findClientByFd(event_list[i].ident);
	curr_client->parser.parsing(curr_client, buffer, this);
	
	return ;
}

void	server::parse_config_file()
{
	std::ifstream	ifs("config_irc.conf");
	std::string		buff;
	while (getline(ifs, buff))
	{
		if (strncmp(buff.c_str(), "serv_accept_connex:", 20) == 0)
			serv_accept_connex = ft_split(buff, ": ", 1)[1];
		else if (strncmp(buff.c_str(), "location:", 10) == 0)
			location = ft_split(buff, ": ", 1)[1];
		else if (strncmp(buff.c_str(), "oper:", 6) == 0)
			pass_oper = ft_split(buff, ": ", 1)[1];
		else if (strncmp(buff.c_str(), "server_responsible:", 20) == 0)
			serv_responsible = ft_split(buff, ": ", 1)[1];
	}
}

void			server::deleteClient(client* tmp)
{
	std::vector<client *>::iterator	it	=	this->clients.begin();
	std::vector<client *>::iterator	ite =	this->clients.end();

	for ( ; it != ite ; it++ )
	{
		if (tmp->getNickname() == (*it)->getNickname())
		{
			if ((*it)->curr_chan != NULL)
				(*it)->curr_chan->deleteClientFromChan(*it);
			std::cout << (*it)->getNickname() << " - " << (*it)->getUsername() << std::endl;
			this->clients.erase(it);
			delete tmp;
			return ;
		}
	}
}