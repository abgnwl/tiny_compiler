#ifndef TOKENTYPE_H_INCLUDED
#define TOKENTYPE_H_INCLUDED

#include <map>
#include <memory>
#include <string>
#include <vector>

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
    {TokenType::KEYWORD,"KEYWORD"},
    {TokenType::ID,"ID"},
    {TokenType::INT,"INT"},
    {TokenType::FLOAT,"FLOAT"},
    {TokenType::CHAR,"CHAR"},
    {TokenType::STRING,"STRING"},
    {TokenType::OPERATOR,"OPERATOR"},
    {TokenType::DELIMITER,"DELIMITER"},
    {TokenType::OTHER,"OTHER"}
};


static std::vector<std::string> TokenStringType =
{
    //constant
    "INT","FLOAT","CHAR","STRING",
    //id
    "ID",
    //operator
    "+","-","*","/","&","^","~","|","&","++","--","||","&&","!","==","!=","<",">","<=",">=","=",
    //delimiter
    ",",";","{","}","[","]","(",")","#",".","\"","'",
    //keyword
    "break","char","string","const","continue","else","float","for","if","int","return","signed","typedef","unsigned","void","include"
};

static std::map<std::string, int> TokenCode =
{
    {"INT",1},
    {"FLOAT",2},
    {"CHAR",3},
    {"STRING",4},
    {"ID",5},
    {"+",6},
    {"-",7},
    {"*",8},
    {"/",9},
    {"&",10},
    {"^",11},
    {"~",12},
    {"|",13},
    {"&",14},
    {"++",15},
    {"--",16},
    {"||",17},
    {"&&",18},
    {"!",19},
    {"==",20},
    {"!=",21},
    {"<",22},
    {">",23},
    {"<=",24},
    {">=",25},
    {"=",26},
    {",",27},
    {";",28},
    {"{",29},
    {"}",30},
    {"[",31},
    {"]",32},
    {"(",33},
    {")",34},
    {"#",35},
    {".",36},
    {"\"",37},
    {"'",38},
    {"break",39},
    {"char",40},
    {"string",41},
    {"const",42},
    {"continue",43},
    {"else",44},
    {"float",45},
    {"for",46},
    {"if",47},
    {"int",48},
    {"return",49},
    {"signed",50},
    {"typedef",51},
    {"unsigned",52},
    {"void",53},
    {"include",54}
};

#endif // TOKENTYPE_H_INCLUDED
