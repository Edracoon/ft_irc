/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:59:30 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/25 15:28:01 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_nick(client* cl, std::vector<std::string> cmd,  server* serv)
{
	if  (cmd.size() < 2)
	{
		send(cl->getFd(), "ERR_NONICKNAMEGIVEN\r\n", 22, 0);
		return ;
	}
	cmd[1] = ft_split(cmd[1], "\n", 1)[0];
	if (serv->findClientByName(cmd[1]) != NULL)
		send(cl->getFd(), "ERR_NICKNAMEINUSE\r\n", 20, 0);
	else
	{
		std::cout << "hello 1" << std::endl;
		cl->setNickname(cmd[1]);
		cl->nick = true;
		cl->nickname_history.push_back(cmd[1]);
		/* Update name in client's current channel */
		if (cl->curr_chan != NULL && serv->findChannelByName(cl->curr_chan->getName()) != NULL)
			serv->findChannelByName(cl->curr_chan->getName())->findClientByName(cl->getNickname())->setNickname(cmd[1]);
	}

	if (!cl->isAccepted() && cl->nick == true && cl->pass == true && cl->user == true)
	{
		std::string msg = ":127.0.0.1 001 " + cl->getNickname() + " :Welcome to the Internet Relay Network " + cl->getNickname() + "!" + cl->getUsername() + "@*\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
		// msg = cl->getNickname() + "@" + cl->getUsername() + " running in v1.0\r\n";
		// send(cl->getFd(), msg.c_str(), msg.length(), 0);
		cl->AcceptClient();
	}
}
