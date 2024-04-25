#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	//zero argument case: ERROR
	if(argc==1){
		errno = EINVAL;
		perror("Error occured");
		exit(EINVAL);
	}
	int i;
	int fd[2]; 
	for(i = 1; i<(argc); i++){
		if(i!=argc-1){
			if (pipe(fd) == -1) { 
				perror("Error Occured");
				exit(EXIT_FAILURE);
			}
		}
		int status; 
		pid_t pid = fork(); 
		if (pid == -1) { 
			perror("Error Occured");
			exit(EXIT_FAILURE);
		}
		else if(pid==0){
			if(i!=argc-1){
				close(fd[0]); 
				dup2(fd[1], 1); 
				close(fd[1]); 
			}
			if (execlp(argv[i], argv[i], NULL) == -1){ 
				perror("execlp"); 
				exit(EXIT_FAILURE);
			} 
		}
		else{
			waitpid(pid, &status, 0); 
			if(WIFEXITED(status)){
				if (!WIFEXITED(status) || WEXITSTATUS(status) != 0){ 
				exit(EINVAL);
			}

			}
			if(i!=argc-1){
				close(fd[1]);
				dup2(fd[0], 0); 
				close(fd[0]);
			}
		}

	}


	return 0;
}