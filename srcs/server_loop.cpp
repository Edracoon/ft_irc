/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:44:59 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/16 18:59:54 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void	server_loop(server* serv, int kq, struct kevent change_list, struct kevent event_list[64])
{
	int		n_ev;
	
	char	buffer[512];

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
					bzero(buffer, 512);
					recv(event_list[i].ident, buffer, 512, 0);
					if (std::string(buffer) == "\n")
						;
					else
					{
						std::vector<std::string>	tab = ft_split(std::string(buffer), "\n");
						for (int j = 0 ; !tab[j].empty() ; j++)
							serv->recevMessage(tab[j], event_list, i);
					}
				}
			}
		}
	}
}