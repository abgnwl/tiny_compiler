#ifndef LRITEM_H_INCLUDED
#define LRITEM_H_INCLUDED

#include <vector>
#include <string>

class LR0item
{
private:
    std::pair<int, int> item;
public:
    LR0item()
    {
        item = std::make_pair(0,0);
    }
    LR0item(int l, int r)
    {
        item = std::make_pair(l,r);
    }
    LR0item(std::pair<int, int> item)
    {
        this->item = item;
    }

    std::pair<int, int> getItem() const;

    bool operator==(const LR0item &item) const;
};

class LR1item
{
private:
    std::pair<LR0item, std::string> item;
public:
    LR1item()
    {
        item = std::make_pair(LR0item(), "");
    }
    LR1item(const LR0item &first, const std::string &second)
    {
        item = std::make_pair(first, second);
    }
    LR1item(std::pair<LR0item, std::string> item)
    {
        this->item = item;
    }

    std::pair<LR0item, std::string> getItem() const;

    bool operator==(const LR1item &item) const;
};

#endif // LR1ITEM_H_INCLUDED
