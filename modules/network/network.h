// Provide prototype of functions meant for accessing the network

#define QUEUE_LIMIT 10
#define MAX_BUFF_LEN 100
#define LOCALHOST "127.0.0.1"
#define START_PORT 1025
#define MAX_NODE_COUNT 30

// Parse an IPv4 Address and port no. into struct sockaddr_in type data 
int parse_address (char*, int, struct sockaddr_in*);

// Provide timeout limit in seconds
void set_receiver_timeout(int socket_fd, unsigned int max_time);

// UDP Socket Setup functions
int create_udp_socket (void);
int perform_binding (int, char*, int);

