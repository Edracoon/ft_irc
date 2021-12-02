#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"
#include "../../includes/irc.hpp"

void	cmd_topic(client* cl, std::vector<std::string> cmd, server* serv)
{
	std::string msg;
	channel*	curr_chan = NULL;

	if (cl->curr_chan == NULL)
	{
		send_error_code(cl->getFd(), "461", cl->getNickname(), cmd[0], ":Not enough parameters");
		send_error_code(cl->getFd(), "650", cl->getNickname(), cmd[0], ":<channel> [:<topic>]");
	}
	else if (cmd.size() == 2)
	{
		if (cmd[1][0] == '#' || cmd[1][0] == '&')
		{
			curr_chan = serv->findChannelByName(cmd[1]);

			std::vector<client *>::iterator it = curr_chan->users.begin();
			std::vector<client *>::iterator ite = curr_chan->users.end();
			
			if (curr_chan != NULL)
			for ( ; it != ite; it++)
			{
				msg = ":NiceIRC 322 " + cl->getNickname() + " " + (*it)->getName() + " " + ft_itos((*it)->getNbuser()) + " :[+" + (*it)->modes + "]\r\n";
				send(cl->getFd(), msg.c_str(), msg.length(), 0);
			}
		}
		else if (cl->curr_chan == NULL)
		{
			// std::vector<std::string> channel = ft_split(cmd[1], ",", 512);

			// std::vector<std::string>::iterator it_name = channel.begin();
			// std::vector<std::string>::iterator ite_name = channel.end();

			// for ( ; it_name != ite_name; it_name++) {
			// 	for ( ; it != ite; it++) {
			// 		if (*it_name == (*it)->getName())
			// 		{
			// 			msg = ":NiceIRC 322 " + cl->getNickname() + " " + (*it)->getName() + " " + ft_itos((*it)->getNbuser()) + " :[+" + (*it)->modes + "]\r\n";
			// 			send(cl->getFd(), msg.c_str(), msg.length(), 0);
			// 			it_name++;
			// 		}
			// 	}
			// }
		}
		// msg = ":NiceIRC 323 " + cl->getNickname() + " :End of channel list.\r\n";
		// send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}
}