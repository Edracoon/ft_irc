/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:44:29 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/17 15:50:35 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <iostream>
#include "../../includes/irc.hpp"
#include <vector>
#include "channel.hpp"

class client
{
	private:
				std::string					username;
				std::string					nickname;
				std::vector<std::string>	nickname_history;
				bool						accepted;
				unsigned long				fd;
				bool						ope;
				channel						curr_chan;

				/* parser					client_parser; */
				std::string					curr_msg;

	public:
				client(int Fd);
				~client();

				void					login(std::string message, char type, std::string password);
				bool					isAccepted() const;
				void					setUsername(const std::string & Username);
				void					setNickname(const std::string & Nickname);
				const std::string & 	getNickname(void) const;
				const std::string & 	getUsername(void) const;
				unsigned long 			getFd() const;

				std::string&			getCurrMsg(void);

				void					joinChannel(channel chan);

};

#include "channel.hpp"

#endif