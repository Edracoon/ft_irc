#ifndef PARSER_HPP
# define PARSER_HPP

#include <iostream>
#include <vector>
#include <utility>

class client;
class server;

class parser
{
	public:
			enum msg_type {
				HELP,
				PASS,
				NICK,
				USER,
				OPER,
				JOIN,
				PRIVMSG,
				MSG
			};

			enum token_type {
				CMD,
				ARG,
				COLON,
				CHAN,		// maybe
				USERNAME,	// maybe
				COMMENT		// maybe
			};

			std::string										msg;		// Buffer envoyé au parser
			std::string										prefix;		// if prefix, print it in place of nickname
			std::string										tab[7];		// Tableau des commandes
			int												ac;			// Nombre d'argument

			int												cmd_type;	// Categorie de commande
			std::string										cmd;		// OPER / JOIN / PRIVMSG etc ...

			std::vector< std::pair<int, std::string> >		tokens;

			parser();
			~parser(void);

			void	parsing(client cl, std::string str, server serv);
			int		whatIsCmd(std::string cmd);
			// pass(client, tab);

};

/* === CMD FUNCTIONS === */
void						cmd_help(client cl);
void						cmd_pass(client cl, std::vector<std::string> cmd, server serv);
void						cmd_user(client cli, std::vector<std::string> cmd);
void						cmd_nick(client cl, std::vector<std::string> cmd, server serv);
void						cmd_oper(client cli, std::vector<std::string> cmd, server serv);


#include "client.hpp"
#include "../../includes/irc.hpp"

#endif