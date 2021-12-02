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

		if (cmd[1][0] != '#' || cmd.size() == 1)
		{
			for ( ; it != ite; it++)
			{
				msg = ":NiceIRC 322 " + cl->getNickname() + " " + (*it)->getName() + " " + ft_itos((*it)->getNbuser()) + " :[+" + (*it)->modes + "]\r\n";
				send(cl->getFd(), msg.c_str(), msg.length(), 0);
			}
		}
		else
		{
			std::vector<std::string> channel = ft_split(cmd[1], ",", 512);

			std::vector<std::string>::iterator it_name = channel.begin();
			std::vector<std::string>::iterator ite_name = channel.end();

			for ( ; it_name != ite_name; it_name++) {
				for ( ; it != ite; it++) {
					if (*it_name == (*it)->getName())
					{
						msg = ":NiceIRC 322 " + cl->getNickname() + " " + (*it)->getName() + " " + ft_itos((*it)->getNbuser()) + " :[+" + (*it)->modes + "]\r\n";
						send(cl->getFd(), msg.c_str(), msg.length(), 0);
						it_name++;
					}
				}
			}
		}
		msg = ":NiceIRC 323 " + cl->getNickname() + " :End of channel list.\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}
}
