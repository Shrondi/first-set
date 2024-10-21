#ifndef INITIAL_SETS
#define INITIAL_SETS

#include "GrammarParser.hpp"
#include <vector>
#include <string>
#include <map>
#include <set>


bool isTerminal(std::string cad);

std::map<std::string, std::set<std::string>> FirstSetGrammar(ProductionRules &grammar);

void FirstSet(std::map<std::string, std::set<std::string>> &firstSets, std::map<std::string, bool> &nullable, const ProductionRules &grammar, std::string symbolCalc);

std::map<std::string, bool> Nullable(ProductionRules grammar);

std::set<std::string> getNonTerminal(ProductionRules grammar);

std::set<std::string> getTerminal(ProductionRules grammar);

bool allNonTerminals(std::vector<std::string> alpha);

#endif