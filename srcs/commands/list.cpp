#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"
#include "../../includes/irc.hpp"

void	cmd_list(client* cl, std::vector<std::string> cmd, server* serv)
{
	std::string msg;
	if (cmd.size() == 2)
	{
		std::vector<channel *>::iterator it = serv->channels.begin();
		std::vector<channel *>::iterator ite = serv->channels.end();
		
		for ( ; it != ite; it++)
		{
			msg = ":NiceIRC 322 " + cl->getNickname() + " " + (*it)->getName() + " " + ft_itos((*it)->getNbuser()) + " :[+" + (*it)->modes + "]\r\n";
			send(cl->getFd(), msg.c_str(), msg.length(), 0);
		}
		msg = ":NiceIRC 323 " + cl->getNickname() + " :End of channel list.\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}
}
