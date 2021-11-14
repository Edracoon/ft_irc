#ifndef IDEA_CLASS_IRC_HPP
# define IDEA_CLASS_IRC_HPP

#include <iostream>
#include "channel.hpp"
#include "idea_class_clients.hpp"

class irc
{
	private:
			std::string					password;
			std::vector<channel *>		irc_channels;
			std::vector<client *>		irc_clients;

	public:
			irc();
			~irc();
};

#endif
