#include <sys/types.h>
#include <signal.h>
#include <cstdlib>




auto main(int argc, char* argv[]) -> int {
	
	auto pid = std::atoi(argv[1]);
	auto signo = std::atoi(argv[2]);
	
	kill(pid, signo); 
	
	return 0;
}
