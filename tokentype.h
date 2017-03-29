#ifndef TOKENTYPE_H_INCLUDED
#define TOKENTYPE_H_INCLUDED

#include <map>
#include <memory>
#include <string>

enum class TokenType
{
    KEYWORD,
    ID,
    INT,
    FLOAT,
    CHAR,
    STRING,
    OPERATOR,
    DELIMITER,
    OTHER
};

static std::map<TokenType, std::string> TokenDict=
{
    {TokenType::KEYWORD,"keyword"},
    {TokenType::ID,"id"},
    {TokenType::INT,"int"},
    {TokenType::FLOAT,"float"},
    {TokenType::CHAR,"char"},
    {TokenType::STRING,"string"},
    {TokenType::OPERATOR,"operator"},
    {TokenType::DELIMITER,"delimiter"},
    {TokenType::OTHER,"other"}
};

#endif // TOKENTYPE_H_INCLUDED
