/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:59:30 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/26 13:11:25 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_nick(client* cl, std::vector<std::string> cmd,  server* serv)
{
	if  (cmd.size() < 2)
	{
		send(cl->getFd(), ":No nickname given\r\n", 20, 0);
		return ;
	}
	if (serv->findClientByName(cmd[1]) != NULL)
		send(cl->getFd(), (cmd[1] + " :Nickname is already in use\r\n").c_str(), cmd[1].length() + 30, 0);
	else
	{
		cl->setNickname(cmd[1]);
		cl->nick = true;
		cl->nickname_history.push_back(cmd[1]);
		/* Update name in client's current channel */
		if (cl->curr_chan != NULL && serv->findChannelByName(cl->curr_chan->getName()) != NULL)
			serv->findChannelByName(cl->curr_chan->getName())->findClientByName(cl->getNickname())->setNickname(cmd[1]);
	}

	if (!cl->isAccepted() && cl->nick == true && cl->pass == true && cl->user == true)
	{
		std::string msg = ":NiceIRC 001 " + cl->getNickname() + " :Welcome to the Internet Relay Network " + cl->getNickname() + "!" + cl->getUsername() + "@127.0.0.1\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
		cl->AcceptClient();
	}
}
