/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:42:17 by fgomez            #+#    #+#             */
/*   Updated: 2021/12/03 14:50:48 by epfennig         ###   ########.fr       */
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
		send_error_code(cl->getFd(), cl->getNickname(), ":407 recipients. Too many targets.", "", "");
	else if (cmd.size() < 3)
		send_error_code(cl->getFd(), "481", cl->getNickname(), ":No text to send", "");
	else
	{
		for (unsigned int i = 0; i < destinataire.size(); i++)
		{
			if (serv->findClientByName(destinataire[i]) == NULL && serv->findChannelByName(destinataire[i]) == NULL)
			{
				send_error_code(cl->getFd(), "401", cl->getNickname(), cmd[1], ":No such nick/channel");
				return ;
			}
		}
		client	*tmp_cl;
		channel	*tmp_chan;
		msg = ":" + cl->getNickname() + "!" + cl->getUsername() + "@127.0.0.1 " + cl->getCurrMsg();
		for (unsigned int i = 0 ; i < destinataire.size() ; i++)
		{
			tmp_cl		= serv->findClientByName(destinataire[i]);
			tmp_chan	= serv->findChannelByName(destinataire[i]);
			if (tmp_chan != NULL && tmp_chan->modes.find('n') != std::string::npos)
				send_error_code(cl->getFd(), "404", cl->getNickname(), tmp_chan->getName(), ":You cannot send external messages to this channel whilst the +n (noextmsg) mode is set.");
			else if ((destinataire[i][0] == '#' || destinataire[i][0] == '&'))
				sendToChan(cl, msg);
			else if (tmp_cl != NULL && tmp_cl->isAccepted())
				send(tmp_cl->getFd(), msg.c_str(), msg.length(), 0);
		}
	}
}
