#ifndef IDEA_CLASS_CHANNEL_HPP
# define IDEA_CLASS_CHANNEL_HPP

#include <iostream>
#include <vector>

class	client;

class channel
{
	private:
				std::string						name;
				std::vector<client *>			operators;	// operator list in the channel
				std::vector<client *>			users;		// users list in the channel

				std::string						topic;
				std::vector<int>				modes;		// channels modes
				
				
	public:
				channel();
				~channel();

};

#include "idea_class_clients.hpp"

#endif