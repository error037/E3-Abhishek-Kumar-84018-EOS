#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void){
	int ret1,ret2,ret3,s1,s2,s3;
	ret1 = fork();
	sleep(1);
	if(ret1 == 0){
		ret2 = fork();
		if(ret2 == 0){
			ret3 = fork();
			if(ret3 == 0){
				printf("Child3 is child of child2\n");
				printf("Child of %d is %d\n",getppid(),getpid());
				_exit(1);
			}
				printf("Child2 is child of child1\n");
			printf("Child of %d is %d \n",getppid(),getpid());
			waitpid(ret3,&s1,0);
			_exit(1);
		}
				printf("Child1 is main child\n");
		printf("Child of %d is %d \n",getppid(),getpid());
		waitpid(ret2,&s2,0);
			_exit(1);
	}
	printf("Parent : %d \n",getpid());
	waitpid(ret1,&s3,0);

}
