#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_REQ "/tmp/fifo_req"
#define FIFO_RESP "/tmp/fifo_resp"

int main() {
    int req_fd, resp_fd;
    int num1, num2, sum;

    // Get numbers from user
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    // Open the request FIFO for writing
    req_fd = open(FIFO_REQ, O_WRONLY);
    if (req_fd < 0) {
        perror("open fifo_req");
        exit(EXIT_FAILURE);
    }

    // Write the numbers to the request FIFO
    write(req_fd, &num1, sizeof(int));
    write(req_fd, &num2, sizeof(int));
    close(req_fd);

    // Open the response FIFO for reading
    resp_fd = open(FIFO_RESP, O_RDONLY);
    if (resp_fd < 0) {
        perror("open fifo_resp");
        exit(EXIT_FAILURE);
    }

    // Read the result from the response FIFO
    read(resp_fd, &sum, sizeof(int));
    close(resp_fd);

    // Print the result
    printf("The sum is: %d\n", sum);

    return 0;
}

