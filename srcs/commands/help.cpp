/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:53:40 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/25 12:53:44 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"

void	cmd_help(client* cl)
{
	if (cl->isAccepted() == false)
	{
		send(cl->getFd(), "You need to login first: PASS, NICK, USER\r\n", 43, 0);
		send(cl->getFd(), "1. PASS <mdp>\r\n", 15, 0);
		send(cl->getFd(), "2. USER <nom d'utilisateur> <hôte> <nom de serveur> :<nom réel>\r\n", 67, 0);
		send(cl->getFd(), "3. NICK <pseudonyme>\r\n", 22, 0);
	}
	else
	{
		send(cl->getFd(), "$=========< Help Page >=========$\r\n", 35, 0);
		send(cl->getFd(), "-> JOIN <canal> [<mdp>]\r\n", 25, 0);
		send(cl->getFd(), "-> OPER <utilisateur> <mot de passe>\r\n", 38, 0);
		send(cl->getFd(), "-> NICK <pseudonyme>\r\n", 22, 0);
		send(cl->getFd(), "-> PRIVMSG <destinataire> <texte à envoyer>\r\n", 46, 0);
	}
}