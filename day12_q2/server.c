#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define SOCKET_PATH "/tmp/unix_sock.server"
#define BUFFER_SIZE 256

void handle_client(int client_socket) {
    int num1, num2, sum;

    // Read two numbers from client
    if (read(client_socket, &num1, sizeof(int)) <= 0) {
        perror("read num1");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    if (read(client_socket, &num2, sizeof(int)) <= 0) {
        perror("read num2");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Calculate sum
    sum = num1 + num2;

    // Send result back to client
    if (write(client_socket, &sum, sizeof(int)) <= 0) {
        perror("write");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Close client connection
    close(client_socket);
    exit(EXIT_SUCCESS);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_addr_len;

    // Create a UNIX domain socket
    if ((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Remove any existing socket file
    unlink(SOCKET_PATH);

    // Setup the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Bind the socket to the address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on %s\n", SOCKET_PATH);

    while (1) {
        client_addr_len = sizeof(client_addr);
        // Accept a client connection
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
            perror("accept");
            continue;
        }

        // Handle each client in a new process
        if (fork() == 0) {
            close(server_socket);
            handle_client(client_socket);
        }

        close(client_socket);
    }

    close(server_socket);
    unlink(SOCKET_PATH);
    return 0;
}

