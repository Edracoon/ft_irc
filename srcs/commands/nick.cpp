/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:59:30 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/24 19:39:41 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_nick(client* cl, std::vector<std::string> cmd,  server* serv)
{
	if  (cmd.size() < 2)
		send(cl->getFd(), "ERR_NONICKNAMEGIVEN\r\n", 22, 0);
	else if (serv->findClientByName(cmd[1]) != NULL)
		send(cl->getFd(), "ERR_NICKNAMEINUSE\r\n", 20, 0);
	else
	{
		cl->setNickname(cmd[1]);
		cl->nick = true;
		cl->nickname_history.push_back(cmd[1]);
		/* Update name in client's current channel */
		if (cl->curr_chan != NULL && serv->findChannelByName(cl->curr_chan->getName()) != NULL)
			serv->findChannelByName(cl->curr_chan->getName())->findClientByName(cl->getNickname())->setNickname(cmd[1]);
	}

	if (cl->nick == true && cl->pass == true && cl->user == true)
	{
		std::string msg = "Welcome to $===< Ed&Flo IRC >===$\r\n"; 
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
		msg = cl->getNickname() + "@" + cl->getUsername() + " running in v1.0\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
		cl->AcceptClient();
	}
}
