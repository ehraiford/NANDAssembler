#include <bitset>
#include "header.h"


Assembler::Assembler(std::string asm_file_path) 
: file_reader(asm_file_path), 
    symbol_table()              
{}

// Reads through the file within the file_reader and generates a symbol table with the discovered labels
void Assembler::generateSymbolTable() {
    while (auto line = file_reader.get_next_label()) {
        symbol_table.addSymbol(*line, file_reader.get_instructions_read() + 1);
        std::cout << *line << ": " << file_reader.get_instructions_read() + 1 << std::endl;
    }
    file_reader.go_back_to_file_start();
}

// Takes an a instruction line and returns the binary equivalent
// Does not do any error handling so BEWARE
std::string Assembler::assemble_a_instruction(std::string line) {
    std::string symbol = "";
    for (int index = line.find_first_of('@') + 1; index < line.length(); index++) {
        symbol += line.at(index);
    }
    if (isdigit(symbol.at(0))) {
        int as_int = std::stoi(symbol);
        std::bitset<15> binary(as_int);
        return "0" + binary.to_string();
    } else {

    }; 
}
// Takes a c instruction line and returns the binary equivalent
// Does not do any error handling so BEWARE
std::string Assembler::assemble_c_instruction(std::string line) {

}

// Reads through the file within the file_reader and generates the .hack output
std::string Assembler::assemble() {
    generateSymbolTable();
    while (auto line = file_reader.get_next_instruction()) {
        if (is_a_instruction(*line)) {

        } else {

        }
    }
    file_reader.go_back_to_file_start();
}