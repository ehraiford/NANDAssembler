#include "header.h"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <optional>
#include <unordered_map>


std::unordered_map<std::string, int> STANDARD_SYMBOLS = {
    {"R0", 0},
    {"R1", 1},
    {"R2", 2},
    {"R3", 3},
    {"R4", 4},
    {"R5", 5},
    {"R6", 6},
    {"R7", 7},
    {"R8", 8},
    {"R9", 9},
    {"R10", 10},
    {"R11", 11},
    {"R12", 12},
    {"R13", 13},
    {"R14", 14},
    {"R15", 15},
    {"SP", 0},
    {"LCL", 1},
    {"ARG", 2}, 
    {"THIS", 3},
    {"THAT", 4}, 
    {"SCREEN", 16384},
    {"KBD", 24576}
    
};

SymbolTable::SymbolTable() {
    table = STANDARD_SYMBOLS;
}
void SymbolTable::addSymbol(std::string symbol, int value) {
    table.insert_or_assign(symbol, value);
}
std::optional<int> SymbolTable::retrieveSymbol(std::string symbol) {
    try{
        return table.at(symbol);
    } catch (std::out_of_range e) {
        return std::nullopt;
    }
}