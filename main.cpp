#include <iostream>
#include <cstdio>
#include "scanner/scanner.h"
#include "parser/parser.h"

using namespace std;


void getToken()
{
    Scanner scanner;
    string FileName = "test.txt";

    auto tokens = scanner.getTokens(FileName);

    for(auto token:tokens)
    {
        //cout<<token.getName()<<endl;
        cout<<"    "<<token.getName()<<" "<<TokenDict[token.getType()]<<"  "<<token.getLine()<<endl;
    }
}

void getGrammar()
{
    Parser parser;
    if(parser.openFile("parser/grammar.txt"))
        cout<<"ok"<<endl;
    else
    {
        cout<<"oh no!"<<endl;
        return;
    }
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
    cout<<endl;
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
    cout<<endl;

    cout<<"\t";
    for(auto e:parser.getTerminalSet())
        cout<<e<<"\t";
    for(auto e:parser.getVariableSet())
        cout<<e<<"\t";
    cout<<endl;

    auto action = parser.getAction();
    auto go = parser.getGo();
    for(unsigned int i=0;i<action.size();i++)
    {
        cout<<"I"<<i<<"\t";

        for(auto e:parser.getTerminalSet())
        {
            for(auto one:action[i])
                if(one.first==e)
                    cout<<one.second.first<<one.second.second;
            cout<<"\t";
        }
        for(auto e:parser.getVariableSet())
        {
            for(auto one:go[i])
                if(one.first==e)
                    cout<<one.second<<"\t";
            cout<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
}

void analyse()
{
    Scanner scanner;
    auto tokens = scanner.getTokens("test.txt");
    //for(auto i:tokens)cout<<i.getName()<<" ";cout<<endl;
    Parser parser;
    parser.openFile("parser/grammar.txt");
    parser.build();
    parser.analyse(tokens);
    //cout<<parser.analyse(tokens)<<endl;
}
int main()
{
    freopen("output.txt","w",stdout);
    //getToken();
    //getGrammar();
    analyse();
    return 0;
}
