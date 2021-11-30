/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:38:47 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/30 17:02:57 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_oper(client* cl, std::vector<std::string> cmd, server* serv)
{
	std::string	msg;
	if (cmd.size() < 3)
	{
		msg = ":NiceIRC 461 " + cl->getNickname() + " " + cmd[0] + " :Not enough parameters\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (cl->isOpe())
	{
		msg = ":" + cl->getNickname() + "!" + cl->getUsername() + "127.0.0.1 " + "OPER " + ":" + cmd[1] + "\r\n";
		send(serv->findClientByName(cmd[1])->getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (cmd[2] != serv->getOperPassword())
	{
		msg = ":NiceIRC 464 " + cl->getNickname() + " :Password incorrect\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (cmd[2] == serv->getOperPassword())
	{
		client* tmp = serv->findClientByName(cmd[1]);
		if (tmp != NULL)
		{
			tmp->ope	= true;
			msg = ":" + cl->getNickname() + "!" + cl->getUsername() + "127.0.0.1 " + "OPER " + ":" + cmd[1] + "\r\n";
			send(tmp->getFd(), msg.c_str(), msg.length(), 0);
		}
	}
}