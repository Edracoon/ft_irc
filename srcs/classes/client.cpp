/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:10:21 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/17 15:08:30 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

client::client(int Fd)
{
	this->fd		= Fd;
	this->accepted	= false;
	this->ope		= false;
}

client::~client() {}

bool				client::isAccepted() const { return this->accepted; }

void				client::setUsername(const std::string & Username) { this->username = Username; }
void				client::setNickname(const std::string & Nickname) { this->nickname = Nickname; }
const std::string & client::getNickname(void) const { return this->nickname; }
const std::string & client::getUsername(void) const { return this->username; }
std::string&		client::getCurrMsg(void) { return this->curr_msg; }

unsigned long 		client::getFd() const { return this->fd; }

void				client::login(std::string message, char type, std::string password)
{
	std::vector<std::string> tab;
	std::cout << "type = " << type << std::endl;
	if (type == 'a')
	{
		tab = ft_split(message, "\n");
		this->login(tab[0], 'p', password);
		this->login(tab[1], 'u', password);
		this->login(tab[2], 'n', password);
	}
	else
		tab = ft_split(message, " ");

	// if (type == 'p')
	// {
	// 	if (strcmp(tab[1].c_str(), password.c_str()) == 0)
	// 		std::cout << password << std::endl;
	// 	std::cout << "p " << tab[1] << std::endl;
	// }
	for (int i = 0 ; !tab[i].empty() ; i++)
		std::cout << tab[i] << std::endl;
	// tab.clear();
}

void				client::joinChannel(channel chan)
{
	(void)chan;
}