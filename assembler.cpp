#include <bitset>
#include "header.h"


std::string translate_dest(std::string line) {
    if (line == "M") {
        return "001";
    } else if (line == "D") {
        return "010";
    } else if (line == "DM" || line == "MD") {
        return "011";
    } else if (line == "A") {
        return "100";
    } else if (line == "AM") {
        return "101";
    } else if (line == "AD") {
        return "110";
    } else {
        // (line == "ADM")
        return "111";
    }
}
std::string translate_jump(std::string line) {
    if (line == "JGT") {
        return "001";
    } else if (line == "JEQ") {
        return "010";
    } else if (line == "JGE") {
        return "011";
    } else if (line == "JLT") {
        return "100";
    } else if (line == "JNE") {
        return "101";
    } else if (line == "JLE") {
        return "110";
    } else {
        // (line == "JMP")
        return "111";
    }
}
std::string translate_comp(std::string line, char* a_reg) {
    if (line == "0") {
        return "101010";
    } else if (line == "1") {
        return "111111";
    } else if (line == "-1") {
        return "111010";
    } else if (line == "D") {
        return "001100";
    } else if (line == "A") {
        return "110000";
    } else if (line == "!D") {
        return "001101";
    } else if (line == "!A") {
        return "110001";
    } else if (line == "-D") {
        return "001111";
    } else if (line == "-A") {
        return "110011";
    } else if (line == "D+1") {
        return "011111";
    } else if (line == "A+1") {
        return "110111";
    } else if (line == "D-1") {
        return "001110";
    } else if (line == "A-1") {
        return "110010";
    } else if (line == "D+A") {
        return "000010";
    } else if (line == "D-A") {
        return "010011";
    } else if (line == "A-D") {
        return "000111";
    } else if (line == "D&A") {
        return "000000";
    } else if (line == "D|A") {
        return "010101";
    } else if (line == "M") {
        *a_reg = '1';
        return "110000";
    } else if (line == "!M") {
        *a_reg = '1';
        return "110001";
    } else if (line == "-M") {
        *a_reg = '1';
        return "110001";
    } else if (line == "M+1") {
        *a_reg = '1';
        return "110111";
    } else if (line == "M-1") {
        *a_reg = '1';
        return "110010";
    } else if (line == "D+M") {
        *a_reg = '1';
        return "000010";
    } else if (line == "D-M") {
        *a_reg = '1';
        return "010011";
    } else if (line == "M-D") {
        *a_reg = '1';
        return "000111";
    } else if (line == "D&M") {
        *a_reg = '1';
        return "000000";
    } else {
        // (line == "D|M")
        *a_reg = '1';
        return "010101";
    } 
}

Assembler::Assembler(std::string asm_file_path) : 
    file_reader(asm_file_path), 
    next_instruction_address(0),
    next_variable_address(16),
    symbol_table()              
{}

// Reads through the file within the file_reader and generates a symbol table with the discovered labels
void Assembler::generateSymbolTable() {
    while (auto line = file_reader.get_next_label(next_instruction_address)) {
        std::string symbol = line.value();
        symbol = substring_by_index(symbol, 1, symbol.length() - 1);
        symbol_table.addSymbol(symbol, next_instruction_address);
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
    std::string dest = "000";
    char a_reg = '0';
    auto instance_of_space = line.find_first_of('=');
    if (instance_of_space != std::string::npos) {
        dest = translate_dest(substring_by_index(line, 0, instance_of_space));
        line = substring_by_index(line, instance_of_space + 1, line.length());
    }
    std::string jump = "000";
    auto instance_of_semi = line.find_first_of(';');
    if (instance_of_semi != std::string::npos) {
        jump = translate_jump(substring_by_index(line, instance_of_semi + 1, line.length()));
        line = substring_by_index(line, 0, instance_of_semi);
    }
    std::string comp = translate_comp(line, &a_reg);

    std::string return_value = "111";
    return_value += a_reg + comp + dest + jump;
    return return_value;
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
