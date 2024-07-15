#include <bitset>
#include "header.h"


Assembler::Assembler(std::string asm_file_path) : 
    file_reader(asm_file_path), 
    next_instruction_address(0),
    next_variable_address(15),
    symbol_table()              
{}

// Reads through the file within the file_reader and generates a symbol table with the discovered labels
void Assembler::generateSymbolTable() {
    while (auto line = file_reader.get_next_label(next_instruction_address)) {
        symbol_table.addSymbol(*line, next_instruction_address);
    }
    file_reader.go_back_to_file_start();
}

// Takes an a instruction line and returns the binary equivalent
// Adds variables to the symbol table in the process
// Does not do any error handling so BEWARE
std::string Assembler::assemble_a_instruction(std::string line) {
    std::string symbol = "";
    for (int index = line.find_first_of('@') + 1; index < line.length(); index++) {
        symbol += line.at(index);
    }
    int int_rep = 0;
    if (isdigit(symbol.at(0))) {
        int_rep = std::stoi(symbol);
     } else {
        if(auto symbol_value = symbol_table.retrieveSymbol(symbol)) {
            int_rep = *symbol_value;
        } else {
            symbol_table.addSymbol(symbol, next_variable_address);
            int_rep = next_variable_address;
            next_variable_address++;
        }
    }; 

    std::bitset<15> binary(int_rep);
    return "0" + binary.to_string();
}
// Takes a c instruction line and returns the binary equivalent
// Does not do any error handling so BEWARE
std::string Assembler::assemble_c_instruction(std::string line) {
    return "C INSTRUCTION";
}

// Reads through the file within the file_reader and generates the .hack output
std::string Assembler::assemble() {
    generateSymbolTable();
    std::string hack_file = "";
    while (auto line = file_reader.get_next_instruction()) {
        if (is_a_instruction(*line)) {
            hack_file += assemble_a_instruction(*line) + '\n';
        } else {
            hack_file += assemble_c_instruction(*line) + '\n';
        }
    }
    file_reader.go_back_to_file_start();
    return hack_file;
}