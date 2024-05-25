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

    // Create the FIFOs
    mkfifo(FIFO_REQ, 0666);
    mkfifo(FIFO_RESP, 0666);

    // Open the request FIFO for reading
    req_fd = open(FIFO_REQ, O_RDONLY);
    if (req_fd < 0) {
        perror("open fifo_req");
        exit(EXIT_FAILURE);
    }

    // Read the numbers from the request FIFO
    read(req_fd, &num1, sizeof(int));
    read(req_fd, &num2, sizeof(int));
    close(req_fd);

    // Calculate the sum
    sum = num1 + num2;

    // Open the response FIFO for writing
    resp_fd = open(FIFO_RESP, O_WRONLY);
    if (resp_fd < 0) {
        perror("open fifo_resp");
        exit(EXIT_FAILURE);
    }

    // Write the result to the response FIFO
    write(resp_fd, &sum, sizeof(int));
    close(resp_fd);

    // Remove the FIFOs
    unlink(FIFO_REQ);
    unlink(FIFO_RESP);

    return 0;
}

