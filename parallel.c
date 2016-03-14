#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/* function declaration */
int runProgram(char *program, char *args);

int main(int argc, char *argv[]) {
	int concurrency = atoi(argv[1]);
	char* program = argv[2];
	int argsLen = argc - 3;
	int running = 0;
	printf("%d\n",  argsLen);
	for (int i = 0; i < argsLen; i++) {
		pid_t pid = fork();

		if (pid == -1) {
			fprintf(stderr, "Error at child process creation\n");
			return 1;
		} else if (pid == 0) {
			//TODO I am the child
			runProgram(program, argv[i + 3]);
		} else {
			running++;
			if (running == concurrency) {
				pid_t child = wait(NULL);
				running--;
				printf("\nChild %d Complete\n", child);
			}
		}
	}

	while (running > 0) {
		pid_t child = wait(NULL);
		running--;
		printf("\nChild %d Complete\n", child);
  }
}

int runProgram(char *program, char *args) {
	char programAndArgs[strlen(program) + strlen(args) + 2];
	snprintf(programAndArgs, sizeof programAndArgs, "%s %s", program, args);

  char *argv[] = { "sh", "-c", programAndArgs, 0 };
	int failed = execvp("sh", argv);
	if (failed < 0) {
		fprintf(stderr, "Failed to exec %s %s\n", program, args);
    return 1;
	} else {
			return 0;
	}
}
