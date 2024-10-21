#include "InitialSets.hpp"
#include "GrammarParser.hpp"

#include <vector>
#include <string>
#include <map>
#include <iostream>

#include <set>

#include <cctype> // islower

bool isTerminal(std::string cad) {

    if (cad == "ε"){
        return false;
    }

    for (char ch : cad) {
        
        if (!(std::islower(ch) || std::ispunct(ch))) {
            return false;
        }
    }

    return true;
}

bool allNonTerminals(std::vector <std::string> alpha){

    for (std::string cad : alpha){

        if (isTerminal(cad) || cad == "ε" )
        {
            return false;
        }
    }

    return true;
}

std::set <std::string> getNonTerminal(ProductionRules grammar){

    std::set<std::string> nonTerminal;

    for (const auto &rule : grammar){
        nonTerminal.insert(rule.first);
    }

    return nonTerminal;
}

std::set <std::string> getTerminal(ProductionRules grammar){

    std::set<std::string> terminal;

    for (const auto &rule : grammar){
        for (const auto &symbol : rule.second){
            if (isTerminal(symbol)){
                terminal.insert(symbol);
            }
        }
    }

    return terminal;
}

std::map<std::string, bool> Nullable(ProductionRules grammar){

    std::map<std::string, bool> nullable;

    //Initializate the nullable map with the non-terminal with the false value
    for (std::string c : getNonTerminal(grammar)) {
        nullable[c] = false;
    }

    //Search the epsilon rules in the grammar
    for (const auto& rule : grammar){

        std::string nonTerminal = rule.first;

        //If there is a epsilon rule, the non-terminal is nullable
        if (rule.second[0] == "ε") {
            nullable[nonTerminal] = true;
        }
    }

    //Search in the grammar the rules with the form A -> Y1Y2Y3... (the righ-hand is all non-terminal symbols)
    for (const auto& rule : grammar){

        std::string nonTerminal = rule.first;

        if (allNonTerminals(rule.second)){

            //Check if the non-terminal symbols in the right-hand are nullable
            for (const std::string &symbol : rule.second){

                //If a non-terminal is NOT nullable, the non-terminal in the left-hand is NOT nullable
                if (!nullable[symbol]){
                    nullable[nonTerminal] = false;
                    break;
                }
            }

        }
    }

    /* for (const auto& pair : nullable) {
        std::cout << "Simbolo: " << pair.first << ", Valor: ";
        if (pair.second) {
            std::cout << "True" << std::endl;
        } else {
            std::cout << "False" << std::endl;
        }
    } */

    return nullable;
}

std::map<std::string, std::set<std::string>> FirstSetGrammar(ProductionRules &grammar){

    // First Set for all non-terminals in the lef-hand of the grammar's rules
    std::map<std::string, std::set<std::string>> firstSets;

    //Calculate the nullable non-terminals (ε is in their First Set)
    std::map<std::string, bool> nullable = Nullable(grammar);

    //Calc of the Fist Set for each non-terminal in the left-hand of the grammar's rules
    for (std::string A : getNonTerminal(grammar)){

        // Avoid re-calculate the First Set because it has been previously calculated as a subset of another non-terminal
        if (firstSets.find(A) == firstSets.end()){
            FirstSet(firstSets, nullable, grammar, A);
        }
    }
    
    //Add the epsilon to the first set
    for (auto pair : nullable) {
        if (pair.second){
            firstSets[pair.first].insert("ε");
        }
    }

    return firstSets;
}

void FirstSet(std::map<std::string, std::set<std::string>> &firstSets, std::map<std::string, bool> &nullable, const ProductionRules &grammar, std::string symbolCalc){

    //Process each Grammar's production rule where is the non-terminal indicated
    for (const auto& rule : grammar) {

        std::string nonTerminal = rule.first;

        if (nonTerminal != symbolCalc){
            continue;
        }

        std::vector<std::string> alpha = rule.second;

        //Process the right-hand side of the production rule
        for (const std::string &symbol : alpha){

            //Terminal symbol: Add to the First(NonTerminal)
            if (isTerminal(symbol)) {
                firstSets[nonTerminal].insert(symbol);
                break;

            // Non-terminal symbol, recursively calculate its First Set
            }else if(!isTerminal(symbol) && symbol != "ε"){

                //Self set
                if (symbol == nonTerminal && nullable[nonTerminal] == true){
                    continue;
                }else if(symbol == nonTerminal && nullable[nonTerminal] == false){
                    break;
                }

                if (firstSets.find(symbol) == firstSets.end())
                {
                    FirstSet(firstSets, nullable, grammar, symbol);
                }

                // First Set of non-terminal in the right-hand side of the production rule
                std::set<std::string> FirstSet = firstSets[symbol];

                // Union of the first sets
                firstSets[nonTerminal].insert(FirstSet.begin(), FirstSet.end());

                if (nullable[symbol] == true){
                    continue;
                }else if(nullable[symbol] == false){
                    break;
                }
            }
        }
    }
}


