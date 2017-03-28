#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include "token.h"
#include "tokentype.h"
#include <vector>

enum class Process
{
    BEGIN,
    IN_KEYWORD,
    IN_ID,
    IN_INTEGER,
    IN_FLOAT,
    IN_OPERATOR,
    IN_DELIMITER,
    END
};

class Scanner
{
private:
    Process proc;
    std::string FileName;
    std::string code;
    std::string::const_iterator iter;
    size_t line;


    void dealBegin(std::string &name, TokenType &type);
    void dealKeyWord(std::string &name, TokenType &type);
    void dealID(std::string &name, TokenType &type);
    void dealInteger(std::string &name, TokenType &type);
    void dealFloat(std::string &name, TokenType &type);
    void dealOperator(std::string &name, TokenType &type);
    void dealDelimiter(std::string &name, TokenType &type);
    Token dealEnd(const std::string &name, const TokenType &type);

    void skipBlank();
    bool openFile(const std::string &FileName);
    Token getNextToken();

public:
    Scanner(){}
    std::vector<Token> getTokens(const std::string FileName);
};

#endif // SCANNER_H_INCLUDED
