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
		msg = ":NiceIRC 461 " + cl->getNickname() + " " + cmd[0] + " :Not enough parameters\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	curr_chan = serv->findChannelByName(cmd[1]);
	if (curr_chan == NULL)
	{
		msg = ":NiceIRC 401 " + cl->getNickname() + " " + cmd[1] + " :No such nick/channel\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}
	else if ((curr_chan != NULL && cl->curr_chan && cl->curr_chan->getName() != cmd[1]) || cl->curr_chan == NULL)
	{
		msg = ":NiceIRC 442 " + cl->getNickname() + " " + cmd[1] + " :You're not on that channel\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (curr_chan != NULL && curr_chan->getName() ==  cmd[1])
	{
		if (cl->getCurrMsg().find(':') != std::string::npos)
			msg = ":" + cl->getNickname() + "!" + cl->getUsername() + "@127.0.0.1 PART " + cmd[1] + " :" + ft_split(cl->getCurrMsg(), ":", 1)[1];
		else
			msg = ":" + cl->getNickname() + "!" + cl->getUsername() + "@127.0.0.1 PART :" + cmd[1] + "\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
		sendToChan(cl, msg);
		curr_chan->deleteClientFromChan(cl);
		cl->curr_chan = NULL;
		return ;
	}
}