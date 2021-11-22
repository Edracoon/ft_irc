#include "parser.hpp"

parser::parser()
{
	this->tab[0] = "HELP";
	this->tab[1] = "PASS";
	this->tab[2] = "NICK";
	this->tab[3] = "USER";
	this->tab[4] = "OPER";
	this->tab[5] = "JOIN";
	this->tab[6] = "PRIVMSG";
}

parser::~parser() { }

void	parser::parsing(client cli, std::string msg)
{
	this->msg	= msg;
	(void)cli;

	std::vector<std::string>	cmd = ft_split(msg, " ", 1);
	cmd_type = this->whatIsCmd(cmd[0]);				// Recup cmd type via enum, faciliter le parsing

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
		;
	else if (cmd_type == PASS)
		;
	else if (cmd_type == NICK)
		;
	else if (cmd_type == USER)
		;
	else if (cmd_type == OPER)
		;
	else if (cmd_type == JOIN)
		;
	else if (cmd_type == PRIVMSG)
		;
	else if (cmd_type == MSG)
		;
}

int		parser::whatIsCmd(std::string cmd)
{
	for (int i = 0; i < 20; i++)
	{
		if (cmd == tab[i])
			return (i);
	}
	return (7);
}
