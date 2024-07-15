#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>    
#include <optional>
#include <unordered_map>


class SymbolTable {
    std::unordered_map<std::string, int> table; 

    public: 
        SymbolTable();
        void addSymbol(std::string symbol, int value);
        std::optional<int> retrieveSymbol(std::string symbol);
};

class FileReader {
    std::ifstream file;

    public:
        FileReader(std::string file_path);
        ~FileReader();
        std::optional<std::string> get_next_label(int& instruction_count);
        std::optional<std::string> get_next_instruction();
        void go_back_to_file_start();
    
    private:
        std::optional<std::string> get_next_line();
};

class Assembler {
    SymbolTable symbol_table;
    FileReader file_reader;
    int next_instruction_address;
    int next_variable_address;

    public: 
        Assembler(std::string asm_file_path); 
        std::string assemble();     
    private:  
        void generateSymbolTable();
        std::string assemble_a_instruction(std::string line);
        std::string assemble_c_instruction(std::string line);
};

bool is_a_instruction(std::string line);
bool is_c_instruction(std::string line);


std::string substring_by_index(std::string string, int start, int end);