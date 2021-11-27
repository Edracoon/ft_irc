/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:49:07 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/27 14:37:01 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"
#include "../classes/channel.hpp"

void	norme_client(client* cl)
{
	// ==================== Confirm client join chan ===================
	std::string msg = ":" + cl->getNickname() + "!" + cl->getUsername() + "@127.0.0.1 " + cl->getCurrMsg();
	send(cl->getFd(), msg.c_str() , msg.length(), 0);
	// ==================== Message for topic ==========================
	msg = ":NiceIRC 332 " + cl->getNickname() + " " + cl->curr_chan->getName() + " :No Topic set";
	send(cl->getFd(), (msg + "\r\n").c_str() , msg.length(), 0);
	std::cout << msg << std::endl;
	// ================== List Name ====================================
	std::vector<client *>::iterator it = cl->curr_chan->users.begin();
	std::vector<client *>::iterator ite = cl->curr_chan->users.end();

	msg = ":NiceIRC 353 " + cl->getNickname() + " == " + cl->curr_chan->getName() + " :";
	for ( ; it != ite ; it++)
	{
		msg += (*it)->getNickname() + " ";
	}
	msg.pop_back(); /* C++11 ? */
	send(cl->getFd(), (msg + "\r\n").c_str(), msg.length() + 2, 0);
	std::cout << msg << std::endl;
	// ====================== RPL_END_OF_NAMES =========================
	msg = ":NiceIRC 366 " + cl->getNickname() + " " + cl->curr_chan->getName() + " :End of NAMES list";
	send(cl->getFd(), (msg + "\r\n").c_str(), msg.length() + 2, 0);
	std::cout << msg << std::endl;
}

channel*	create_channel(client* cl, std::vector<std::string> cmd, server* serv)
{
	channel*	new_chan = new channel(cmd[1]);
	new_chan->addClient(cl, cmd);
	serv->channels.push_back(new_chan);
	cl->curr_chan = new_chan;
	return (new_chan);
}

void	cmd_join(client* cl, std::vector<std::string> cmd, server* serv)
{
	channel*	curr_chan = NULL;
	if (cmd.size() < 2)
		send(cl->getFd(), (cmd[0] + " :Not enough parameters\r\n").c_str(), cmd[0].length() + 25, 0);
	else if (cmd[1][0] != '#' && cmd[1][0] != '&')
		send(cl->getFd(), (cmd[1] + " :Bad Channel Mask\r\n").c_str(), cmd[1].length() + 20, 0);
	else
	{
		curr_chan = serv->findChannelByName(cmd[1]);

		/* Leave Channel if Client is already in one */
		if (cl->curr_chan != NULL)
		{
			std::cout << "here\n" << std::endl;
			cl->curr_chan->deleteClientFromChan(cl);
			cl->curr_chan = NULL;
		}

		/* Create chan or join it if its exists */
		if (curr_chan == NULL)
		{
			curr_chan = create_channel(cl, cmd, serv);
			norme_client(cl);
		}
		else
		{
			if (curr_chan->addClient(cl, cmd) == 0)
				return ;
			cl->curr_chan = curr_chan;
			sendToChan(cl);
			norme_client(cl);
		}
	}
}
