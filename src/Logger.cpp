#include "Logger.h"
#include <sys/stat.h>
#include <ctime>

bool is_file(std::string filename) {
    struct stat buf{};
    return (stat(filename.c_str(), &buf) == 0);
}

std::string get_filename(const std::string &filein) {
    return std::string(filein);
}
