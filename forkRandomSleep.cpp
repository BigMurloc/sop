#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>

int randomTime;
int healthyBabyCounter = 0;

auto handleChild(int randomTime) -> int {
	printf("spawned sleeping(%ds) child %d from parent %d\n", randomTime, getpid(), getppid());
	sleep(randomTime);
	auto randomStatus = rand() % 2;
	if(randomStatus == 0) {
		exit(0);
	} else {
		exit(EXIT_FAILURE);
	}
}

auto sigchld_handler(int signo) -> void {
	int status;
	auto child = waitpid(-1, &status, 0);
	if (WIFEXITED(status)){
		if (WEXITSTATUS(status) == 1) {
			std::cout
			<< "child: " << child
			<< " has ended process with status code " << WEXITSTATUS(status)
			<< ", creating new child" << "\n";
			randomTime = rand() % 10 + 3;
			if (fork() == 0) {
				handleChild(randomTime);
			}
		} else {
			healthyBabyCounter++;
			std::cout
			<< "child: " << child
			<< " exited normally with " << WEXITSTATUS(status) << "\n"
			<< "Baby Counter: " << healthyBabyCounter << "\n";
		}
	}
}

auto main() -> int {
	for(int i = 0; i < 4; i++){
		randomTime = rand() % 10 + 3;
		if(fork() == 0){
			handleChild(randomTime);
		} else {
			signal(SIGCHLD, sigchld_handler);
		}
	
	}

	while(healthyBabyCounter < 4);

	return 0;
}
