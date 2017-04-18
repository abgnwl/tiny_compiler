#include "parser.h"
#include "production.h"
#include "variable.h"
#include "terminal.h"
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <queue>
#define test

#ifdef test
#include <iostream>
using namespace std;
#endif // test

std::set<std::string> Parser::getFirst(const std::vector<std::string> &beta)
{
    if(terminalSet.find(beta[0])!=terminalSet.end() || beta[0]=="@")
        return std::set<std::string>{beta[0]};

    std::set<std::string> ret;
    bool isAllEmpty = 1;
    for(auto str:beta)
    {
        if(terminalSet.find(str)!=terminalSet.end())
        {
            isAllEmpty = 0;
            ret.insert(str);
            return ret;
        }
        else
        {
            bool isEmpty = 0;
            for(auto production:grammar)
                if(production.getLeft()==str)
                {
                    auto right = production.getRight();

                    if(right.size()==1 && right[0]=="@")
                    {
                        isEmpty = 1;
                        continue;
                    }
                    if(terminalSet.find(right[0])!=terminalSet.end())
                    {
                        ret.insert(right[0]);
                        continue;
                    }
                    else
                    {
                        auto first = getFirst(right);
                        for(auto one:first)
                            if(one!="@")
                                ret.insert(one);
                            else
                                isEmpty = 1;
                    }
                }
            if(!isEmpty)
            {
                isAllEmpty = 0;
                break;
            }
        }
    }
    if(isAllEmpty)
        ret.insert("@");
    return ret;
}

void Parser::build()
{
    if(closuremap.size()!=0)
        return;

    auto closure0 = getClosure(LR1item(LR0item(0,0),"$"));
    std::queue<LR1set> q;
    q.push(closure0);
    closuremap[closure0] = closuremap.size();

    //closurelist.push_back(getClosure(LR1item(LR0item(0,0),"$")));
    //closuremap[closurelist[0]]=closurelist.size()-1;

    while(!q.empty())
    {
        auto lr1set = q.front();
        q.pop();
        cout<<"head"<<endl;
        for(auto i:lr1set)cout<<"id="<<i.getLeft().getLeft()<<" point="<<i.getLeft().getRight()<<"  symbol="<<i.getRight()<<endl;
        transfer.push_back(vpsi());

        for(auto terminal:terminalSet)
        {
            LR1set newset;
            for(auto lr1:lr1set)
            {
                auto lr0 = lr1.getLeft();
                auto id = lr0.getLeft();
                auto pointpos = lr0.getRight();
                if(grammar[id].getRight().size()!=pointpos && grammar[id].getRight()[pointpos]==terminal)
                {
                    newset.insert(LR1item(LR0item(id,pointpos+1),lr1.getRight()));
                }
            }
            if(newset.size()!=0)
            {

                getClosure(newset);
                if(closuremap.find(newset)==closuremap.end())
                {
                    //closurelist.push_back(newset);
                    closuremap[newset]=closuremap.size();
                    //cout<<"push newset, terminal=|"<<terminal<<endl;
                    //for(auto i:newset)cout<<"id="<<i.getLeft().getLeft()<<" point="<<i.getLeft().getRight()<<"  symbol="<<i.getRight()<<endl;
                    q.push(newset);
                }
                transfer[transfer.size()-1].push_back(std::make_pair(terminal,closuremap[newset]));
            }
        }

        for(auto variable:variableSet)
        {
            LR1set newset;
            for(auto lr1:lr1set)
            {
                auto lr0 = lr1.getLeft();
                auto id = lr0.getLeft();
                auto pointpos = lr0.getRight();
                if(grammar[id].getRight().size()>pointpos && grammar[id].getRight()[pointpos]==variable)
                {
                    newset.insert(LR1item(LR0item(id,pointpos+1),lr1.getRight()));
                }
            }
            if(newset.size()!=0)
            {
                getClosure(newset);
                if(closuremap.find(newset)==closuremap.end())
                {
                    //closurelist.push_back(newset);
                    closuremap[newset]=closuremap.size();
                    //cout<<"push newset, variable=|"<<variable<<endl;
                    //for(auto i:newset)cout<<"id="<<i.getLeft().getLeft()<<" point="<<i.getLeft().getRight()<<"  symbol="<<i.getRight()<<endl;
                    q.push(newset);
                }
                transfer[transfer.size()-1].push_back(make_pair(variable,closuremap[newset]));
            }
        }
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
            if(str=="")
                continue;
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
    return closure;
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

            unsigned int pointPos = lr0.getRight();
            auto right = grammar[lr0.getLeft()].getRight();

            if(pointPos!=right.size() && variableSet.find(right[pointPos])!=variableSet.end())
            {
                std::string B = right[pointPos];
                std::vector<std::string> beta;
                for(unsigned int i = pointPos+1; i<right.size(); i++)
                    beta.push_back(right[i]);
                beta.push_back(lookahead);

                auto first = getFirst(beta);

                for(unsigned int productionID = 0; productionID<grammar.size(); productionID++)
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
/*
    if(closuremap.find(closure) == closuremap.end())
    {
        closurelist.push_back(closure);
        closuremap[closure] = closurelist.size();
    }
    */
}


std::vector< std::set<LR1item> > Parser::getClosurelist()
{
    return closurelist;
}

std::map< std::set<LR1item>, int> Parser::getClosuremap()
{
    return closuremap;
}


std::vector< vpsi > Parser::getTransfer()
{
    return transfer;
}
