#include <iostream>
#include <cstdio>
#include "scanner/scanner.h"
#include "parser/parser.h"

using namespace std;

int main()
{
    Parser parser;
    if(parser.openFile("parser/grammar.txt"))
        cout<<"ok"<<endl;

    auto e = parser.getFirst(vector<string>{"S","L"});
    for(auto i:e)
        cout<<"first S="<<i<<endl;

    auto ret = parser.getClosure(LR1item(LR0item(0,0),"$"));
    for(auto i:ret)
    {
        auto j=i.getLeft().getLeft();
        int pos = i.getLeft().getRight();
        auto grammar = parser.getGrammar();
        cout<<grammar[j].getLeft();
        cout<<"->";
        for(auto str:grammar[j].getRight())cout<<str<<" ";
        cout<<" point at"<<pos<<","<<i.getRight()<<endl;
    }
    /*
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
    */
    //getchar();

    return 0;
}
