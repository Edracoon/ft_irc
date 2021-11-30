/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:34:03 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/30 13:32:24 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				KILL,
				PART,
				MODE,
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
			std::string										tab[11];	// Tableau des commandes
			int												ac;			// Nombre d'argument

			int												cmd_type;	// Categorie de commande
			std::string										cmd;		// OPER / JOIN / PRIVMSG etc ...

			std::vector< std::pair<int, std::string> >		tokens;

			parser();
			~parser(void);

			void	parsing(client* cli, std::string str, server* serv);
			int		whatIsCmd(std::string cmd);
};

/* === CMD FUNCTIONS === */
void						cmd_help(client* cl);
void						cmd_pass(client* cl, std::vector<std::string> cmd, server* serv);
void						cmd_user(client* cl, std::vector<std::string> cmd);
void						cmd_nick(client* cl, std::vector<std::string> cmd, server* serv);
void						cmd_oper(client* cl, std::vector<std::string> cmd, server* serv);
void						cmd_privmsg(client* cl, std::vector<std::string> cmd,  server* serv);
void						cmd_kill(client* cl, std::vector<std::string> cmd, server* serv);
void						cmd_join(client* cl, std::vector<std::string>	cmd, server* serv);
void						sendToChan(client* cl);
void						cmd_part(client* cl, std::vector<std::string> cmd, server* serv);

#include "client.hpp"
#include "../../includes/irc.hpp"

#endif