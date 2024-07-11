#include <header.h>

class Assembler {
    SymbolTable symbol_table;
    FileReader file_reader;

    public: 
        Assembler(std::string asm_file_path) 
        : file_reader(asm_file_path), 
          symbol_table()              
        {}
        
        void generate_symbol_table() {
            while (auto result = file_reader.get_next_label()) {
                symbol_table.add_symbol(*result, file_reader.get_instructions_read() + 1);
                std::cout << *result << ": " << file_reader.get_instructions_read() + 1 << std::endl;
            }
            
        }
           
};