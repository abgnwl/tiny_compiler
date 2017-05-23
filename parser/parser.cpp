#include "parser.h"
#include "production.h"
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <queue>
#include <stack>
#include <sstream>
#define test

#ifdef test
#include <iostream>
using namespace std;
#endif // test

int Parser::analyse(const std::vector<Token> &tokens)
{
    build();
    std::stack<std::pair<unsigned int, std::string>> st;
    st.push({0,"$"});

    auto iter = tokens.cbegin();
    for(; ; )
    {
        auto I = st.top().first;
        if(action[I].find(iter->getName()) != action[I].end())
        {
            auto act = action[I][iter->getName()];
            if(act.first == "S")
            {
                st.push({act.second,iter->getName()});
                iter++;
            }
            else if(act.first == "r")
            {
                auto id = act.second;
                auto right = grammar[id].getRight();
                for(unsigned int i=0; i<right.size(); i++)
                    st.pop();
                auto newI = st.top().first;
                st.push({go[newI][grammar[id].getLeft()],grammar[id].getLeft()});
                std::cout<<"use production: "<<grammar[id].getLeft()<<"->";for(auto e:right)std::cout<<e;std::cout<<std::endl;
            }
            else if(act.first == "acc")
            {
                std::cout<<"Accept!"<<std::endl;
                return 0;
            }
        }
        else
        {
            std::cout<<"ERROR! at line "<<iter->getLine()<<std::endl;
            return iter->getLine();
        }
    }
    return 0;
}

std::set<std::string> Parser::getFirst(const std::vector<std::string> &beta)
{
    if(terminalSet.find(beta[0])!=terminalSet.end())
        return std::set<std::string>{beta[0]};

    std::set<std::string> ret;
    bool isAllEmpty = 1;

    for(auto str:beta)
    {
        if(terminalSet.find(str)!=terminalSet.end())  // symbol in terminal set
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

                    if(right.empty())
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

    auto closure0 = getClosure(LR1item(LR0item(0,0), "$"));

    std::queue<LR1set> q;
    q.push(closure0);

    //closuremap[closure0] = closuremap.size();   // first insert closure, then map[closure] = 1

    closurelist.push_back(closure0);
    closuremap.insert(make_pair(closure0,closuremap.size()));


    while(!q.empty())
    {
        auto lr1set = q.front();
        q.pop();
        transfer.push_back(vpsi());

        for(auto variable:variableSet)
        {
            LR1set newset;
            for(auto lr1:lr1set)
            {
                auto lr0 = lr1.getLeft();
                auto id = lr0.getLeft();
                auto pointpos = lr0.getRight();
                if(grammar[id].getRight().size()>pointpos && grammar[id].getRight()[pointpos]==variable)
                    newset.insert(LR1item(LR0item(id,pointpos+1),lr1.getRight()));
            }
            if(newset.size()!=0)
            {
                getClosure(newset);
                if(closuremap.find(newset)==closuremap.end())
                {
                    closurelist.push_back(newset);
                    closuremap.insert(make_pair(newset,closuremap.size()));
                    //closuremap[newset]=closuremap.size();
                    q.push(newset);
                }
                transfer[transfer.size()-1].push_back(make_pair(variable,closuremap[newset]));
            }
        }

        for(auto terminal:terminalSet)
        {
            LR1set newset;
            for(auto lr1:lr1set)
            {
                auto lr0 = lr1.getLeft();
                auto id = lr0.getLeft();
                auto pointpos = lr0.getRight();
                if(grammar[id].getRight().size()!=pointpos && grammar[id].getRight()[pointpos]==terminal)
                    newset.insert(LR1item(LR0item(id,pointpos+1),lr1.getRight()));
            }
            if(newset.size()!=0)
            {
                getClosure(newset);
                if(closuremap.find(newset)==closuremap.end())
                {
                    closurelist.push_back(newset);
                    closuremap.insert(make_pair(newset,closuremap.size()));
                    //closuremap[newset]=closuremap.size();
                    q.push(newset);
                }
                transfer[transfer.size()-1].push_back(std::make_pair(terminal,closuremap[newset]));
            }
        }
    }

    for(unsigned int i=0; i<closurelist.size(); i++)
    {
        action.push_back(std::map<std::string, psi>());
        go.push_back(std::map<std::string, int>());

        for(auto lr1:closurelist[i])
        {
            auto point = lr1.getLeft().getRight();
            auto right = grammar[lr1.getLeft().getLeft()].getRight();
            if(point < right.size() && terminalSet.find(right[point])!=terminalSet.end())
            {
                for(auto go:transfer[i])
                    if(go.first==right[point])
                    {
                        if(action[i].find(right[point]) != action[i].end()
                           && action[i][right[point]] !=s td::pair<std::string, int>("S",go.second))
                        {
                            std::cout<<"error 1 at action["<<i<<"]["<<right[point]<<"]=S"<<go.second;
                            std::cout<<"  old="<<action[i][right[point]].first<<action[i][right[point]].second<<std::endl;
                        }
                        action[i][right[point]]=std::make_pair("S",go.second);
                    }
            }
        }

        for(auto tf:transfer[i])
        {
            if(variableSet.find(tf.first)!=variableSet.end())
            {
                if(go[i].find(tf.first)!=go[i].end())
                    std::cout<<"error at go["<<i<<"]["<<tf.first<<"]"<<std::endl;

                go[i][tf.first]=tf.second;

            }
        }

        for(auto lr1:closurelist[i])
        {
            auto lookahead = lr1.getRight();
            auto lr0 = lr1.getLeft();
            auto id = lr0.getLeft();
            auto point = lr0.getRight();
            auto right = grammar[id].getRight();

            if(point == right.size())
            {
                if(action[i].find(lookahead)!=action[i].end() && action[i][lookahead]!=std::pair<std::string,int>("r",id))
                    std::cout<<"error 2 at action["<<i<<"]["<<lookahead<<"]=r"<<id<<" old="<<action[i][lookahead].first<<action[i][lookahead].second<<std::endl;

                action[i][lookahead]=std::make_pair("r",id);

                if(lookahead=="$" && id==0)
                {
                    //if(action[i].find(lookahead)!=action[i].end())
                    //cout<<"error 3 at action["<<i<<"]["<<lookahead<<"]=acc"<<endl;

                    action[i][lookahead]=std::make_pair("acc",0);
                }
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
        int type = 0;
        while(in>>str)
        {
            if(str=="[terminal]")
            {
                type = 1;
                continue;
            }
            else if(str=="[variable]")
            {
                type = 2;
                continue;
            }
            else if(str=="[production]")
                break;
            else
            {
                if(type==1)
                    terminalSet.insert(str);
                else if(type==2)
                    variableSet.insert(str);
            }
        }

        while(getline(in,str))
        {
            if(str.empty())
                continue;
            std::string temp;
            std::istringstream iss = std::istringstream(str);
            Production production;
            iss >> temp;
            production.setLeft(temp);
            while(iss >> temp)
            {
              if(temp == "->" || temp == "@")
                continue;
              production.addRight(temp);
            }
            std::cout<<production.getLeft()<<"->";
            for(auto e:production.getRight())
              std::cout<<e<<" ";
            std::cout<<std::endl;
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

            if(pointPos != right.size() && variableSet.find(right[pointPos]) != variableSet.end())
            {
                std::string B = right[pointPos];
                std::vector<std::string> beta;
                for(unsigned int i = pointPos + 1; i < right.size(); i++)
                    beta.push_back(right[i]);
                beta.push_back(lookahead);

                auto first = getFirst(beta);

                #ifdef test
                cout<<"first[";for(auto e:beta)cout<<e<<" ";cout<<"]=";
                for(auto e:first)cout<<"("<<e<<")";
                cout<<endl;
                #endif // test

                for(unsigned int productionID = 0; productionID < grammar.size(); productionID++)
                {
                    const Production &production = grammar[productionID];
                    if(production.getLeft() == B)
                    {
                        for(auto terminal:first)
                        {
                            LR1item newItem = LR1item(LR0item(productionID,0),terminal);
                            if(closure.find(newItem) == closure.end())
                                temp.insert(newItem);
                        }
                    }
                }
            }
        }
        if(temp==closure)
            break;
        else
            closure = temp;
    }
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

std::vector< std::map<std::string, psi>> Parser::getAction()
{
    return action;
}

std::vector< std::map<std::string, int>> Parser::getGo()
{
    return go;
}

std::set< std::string > Parser::getVariableSet()
{
    return variableSet;
}

std::set< std::string > Parser::getTerminalSet()
{
    return terminalSet;
}
