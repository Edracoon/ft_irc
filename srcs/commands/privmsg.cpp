/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:42:17 by fgomez            #+#    #+#             */
/*   Updated: 2021/11/24 15:01:29 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_privmsg(client* cl, std::vector<std::string> cmd,  server* serv)
{
	std::vector<std::string>	destinataire = ft_split(cmd[1], ",", 512);
	if (destinataire.size() > 14)
		send(cl->getFd(), "ERR_TOOMANYTARGETS\r\n", 20, 0);
	else if (cmd.size() < 3)
		send(cl->getFd(), "ERR_NOTEXTTOSEND\r\n", 18, 0);
	for (unsigned int i = 0; i < destinataire.size(); i++)
	{
		if (serv->findClientByName(destinataire[i]) == NULL)
		{
			send(cl->getFd(), "ERR_NOSUCHNICK\r\n", 16, 0);
			return ; 
		}
	}
	for (unsigned int i = 0; i < destinataire.size(); i++)
	{
		client *tmp;
		tmp = serv->findClientByName(destinataire[i]);
		if (tmp->isAccepted())
		{
			std::string msg = "From " + cl->getNickname() + ": " + ft_split(cl->getCurrMsg(), cmd[1] + " ", 1)[1];
			send(tmp->getFd(), msg.c_str(), msg.length(), 0);
		}
	}
}