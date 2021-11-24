/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:49:07 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/24 12:54:12 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"
#include "../classes/channel.hpp"

void	create_channel(client* cli, std::vector<std::string> cmd, server* serv)
{
	channel*	new_chan = new channel(cmd[1]);
	new_chan->addClient(cli, cmd);
	serv->channels.push_back(new_chan);
	cli->curr_chan = new_chan;

}

void	cmd_join(client* cli, std::vector<std::string> cmd, server* serv)
{
	channel*	curr_chan = NULL;
	if (cmd.size() < 2)
		send(cli->getFd(), "ERR_NEEDMOREPARAMS\r\n", 21, 0);
	else if (cmd[1][0] != '#' && cmd[1][0] != '&')
		send(cli->getFd(), "ERR_BADCHANMASK\r\n", 18, 0);
	else
	{
		curr_chan = serv->findChannelByName(cmd[1]);

		/* Leave Channel if Client is already in one */
		if (cli->curr_chan != NULL)
		{
			cli->curr_chan->deleteClientFromChan(cli);
			cli->curr_chan = NULL;
		}

		/* Create chan or join it if its exists */
		if (curr_chan == NULL)
		{
			create_channel(cli, cmd, serv);
		}
		else
		{
			if (curr_chan->addClient(cli, cmd) == 0)
				return ;
			cli->curr_chan = curr_chan;

			/* Print List of Users in chan */
			curr_chan->printListUser(cli);
		}
	}
}