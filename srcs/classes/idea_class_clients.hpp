#ifndef IDEA_CLASS_CLIENTS_HPP
# define IDEA_CLASS_CLIENTS_HPP

#include <iostream>

class	channel;

class client
{
	private:
				std::string					username;
				std::string					nickname;
				std::vector<std::string>	nickname_history;
				int							fd;
				channel						curr_chan;

	public:
				client();
				~client();
};

#include "channel.hpp"

#endif