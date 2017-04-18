#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "production.h"
#include <vector>
#include <string>

class Parser
{
private:
    std::vector<Production> grammar;
public:
    Parser(){}
    Parser(std::vector<Production> grammar)
    {
        this->grammar = grammar;
    }


    bool openFile(const std::string &fileName);
    std::vector<Production> getGrammar();


};
#endif // PARSER_H_INCLUDED
