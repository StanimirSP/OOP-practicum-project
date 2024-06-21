#include "Shoes.h"
#include <iostream>
#include <cstdint>

Shoes::Shoes(const std::string& name, const std::string& description, double price, Color color, unsigned short size):
    Item(Item::Type::Shoes, name, description, price),
    color(color),
    size(size) {}

Shoes::Shoes(std::string&& name, std::string&& description, double price, Color color, unsigned short size):
    Item(Item::Type::Shoes, std::move(name), std::move(description), price),
    color(color),
    size(size) {}

Color Shoes::getColor() const noexcept
{
    return color;
}

unsigned short Shoes::getSize() const noexcept
{
    return size;
}

std::ostream& Shoes::print(std::ostream& os, char delim, bool readable) const
{
    Item::print(os << "Shoes" << delim, delim, readable) << delim;
    if(readable) os << color;
    else os << static_cast<std::uint32_t>(color);
    return os << delim << size;
}

Shoes* Shoes::clone() const&
{
    return new Shoes(*this);
}

Shoes* Shoes::clone() &&
{
    return new Shoes(std::move(*this));
}

Shoes Shoes::create(std::istream& is)
{
    std::string name, description;
    double price;
    std::uint32_t color;
    unsigned short size;
    std::getline(is, name);
    std::getline(is, description) >> price >> color >> size;
    return {name, description, price, Color{color}, size};
}
