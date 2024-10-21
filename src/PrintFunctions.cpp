#include "PrintFunctions.hpp"
#include "InitialSets.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

void printFirstSetsGrammar(const std::map<std::string, std::set<std::string>> &firstSets){

    // Print the calculated First Sets
    for (const auto& entry : firstSets) {
        std::cout << "First(" << entry.first << ") = { ";
        for (const std::string& terminal : entry.second) {
            std::cout << terminal << " ";
        }
        std::cout << "}" << std::endl;
    } 
}

void printRulesGrammar(const ProductionRules &grammar){
    
    //Print the production rules parsed
    int i = 1;
    std::cout << "P = {\n";
    for (const auto &rule : grammar)
    {
        std::string nonTerminal = rule.first;
        const std::vector<std::string>& symbols = rule.second;

        std::cout << "\t" << i++ << ") " << nonTerminal << " -> ";
        for (const std::string& symbol : symbols) {
            std::cout << symbol << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "}\n" << std::endl;

}

void printTerminal(const ProductionRules &grammar){

    std::cout << "Σ = { ";
    for (const auto &terminal : getTerminal(grammar)){
        std::cout << terminal << " ";
    }
    std::cout << "}\n";
}

void printNonTerminal(const ProductionRules &grammar){

    std::cout << "N = { ";
    for (const auto &terminal : getNonTerminal(grammar)){
        std::cout << terminal << " ";
    }
    std::cout << "}\n";
}

void printGrammar(const ProductionRules &grammar){

    printNonTerminal(grammar);
    printTerminal(grammar);
    printRulesGrammar(grammar);
}