#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "production.h"
#include "lritem.h"
#include "../scanner/token.h"
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
    std::vector< std::map<std::string, psi>> action;
    std::vector< std::map<std::string, int>> go;
    std::set< std::string > variableSet;
    std::set< std::string > terminalSet;

    std::set<std::string> getFirst(const std::vector<std::string> &beta);
    std::set<LR1item> getClosure(const LR1item &item);
    void getClosure(LR1set &closure);

public:
    Parser(){}

    bool openFile(const std::string &fileName);
    void build();

    std::vector<Production> getGrammar();


    std::vector< LR1set > getClosurelist();
    std::map< LR1set, int> getClosuremap();
    std::vector< vpsi > getTransfer();
    std::vector< std::map<std::string, psi>> getAction();
    std::vector< std::map<std::string, int>> getGo();
    int analyse(const std::vector<Token> &tokens);

};
#endif // PARSER_H_INCLUDED
