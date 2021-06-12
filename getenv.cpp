#include <stdlib.h>
#include <iostream>

auto main(int argc, char* argv[]) -> int {
	
	auto env = argv[1];
	
	auto result = getenv(env);
	
	if(result != nullptr){
		std::cout << result << "\n";
	}
	return 0;
}
