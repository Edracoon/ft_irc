#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"
#include "../classes/channel.hpp"

void	cmd_part(client* cl, std::vector<std::string> cmd, server* serv)
{
	channel*	curr_chan = NULL;
	std::string msg;
	if (cmd.size() < 2)
	{
		msg = cmd[0] + " :Not enough parameters\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	curr_chan = serv->findChannelByName(cmd[1]);
	if (curr_chan != NULL && curr_chan->getName() ==  cmd[1])
	{
		if (curr_chan->deleteClientFromChan(cl) == true)
		{
			sendToChan(cl);
			cl->curr_chan = NULL;
			return ;
		}
		else
		{
			msg = cmd[1] + " :You're not on that channel\r\n";
			send(cl->getFd(), msg.c_str(), msg.length(), 0);
			return ;
		}
	}
	msg = cmd[1] + " :No such channel\r\n";
	send(cl->getFd(), msg.c_str(), msg.length(), 0);
}