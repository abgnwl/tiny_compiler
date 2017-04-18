#include "parser.h"
#include "production.h"
#include "variable.h"
#include "terminal.h"
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#define test

#ifdef test
#include <iostream>
using namespace std;
#endif // test

std::vector<std::string> Parser::getFirst(const std::vector<std::string> &beta)
{
    std::vector<std::string> first;
    for(auto str:beta)
    {
        if(terminalSet.find(str)!=terminalSet.end())
        {
            first.push_back(str);
            return first;
        }
        else
    }
}

bool Parser::openFile(const std::string &fileName)
{
    std::ifstream in(fileName);

    if(in)
    {
        std::string str;
        while(getline(in,str))
        {
            std::string temp;
            Production production;
            auto iter = str.cbegin();
            while(iter!=str.cend() && isblank(*iter))
                iter++;
            for( ; iter!=str.cend(); )
            {
                if(isblank(*iter))
                {
                    if(production.getLeft()=="")
                        production.setLeft(temp);
                    else
                        production.addRight(temp);
                    temp="";
                    while(iter!=str.cend() && isblank(*iter))
                        iter++;
                }
                else
                {
                    temp+=*iter;
                    iter++;
                }
            }
            production.addRight(temp);
            grammar.push_back(production);
        }
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<Production> Parser::getGrammar()
{
    return grammar;
}

std::set<LR1item> Parser::getClosure(const LR1item &item)
{
    std::set<LR1item> closure = {item};
    getClosure(closure);
}

void Parser::getClosure(std::set<LR1item> &closure)
{
    std::set<LR1item> temp;

    for(;;)
    {
        temp = closure;

        for(auto lr1:closure)
        {
            LR0item lr0 = lr1.getLeft();
            std::string lookahead = lr1.getRight();

            int pointPos = lr0.getRight();
            auto right = grammar[lr0.getLeft()].getRight();

            if(pointPos!=right.size() && variableSet.find(right[pointPos])!=variableSet.end())
            {
                std::string B = right[pointPos];
                std::vector<std::string> beta;
                for(int i = pointPos+1; i<right.size(); i++)
                    beta.push_back(right[i]);
                beta.push_back(lookahead);

                auto first = getFirst(beta);

                for(int productionID = 0; productionID<grammar.size(); productionID++)
                {
                    const Production &production = grammar[productionID];
                    if(production.getLeft() == B)
                        for(auto terminal:first)
                        {
                            LR1item newItem = LR1item(LR0item(productionID,0),terminal);
                            if(closure.find(newItem) == closure.end())
                                temp.insert(newItem);
                        }
                }
            }
        }

        if(temp==closure)
            break;
        else
            closure = temp;
    }

    if(closuremap.find(closure) == closuremap.end())
    {
        closurelist.push_back(closure);
        closuremap[closure] = closurelist.size();
    }
}


std::set<LR1item> Parser::getGo(const std::set<LR1item> &closure, const std::string &variable)
{

}


std::vector< std::set<LR1item> > Parser::getClosurelist()
{
    return closurelist;
}

std::map< std::set<LR1item>, int> Parser::getClosuremap()
{
    return closuremap;
}


std::vector< std::vector<int> > Parser::getTransfer()
{
    return transfer;
}
