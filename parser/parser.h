#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "production.h"
#include "lritem.h"
#include <vector>
#include <string>
#include <set>
#include <map>

typedef std::pair<std::string, int> psi;
typedef std::vector<psi> vpsi;
typedef std::set<LR1item> LR1set;

class Parser
{
private:
    std::vector<Production> grammar;    //store grammar
    std::vector< LR1set > closurelist;  //closure list
    std::map< LR1set, int> closuremap;  //closure map
    std::vector< vpsi > transfer;       //transfer function
public:
    void build();
    std::set<std::string> getFirst(const std::vector<std::string> &beta);

    Parser(){}
    Parser(std::vector<Production> grammar)
    {
        this->grammar = grammar;
    }


    bool openFile(const std::string &fileName);
    std::vector<Production> getGrammar();

    std::set<LR1item> getClosure(const LR1item &item);
    void getClosure(std::set<LR1item> &closure);

    std::vector< std::set<LR1item> > getClosurelist();
    std::map< std::set<LR1item>, int> getClosuremap();
    std::vector< vpsi > getTransfer();

    int analyse();

};
#endif // PARSER_H_INCLUDED
