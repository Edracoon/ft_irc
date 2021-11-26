/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:46:50 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/26 13:11:32 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_user(client* cl, std::vector<std::string> cmd)
{
	if  (cmd.size() < 5)
		send(cl->getFd(), (cmd[0] + " :Not enough parameters\r\n").c_str(), cmd[0].length() + 25, 0);
	else if (cl->isAccepted())
		send(cl->getFd(), ":Unauthorized command (already registered)\r\n", 44, 0);
	else if (cmd.size() >= 5 && !cl->isAccepted())
	{
		/* We just need to take the username and realname (not usefull in our case but it's rfc) */
		cl->setUsername(cmd[1]);
		cl->setRealname(ft_split(cl->getCurrMsg(), ":", 1)[1]);
		cl->user = true;
	}

	if (!cl->isAccepted() && cl->nick == true && cl->pass == true && cl->user == true)
	{
		std::string msg = ":NiceIRC 001 " + cl->getNickname() + " :Welcome to the Internet Relay Network " + cl->getNickname() + "!" + cl->getUsername() + "@127.0.0.1\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
		cl->AcceptClient();
	}
}
