#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "production.h"
#include "lritem.h"
#include <vector>
#include <string>
#include <set>
#include <map>

class Parser
{
private:
    std::vector<Production> grammar;
    std::vector< std::set<LR1item> > closurelist;
    std::map< std::set<LR1item>, int> closuremap;
    std::vector< std::vector<int> > transfer;

public:
    Parser(){}
    Parser(std::vector<Production> grammar)
    {
        this->grammar = grammar;
    }


    bool openFile(const std::string &fileName);
    std::vector<Production> getGrammar();

    void Closure(const LR1item &item);
    void Closure(std::set<LR1item> &closure);
    void getClosure(std::set<LR1item> &closure);

    std::set<LR1item> Go(const std::set<LR1item> &closure, const std::string &variable);


    std::vector< std::set<LR1item> > getClosurelist();
    std::map< std::set<LR1item>, int> getClosuremap();
    std::vector< std::vector<int> > getTransfer();


};
#endif // PARSER_H_INCLUDED
