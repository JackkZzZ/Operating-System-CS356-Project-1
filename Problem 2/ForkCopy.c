/*
 * ForkCopy.c
 * Author: Christian Würthner
 * Description: Use MyCopy to copy a file in a new process.
 */

#define EXECLP_ERROR 42

#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
	
	/* Fork process */
	pid_t pid = fork();

	/* Code for parent */
	if(pid > 0) {
		/* Wait for child */
		int status = 0;
		wait(&status);

		/* Query the plain exit status */
		status = WEXITSTATUS(status);

		/* Print success or error text */
		if(status != 0) {
			printf("ERROR: Child process finished abnormally with status %d\n", status);

			if(status == EXECLP_ERROR) {
 				printf("HINT: execlp() failed. Please make shure that you call ForkCopy in the bin folder and all needed programs are also in the bin folder.\n");
 			}

		} else {
			printf("SUCCESS: Child finished normally.\n");
		}

		/* Return the child's exit status */
		return status;

	}

	/* Code for child */
	else if(pid == 0) {
		execlp("./MyCopy", argv[0], argv[1], argv[2], NULL);
		return EXECLP_ERROR;
	}

	/* Code for error handling */
	else if(pid < 0) {
		printf("ERROR: Unable to fork process!\n");
		return 1;
	}

	return 0;
}