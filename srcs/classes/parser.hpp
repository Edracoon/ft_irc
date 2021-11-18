#ifndef PARSER_HPP
# define PARSER_HPP

#include <iostream>
#include <vector>
#include <utility>

class client;

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
				COLON,
				CHAN,		// maybe
				USERNAME,	// maybe
				COMMENT		// maybe
			};

			std::string										msg;
			std::string										tab[20];
			int												ac;
			int												cmd_type;
			std::vector< std::pair<int, std::string> >		tokens;

			parser();
			~parser(void);

			void	parsing(client cl, std::string str);
			int		isCmd(std::string cmd);
			// pass(client, tab);


};

#include "client.hpp"

#endif