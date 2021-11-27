/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:42:17 by fgomez            #+#    #+#             */
/*   Updated: 2021/11/26 15:24:57 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_privmsg(client* cl, std::vector<std::string> cmd,  server* serv)
{
	std::vector<std::string>	destinataire = ft_split(cmd[1], ",", 512);
	if (destinataire.size() > 14)
	{
		std::string	msg = cl->getNickname() + " :407 recipients. Too many targets.\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (cmd.size() < 3)
		send(cl->getFd(), ":No text to send\r\n", 18, 0);
	for (unsigned int i = 0; i < destinataire.size(); i++)
	{
		if (serv->findClientByName(destinataire[i]) == NULL && serv->findChannelByName(destinataire[i]) == NULL)
		{
			send(cl->getFd(), (cmd[1] + " :No such nick/channel\r\n").c_str(), cmd[1].length() + 24, 0);
			return ;
		}
	}

	client *tmp;
	for (unsigned int i = 0; i < destinataire.size(); i++)
	{
		tmp = serv->findClientByName(destinataire[i]);
		if (destinataire[i][0] == '#' || destinataire[i][0] == '&')
			sendToChan(cl);
		else if (tmp->isAccepted())
		{
			std::string msg = ":" + cl->getNickname() + "!" + cl->getUsername() + "@127.0.0.1 " + cl->getCurrMsg();
			send(tmp->getFd(), msg.c_str(), msg.length(), 0);
		}
	}
}
