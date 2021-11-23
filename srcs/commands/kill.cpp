/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:03:44 by fgomez            #+#    #+#             */
/*   Updated: 2021/11/23 14:33:38 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_kill(client* cl, std::vector<std::string> cmd, server serv)
{
    if (cl->isOpe() == false)
        send(cl->getFd(), "ERR_NOPRIVILEGES\r\n", 19, 0);
    else if (cmd.size() < 3)
        send(cl->getFd(), "ERR_NEEDMOREPARAMS\r\n", 21, 0);
    else if (serv.findClientByName(cmd[1]) == NULL)
            send(cl->getFd(), "ERR_NOSUCHNICK\r\n", 17, 0);
    else
    {
        client *tmp = serv.findClientByName(cmd[1]);
        send(tmp->getFd(), "you have been banned\r\n", 23, 0);
        send(tmp->getFd(), cmd[2].c_str(), cmd[2].length(), 0);
        send(tmp->getFd(), "\r\n", 3, 0);
        close(tmp->getFd());
    }
}