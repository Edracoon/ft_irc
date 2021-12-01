#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"
#include "../classes/channel.hpp"

int check_mode(std::vector<std::string> cmd)
{
	for (unsigned int j = 1; j < cmd[2].size(); j++)
	{
		if (cmd[2][j] == 'o')
			return j;
		else if (cmd[2][j] == 'k')
			return j;
		else if (cmd[2][j] == 'v')
			return j;
		else if (cmd[2][j] == 'l')
			return j;
		else if (cmd[2][j] == 'i')
			return j;
		else if (cmd[2][j] == 's')
			return j;
		else if (cmd[2][j] == 'p')
			return j;
		else if (cmd[2][j] == 'b')
			return j;
		else if (cmd[2][j] == 'n')
			return j;
		else if (cmd[2][j] == 't')
			return j;
	}
	return (0);
}

void	removeMode(client* cl, std::vector<std::string> cmd)
{
	for (unsigned int i = 1; i < cmd[2].size(); i++)
		cl->curr_chan->modes.erase(cmd[2][i]);
}

void	addMode(client* cl, std::vector<std::string> cmd)
{
	for (unsigned int i = 1; i < cmd[2].size(); i++)
		cl->curr_chan->modes.push_back(cmd[2][i]);
}

void	cmd_mode(client* cl, std::vector<std::string> cmd, server* serv)
{
	std::string msg;
	int i;

	if (cmd.size() < 2)
	{
		msg = ":NiceIRC 461 " + cl->getNickname() + " " + cmd[0] + " :Not enough parameters\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
	}	
	else if (cmd[1][0] == '#' || cmd[1][0] == '&')
	{
		if (!serv->findChannelByName(cmd[1]))
		{
			msg = ":NiceIRC 403 " + cl->getNickname() + " " + cmd[1] + " :No such channel\r\n";
			send(cl->getFd(), msg.c_str(), msg.length(), 0);
		}
		else if (cmd.size() < 3)
		{
			msg = ":NiceIRC 324 " + cl->getNickname() + " " + cl->curr_chan->getName() + " :+" + cl->curr_chan->modes + "\r\n";
			send(cl->getFd(), msg.c_str(), msg.length(), 0);
		}
		else
		{
			if ((i = check_mode(cmd)) == 0)
			{
				msg = ":NiceIRC 324 " + cl->getNickname() + " " + cmd[2][i] + " :is unknown mode char to me for " + cl->curr_chan->getName() + "\r\n";
				send(cl->getFd(), msg.c_str(), msg.length(), 0);
				return ;
			}
			if (cmd[2][0] == '+')
			{
				addMode(cl, cmd);
				msg = ":" + cl->getNickname() + "!" + cl->getUsername() + "@127.0.0.1 " + cmd[0] + " " + cmd[1] + " :" + cmd[2];
				send(cl->getFd(), msg.c_str(), msg.length(), 0);
			}
			else if (cmd[2][0] == '-')
			{
				removeMode(cl, cmd);
				msg = ":" + cl->getNickname() + "!" + cl->getUsername() + "@127.0.0.1 " + cmd[0] + " " + cmd[1] + " :" + cmd[2];
				send(cl->getFd(), msg.c_str(), msg.length(), 0);
			}
		}
	}
}