#include "header.h"
#include <fstream>
#include <algorithm>
#include <optional>

enum FirstOrLast {
    First,
    Last
};

// Returns whether or not a string is all blanks
bool is_blank(std::string line) {
    return (empty(line) || line.find_first_not_of(' ') == std::string::npos);
}

// Returns true if the first and last non-space char in a string are ( and ) respectively
bool is_label(std::string line) {
   char first = line.at(0);
   char last = line.at(line.length() - 1);
   return first == '(' && last == ')';
}

// Returns true if the first non-space char is @
bool is_a_instruction(std::string line) {
    char first = line.at(0);
    return first == '@';
}

// Returns true if the first char is valid for starting a symbol
bool is_c_instruction(std::string line) {
    char first = line.at(0);
    return (
        first && 
        (   
            isdigit(first) ||
            isalpha(first) ||
            first == '_' ||
            first == '.' ||
            first == '$' ||
            first == ':'
        )
    );
}



//TODO: This cannot handle file_paths that are not valid
FileReader::FileReader(std::string file_path) {
    file.open(file_path, std::ios::in | std::ios::out | std::ios::app);
}
FileReader::~FileReader() {
    if (file.is_open()) {
        file.close();
    }
}

// Reads through the file until it finds a new label and returns the line
std::optional<std::string> FileReader::get_next_label(int& instruction_count) {
    while (auto result = get_next_line()) {
        if (is_label(*result)) {
            return *result;
        } else if (is_a_instruction(*result) || is_c_instruction(*result)) {
            instruction_count++;
        }
    }
    return std::nullopt;
}

// Reads through the file until it finds either an A or C instruction and returns the line
std::optional<std::string> FileReader::get_next_instruction() {
    while (auto result = get_next_line()) {
        std::string next_line = result.value();
        next_line.erase(remove(next_line.begin(), next_line.end(), ' '), next_line.end());
        if (is_a_instruction(next_line) || is_c_instruction(next_line)) {
            return next_line;
        }
    }
    return std::nullopt;
}

// Returns the next non-blank line in the file
std::optional<std::string> FileReader::get_next_line() {
    std::string next_line = "";
    while (std::getline(this->file, next_line)) {
        if (!is_blank(next_line)) {
            next_line.erase(remove(next_line.begin(), next_line.end(), ' '), next_line.end());
            return next_line;
        }
    }
    return std::nullopt;
}

void FileReader::go_back_to_file_start() {
    file.clear();
    file.seekg(0);
}
