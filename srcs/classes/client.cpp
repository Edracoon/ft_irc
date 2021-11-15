/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:10:21 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/16 00:34:47 by epfennig         ###   ########.fr       */
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

unsigned long 		client::getFd() const { return this->fd; }

void				client::login(std::string message, char type)
{
	int i = 0;
	std::vector<std::string> tab;

	std::cout << "login" << std::endl;


	if (type == 'a')
		tab = ft_split(message, "\n");
	else
		tab = ft_split(message, " ");

	while (!(tab[i].empty()))
	{
		std::cout << tab[i] << std::endl;
		i++;
	}
}


void				client::joinChannel(channel chan)
{
	(void)chan;
}