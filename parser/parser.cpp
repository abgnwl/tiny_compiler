#include "parser.h"
#include "production.h"
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#define test

#ifdef test
#include <iostream>
using namespace std;
#endif // test



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

void Parser::getClosure(const LR1item &item)
{
    std::set<LR1item> closure = {item};
    Closure(closure);
}

void Parser::getClosure(std::set<LR1item> &closure)
{
    std::set<LR1item> temp;

    for(;;)
    {
        temp = closure;

        for(auto item:closure)
            for(auto production:grammar)
                for(auto )
                {

                    if(closure.find()==closure.end())
                        temp.insert()
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
