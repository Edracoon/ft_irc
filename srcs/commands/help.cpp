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

void	Error_argument(client cl, int cmd_type)
{
	if (cmd_type == 1)
		send(cl.getFd(), "PASS <mdp>\r\n", 13, 0);
	else if (cmd_type == 2)
		send(cl.getFd(), "NICK <pseudonyme>\r\n", 20, 0);
	else if (cmd_type == 3)
		send(cl.getFd(), "USER <nom d'utilisateur> <hôte> <nom de serveur> :<nom réel>\r\n", 65, 0);
	else if (cmd_type == 4)
		send(cl.getFd(), "OPER <utilisateur> <mot de passe>\r\n", 36, 0);
	else if (cmd_type == 5)
		send(cl.getFd(), "JOIN <canal> [<mdp>]\r\n", 23, 0);
	else if (cmd_type == 6)
		send(cl.getFd(), "PRIVMSG <destinataire> <texte à envoyer>\r\n", 44, 0);
	send(cl.getFd(), "If you need help : /HELP\r\n", 27, 0);
}