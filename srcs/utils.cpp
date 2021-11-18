/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:45:05 by epfennig          #+#    #+#             */
/*   Updated: 2021/11/18 15:39:17 by fgomez           ###   ########.fr       */
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

std::vector<std::string>	ft_split(std::string str, std::string delimiter, int times)
{
	size_t							pos;
	std::string						token;
	std::vector<std::string>		tab;

	while ((pos = str.find(delimiter)) != std::string::npos && times)
	{
		token = str.substr(0, pos);
		tab.push_back(token);
		str.erase(0, pos + delimiter.length());
		times--;
	}
	tab.push_back(str);
	return (tab);
}