#ifndef PARSER_HPP
# define PARSER_HPP

#include <iostream>
#include <vector>
#include <utility>

class parser
{
	public:
			enum cmd_type {
				CMD_CONNEX,
				CMD_CHANNEL,
				CMD_USER,
				CMD_DIVERS,
				MSG_CHAN
			};

			enum token_type {
				CMD,
				ARG,
				CHAN,		// maybe
				USERNAME,	// maybe
				COMMENT		// maybe
			};

			int												cmd_type;
			std::vector< std::pair<int, std::string> >		tab;

			
};

#endif