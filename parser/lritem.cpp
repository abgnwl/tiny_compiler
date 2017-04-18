#include "lritem.h"

std::pair<int, int> LR0item::getItem() const
{
    return item;
}

int LR0item::getLeft()
{
    return item.first;
}

int LR0item::getRight()
{
    return item.second;
}

bool LR0item::operator==(const LR0item &item) const
{
    return this->getItem()==item.getItem();
}

std::pair<LR0item, std::string> LR1item::getItem() const
{
    return item;
}

LR0item LR1item::getLeft()
{
    return item.first;
}

std::string LR1item::getRight()
{
    return item.second;
}

bool LR1item::operator==(const LR1item &item) const
{
    return this->getItem()==item.getItem();
}
