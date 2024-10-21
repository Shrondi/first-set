#ifndef PRINT_FUNCTIONS
#define PRINT_FUNCTIONS

#include "GrammarParser.hpp"
#include <map>
#include <string>
#include <vector>
#include <set>

void printRulesGrammar(const ProductionRules &grammar);

void printTerminal(const ProductionRules &grammar);

void printNonTerminal(const ProductionRules &grammar);

void printGrammar(const ProductionRules &grammar);

void printFirstSetsGrammar(const std::map<std::string, std::set<std::string>> &firstSets);

#endif