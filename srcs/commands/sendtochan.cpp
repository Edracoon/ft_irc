/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendtochan.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:42:23 by fgomez            #+#    #+#             */
/*   Updated: 2021/11/24 10:07:00 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	sendToChan(client* cl, std::vector<std::string> cmd)
{
	if (cl->curr_chan)
	{
		std::vector<client *>::iterator it = cl->curr_chan->users.begin();
		std::vector<client *>::iterator ite = cl->curr_chan->users.end();
		
		for ( ; it != ite ; it++)
		{
			// if ((*it)->getNickname() == cl->getNickname())
			// 	continue ;
			for (unsigned int i = 0; i < cmd.size(); i++)
				send((*it)->getFd(), (cmd[i] + "\r\n").c_str() , cmd[i].length() + 3, 0);
		}
	}
}