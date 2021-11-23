#include "channel.hpp"

channel::channel(std::string Name)
{
	this->name		= Name;
	this->max_user	= 10;
	this->status	= 'n';	/* No status yet */

}

channel::~channel() {}

int		channel::addClient(client* cl, std::vector<std::string> cmd)  // JOIN d'un client, Verif, etc
{
	if (this->operators.size() == 0) /* It means it's a new channel */
	{
		this->operators.push_back(cl);
		this->users.push_back(cl);
		return (1);
	}
	
	if (this->status == 'p')
	{
		if (cmd.size() < 3)
			send(cl->getFd(), "ERR_PRIVCHANNEEDKEY\r\n", 22, 0);
		else if (cmd[2] != this->password)
			send(cl->getFd(), "ERR_BADCHANNELKEY\r\n", 20, 0);
		else
			this->users.push_back(cl);
		return (1);
	}

	if (this->status == 'i')
	{
		send(cl->getFd(), "ERR_INVITEONLYCHAN\r\n", 21, 0);
		return (0);
	}

	if (this->users.size() == max_user)
	{
		send(cl->getFd(), "ERR_CHANNELISFULL\r\n", 20, 0);
		return (0);
	}
	
	return (1);
}

const std::string&		channel::getName(void) const { return this->name; }
const std::string&		channel::getPassword(void) const { return this->name; }
const std::string&		channel::getTopic(void) const { return this->topic; }

bool					channel::isOperator(std::string user)
{
	(void)user;
	return false;
}

char		 			channel::checkStatus(void) const
{
	return this->status;
}

bool 					channel::checkMode(char mode) const
{
	(void)mode;
	return false;
}

bool					channel::checkBlackList(std::string user) const
{
	(void)user;
	return false;
}

bool					channel::checkMaxUser(void) const { return false; }

void					channel::printListUser(client* cli)
{
	std::vector<client*	>::iterator	it	=	this->users.begin();
	std::vector<client*	>::iterator	ite	=	this->users.end();

	send(cli->getFd(), std::string("$=========< Users in " + name + ">=========$\r\n").c_str(), name.length() + 36, 0);
	for ( ; it != ite ; it++) {
		send(cli->getFd(), ("	- " + (*it)->getNickname() + "\r\n").c_str(), (*it)->getNickname().length() + 7, 0);
	}
}