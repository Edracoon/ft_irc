/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:03:44 by fgomez            #+#    #+#             */
/*   Updated: 2021/11/30 16:52:49 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_kill(client* cl, std::vector<std::string> cmd, server* serv)
{
	std::string msg;
	if (cl->isOpe() == false)
	{
		msg = ":NiceIRC 481 " + cl->getNickname() + " :Permission Denied- You're not an IRC operator\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (cmd.size() < 3)
	{
		msg = ":NiceIRC 461 " + cl->getNickname() + " " + cmd[0] + " :Not enough parameters\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->findClientByName(cmd[1]) == NULL)
	{
		msg = ":NiceIRC 401 " + cl->getNickname() + " " + cmd[1] + " :No such nick/channel\r\n";
		send(cl->getFd(), msg.c_str(), cmd[1].length(), 0);
	}
	else
	{
		client *tmp = serv->findClientByName(cmd[1]);
		if (tmp->getNickname() == cl->getNickname())
		{
			msg = ":NiceIRC 401 " + cl->getNickname() + " :You cannot kill yourself\r\n";
			send(tmp->getFd(), msg.c_str(), msg.length(), 0);
		}
		else if (ft_split(cl->getCurrMsg(), ":", 1).size() == 1)
		{
			msg = ":NiceIRC 461 " + cl->getNickname() + " " + cmd[0] + " :Not enough parameters\r\n";
			send(cl->getFd(), msg.c_str(), cmd[0].length(), 0);
		}
		else
		{
			msg = ":NiceIRC 361 " + cl->getNickname() + " :You are killed from this server for :" + (ft_split(cl->getCurrMsg(), ":", 1)[1]) + "\r\n";
			send(tmp->getFd(), msg.c_str(), msg.length(), 0);
			close(tmp->getFd());
			serv->deleteClient(tmp->getFd());
		}
	}
}
