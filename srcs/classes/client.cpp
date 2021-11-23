/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:10:21 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/23 10:54:18 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

client::client(int Fd)
{
	this->fd		= Fd;
	this->accepted	= true;
	this->ope		= false;
	this->pass		= false;
}

client::~client() {}

bool				client::isAccepted() const { return this->accepted; }

void				client::setUsername(const std::string & Username) { this->username = Username; }
void				client::setNickname(const std::string & Nickname) { this->nickname = Nickname; }
const std::string & client::getNickname(void) const { return this->nickname; }
const std::string & client::getUsername(void) const { return this->username; }
std::string&		client::getCurrMsg(void) { return this->curr_msg; }

unsigned long 		client::getFd() const { return this->fd; }

bool				client::isOpe(void) { return this->ope; }

void				client::joinChannel(channel chan)
{
	(void)chan;
}
