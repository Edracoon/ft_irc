/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:44:43 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/23 10:54:43 by epfennig         ###   ########.fr       */
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
			/* Config File Data */
			std::string	serv_accept_connex;
			std::string	location;
			std::string	pass_oper;
			std::string	serv_responsible;
			/* Serv Data */
			std::string					password;
			std::vector<channel *>		channels;
			std::vector<client *>		clients;
	public:
			int							sfd;
	public:
			server();
			~server();

			void	parse_config_file();


			int						acceptClient(int kq, struct kevent change_list);
			void					disconnectClient();
			void					recevMessage(std::string buffer, struct kevent event_list[64], int i);
			void					setPassword(const std::string & pass);
			const std::string &		getPassword(void) const;


			client*					findClientByFd(unsigned long Fd);

};


#endif
