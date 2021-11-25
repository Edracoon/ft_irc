#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_pass(client* cl, std::vector<std::string> cmd, server* serv)
{
	if (cmd.size() < 2)
		send(cl->getFd(), (cmd[0] + " :Not enough parameters\r\n").c_str(), cmd[0].length() + 25, 0);
	else if (cl->isAccepted() == true)
		send(cl->getFd(), ":Unauthorized command (already registered)\r\n", 44, 0);
	else if (cl->isAccepted() == false)
	{
		/* Check for ':' some client are using it */
		if (cmd[1][0] == ':')
			cmd[1] = cmd[1].substr(1);
		if (cmd[1] == serv->getPassword())
			cl->pass = true;
		else
			send(cl->getFd(), ":Password incorrect\r\n", 21, 0);
	}
	else
		cl->pass = false;
	
	if (!cl->isAccepted() && cl->nick == true && cl->pass == true && cl->user == true)
	{
		std::string msg = "Welcome to the Internet Relay Network " + cl->getNickname() + "!" + cl->getUsername() + "@*\r\n";
		send(cl->getFd(), msg.c_str(), msg.length(), 0);
		cl->AcceptClient();
	}
}