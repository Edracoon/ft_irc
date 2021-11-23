#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"

void    cmd_nick(client cl, std::vector<std::string> cmd,  server serv)
{
    std::cout << "cmd[i] = '" << cmd[1] << "'" << std::endl;
    if  (cmd.size() < 2)
        send(cl.getFd(), "ERR_NONICKNAMEGIVEN\r\n", 22, 0);
    else if (serv.findClientByName(cmd[1]) != NULL)
        send(cl.getFd(), "ERR_NICKNAMEINUSE\r\n", 20, 0);
    else
    {
        cl.setNickname(cmd[1]);
        cl.nick = true;
        cl.nickname_history.push_back(cmd[1]);
    }
}