/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:44:29 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/23 09:51:51 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <iostream>
#include "../../includes/irc.hpp"
#include <vector>
#include "channel.hpp"

#include "parser.hpp"

class client
{
	private:
				std::string					username;
				std::string					nickname;
				bool						accepted;
				
				unsigned long				fd;
				bool						ope;
				channel						curr_chan;

				
				std::string					curr_msg;
	public:
				std::vector<std::string>	nickname_history;
				parser						parser;
				bool						pass;
				bool						nick;

	public:
				client(int Fd);
				~client();

				bool					isAccepted() const;
				void					setUsername(const std::string & Username);
				void					setNickname(const std::string & Nickname);
				const std::string & 	getNickname(void) const;
				const std::string & 	getUsername(void) const;
				unsigned long 			getFd(void) const;

				bool					isOpe(void);

				std::string&			getCurrMsg(void);

				void					joinChannel(channel chan);

};

#include "channel.hpp"

#endif