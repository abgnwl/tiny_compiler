#include <iostream>
#include <cstdio>
#include "Scanner.h"

using namespace std;

int main()
{
    Scanner scanner;
    string FileName = "D:/Workspace/Tiny_Compiler/bin/Debug/test.cpp";
    auto tokens = scanner.getTokens(FileName);
    for(auto token:tokens)
        cout<<token.getName()<<" "<<token.getLine()<<endl;
    getchar();
    return 0;
}
