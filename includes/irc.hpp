#ifndef IRC_HPP
# define IRC_HPP

/* C++ Includes */
#include <iostream>
#include <string>
#include <map>
#include <sstream>

/* TCP / IP */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/event.h>
#include <netdb.h>
#include <arpa/inet.h>

/* C Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>		
#include <unistd.h>
#include <fcntl.h>		// fcntl (fd non bloquant)
#include <errno.h>		// errno

/* ***************************************************************************

====================================
**	=== Server TCP / IP ===
**	Socket()
**	Bind()
**	Listen()
**	Accept()
**	Write() / Read() -> (server <--> client)
**	Close()
====================================

struct sockaddr_in
{
	__uint8_t       sin_len;							// unsigned char  0 - 255
	sa_family_t     sin_family;							// unsigned char  0 - 255
	in_port_t       sin_port;							// unsigned short 0	- 65535
	struct  in_addr sin_addr;		sin_addr.s_addr;	// unsigned int   (0xffffffff) address
	char            sin_zero[8];
};

[XSI] Structure used by kernel to store most addresses.
struct sockaddr
{
	__uint8_t       sa_len;         total length		// unsigned char
	sa_family_t     sa_family;      address family		// unsigned char
	char            sa_data[14];    addr value (actually larger)
};

struct in_addr
{
	in_addr_t s_addr;  base type for internet address
};

in_addr_t == uint32_t

struct kevent {
            uintptr_t  ident;        identifier for this event
            uint32_t   filter;       filter for event
            uint32_t   flags;        action flags for kqueue
            uint32_t   fflags;       filter flag value
            int64_t    data;         filter data value
            void       *udata;        opaque user data identifier
};

*************************************************************************** */


/* === UTILS FUNCTIONS === */

void			exit_error(std::string error);
const char*		ft_itos ( int Number );


#endif