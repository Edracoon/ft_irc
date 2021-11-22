#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void    cmd_pass(client cl, std::vector<std::string> cmd, server serv)
{
    if (cmd.size() != 2)
        Error_argument(cl, 1);
    else if (cmd[1] == serv.getPassword())
        cl.pass = true;
    else
        cl.pass = false;
}