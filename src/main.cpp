#include <vector>
#include <string>
#include "InitialSets.hpp"
#include "GrammarParser.hpp"
#include  "PrintFunctions.hpp"
#include <iostream>
#include <map>

int main(int argc, char **argv){

    ProductionRules grammar;

    if (argc == 2){
        grammar = inputGrammarFile(argv[1]);

        if (grammar.size() == 0){
            exit(EXIT_FAILURE);
        }
    }else{
        grammar = inputGrammarTerminal();
    }

        printGrammar(grammar);

    std::map<std::string, std::set<std::string>> firstSets = FirstSetGrammar(grammar);

    printFirstSetsGrammar(firstSets);

    exit(EXIT_SUCCESS);
}