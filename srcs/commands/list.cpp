#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"
#include "../../includes/irc.hpp"

void	cmd_list(client* cl, std::vector<std::string> cmd, server* serv)
{
	std::string msg;

	std::vector<channel *>::iterator it = serv->channels.begin();
	std::vector<channel *>::iterator ite = serv->channels.end();
	if (cmd.size() == 1) // nc sans l'espace a la fin
	{
		for ( ; it != ite; it++)
			send_error_code(cl->getFd(), "332", cl->getNickname(), (*it)->getName() + " " + ft_itos((*it)->getNbuser()), ":[+" + (*it)->modes + "]");
	}
	else if (cmd.size() == 2)
	{
		std::vector<std::string> channel = ft_split(cmd[1], ",", 512);

		std::vector<std::string>::iterator it_name = channel.begin();
		std::vector<std::string>::iterator ite_name = channel.end();

		for ( ; it_name != ite_name; it_name++)
		{
			it = serv->channels.begin();
			for ( ; it != ite; it++) {
				if (*it_name == (*it)->getName() && (*it)->modes.find('p') == std::string::npos && (*it)->modes.find('s') == std::string::npos)
					send_error_code(cl->getFd(), "332", cl->getNickname(), (*it)->getName() + " " + ft_itos((*it)->getNbuser()), ":[+" + (*it)->modes + "]");
				else if (*it_name == (*it)->getName() && (*it)->modes.find('p') != std::string::npos && (*it)->modes.find('s') == std::string::npos)
					send_error_code(cl->getFd(), "332", cl->getNickname(), "* " + ft_itos((*it)->getNbuser()), ":");
			}
		}
	}
	send_error_code(cl->getFd(), "332", cl->getNickname(), ":End of channel list.", "");
}
