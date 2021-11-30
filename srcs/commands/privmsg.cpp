/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:42:17 by fgomez            #+#    #+#             */
/*   Updated: 2021/11/30 17:20:18 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_privmsg(client* cl, std::vector<std::string> cmd,  server* serv)
{
	std::vector<std::string>	destinataire = ft_split(cmd[1], ",", 512);
	std::string msg;
	if (destinataire.size() > 14)
	{
		msg = cl->getNickname() + " :407 recipients. Too many targets.\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (cmd.size() < 3)
	{
		msg = ":NiceIRC 481 " + cl->getNickname() + " :No text to send\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}
	for (unsigned int i = 0; i < destinataire.size(); i++)
	{
		if (serv->findClientByName(destinataire[i]) == NULL && serv->findChannelByName(destinataire[i]) == NULL)
		{
			msg = ":NiceIRC 401 " + cl->getNickname() + " " + cmd[1] + " :No such nick/channel\r\n";
			send(cl->getFd(), msg.c_str(), msg.length(), 0);
			return ;
		}
	}

	client *tmp;
	msg = ":" + cl->getNickname() + "!" + cl->getUsername() + "@127.0.0.1 " + cl->getCurrMsg();
	for (unsigned int i = 0; i < destinataire.size(); i++)
	{
		tmp = serv->findClientByName(destinataire[i]);
		if (destinataire[i][0] == '#' || destinataire[i][0] == '&')
			sendToChan(cl, msg);
		else if (tmp->isAccepted())
			send(tmp->getFd(), msg.c_str(), msg.length(), 0);
	}
}
