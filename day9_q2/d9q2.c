#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sigint_handler(int sig) {
		printf("SIGINT caught: %d\n", sig);
		}

int main() {
		int i=1;
		signal(SIGINT, sigint_handler);
		while(1) {
				printf("running: %d\n", i++);
				sleep(1);
		}
		return 0;
}

