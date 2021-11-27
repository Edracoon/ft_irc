/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:03:44 by fgomez            #+#    #+#             */
/*   Updated: 2021/11/27 18:59:06 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_kill(client* cl, std::vector<std::string> cmd, server* serv)
{
	if (cl->isOpe() == false)
		send(cl->getFd(), " :Permission Denied- You're not an IRC operator\r\n", 49, 0);
	else if (cmd.size() < 3)
		send(cl->getFd(), (cmd[0] + " :Not enough parameters\r\n").c_str(), cmd[0].length() + 25, 0);
	else if (serv->findClientByName(cmd[1]) == NULL)
			send(cl->getFd(), (cmd[1] + " :No such nick/channel\r\n").c_str(), cmd[1].length() + 24, 0);
	else
	{
		client *tmp = serv->findClientByName(cmd[1]);
		if (tmp->getNickname() == cl->getNickname())
			send(tmp->getFd(), " :You cannot KILL yourself\r\n", 28, 0);
		else if (ft_split(cl->getCurrMsg(), ":", 1).size() == 1)
			send(cl->getFd(), (cmd[0] + " :Not enough parameters\r\n").c_str(), cmd[0].length() + 25, 0);
		else
		{
			std::string msg = " :You are killed from this server for : " + (ft_split(cl->getCurrMsg(), ":", 1)[1]) + "\r\n";
			send(tmp->getFd(), msg.c_str(), msg.length(), 0);
			close(tmp->getFd());
			serv->deleteClient(tmp);
		}
	}
}
