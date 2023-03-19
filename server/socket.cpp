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

#define	MAX_FD 200
#define PORT 8080
int main(void)
{
	std::ofstream file;
	typedef	std::vector<struct pollfd > _vector_fd;
	int									server_fd = -1;
	int									new_client = -1;
	int									rcv;
	int									on = 1;
	int									rc = 1;
	int									nfds = 1;
	int									timeout;
	int									fd_counts;
	int									current_size = 1;
	struct	addrinfo					hints, *ai, *point;
	struct	sockaddr_storage			remoteaddr;
	socklen_t 							addrlen;
	char								buf[1024];
	_vector_fd	fd_s;
	fd_s.resize(1);
	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((rcv = getaddrinfo(NULL, "8080", &hints, &ai)) != 0){
		std::cerr << gai_strerror(rcv) << std::endl;
	}
	for(point = ai; point != NULL; point = point->ai_next)
	{
		server_fd = socket(point->ai_family, point->ai_socktype, point->ai_protocol);
		if (server_fd < 0)
			continue;
		rc = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
		if (rc < 0)
		{
			perror("setsocketopt failed");
			close(server_fd);
			exit(-1);
		}
		if(bind(server_fd, point->ai_addr, point->ai_addrlen) < 0)
			{
				close(server_fd);
				continue;
			}
			break ;
	}
	freeaddrinfo(ai);
	if (point == NULL)
		return -1;
	if(listen(server_fd, 10) == -1)
	{
		perror("listen() failed");
		return -1;
	}
	int terminal_fd = open("ok.txt", O_CREAT | O_WRONLY, 0777);
	if (terminal_fd == -1)
		perror("fd");
	fd_s.push_back(pollfd());
	fd_s[0].fd = server_fd;
	fd_s[0].events = POLLIN;
	timeout = (2 * 60 * 1000);
	fd_counts = 1;
	while(1)
	{
		rc = poll(&fd_s[0], fd_s.size(), timeout);
		if (rc < 0)
		{
			perror("poll() failed");
			break ;
		}
		if (rc == 0)
		{
			std::cerr << "poll() timed out , End program\n" << std::endl;
			break ;
		}
		current_size = nfds;
		for(int i = 0; i < fd_s.size(); i++)
		{
			// if (fd_s[i].revents == 0)
			// 	continue;
			if (fd_s[i].revents & POLLIN)
			{
				if (fd_s[i].fd == server_fd)
				{
					addrlen = sizeof remoteaddr;
					int newfd = accept(server_fd, (struct sockaddr *) &remoteaddr, &addrlen);
					if (newfd == -1)
						perror("accept");
					else
					{

						fd_s.push_back(pollfd());
						fd_s.back().fd = newfd;
						fd_s.back().events = POLLIN;
						fd_counts++;
					}
			}
			else
			{
				int bytes = recv(fd_s[i].fd, buf, 1024, 0);
				buf[bytes] = '\0';
				std::string message(buf);
				int sender_fd = fd_s[i].fd;
				if(bytes <= 0)
				{
					if (bytes == 0)
					{
						std::cerr << "this client hung up " << sender_fd<< std::endl;
					}
					else
					{
						perror("rev");
					}
					close(fd_s[i].fd);
					fd_s[i] = fd_s.back();
					fd_s.pop_back();
				}
				else
					{
						write(terminal_fd, message.c_str(), message.length());

	
							
					}
				}
			}
		}
	}
	
	return 0;
}