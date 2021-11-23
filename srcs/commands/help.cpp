/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:53:40 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/23 14:15:09 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"

void	cmd_help(client* cl)
{
	if (cl->isAccepted() == false)
	{
		send(cl->getFd(), "You need to login first: PASS, NICK, USER\r\n", 43, 0);
		send(cl->getFd(), "1. PASS <mdp>\r\n", 16, 0);
		send(cl->getFd(), "2. NICK <pseudonyme>\r\n", 23, 0);
		send(cl->getFd(), "3. USER <nom d'utilisateur> <hôte> <nom de serveur> :<nom réel>\r\n", 68, 0);
	}
	else
	{
		send(cl->getFd(), "$=========< Help Page >=========$\r\n", 36, 0);
		send(cl->getFd(), "-> JOIN <canal> [<mdp>]\r\n", 26, 0);
		send(cl->getFd(), "-> OPER <utilisateur> <mot de passe>\r\n", 39, 0);
		send(cl->getFd(), "-> NICK <pseudonyme>\r\n", 23, 0);
		send(cl->getFd(), "-> PRIVMSG <destinataire> <texte à envoyer>\r\n", 47, 0);
	}
}