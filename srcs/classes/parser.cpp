#include "parser.hpp"

parser::parser()
{
	this->tab[0] = "JOIN";
	this->tab[1] = "NICK";
	this->tab[2] = "PASS";
	this->tab[3] = "USER";
	this->tab[0] = "JOIN";
	this->tab[1] = "NICK";
	this->tab[2] = "PASS";
	this->tab[3] = "USER";
	this->tab[0] = "JOIN";
	this->tab[1] = "NICK";
	this->tab[2] = "PASS";
	this->tab[3] = "USER";
	this->tab[0] = "JOIN";
	this->tab[1] = "NICK";
	this->tab[2] = "PASS";
	this->tab[3] = "USER";
	this->tab[0] = "JOIN";
	this->tab[1] = "NICK";
	this->tab[2] = "PASS";
	this->tab[3] = "USER";
}

parser::~parser() { }

void	parser::parsing(client cli, std::string msg)
{
	this->msg	= msg;
	
	if (!cli.isAccepted())
		this->cmd_type	= CMD_CONNEX;
	
	std::vector<std::string> iscmd = ft_split(msg, " ", 1);
	this->isCmd(iscmd[0]);
	for (unsigned long i = 0 ; i < iscmd.size() ; i++)
		std::cout << "test[i] = '" << iscmd[i] << "'" <<  std::endl;
}

int	parser::isCmd(std::string cmd)
{
	for (int i = 0; i < 20; i++)
	{
		if (cmd == tab[i])
		{
			return (i);
		}
	}
	return (-1);
}