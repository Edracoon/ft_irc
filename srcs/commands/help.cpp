/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:53:40 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/22 17:53:41 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../classes/client.hpp"

void	cmd_help(client cl)
{
	if (cl.isAccepted() == false)
	{
		send(cl.getFd(), "You need to login first: PASS, NICK, USER\r\n", 43, 0);
		send(cl.getFd(), "PASS <mdp>\r\n", 13, 0);
		send(cl.getFd(), "NICK <pseudonyme>\r\n", 20, 0);
		send(cl.getFd(), "USER <nom d'utilisateur> <hôte> <nom de serveur> :<nom réel>\r\n", 65, 0);
	}
	else
	{
		send(cl.getFd(), "JOIN <canal> [<mdp>]\r\n", 23, 0);
		send(cl.getFd(), "OPER <utilisateur> <mot de passe>\r\n", 36, 0);
		send(cl.getFd(), "NICK <pseudonyme>\r\n", 20, 0);
		send(cl.getFd(), "PRIVMSG <destinataire> <texte à envoyer>\r\n", 44, 0);
	}
}