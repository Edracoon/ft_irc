#include <iostream>
#include <vector>
#include "idea_class_clients.hpp"


class channel
{
	private:
				std::vector<client *>			operators;	// operator list in the channel
				std::vector<int>				modes;		// channels modes
				std::vector<client *>			users;		// users list in the channel
				
	public:

};