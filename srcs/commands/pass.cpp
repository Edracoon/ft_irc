#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void    cmd_pass(client cl, std::vector<std::string> cmd, server serv)
{
    if (cmd.size() < 2)
        send(cl.getFd(), "ERR_NEEDMOREPARAMS \r\n", 22, 0);
    else if (cl.isAccepted() == true)
        send(cl.getFd(), "ERR_ALREADYREGISTRED \r\n", 24, 0);
    else if (cmd[1] == serv.getPassword())
        cl.pass = true;
    else
        cl.pass = false;
}