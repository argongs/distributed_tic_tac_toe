// Define all the functions prototyped in network.h to perform all the networking related functionalities

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int parse_address(char *ipv4_addr, int port_no, struct sockaddr_in *parsed_data)
{
	struct in_addr parsed_ipv4;

	parsed_data->sin_family = AF_INET;
	parsed_data->sin_port = htons(port_no);

	// Convert input ip address from string format to struct in_addr format
	if (inet_aton(ipv4_addr, &parsed_ipv4) == 0)
	{
		printf("[info] %s is not a valid IPv4 Address.\n", ipv4_addr);
		return 1;
	}
	else
	{
		parsed_data->sin_addr = parsed_ipv4;
		return 0;
	}
}

void set_receiver_timeout(int socket_fd, unsigned int max_time) {
	struct timeval max_wait_time = {max_time, 0};
	if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, &max_wait_time, sizeof max_wait_time) == -1)
	{
		perror("setsockopt (SO_RCVTIMEO)");
		exit(1);
	}
}

int create_udp_socket()
{
	// Create a socket
	int socket_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socket_fd == -1)
	{
		printf("[info] Failed to create a socket.");
		exit(EXIT_FAILURE);
	}

	set_receiver_timeout(socket_fd, 30);

	return socket_fd;
}

int perform_binding(int socket_fd, char *ipv4_addr, int port_no)
{
	// Perform binding
	struct sockaddr_in socket_data;
	int parse_status = parse_address(ipv4_addr, port_no, &socket_data);

	if (parse_status == 1)
	{
		return 1;
	}

	// Try to bind the given ip address, port no. and socket file descriptor together
	int bind_status = bind(socket_fd, (struct sockaddr *)&socket_data, sizeof(socket_data));

	if (bind_status == -1)
	{
		printf("[info] Failed to perform binding.");
		return -1;
	}

	// printf ("[....] Bound to %s:%d\n", ipv4_addr, htons (port_no));
	return 0;
}
