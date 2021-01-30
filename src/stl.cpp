// from https://rosettacode.org/wiki/Walk_a_directory/Recursively#C.2B.2B

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    std::ios_base::sync_with_stdio();

    //fs::path current_dir(".");
    auto fs_it = fs::recursive_directory_iterator(fs::path("."),
        fs::directory_options::skip_permission_denied); // eq to find -H, which gets 651.7 10

    for (auto &file : fs_it) {
        //std::cout << file.path().filename().string() << "\n"; // only filename, 909.5 19.8
        //std::cout << std::filesystem::absolute(file.path()).string() << "\n"; // root path, 1500 25 (v bad)
        puts(std::filesystem::absolute(file.path()).c_str()); // root path, puts over cout, 1452 9 (still slow)
        //++counter;    // just traversal: 850.2 15.6 (too slow, give up on this iterator thing)
    }
}

