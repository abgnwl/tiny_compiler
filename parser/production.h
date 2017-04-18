#ifndef GRAMMAR_H_INCLUDED
#define GRAMMAR_H_INCLUDED

#include <string>
#include <vector>

class Production
{
private:
    std::string left;
    std::vector<std::string> right;

public:

    Production(){left="";}

    Production(std::string left, std::vector<std::string>right)
    {
        this->left = left;
        this->right = right;
    }

    std::string getLeft();
    std::vector<std::string> getRight();
    void setLeft(std::string left);
    void setRight(std::vector<std::string> right);
    void addRight(std::string rightOne);
};

#endif // GRAMMAR_H_INCLUDED
