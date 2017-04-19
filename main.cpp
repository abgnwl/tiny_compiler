#include <iostream>
#include <cstdio>
#include "scanner/scanner.h"
#include "parser/parser.h"

using namespace std;


void getToken()
{
    Scanner scanner;
    string FileName = "test.cpp";

    auto tokens = scanner.getTokens(FileName);

    for(auto token:tokens)
    {
        TokenType type = token.getType();
        //cout<<token.getName()<<endl;
        if(type==TokenType::ID||type==TokenType::FLOAT||type==TokenType::INT||type==TokenType::CHAR||type==TokenType::STRING)
            cout<<"("<<TokenCode[TokenDict[token.getType()]]<<","<<token.getName()<<")";
        else
            cout<<"("<<TokenCode[token.getName()]<<", )";
        cout<<"    "<<token.getName()<<" "<<TokenDict[token.getType()]<<"  "<<token.getLine()<<endl;
    }
}

void getGrammar()
{
    Parser parser;
    if(parser.openFile("parser/grammar.txt"))
        cout<<"ok"<<endl;
    parser.build();
    auto grammar = parser.getGrammar();
    auto closurelist = parser.getClosurelist();
    auto closuremap = parser.getClosuremap();
    for(auto lr1set:closurelist)
    {
        cout<<"I"<<closuremap[lr1set]<<endl;
        for(auto lr1:lr1set)
        {
            cout<<"  ";
            auto id = lr1.getLeft().getLeft();
            auto point = lr1.getLeft().getRight();
            auto str = lr1.getRight();
            cout<<grammar[id].getLeft()<<"->";
            auto right = grammar[id].getRight();
            for(unsigned int i=0;i<right.size();i++)
            {
                if(i==point)
                    cout<<".";
                cout<<right[i];
            }
            if(point==right.size())
                cout<<".";
            cout<<"|"<<str<<endl;
        }
    }
    auto transfer = parser.getTransfer();
    for(unsigned int i=0;i<transfer.size();i++)
    {
        if(transfer[i].size())
        {
            cout<<"from I"<<i<<":"<<endl;
            for(auto e:transfer[i])
            {
                cout<<"  str=|"<<e.first<<"|  to  I"<<e.second<<endl;
            }
        }
    }

    auto action = parser.getAction();
    auto go = parser.getGo();
    for(unsigned int i=0;i<action.size();i++)
    {
        cout<<"I"<<i<<" ";
        for(auto one:action[i])
            cout<<one.first<<","<<one.second.first<<one.second.second<<" ";
        for(auto one:go[i])
            cout<<one.first<<","<<one.second<<" ";
        cout<<endl;
    }
}

void analyse()
{
    Scanner scanner;
    auto tokens = scanner.getTokens("test.cpp");
    for(auto i:tokens)cout<<i.getName()<<" ";cout<<endl;
    Parser parser;
    parser.openFile("parser/grammar.txt");
    cout<<parser.analyse(tokens)<<endl;
}
int main()
{
    getGrammar();
    analyse();
    return 0;
}
