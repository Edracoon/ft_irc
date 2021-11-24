/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:03:33 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/24 19:22:59 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <vector>

class	client;

class channel
{
	private:
				std::string						name;
				std::string						password;	// if private
				char							status;		// private ; secret ; invitation
				unsigned int					max_user;

				std::string						topic;
	
	public:
				std::vector<client *>			operators;	// operator list in the channel
				std::vector<client *>			users;		// users list in the channel
				std::vector<std::string>		black_list;	// mode +b
				std::vector<char>				modes;		// channels modes

	public:
				channel(std::string Name);
				~channel();

				int						addClient(client* cl, std::vector<std::string> cmd); // /JOIN d'un client, toutes les etapes de verifications du channel etc
				void					deleteClientFromChan(client *cl);

				const std::string&		getName(void) const;
				const std::string&		getPassword(void) const;
				const std::string&		getTopic(void) const;
				bool					isOperator(std::string user);

				char 					checkStatus(void) const;
				bool 					checkMode(char mode) const;
				bool					checkBlackList(std::string user) const;
				bool					checkMaxUser(void) const;

				void					printListUser(client* cli);

				client*					findClientByName(std::string nickname);

};

#include "client.hpp"

#endif