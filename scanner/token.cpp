#include "token.h"

void Token::setName(const std::string &name)
{
    this->name = name;
}

std::string Token::getName() const
{
    return this->name;
}

void Token::setType(TokenType type)
{
    this->type = type;
}

TokenType Token::getType() const
{
    return this->type;
}

void Token::setLine(size_t line)
{
    this->line = line;
}

size_t Token::getLine() const
{
    return this->line;
}

