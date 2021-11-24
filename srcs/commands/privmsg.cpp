/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:42:17 by fgomez            #+#    #+#             */
/*   Updated: 2021/11/24 09:42:19 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_privmsg(client* cl, std::vector<std::string> cmd,  server* serv)
{
	std::vector<std::string>	destinataire = ft_split(cmd[1], ",", 512);
	if (destinataire.size() > 14)
		send(cl->getFd(), "ERR_TOOMANYTARGETS\r\n", 21, 0);
	else if (cmd.size() < 3)
		send(cl->getFd(), "ERR_NOTEXTTOSEND\r\n", 19, 0);
	for (unsigned int i = 0; i < destinataire.size(); i++)
	{
		if (serv->findClientByName(destinataire[i]) == NULL)
		{
			send(cl->getFd(), "ERR_NOSUCHNICK\r\n", 17, 0);
			return ; 
		}
	}
	for (unsigned int i = 0; i < destinataire.size(); i++)
	{
		client *tmp;
		tmp = serv->findClientByName(destinataire[i]);
		cmd[2] += "\r\n";
		if (tmp->isAccepted())
			send (tmp->getFd(), ("From " + cl->getNickname() + ": " + cmd[2]).c_str(), cl->getNickname().length() + cmd[2].length() + 7, 0);
	}

	std::vector<client *>::iterator	it = serv->clients.begin();
	std::vector<client *>::iterator	ite = serv->clients.end();

	for (; it != ite; it++)
	{
		std::cout << (*it)->isAccepted() << " - ";
		std::cout << (*it)->getNickname() << " - ";
		std::cout << (*it)->getUsername() << std::endl;
	}
}