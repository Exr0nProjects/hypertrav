// from https://rosettacode.org/wiki/Walk_a_directory/Recursively#C.2B.2B

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    std::ios_base::sync_with_stdio();

    //fs::path current_dir(".");
    auto fs_it = fs::recursive_directory_iterator(fs::path("."),
        fs::directory_options::skip_permission_denied);

    for (auto &file : fs_it) {
        std::cout << file.path().filename().string() << "\n";
    }
}

