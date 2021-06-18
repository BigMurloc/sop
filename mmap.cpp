#include <iostream>
#include <sys/mman.h>


auto main() -> int {
	auto const page = mmap(nullptr, 4096, PROT_WRITE | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	std::cout << munmap(page, 4096) << "\n"; 
}
