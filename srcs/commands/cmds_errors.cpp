#include "../classes/client.hpp"
#include "../classes/server.hpp"
#include "../classes/parser.hpp"
#include "../classes/channel.hpp"

void	send_error_code(unsigned int fd, std::string error_code, std::string nickname, std::string arg, std::string error_msg)
{
	std::string		msg;
	msg = ":NiceIRC " + error_code + " " + nickname + " " + arg + " " + error_msg + "\r\n";
	send(fd, msg.c_str(), msg.length(), 0);
}
