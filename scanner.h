#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include "token.h"
#include "tokentype.h"

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
    std::string::iterator iter;
    size_t line;


    void skipBlank();

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

    bool openFile();
    bool exit();
    Token getNextToken();

public:
    Scanner(){}
    std::vector<Token> getTokens(const std::string FileName);
};

#endif // SCANNER_H_INCLUDED
