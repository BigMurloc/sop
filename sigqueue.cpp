#include <signal.h>
#include <cstdlib>
#include <iostream>

auto main(int argc, char* argv[]) -> int {
	
	auto pid = std::atoi(argv[1]);
	auto signo = std::atoi(argv[2]);
    union sigval val;
    val.sival_int = 0;
	
	if (argc == 4) {
		val.sival_int = std::atoi(argv[3]);
	}
	
	sigqueue(pid, signo, val);
	
	return 0;
}
