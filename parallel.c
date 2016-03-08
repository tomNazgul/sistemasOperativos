#include <stdio.h>
#include <unistd.h>
#include <parallel.h>

int main(int argsc, char *argsv[]) {
	
	for (int i = 0; i < argsc; i++) {
		pid_t pid = fork();
		
		if (pid == -1) {
			printf(stderr, "Error at child process creation\n");
			exit(1);
		} else if (pid == 0) {
			//TODO I am the child
			exceclp("sh", "sh", "-c", );
		} else {
		
		}


	}	

}

