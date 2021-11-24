/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:38:47 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/24 17:16:00 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_oper(client* cli, std::vector<std::string> cmd, server* serv)
{
	(void)cli;
	(void)cmd;
	(void)serv;
	// serv->findChannelByName(cl->curr_chan->getName())->findClientByName(cl->getNickname()).setNickname(cmd[1]);
}