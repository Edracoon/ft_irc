/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendtochan.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:42:23 by fgomez            #+#    #+#             */
/*   Updated: 2021/11/25 12:54:19 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	sendToChan(client* cl)
{
	if (cl->curr_chan)
	{
		std::vector<client *>::iterator it = cl->curr_chan->users.begin();
		std::vector<client *>::iterator ite = cl->curr_chan->users.end();
		
		for ( ; it != ite ; it++)
		{
			if ((*it)->getNickname() == cl->getNickname())
				continue ;
			std::string msg = cl->getNickname() + ": " + cl->getCurrMsg();
			send((*it)->getFd(), msg.c_str() , msg.length(), 0);
		}
	}
}
