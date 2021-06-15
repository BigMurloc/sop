#include <iostream>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


auto signal_handler(int, siginfo_t* info, void*) -> void {
	std::cout
	<< "Process PID " << getpid()
	<< " got signal " << info->si_signo
	<< " (" << strsignal(info->si_signo) << ")\n";
}

auto main() -> int {
	struct sigaction action;
	memset(&action, 0, sizeof(action));
	
	action.sa_sigaction = &signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGALRM, &action, nullptr); 
	sigaction(SIGHUP, &action, nullptr);
	sigaction(SIGINT, &action, nullptr);
	sigaction(SIGPIPE, &action, nullptr);
	sigaction(SIGQUIT, &action, nullptr);
	sigaction(SIGTERM, &action, nullptr); 
	sigaction(SIGUSR1, &action, nullptr);
	sigaction(SIGUSR2, &action, nullptr);

	while(true);
	return 0;
}
