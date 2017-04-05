#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <string>
#include "tokentype.h"

class Token
{
private:
    std::string name;
    TokenType type;
    size_t line;

public:
    Token()
    {
        name = "";
        type = TokenType::OTHER;
        line = 0;
    }

    Token(std::string name, TokenType type, size_t line)
    {
        this->name = name;
        this->type = type;
        this->line = line;
    }

    operator bool()
    {
        if(type == TokenType::OTHER)
            return false;
        else
            return true;
    }

    void setName(const std::string &name);
    std::string getName();
    void setType(TokenType type);
    TokenType getType();
    void setLine(size_t line);
    size_t getLine();
};


#endif // TOKEN_H_INCLUDED
