/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:44:29 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/23 11:42:53 by epfennig         ###   ########.fr       */
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
				bool						user;

	public:
				client(int Fd);
				~client();

				bool					isAccepted() const;
				void					AcceptClient();
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