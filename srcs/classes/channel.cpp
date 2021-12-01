/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:34:22 by epfennig          #+#    #+#             */
/*   Updated: 2021/12/01 15:33:17 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

channel::channel(std::string Name)
{
	this->name		= Name;
	this->max_user	= 10;
	this->status	= 'n';	/* No status yet */

}

channel::~channel() {}

int		channel::addClient(client* cl, std::vector<std::string> cmd)  // JOIN d'un client, Verif, etc
{
	if (this->operators.size() == 0) /* It means it's a new channel */
	{
		this->operators.push_back(cl);
		this->users.push_back(cl);
		return (1);
	}

	else if (this->status == 'p')
	{
		if (cmd.size() < 3)
			send(cl->getFd(), "ERR_PRIVCHANNEEDKEY\r\n", 22, 0);
		else if (cmd[2] != this->password)
			send(cl->getFd(), "ERR_BADCHANNELKEY\r\n", 20, 0);
		else
			this->users.push_back(cl);
		return (1);
	}

	else if (this->status == 'i')
	{
		send(cl->getFd(), "ERR_INVITEONLYCHAN\r\n", 21, 0);
		return (0);
	}

	else if (this->users.size() == max_user)
	{
		send(cl->getFd(), "ERR_CHANNELISFULL\r\n", 20, 0);
		return (0);
	}

	else
		this->users.push_back(cl);

	return (1);
}


bool					channel::deleteClientFromChan(client *cl)
{
	std::vector<client *>::iterator	it	=	this->users.begin();
	std::vector<client *>::iterator	ite	=	this->users.end();

	std::vector<client *>::iterator	it2		=	this->operators.begin();
	std::vector<client *>::iterator	ite2	=	this->operators.end();
	
	for ( ; it != ite ; it++ )
	{
		if ((*it) == cl)
		{
			if (isOperator(cl->getNickname()) == true)
			{
				for ( ; it2 != ite2 ; )
				{
					if (*it2 == cl)
					{
						this->operators.erase(it2);
						break ;
					}
				}
			}
			this->users.erase(it);
			return (true);
		}
	}
	return (false);
}

const std::string&		channel::getName(void) const { return this->name; }
const std::string&		channel::getPassword(void) const { return this->name; }
const std::string&		channel::getTopic(void) const { return this->topic; }

bool					channel::isOperator(std::string user)
{
	std::vector<client *>::iterator	it	= this->operators.begin();
	std::vector<client *>::iterator	ite	= this->operators.end();

	for ( ; it != ite ; it++)
	{
		if ((*it)->getNickname() == user)
			return (true);
	}
	return false;
}

char		 			channel::checkStatus(void) const
{
	return this->status;
}

bool 					channel::checkMode(char mode) const
{
	(void)mode;
	return false;
}

bool					channel::checkBlackList(std::string user) const
{
	(void)user;
	return false;
}

bool					channel::checkMaxUser(void) const { return false; }

client*					channel::findClientByName(std::string nickname)
{
	std::vector<client *>::iterator	it	=	this->users.begin();
	std::vector<client *>::iterator	ite	=	this->users.end();

	for ( ; it != ite ; it++) {
		if ((*it)->getNickname() == nickname)
			return (*it);
	}
	return NULL;
}