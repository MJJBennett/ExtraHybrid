#include "Logger.h"
#include <sys/stat.h>
#include <ctime>
#include <experimental/filesystem>

bool is_file(std::string filename) {
    struct stat buf{};
    return (stat(filename.c_str(), &buf) == 0);
}

std::string get_filename(const std::string &filein) {
    return std::string(filein);
}

bool create_directories(const std::string &full_path, std::string delim) {
    namespace fs = std::experimental::filesystem;

    std::vector<std::string> directories;
    size_t pos = 0;
    size_t prev_pos = 0;
    while (true) {
        // Find the location of the delimiter, starting from where we were last time + 1
        pos = full_path.find(delim, prev_pos + 1);
        // If we couldn't find it, add the full string and quit
        if (pos == std::string::npos) {
            directories.push_back(full_path);
            break;
        }
        // If we could find it, add everything up to it and update variables
        directories.push_back(full_path.substr(0, pos));
        prev_pos = pos;
    }

    // We want to return 'true' if we create a directory, false otherwise
    bool created_dirs = false;

    // Iterate through all of the directories and create ones that do not exist
    for (auto &&pathname : directories) {
        if (!fs::is_directory(pathname)) {
            fs::create_directory(pathname);
            created_dirs = true;
        }
    }

    return created_dirs;
}
