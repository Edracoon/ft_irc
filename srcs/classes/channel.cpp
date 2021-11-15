#include "channel.hpp"

channel::channel()
{
	this->max_user = 10;
}

channel::~channel() {}

int						channel::addClient() { return 1; } // /JOIN d'un client, toutes les etapes de verifications du channel etc

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