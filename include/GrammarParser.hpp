#ifndef GRAMMAR_PARSER
#define GRAMMAR_PARSER

#include <vector>
#include <utility>
#include <string>

typedef std::vector<std::pair<std::string, std::vector<std::string>>> ProductionRules;

ProductionRules inputGrammarFile(std::string inputGrammarNameFile);

ProductionRules inputGrammarTerminal();



#endif