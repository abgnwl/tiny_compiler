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
    OPERATOR,
    DELIMITER,
    OTHER
};

typedef std::map<TokenType, std::string> TokenDict;


class TokenDictInstance
{
private:
    std::shared_ptr<TokenDict> TokenDictPtr;
public:
    std::shared_ptr<TokenDict> getTokenDictPtr();

};


#endif // TOKENTYPE_H_INCLUDED
