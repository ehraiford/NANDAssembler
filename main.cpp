#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <optional>
#include "header.h"

using namespace std;

int main()
{
    std::string dir = "./input_files";
    for (const auto & entry : std::filesystem::directory_iterator(dir)) {
        Assembler assembler = Assembler(entry.path());
        string hack = assembler.assemble();

        std::string save_path = entry.path();
        save_path = "./created_files/" + 
            substring_by_index(save_path, save_path.find_last_of('/') + 1, save_path.length() - 4) + 
            ".hack";
        std::cout << save_path << std::endl;
        std::ofstream file(save_path);
        if (file.is_open()) {
            file << hack.substr(0, hack.length() - 1);
            file.close();
        }
    }
    return 0;
}


optional<std::ifstream> open_file(std::string file_path) {
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (file) {
        return file;
    } else {
        return std::nullopt;
    }
}
std::string substring_by_index(std::string string, int start, int end) {
    return string.substr(start, end - start);
}