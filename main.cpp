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
    // std::string dir = "./input_files";
    // for (const auto & entry : std::filesystem::directory_iterator(dir)) {
    //     Assembler assembler = Assembler(entry.path());
    //     assembler.generateSymbolTable();
    
    // }

    Assembler assembler = Assembler("./input_files/Max.asm");
    assembler.assemble();
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
