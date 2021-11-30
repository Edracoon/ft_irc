/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:34:11 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/30 20:30:00 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

parser::parser()
{
	this->tab[0] = "HELP";		this->tab[1] = "PASS";
	this->tab[2] = "NICK";		this->tab[3] = "USER";
	this->tab[4] = "OPER";		this->tab[5] = "JOIN";
	this->tab[6] = "PRIVMSG";	this->tab[7] = "KILL";
	this->tab[8] = "PART";		this->tab[9] = "MODE";
	this->tab[10] = "KICK";
}

parser::~parser() { }

void	parser::parsing(client* cli, std::string msg, server* serv)
{
	if (cli == NULL)
		return ;
	this->msg	= msg;

	std::vector<std::string>	cmd = ft_split(this->msg, " ", 512);
	/* Checking for prefix in case it's not an operator */
	if (cmd[0][0] == ':' && (cmd[0].substr(1, cmd[0].find(' ')) != cli->getNickname()) && !cli->isOpe())
	{
		send(cli->getFd(), "Server: You canno't prefix a message this way (use your nickname or do not prefix)\r\n", 84, 0);
		return ;
	}
	/* Store prefix in case it's an operator */
	else if (cmd[0][0] == ':' && (cmd[0].substr(1, cmd[0].find(' ')) != cli->getNickname()))
	{
		this->prefix	= cmd[0].substr(1, cmd[0].find(' '));
		this->msg		= msg.substr(cmd[0].substr(1, cmd[0].find(' ')).length() + 2, msg.length());
		cmd = ft_split(this->msg, " ", 512);
	}
	else if (cmd[0][0] == ':' && (cmd[0].substr(1, cmd[0].find(' ')) == cli->getNickname()))
	{
		this->prefix	= cmd[0].substr(1, cmd[0].find(' '));
		this->msg		= msg.substr(cmd[0].substr(1, cmd[0].find(' ')).length() + 2, msg.length());
		cmd = ft_split(this->msg, " ", 512);
	}

	/* Get What is Cmd */
	cmd_type = this->whatIsCmd(cmd[0]);

	/*
	**	HELP -> Proposer cette commande lorsqu'une commande est mal utilisée
	**	PASS <mot de passe>
	**	USER <nom d'utilisateur> <hôte> <nom de serveur> :<nom réel>
	**	NICK <pseudonyme>
	**	OPER <utilisateur> <mot de passe>
	**	JOIN <canal> [<mdp>]
	**	PRIVMSG <destinataire> <texte à envoyer>
	*/

	if (cmd_type == HELP)
		cmd_help(cli);
	else if (cmd_type == PASS)
		cmd_pass(cli, cmd, serv);
	else if (cmd_type == NICK)
		cmd_nick(cli, cmd, serv);
	else if (cmd_type == USER)
		cmd_user(cli, cmd);
	else if (cmd_type == OPER && cli->isAccepted())
		cmd_oper(cli, cmd, serv);
	else if (cmd_type == JOIN && cli->isAccepted())
		cmd_join(cli, cmd, serv);
	else if (cmd_type == PRIVMSG && cli->isAccepted())
		cmd_privmsg(cli, cmd, serv);
	else if ((cmd_type == KILL || cmd[0] == "kill") && cli->isAccepted())
		cmd_kill(cli, cmd, serv);
	else if (cmd_type == PART && cli->isAccepted())
		cmd_part(cli, cmd, serv);
	else if (cmd_type == MODE && cli->isAccepted())
		;
	else if (cmd_type == KICK && cli->isAccepted())
		cmd_kick(cli, cmd, serv);
	else if (cmd_type == MSG && cli->isAccepted())
		sendToChan(cli, cli->getCurrMsg());

	// Reinitialize data between message
	this->prefix.clear();
	this->msg.clear();
	this->cmd_type = -1;
}

int		parser::whatIsCmd(std::string cmd)
{
	for (int i = 0; i < 11 ; i++)
	{
		if (cmd == tab[i] || cmd == "/" + tab[i])
			return (i);
	}
	return (MSG);
}
