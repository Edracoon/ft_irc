/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:38:47 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/27 15:14:12 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_oper(client* cl, std::vector<std::string> cmd, server* serv)
{
	if (cmd.size() < 3)
		send(cl->getFd(), (cmd[0] + " :Not enough parameters\r\n").c_str(), cmd[0].length() + 25, 0);
	else if (cl->isOpe())
		send(serv->findClientByName(cmd[1])->getFd(), " :You are now an IRC operator\r\n", 31, 0);
	else if (cmd[2] != serv->getOperPassword())
		send(cl->getFd(), " :Password incorrect\r\n", 22, 0);
	else if (cmd[2] == serv->getOperPassword())
	{
		client* tmp = serv->findClientByName(cmd[1]);
		if (tmp != NULL)
		{
			tmp->ope	= true;
			send(tmp->getFd(), " :You are now an IRC operator\r\n", 31, 0);
		}
	}
}