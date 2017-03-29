#include "tokentype.h"


std::shared_ptr<TokenDict>TokenDictInstance::getTokenDictPtr()
{
    if(!TokenDictPtr)
    {
        TokenDictPtr = std::make_shared<TokenDict>();
        TokenDictPtr->insert({TokenType::KEYWORD, "KEYWORD"});
        TokenDictPtr->insert({TokenType::ID, "ID"});
        TokenDictPtr->insert({TokenType::INT, "INT"});
        TokenDictPtr->insert({TokenType::FLOAT, "FLOAT"});
        TokenDictPtr->insert({TokenType::OPERATOR, "OPERATOR"});
        TokenDictPtr->insert({TokenType::DELIMITER, "DELIMITER"});
        TokenDictPtr->insert({TokenType::OTHER, "OTHER"});
        TokenDictPtr->insert({TokenType::CHAR, "CHAR"});
        TokenDictPtr->insert({TokenType::STRING, "STRING"});
    }
    return TokenDictInstance::TokenDictPtr;
}
