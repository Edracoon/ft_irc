/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:44:43 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/23 09:47:01 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include "channel.hpp"
#include "client.hpp"
// #include ""
#include "../../includes/irc.hpp"

class server
{
	private:
			std::string					password;
	public:
			std::vector<channel *>		channels;
			std::vector<client *>		clients;
			int							sfd;
	public:
			server();
			~server();

			int						acceptClient(int kq, struct kevent change_list);
			void					disconnectClient();
			void					recevMessage(std::string buffer, struct kevent event_list[64], int i);
			void					setPassword(const std::string & pass);
			const std::string &		getPassword(void) const;


			client*					findClientByFd(unsigned long Fd);
			client*					findClientByName(std::string name);

};


#endif
