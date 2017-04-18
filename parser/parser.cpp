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
            cout<<"get str="<<str<<"|"<<endl;
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
