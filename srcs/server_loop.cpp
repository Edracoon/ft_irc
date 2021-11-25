/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:44:59 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/25 18:04:02 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void	server_loop(server* serv, int kq, struct kevent change_list, struct kevent event_list[64])
{
	int		n_ev;
	
	char	buffer[1024];

	while (1)
	{
		if ((n_ev = kevent(kq, NULL, 0, event_list, 64, NULL)) < 0 )
			exit_error("kevent failed");

		else if (n_ev > 0)
		{
			
			/* Boucler sur le nombre de nouveaux events */
			for (int i = 0; i < n_ev ; i++)
			{
				/* Handle kevent error */
				if (event_list[i].flags & EV_ERROR)
					exit_error("kevent: EV_ERROR");

				/* Client disconnect */
				if (event_list[i].flags & EV_EOF)
				{
					std::cout << "Client[" << event_list[i].ident << "] disconnected !" << std::endl;
					
					client*	tmp = serv->findClientByFd(event_list[i].ident);
					serv->deleteClient(tmp);
					close(event_list[i].ident);
				}

				/* Accept new clients */
				else if (event_list[i].ident == (unsigned long)serv->sfd)
				{
					if (serv->acceptClient(kq, change_list))
						break ;
				}

				/* Read client messages that are already accepted */
				else if (event_list[i].filter & EVFILT_READ)
				{
					bzero(buffer, 1024);
					recv(event_list[i].ident, buffer, 1024, 0);
					if (ft_strlen(buffer) > 510)
					{
						send(event_list[i].ident, "Limit message to 512 characteres\r\n", 34, 0);
						continue ;
					}
					client* temp = serv->findClientByFd(event_list[i].ident);
					if (std::string(buffer) == "\r\n")
						;
					/* Rebuild string if ctrl+D is pressed by client */
					else if (std::string(buffer).find("\n") == std::string::npos)
					{
						temp->getCurrMsg() += std::string(buffer);
					}
					else
					{
						std::vector<std::string>	tab;
						if (!(temp->getCurrMsg().empty()))
						{
							if (!(std::string(buffer).empty()))
								temp->getCurrMsg() += std::string(buffer);
							tab = ft_split(temp->getCurrMsg(), "\n", 512);
						}
						else
						{
							temp->getCurrMsg() = std::string(buffer);
							tab = ft_split(temp->getCurrMsg(), "\n", 512);
						}
						for (unsigned long j = 0 ; !tab[j].empty() ; j++)
						{
							serv->recevMessage(tab[j], event_list, i);
						}
						temp->getCurrMsg().clear();
					}
				}
			}
		}
	}
}