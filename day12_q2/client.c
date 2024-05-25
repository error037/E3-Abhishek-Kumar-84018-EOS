#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define SOCKET_PATH "/tmp/unix_sock.server"

int main() {
    int client_socket;
    struct sockaddr_un server_addr;
    int num1, num2, sum;

    // Create a UNIX domain socket
    if ((client_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Setup the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Get numbers from user
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    // Send the numbers to the server
    if (write(client_socket, &num1, sizeof(int)) <= 0) {
        perror("write num1");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    if (write(client_socket, &num2, sizeof(int)) <= 0) {
        perror("write num2");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Read the result from the server
    if (read(client_socket, &sum, sizeof(int)) <= 0) {
        perror("read sum");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Print the result
    printf("The sum is: %d\n", sum);

    // Close the connection
    close(client_socket);
    return 0;
}

