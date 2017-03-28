#include "scanner.h"

void Scanner::skipBlank()
{

}

    void dealBegin();
    void dealKeyWord();
    void dealID();
    void dealInteger();
    void dealFloat();
    void dealOperator();
    void dealDelimiter();
    void dealEnd();

    void setProc(Process proc);
    Process getProce();
    void setFileName(const std::tring &FileName);
    std::string getFileName();

bool Scanner::openFile()
{

}

Token Scanner::getNextToken()
{

}


std::vector<Token> Scanner::getTokens(const std::string FileName)
{
    std::vector<Token> tokens;
    if(openFile(FileName))
    {
        for(Token token = getNextToken() && token;; token = getNextToken())
        {
            tokens.push_back(token);
        }
    }
    return tokens;
}
