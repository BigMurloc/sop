#include <iostream>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>



auto signal_handler(int, siginfo_t* info, void*) -> void {
	
	std::cout
	<< "Received " << strsignal(info->si_signo) 
	<< " from PID " << info->si_pid
	<< " with value " << info->si_value.sival_int << "\n";
}


auto main(int argc, char* argv[]) -> int {
	struct sigaction action;
	memset(&action, 0, sizeof(action));

	action.sa_sigaction = &signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, nullptr);
	
	std::cout << getpid() << "\n";
	
	while(true);
	
	return 0;
}
