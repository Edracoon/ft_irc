#include "parser.hpp"

parser::parser() { }

parser::~parser() { }

void	parser::parsing(client cli, std::string msg)
{
	this->msg	= msg;
	
	if (!cli.isAccepted())
		this->cmd_type	= CMD_CONNEX;
	
	std::vector<std::string> test = ft_split(msg, " ", 1);
	for (int i = 0 ; i <= 2 ; i++)
		std::cout << "test[i] = " << test[i] << std::endl;
}
