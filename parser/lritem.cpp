#include "lritem.h"

std::pair<int, int> LR0item::getItem() const
{
    return item;
}

bool LR0item::operator==(const LR0item &item) const
{
    return this->getItem()==item.getItem();
}

std::pair<LR0item, std::string> LR1item::getItem() const
{
    return item;
}

bool LR1item::operator==(const LR1item &item) const
{
    return this->getItem()==item.getItem();
}
