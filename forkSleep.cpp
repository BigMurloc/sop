#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>

auto execute(std::vector<std::string> args) -> int {
	auto argv = std::vector<char*>{};
	for(auto const& each: args) {
		argv.push_back(const_cast<char*> (each.c_str()));
	}
	argv.push_back(nullptr);

	auto env = std::vector<char*>{};
	env.push_back(nullptr);

	execve(argv[0], argv.data(), env.data());
	exit(EXIT_FAILURE);
}

auto sigchld_handler(int signo) -> void {
	std::cout << "got SIGCHLD\n";
	auto status = int {0};
	auto child = waitpid(-1, &status, 0);
	if (WIFEXITED(status)){
		std::cout
		<< "child: " << child
		<< " exited normally with " << WEXITSTATUS(status) << "\n"; 
		exit(0);
	}
}

auto main() -> int {
	auto const child = fork();

	if( child == 0) {
		execute({"/bin/sleep", "10"});
	}
	std::cout << "spawned child " << child << "\n";
	signal(SIGCHLD, sigchld_handler);

	while(true);

	return 0;
}
