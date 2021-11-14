#ifndef IDEA_CLASS_IRC_HPP
# define IDEA_CLASS_IRC_HPP

#include <iostream>
#include "idea_class_channel.hpp"
#include "idea_class_clients.hpp"

class irc
{
	private:
			channel		*irc_channels;
			client		*irc_clients;

	public:
			irc();
			~irc();
};

#endif
