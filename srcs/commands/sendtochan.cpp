/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendtochan.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:42:23 by fgomez            #+#    #+#             */
/*   Updated: 2021/11/24 13:33:31 by fgomez           ###   ########.fr       */
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
			send((*it)->getFd(), ("From " + cl->getNickname() + ": " + cl->getCurrMsg()).c_str() , cl->getNickname().length() + cl->getCurrMsg().length() + 9, 0);
		}
	}
}