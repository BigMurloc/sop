#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <array>
#include <string>

auto cat_to_stdout(std::string const path) -> void
{
    auto const in_fd = open(path.c_str(), O_RDONLY);
    if (in_fd == -1) {
        return;
    }
    
    std::array<char, 4096> buf {0};
    while (true) {
        
        auto const bytes_in = read(in_fd, buf.data(), buf.size());
        if (bytes_in == -1) {
            printf("read error has occured\n");
            break; // error
        }
        if (bytes_in == 0) {
            printf("read succesfully\n");
            break; // end of file
        }

        auto const bytes_out = write(1, buf.data(), bytes_in);
        if(bytes_out == -1){
            printf("write error has occured\n");
            break; // error
        }       
    }
    close(in_fd);
}

auto main(int argc, char* argv[]) -> int
{
    for (auto i = 1; i < argc; ++i) {
        cat_to_stdout(argv[i]);
    }
    return 0;
}
