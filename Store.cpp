#include "Store.h"
#include <utility>
#include <iostream>
#include <stdexcept>

void Store::destroyAllItems(std::vector<Item*>& items)
{
    for(auto pi: items)
        delete pi;
}

void Store::cloneAllItems(std::vector<Item*>& dest, const std::vector<Item*>& src) try
{
    for(auto pi: src)
        dest.push_back(pi->clone());
}
catch(...)
{
    destroyAllItems(dest);
    throw;
}

Store::Store(const BankAccount& bankAcc): bankAcc(bankAcc) {}

Store::Store(BankAccount&& bankAcc): bankAcc(std::move(bankAcc)) {}

Store::Store(const Store& s): bankAcc(s.bankAcc)
{
    items.reserve(s.items.capacity());
    cloneAllItems(items, s.items);
}

Store& Store::operator=(const Store& s)
{
    if(this != &s)
    {
        std::vector<Item*> temp;
        temp.reserve(s.items.capacity());
        cloneAllItems(temp, s.items);
        std::swap(items, temp);
        destroyAllItems(temp);
		bankAcc=s.bankAcc;
    }
    return *this;
}

Store& Store::operator=(Store&& s)
{
    if(this != &s)
    {
        destroyAllItems(items);
        bankAcc=std::move(s.bankAcc);
        items=std::move(s.items);
    }
    return *this;
}

Store::~Store()
{
    destroyAllItems(items);
}

std::size_t Store::itemsCount() const
{
    return items.size();
}

bool Store::addItemToCart(std::size_t index, User& u) const
{
    if(!u.isLoggedIn) throw std::logic_error("User not logged in");
    if(index >= 1 && index <= items.size())
    {
        for(auto id: u.cart)
            if(id == items[index-1]->getID())
                return false;
        u.cart.push_back(items[index-1]->getID());
        return true;
    }
    return false;
}

void Store::printCartOfUser(std::ostream& os, const User& u) const
{
    if(!u.isLoggedIn) throw std::logic_error("User not logged in");
    for(auto id: u.cart)
    {
        std::size_t i=0;
        for(; i<items.size(); i++)
            if(id == items[i]->getID())
            {
                items[i]->print(os << items[i]->getID() << '\t', ' ') << '\n';
                break;
            }
        if(i >= items.size()) throw std::logic_error("Some items are no longer available");
    }
}

bool Store::checkout(User& u)
{
    if(!u.isLoggedIn) throw std::logic_error("User not logged in");
    double toPay = 0;
    std::size_t last = items.size();
    for(auto id: u.cart)
    {
        for(std::size_t i=0; i<last; i++)
            if(id == items[i]->getID())
            {
                toPay += items[i]->getPrice();
                std::swap(items[i], items[--last]);
                goto cont;
            }
        throw std::logic_error("Some items are no longer available");
        cont:;
    }
    if(!u.bankAcc.sendMoney(bankAcc, toPay)) return false;
    u.deleteCart();
    while(last < items.size()) items.pop_back();
    return true;
}

std::ostream& Store::filterByName(std::ostream& os, const std::string& nameContains) const
{
    for(std::size_t i=0; i<items.size(); i++)
        if(items[i]->getName().find(nameContains) != std::string::npos)
            items[i]->print(os << (i+1) << ". ", ' ') << '\n';
    return os;
}

std::ostream& Store::filterByType(std::ostream& os, Item::Type type) const
{
    for(std::size_t i=0; i<items.size(); i++)
        if(items[i]->type() == type)
            items[i]->print(os << (i+1) << ". ", ' ') << '\n';
    return os;
}

std::ostream& Store::filterByPrice(std::ostream& os, double minPrice, double maxPrice) const
{
    for(std::size_t i=0; i<items.size(); i++)
        if(items[i]->getPrice() >= minPrice && items[i]->getPrice() <= maxPrice)
            items[i]->print(os << (i+1) << ". ", ' ') << '\n';
    return os;
}

std::ostream& Store::showAllItems(std::ostream& os, bool readable) const
{
    for(auto pi: items)
        pi->print(os, '\n', readable) << '\n';
    return os;
}

#include "Shoes.h"
#include "Bucket.h"
#include "Candies.h"

std::istream& Store::loadItems(std::istream& is)
{
    std::string type;
    while((is >> type).ignore())
        if(type == "Shoes")
            items.push_back(Shoes::create(is).clone());
        else if(type == "Bucket")
            items.push_back(Bucket::create(is).clone());
        else if(type == "Candies")
            items.push_back(Candies::create(is).clone());
        else
        {
            is.setstate(std::ios_base::failbit);
            return is;
        }
    return is;
}
