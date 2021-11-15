NAME		=	ircserv

CXX			=	clang++

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

SRCS		=	srcs/main.cpp srcs/utils.cpp srcs/tcp_protocol.cpp srcs/server_loop.cpp

classes		=	srcs/classes/server.cpp srcs/classes/client.cpp srcs/classes/channel.cpp

OBJS		=	$(SRCS:.cpp=.o) $(classes:.cpp=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
