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

void	parser::parsing(client cli, std::string msg, server serv)
{
	this->msg	= msg;

	std::vector<std::string>	cmd = ft_split(this->msg, " ", 512);

	/* Checking for prefix in case it's not an operator */
	if (cmd[0][0] == ':' && (cmd[0].substr(1, cmd[0].find(' ')) != cli.getNickname()) && !cli.isOpe())
	{
		send(cli.getFd(), "Server: You canno't prefix a message this way (use your nickname or do not prefix)\r\n", 84, 0);
		return ;
	}
	/* Store prefix in case it's an operator */
	else if (cmd[0][0] == ':' && (cmd[0].substr(1, cmd[0].find(' ')) != cli.getNickname()))
	{
		this->prefix	= cmd[0].substr(1, cmd[0].find(' '));
		this->msg		= msg.substr(cmd[0].substr(1, cmd[0].find(' ')).length() + 2, msg.length());
	}
	std::cout << "prefix: " << (this->prefix.empty() ? cli.getNickname() : this->prefix);
	std::cout << " - msg = " << this->msg << std::endl;

	if (this->prefix.empty())
		cmd_type = this->whatIsCmd(cmd[0]);
	else if (!(this->prefix.empty()))
		cmd_type = this->whatIsCmd(cmd[1]);

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
	else if (cmd_type == PASS && !cli.isAccepted())
		cmd_pass(cli, cmd, serv);
	else if (cmd_type == NICK)
		;
	else if (cmd_type == USER && !cli.isAccepted())
		cmd_user(cli, cmd, serv);
	else if (cmd_type == OPER && cli.isAccepted())
		;
	else if (cmd_type == JOIN && cli.isAccepted())
		;
	else if (cmd_type == PRIVMSG && cli.isAccepted())
		;
	else if (cmd_type == MSG && cli.isAccepted())
		;

	// Reinitialize data between message
	this->prefix.clear();
	this->msg.clear();
	this->cmd_type = -1;
}

int		parser::whatIsCmd(std::string cmd)
{
	for (int i = 0; i < 7 ; i++)
	{
		if (cmd == tab[i] || cmd == "/" + tab[i])
			return (i);
	}
	return (7);
}
