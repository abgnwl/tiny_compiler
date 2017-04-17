#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "production.h"
#include <vector>
#include <string>

class Parser
{
private:
    std::vector<Production> Grammar;
public:
    Parser(){}
    Parser(std::vector<Production> Grammar)
    {
        this->Grammar = Grammar;
    }


    void getGrammar()
    {

    }


};
#endif // PARSER_H_INCLUDED
