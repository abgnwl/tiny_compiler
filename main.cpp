#include <iostream>
#include <cstdio>
#include "scanner/scanner.h"

using namespace std;

int main()
{
    Scanner scanner;
    string FileName = "D:/Workspace/Tiny_Compiler/bin/Debug/test.cpp";

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
    getchar();
    return 0;
}
