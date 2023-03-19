#ifndef SERVER_HPP
# define SERVER_HPP



#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <vector>
#include <iterator>
#include <string>
#include <string>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>

typedef	std::vector<struct pollfd > _vector_fd;

#define	MAX_FD 200
#define PORT 8080
#define BUFFER_SIZE 1024


#endif