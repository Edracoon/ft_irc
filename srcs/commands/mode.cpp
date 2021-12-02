#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"
#include "../classes/channel.hpp"

int check_mode(std::vector<std::string>& cmd, client* cl)
{
	std::string		msg;
	bool			error = false;
	for (unsigned int j = 1 ; j < cmd[2].length() ; j++)
	{
		if (cmd[2][j] == 'o' || cmd[2][j] == 'k' || cmd[2][j] == 'v' || cmd[2][j] == 'l' || cmd[2][j] == 'i' || \
			cmd[2][j] == 's' || cmd[2][j] == 'p' || cmd[2][j] == 'b' || cmd[2][j] == 'n' || cmd[2][j] == 't')
			;
		else
		{
			if (error == false) {
				msg = ":NiceIRC 472 " + cl->getNickname() + " " + cmd[2][j] + " :is unknown mode char to me for " + cmd[1] + "\r\n";
				send(cl->getFd(), msg.c_str(), msg.length(), 0);
				error = true;
			}
			std::string::iterator	it = cmd[2].begin() + cmd[2].find(cmd[2][j]);
			cmd[2].erase(it);
		}
	}
	return (0);
}

void	removeMode(client* cl, std::vector<std::string> cmd)
{
	size_t pos;
	for (unsigned int i = 1; i < cmd[2].length(); i++) {
		if ((pos = cl->curr_chan->modes.find(cmd[2][i])) != std::string::npos)
			cl->curr_chan->modes.erase(pos, 1);
	}
}

void	addMode(client* cl, std::vector<std::string> cmd)
{
	for (unsigned int i = 1; i < cmd[2].size(); i++)
	{
		if (cl->curr_chan->modes.find(cmd[2][i]) == std::string::npos)
			cl->curr_chan->modes.push_back(cmd[2][i]);
	}
}

void	cmd_mode(client* cl, std::vector<std::string> cmd, server* serv)
{
	std::string	msg;

	if (cmd.size() < 2)
		send_error_code(cl->getFd(), "461", cl->getNickname(), cmd[0], ":Not enough parameters");
	else if (cmd[1][0] != '#' && cmd[1][0] != '&')
		send_error_code(cl->getFd(), "666", cl->getNickname(), cmd[0], ":We do not handle client modes !");
	else if (serv->findChannelByName(cmd[1]) == NULL)
		send_error_code(cl->getFd(), "403", cl->getNickname(), cmd[1], ":No such channel");
	else if (cmd.size() == 2)
		send_error_code(cl->getFd(), "324", cl->getNickname(), cl->curr_chan->getName() + " :+" + cl->curr_chan->modes, "");
	else
	{
		check_mode(cmd, cl);
		if (cmd[2][0] == '+')
		{
			addMode(cl, cmd);
			msg = ":" + cl->getNickname() + "!" + cl->getUsername() + "@127.0.0.1 " + cmd[0] + " " + cmd[1] + " :" + cmd[2] + "\r\n";
			send(cl->getFd(), msg.c_str(), msg.length(), 0);
		}
		else if (cmd[2][0] == '-')
		{
			removeMode(cl, cmd);
			msg = ":" + cl->getNickname() + "!" + cl->getUsername() + "@127.0.0.1 " + cmd[0] + " " + cmd[1] + " :" + cmd[2] + "\r\n";
			send(cl->getFd(), msg.c_str(), msg.length(), 0);
		}
	}
}
