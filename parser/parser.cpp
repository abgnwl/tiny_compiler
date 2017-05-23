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

// analyze the tokens with grammar
int Parser::analyse(const std::vector<Token> &tokens)
{
    build();
    std::stack<std::pair<unsigned int, std::string>> st;
    st.push({0,"$"});

    auto iter = tokens.cbegin();
    for(; ; )
    {
        auto I = st.top().first;
        string name;
        if(iter->getType() == TokenType::ID || iter->getType() == TokenType::CHAR
           || iter->getType() == TokenType::INT || iter->getType()== TokenType::FLOAT )
            name = TokenDict[iter->getType()];
        else
            name = iter->getName();

        if(action[I].find(name) != action[I].end())
        {
            auto act = action[I][name];
            if(act.first == "S")
            {
                st.push({act.second, name});
                iter++;
            }
            else if(act.first == "r")
            {
                auto id = act.second;
                auto right = grammar[id].getRight();
                for(unsigned int i=0; i<right.size(); i++)
                    if(right[i] != "@")
                        st.pop();
                auto newI = st.top().first;
                st.push({go[newI][grammar[id].getLeft()],grammar[id].getLeft()});
                #ifdef test
                cout<<"use production: "<<grammar[id].getLeft()<<"->";
                for(auto e:right)cout<<e;
                cout<<endl;
                #endif // test
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

// get one symbol's first set
std::set<std::string> Parser::getFirst(const std::string &symbol)
{
    if(firstMap.find(symbol) != firstMap.end())         // have this set, then return
        return firstMap[symbol];
    std::set<std::string> ret;
    if(terminalSet.find(symbol) != terminalSet.end())   // is a terminal symbol
    {
        ret.insert(symbol);
        return ret;
    }
    else                                                // is a variable symbol
    {
        for(auto production:grammar)
        {
            if(production.getLeft() == symbol)
            {
                auto right = production.getRight();
                if(right.size() == 1 && right[0] == "@")  //insert @
                {
                    ret.insert("@");
                    continue;
                }
                else if(right.size() > 0                //insert the first terminal symbol
                        && terminalSet.find(right[0]) != terminalSet.end())
                {
                    ret.insert(right[0]);
                    continue;
                }
            }
        }
    }
    #ifdef test
    cout<<"get one symbol first["<<symbol<<"]=";
    for(auto e:ret)cout<<e<<" ";
    cout<<endl;
    #endif // test
    return ret;
}

// build the first Map, firstMap[x] = first(x)
void Parser::buildFirstMap()
{
    firstMap.clear();

    // basic
    for(auto symbol : terminalSet)
        firstMap.insert({symbol, getFirst(symbol)});
    for(auto symbol : variableSet)
        firstMap.insert({symbol, getFirst(symbol)});

    // merge
    for(; ; )
    {
        bool changed = false;
        for(auto symbol : variableSet)
        {
            //if(symbol == "ADD")cout<<"get first (add) "<<endl;
            for(;;)
            {
                auto temp = firstMap[symbol];
                //if(symbol == "ADD"){cout<<"first= ";for(auto e:temp)cout<<e<<" ";cout<<endl;}
                for(auto produciton : grammar)
                {
                    if(produciton.getLeft() == symbol)
                    {
                        bool allEmpty = true;
                        auto right = produciton.getRight();
                        //if(symbol == "ADD"){cout<<"  right= ";for(auto e:right)cout<<e<<" ";cout<<endl;}
                        for(auto one:right)
                        {
                            auto oneSet = firstMap[one];
                            //if(symbol == "ADD"){cout<<"  oneset= ";for(auto e:oneSet)cout<<e<<" ";cout<<endl;}
                            if(oneSet.erase("@"))
                            {
                                temp.insert(oneSet.begin(), oneSet.end());
                            }
                            else
                            {
                                temp.insert(oneSet.begin(), oneSet.end());
                                allEmpty = false;
                                break;
                            }
                        }
                        if(allEmpty)
                            temp.insert("@");
                    }
                }
                //if(symbol == "ADD"){cout<<" now tot = ";for(auto e:temp)cout<<e<<" ";cout<<endl;}
                if(temp == firstMap[symbol])
                    break;
                firstMap[symbol] = temp;
                changed = true;
            }
        }
        if(!changed)
            break;
    }
}

// get first(beta), beta = A1A2...An
std::set<std::string> Parser::getFirst(const std::vector<std::string> &beta)
{
    std::set<std::string> ret;
    bool allEmpty = true;
    for(auto one:beta)
    {
        auto oneSet = firstMap[one];
        if(oneSet.erase("@"))
        {
            ret.insert(oneSet.begin(), oneSet.end());
        }
        else
        {
            ret.insert(oneSet.begin(), oneSet.end());
            allEmpty = false;
            break;
        }
    }
    if(allEmpty)
        ret.insert("@");
    return ret;
}

// build action and goto table
void Parser::build()
{
    if(closuremap.size() != 0)                      // have built action and goto table
        return;

    buildFirstMap();

    auto closure0 = getClosure(LR1item(LR0item(0,0), "$"));

    std::queue<LR1set> q;
    q.push(closure0);

    //closuremap[closure0] = closuremap.size();     // first insert closure, then map[closure] = 1

    closurelist.push_back(closure0);
    closuremap.insert(make_pair(closure0, closuremap.size()));


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
                        #ifdef test
                        if(action[i].find(right[point]) != action[i].end()
                           && action[i][right[point]] != pair<string, int>("S", go.second))
                        {
                            cout<<"error 1 at action["<<i<<"]["<<right[point]<<"]=S"<<go.second;
                            cout<<"  old="<<action[i][right[point]].first<<action[i][right[point]].second<<endl;
                        }
                        #endif // test
                        action[i][right[point]]=std::make_pair("S",go.second);
                    }
            }
        }

        for(auto tf:transfer[i])
        {
            if(variableSet.find(tf.first)!=variableSet.end())
            {
                #ifdef test
                if(go[i].find(tf.first)!=go[i].end())
                    cout<<"error at go["<<i<<"]["<<tf.first<<"]"<<endl;
                #endif // test
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
                #ifdef test
                if(action[i].find(lookahead)!=action[i].end()
                   && action[i][lookahead]!=pair<string,int>("r",id))
                    cout<<"error 2 at action["<<i<<"]["<<lookahead<<"]=r"<<id<<" old="<<action[i][lookahead].first<<action[i][lookahead].second<<std::endl;
                #endif
                action[i][lookahead]=std::make_pair("r",id);

                if(lookahead=="$" && id==0)
                {
                    action[i][lookahead]=std::make_pair("acc",0);
                }
            }
        }
    }
}

// open grammar.txt, read grammar
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
              if(temp == "->")
                continue;
              production.addRight(temp);
            }
            #ifdef test
            /*
            cout<<production.getLeft()<<"->";
            for(auto e:production.getRight())
              cout<<e<<" ";
            cout<<endl;
            */
            #endif // test
            grammar.push_back(production);
        }
        return true;
    }
    else
    {
        return false;
    }
}

// get grammar
std::vector<Production> Parser::getGrammar()
{
    return grammar;
}

// get a closure set with LR1item item
std::set<LR1item> Parser::getClosure(const LR1item &item)
{
    std::set<LR1item> closure = {item};
    getClosure(closure);
    return closure;
}

// get the closure
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

                for(unsigned int productionID = 0; productionID < grammar.size(); productionID++)
                {
                    const Production &production = grammar[productionID];
                    if(production.getLeft() == B)
                    {
                        for(auto terminal:first)
                        {
                            LR1item newItem;
                            if(production.getRight().size() == 1 && production.getRight()[0] == "@")
                                newItem = LR1item(LR0item(productionID, 1), terminal);
                            else
                                newItem = LR1item(LR0item(productionID, 0), terminal);
                            if(closure.find(newItem) == closure.end())
                                temp.insert(newItem);
                        }
                    }
                }
            }
        }
        if(temp == closure)
            break;
        else
            closure = temp;
    }
}

// get closure list
std::vector< std::set<LR1item> > Parser::getClosurelist()
{
    return closurelist;
}

// get closure map
std::map< std::set<LR1item>, int> Parser::getClosuremap()
{
    return closuremap;
}

// get transfer
std::vector< vpsi > Parser::getTransfer()
{
    return transfer;
}

// get action table
std::vector< std::map<std::string, psi>> Parser::getAction()
{
    return action;
}

// get goto table
std::vector< std::map<std::string, int>> Parser::getGo()
{
    return go;
}

// get variable symbol set
std::set< std::string > Parser::getVariableSet()
{
    return variableSet;
}

// get terminal symbol set
std::set< std::string > Parser::getTerminalSet()
{
    return terminalSet;
}
