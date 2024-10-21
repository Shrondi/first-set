#include "GrammarParser.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

ProductionRules inputGrammarFile(std::string inputGrammarNameFile){

    std::ifstream file(inputGrammarNameFile);

    if (!file.is_open()){
        std::cout << "Error. Cannot open the file '" << inputGrammarNameFile << "'\n";
        exit(EXIT_FAILURE);
    }

    ProductionRules grammar;

    std::string line;
    int lineNumber = 0;
    bool errorParsing = false;

    while (getline(file, line)){
        lineNumber++;

        // Utiliza regex para validar la estructura de la línea

        // Expresión regular para validar la estructura de una regla de producción
        std::regex rulePattern(R"(\s*([A-Z]+)\s->\s(.+))");

        std::regex ruleComments(R"(//.*)");

        std::smatch match;

        if (std::regex_match(line, match, ruleComments) || line.empty()) {
            continue;

        }else if(std::regex_match(line, match, rulePattern)){
            if (!errorParsing){
                std::string leftSide = match[1].str();
                std::string rightSide = match[2].str();

                std::istringstream rightSideStream(rightSide);

                std::string symbol;
                std::vector<std::string> symbols;
                while (rightSideStream >> symbol) {
                    symbols.push_back(symbol);
                }

                grammar.push_back({leftSide, symbols});
            }
        }else{
            std::cerr << "Parsing error in line " << lineNumber << ": " << "\n\t" << line << std::endl;
            errorParsing = true;
        }
    }

    // Cierra el archivo
    file.close();

    if (errorParsing){
        grammar.clear();
    }

    return grammar;
}

ProductionRules inputGrammarTerminal(){

    ProductionRules grammar;

    std::cout << "Write the production rules of the grammar (a rule per line, not allow alternatives in the same line):\n";
    std::cout << "Input example: \n";
    std::cout << "\tA B\n";
    std::cout << "\tB int\n";
    std::cout << "\tB float\n";
    std::cout << "(Write finish to exit)\n\n";

    std::string line;
    int numberRule = 1;

    std::cout << numberRule++ << ") ";
    while (getline(std::cin, line) && line != "finish"){
        std::cout << numberRule++ << ") ";

        std::istringstream stream(line);

        std::string leftSide;
        std::vector<std::string> rightSide;

        stream >> leftSide;

        std::string symbol;
        while (stream >> symbol) {
            rightSide.push_back(symbol);
        }

        grammar.push_back({leftSide, rightSide});
    }

    return grammar;
}