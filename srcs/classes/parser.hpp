#ifndef PARSER_HPP
# define PARSER_HPP

#include <iostream>
#include <vector>
#include <utility>

class parser
{
	public:
			enum cmd_type {
				CMD_LOGIN,
				CMD_CHANNEL,
				CMD_USER,
				CMD_DIVER,
				MSG_CHAN
			};

			enum token_type {
				CMD,
				CHAN,
				USERNAME,
				COMMENT
			};

			int												cmd_type;
			std::vector< std::pair<int, std::string> >		tab;


};

#endif