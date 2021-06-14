#include <iostream>
#include <stdlib.h>
#include <unistd.h>

auto main(int argc, char* argv[]) -> int {

	auto env_name = argv[1];
	auto env_value = argv[2];
	auto oldShell = getenv("SHELL");
	
	if(env_name[0] != '-'){
		setenv(env_name, env_value, 1);
	} else {
		unsetenv(env_name + 1);
	}
	
	
	char* pointers[] = {oldShell, nullptr};
	
	execvp(oldShell, pointers);
	
	return 0;
}
