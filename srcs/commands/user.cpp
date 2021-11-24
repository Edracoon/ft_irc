/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:46:50 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/24 10:02:43 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_user(client* cli, std::vector<std::string> cmd)
{
	if  (cmd.size() < 5)
		send(cli->getFd(), "ERR_NEEDMOREPARAMS\r\n", 21, 0);
	else if (cli->isAccepted())
		send(cli->getFd(), "ERR_ALREADYREGISTRED\r\n", 23, 0);
	else if (cmd.size() >= 5 && !cli->isAccepted())
	{
		/* We just need to take the username and realname (not usefull in our case but it's rfc) */
		cli->setUsername(cmd[1]);
		cli->setRealname(ft_split(ft_split(cli->getCurrMsg(), "\n", 1)[0], ":", 1)[1]);
		cli->user = true;
	}

	if (cli->nick == true && cli->pass == true && cli->user == true)
	{
		send(cli->getFd(), "You’ve been accepted\n", 24, 0);
		cli->AcceptClient();
	}
}
