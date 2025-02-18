#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

typedef struct s_client {
	int id;
	char msg[100000];
} t_client;

t_client clients[2048];
fd_set current, read_set, write_set;
int server_fd = 0, max_fd = 0, next_id = 0;
char send_buffer[120000], recv_buffer[120000];

void err(const char *msg) {
	if (msg) write(2, msg, strlen(msg));
	else write(2, "Fatal Error", 11);
	exit(write(2, "\n", 1));
}

void send_all(int server_fd, int sender_fd) {
	for (int fd = 0; fd <= max_fd; fd++) {
		if (FD_ISSET(fd, &current) && fd != server_fd && fd != sender_fd) {
			if (send(fd, send_buffer, strlen(send_buffer), 0) == -1) err(NULL);
		}
	}
}

int main(int argc, char **argv) {
	if (argc != 2) err("Wrong number of args");

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) err(NULL);
	max_fd = server_fd;

	struct sockaddr_in server_address;
	socklen_t s_len = sizeof(struct sockaddr_in);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(2130706433);
	server_address.sin_port = htons(atoi(argv[1]));

	FD_ZERO(&current);
	FD_SET(server_fd, &current);

	memset(clients, 0, sizeof(clients));

	if (bind(server_fd, (const struct sockaddr*)&server_address, sizeof(server_address)) == -1) err(NULL);
	if (listen(server_fd, 100) == -1) err(NULL);

	while (1) {
		read_set = current;
		write_set = current;
		if (select(max_fd + 1, &read_set, &write_set, 0, 0) == -1) continue;
		for (int fd = 0; fd <= max_fd; fd++) {
			if (FD_ISSET(fd, &read_set)) {
				if (fd == server_fd) {
					int client_fd = accept(server_fd, (struct sockaddr*)&server_address, &s_len);
					if (client_fd == -1) continue;
					FD_SET(client_fd, &current);
					if (client_fd > max_fd) max_fd = client_fd;
					clients[client_fd].id = next_id++;
					sprintf(send_buffer, "server: %d client just arrived\n", clients[client_fd].id);
					send_all(server_fd, client_fd);
				} else {
					int bytes_rec = recv(fd, recv_buffer, sizeof(recv_buffer), 0);
					if (bytes_rec == -1) continue;
					else if (bytes_rec == 0) {
						sprintf(send_buffer, "server: client %d just left\n", clients[fd].id);
						send_all(server_fd, fd);
						FD_CLR(fd, &current);
						close(fd);
						memset(clients[fd].msg, 0, sizeof(clients[fd].msg));
					} else {
						for (int i = 0, j = strlen(clients[fd].msg); i != bytes_rec; i++, j++) {
							clients[fd].msg[j] = recv_buffer[i];
							if (clients[fd].msg[j] == '\n') {
								clients[fd].msg[j] = '\0';
								sprintf(send_buffer, "client %d: %s\n", clients[fd].id, clients[fd].msg);
								send_all(server_fd, fd);
								memset(clients[fd].msg, 0, sizeof(clients[fd].msg));
								j = -1;
							}
						}
					}
				}
			}
		}
	}

	return (0);
}
