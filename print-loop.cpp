#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

char buff[64] = {0};
auto pathname = "plik.txt";

void read_from_file(char buff[], auto pathname) {
	auto a = open(pathname, 0);
	read(a, buff, 64);
	close(a);
}

void signal_handler(int signo) {
	read_from_file(buff, pathname);
}

auto main(int argc, char* argv[]) -> int {
	
	read_from_file(buff, pathname);
	
	while(true) {
		std::cout << buff << "\n";
		sleep(1);
		signal(SIGHUP, signal_handler);
	}
	
	return 0;
}
