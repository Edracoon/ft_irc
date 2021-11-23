#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void	cmd_pass(client* cl, std::vector<std::string> cmd, server* serv)
{
	if (cmd.size() < 2)
		send(cl->getFd(), "ERR_NEEDMOREPARAMS\r\n", 21, 0);
	else if (cl->isAccepted() == true)
		send(cl->getFd(), "ERR_ALREADYREGISTRED\r\n", 23, 0);
	else if (cl->isAccepted() == false)
	{
		/* Check for ':' some client are using it */
		if (cmd[1][0] == ':')
			cmd[1] = cmd[1].substr(1);
		if (cmd[1] == serv->getPassword())
			cl->pass = true;
	}
	else
		cl->pass = false;
	
	if (cl->nick == true && cl->pass == true && cl->user == true)
		cl->AcceptClient();
}