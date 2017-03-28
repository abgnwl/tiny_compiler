#include "Token.h"

void Token::setName(const std::string &name)
{
    this->name = name;
}

std::string Token::getName()
{
    return this->name;
}

void Token::setType(TokenType type)
{
    this->type = type;
}

TokenType Token::getType()
{
    return this->type;
}

void Token::setLine(size_t line)
{
    this->line = line;
}

size_t Token::getLine()
{
    return this->line;
}
