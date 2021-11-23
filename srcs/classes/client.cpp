/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:10:21 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/23 19:22:50 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

client::client(int Fd)
{
	this->fd		= Fd;
	this->curr_chan	= NULL;
	this->accepted	= false;
	this->ope		= true;
	this->pass		= false;
	this->nick		= false;
}

client::~client() {}

bool				client::isAccepted() const { return this->accepted; }
void				client::AcceptClient() { this->accepted = true; }

void				client::setUsername(const std::string & Username) { this->username = Username; }
void				client::setNickname(const std::string & Nickname) { this->nickname = Nickname; }
void				client::setRealname(const std::string & Realname) { this->realname = Realname; }

const std::string & client::getNickname(void) const { return this->nickname; }
const std::string & client::getUsername(void) const { return this->username; }
const std::string &	client::getRealname(void) const { return this->realname; }

std::string&		client::getCurrMsg(void) { return this->curr_msg; }

unsigned long 		client::getFd() const { return this->fd; }

bool				client::isOpe(void) { return this->ope; }

void				client::joinChannel(channel chan)
{
	(void)chan;
}
