/* ************************************************************************** */
/*                                      */
/*                            :::     ::::::::   */
/*   kill.cpp                                 :+:   :+:    :+:   */
/*                          +:+ +:+       +:+    */
/*   By: epfennig <epfennig@student.42.fr>      +#+  +:+       +#+    */
/*                        +#+#+#+#+#+   +#+     */
/*   Created: 2021/11/23 14:03:44 by fgomez   #+#  #+#          */
/*   Updated: 2021/11/23 14:57:59 by epfennig       ###   ########.fr    */
/*                                      */
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
        send(tmp->getFd(), ("You have been banned\n" + cmd[2] + "\r\n").c_str(), cmd[2].length() + 25, 0);
        close(tmp->getFd());
        
        std::vector<client *>::iterator it = serv.clients.begin();
        std::vector<client *>::iterator ite = serv.clients.end();
        for ( ; it != ite ; it++) {
            if ((*it)->getNickname() == tmp->getNickname())
                serv.clients.erase(it);
        }
    }
}
