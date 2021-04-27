#include <iostream>
#include <sys/types.h>
#include <unistd.h>

auto main() -> int {
	auto fork_value = fork();
	if(fork_value == 0){
		std::cout << "ppid: " << getppid() << "\n";
	} else {
		std::cout << "parent ppid: " << fork_value << "\n";
	}
	return 0;
}
