/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:46:50 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/23 14:35:09 by fgomez           ###   ########.fr       */
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
		/* Au final on s'en fout des information precedentes, je recupere juste l'username */
		cli->setUsername(ft_split(cli->getCurrMsg(), ":", 1)[1]);
		cli->user = true;
	}

	if (cli->nick == true && cli->pass == true && cli->user == true)
		cli->AcceptClient();
}
