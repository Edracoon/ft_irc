/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:45:05 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/16 00:33:49 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void	exit_error(std::string error)
{
	std::cout << "Error: "<< error << std::endl;
	exit(EXIT_FAILURE);
}

const char*	 ft_itos ( int Number )
{
	std::ostringstream	ss;
	ss << Number;
	return ss.str().c_str();
}

std::vector<std::string>	ft_split(std::string str, std::string delimiter)
{
	size_t							pos;
	std::string						token;
	std::vector<std::string>		tab;

	while ((pos = str.find(delimiter)) != std::string::npos)
	{
		token = str.substr(0, pos);
		tab.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	return (tab);
}