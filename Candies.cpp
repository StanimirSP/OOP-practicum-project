#include "Candies.h"
#include <iostream>

Candies::Candies(const std::string& name, const std::string& description, double price, unsigned count, Date expirationDate):
    Item(Item::Type::Candies, name, description, price),
    count(count),
    expirationDate(expirationDate) {}

Candies::Candies(std::string&& name, std::string&& description, double price, unsigned count, Date expirationDate):
    Item(Item::Type::Candies, std::move(name), std::move(description), price),
    count(count),
    expirationDate(expirationDate) {}

unsigned Candies::getCount() const noexcept
{
    return count;
}

Date Candies::getExpirationDate() const noexcept
{
    return expirationDate;
}

std::ostream& Candies::print(std::ostream& os, char delim, bool readable) const
{
    Item::print(os << "Candies" << delim, delim, readable) << delim << count << delim;
    if(readable) os << expirationDate.date("D.M.Y");
    else os << expirationDate.Year() << ' ' << expirationDate.Month() << ' ' << expirationDate.Day();
    return os;
}

Candies* Candies::clone() const&
{
    return new Candies(*this);
}

Candies* Candies::clone() &&
{
    return new Candies(std::move(*this));
}

Candies Candies::create(std::istream& is)
{
    std::string name, description;
    double price;
    unsigned count, year, month, day;
    std::getline(is, name);
    std::getline(is, description) >> price >> count >> year >> month >> day;
    return {name, description, price, count, Date{year, month, day}};
}
