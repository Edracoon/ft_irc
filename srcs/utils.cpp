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
