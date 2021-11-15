/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:44:29 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/15 17:50:04 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <iostream>
#include <vector>
#include "channel.hpp"


class client
{
	private:
				std::string					username;
				std::string					nickname;
				std::vector<std::string>	nickname_history;
				bool						accepted;
				int							fd;
				bool						ope;
				channel						curr_chan;

	public:
				client(int Fd);
				~client();

				bool				isAccepted() const;
				void				setUsername(const std::string & Username);
				void				setNickname(const std::string & Nickname);
				const std::string & getNickname(void) const;
				const std::string & getUsername(void) const;

				void				joinChannel(channel chan);
				
};

#include "channel.hpp"

#endif