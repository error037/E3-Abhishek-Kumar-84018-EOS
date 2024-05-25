#include <stdio.h>
#include <unistd.h>

int main() {
    long pipe_buf_size;

    pipe_buf_size = sysconf(_PC_PIPE_BUF);
    if (pipe_buf_size == -1) {
        perror("sysconf");
        return 1;
    }

    printf("The size of the pipe buffer is: %ld bytes\n", pipe_buf_size);
    return 0;
}

