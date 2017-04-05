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


static std::vector<std::string> TokenStringType =
{
    //constant
    "int","float","char","string",
    //id
    "id",
    //operator
    "+","-","*","/","&","^","~","|","&","++","--","||","&&","!","==","!=","<",">","<=",">=","=",
    //delimiter
    ",",";","{","}","[","]","(",")","#",".","\"","'",
    //keyword
    "break","char","const","continue","else","float","for","if","int","return","signed","typedef","unsigned","void","include"
};

static std::map<std::string, int> TokenCode =
{
    {"int",1},
    {"float",2},
    {"char",3},
    {"string",4},
    {"id",5},
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
    {"const",41},
    {"continue",42},
    {"else",43},
    {"float",44},
    {"for",45},
    {"if",46},
    {"int",47},
    {"return",48},
    {"signed",49},
    {"typedef",50},
    {"unsigned",51},
    {"void",52},
    {"include",53}
};

#endif // TOKENTYPE_H_INCLUDED
