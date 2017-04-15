#include "production.h"

std::string Production::getLeft()
{
    return left;
}

std::vector<std::string> Production::getRight()
{
    return right;
}

void Production::setLeft(std::string left)
{
    this->left = left;
}

void Production::setRight(std::vector<std::string> right)
{
    this->right = right;
}

