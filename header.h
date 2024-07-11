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
        void add_symbol(std::string symbol, int value);
        void retrieveSymbol(std::string symbol);
};

class FileReader {
    std::ifstream file;
    int instructions_read;

    public:
        FileReader(std::string file_path);
        ~FileReader();
        std::optional<std::string> get_next_label();
        int get_instructions_read();
    
    private:
        std::optional<std::string> get_next_line();
};

class Assembler {
    SymbolTable symbol_table;
    FileReader file_reader;

    public: 
        Assembler(std::string asm_file_path);        
        void generate_symbol_table();
};