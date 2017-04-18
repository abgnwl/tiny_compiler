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
    auto now = parser.getGrammar();
    for(auto i:now)
    {
        cout<<i.getLeft()<<" ";
        for(auto j:i.getRight())
            cout<<j<<" ";
        cout<<endl;
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
    getchar();

    return 0;
}
