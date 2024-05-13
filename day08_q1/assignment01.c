#include<unistd.h>
#include<stdio.h>

int main() {
	int ret1, ret2, ret3, ret4, ret5, i;
		ret1 = fork();
		if(ret1 == 0) {
			for(i=1; i<=3; i++) {
					printf("child 1: %d\n", i);
					printf("child 1: pid=%d\n", getpid());
					printf("child 1: parent pid=%d\n", getppid());
					sleep(5);
					}
					_exit(0);
			}
		ret2 = fork();
		if(ret2 == 0) {
			for(i=1; i<=3; i++) {
					printf("child 2: %d\n", i);

					printf("child 2: pid=%d\n", getpid());
					printf("child 2: parent pid=%d\n", getppid());
					sleep(5);
					}
					_exit(0);
			}
		ret3 = fork();
		if(ret3 == 0) {
			for(i=1; i<=3; i++) {
					printf("child 3: %d\n", i);

					printf("child 3: pid=%d\n", getpid());
					printf("child 3: parent pid=%d\n", getppid());
					sleep(5);
					}
					_exit(0);
			}
		ret4 = fork();
		if(ret4 == 0) {
			for(i=1; i<=3; i++) {
					printf("child 4: %d\n", i);
					printf("child 4: pid=%d\n", getpid());
					printf("child 4: parent pid=%d\n", getppid());
					sleep(5);
					}
					_exit(0);
			}
		ret5 = fork();
		if(ret5 == 0) {
			for(i=1; i<=3; i++) {
					printf("child 5: %d\n", i);
					printf("child 5: pid=%d\n", getpid());
					printf("child 5: parent pid=%d\n", getppid());
					sleep(5);
					}
					_exit(0);
			}
		else {
			for(i=1; i<=3; i++) {
					printf("parent: %d\n", i);
					sleep(1);
					}
			}
			return 0;
			}
