#include "Bucket.h"
#include <iostream>

Bucket::Bucket(const std::string& name, const std::string& description, double price, double volume):
    Item(Item::Type::Bucket, name, description, price),
    volume(volume > 0? volume: throw std::invalid_argument("volume must be positive")) {}

Bucket::Bucket(std::string&& name, std::string&& description, double price, double volume):
    Item(Item::Type::Bucket, std::move(name), std::move(description), price),
    volume(volume > 0? volume: throw std::invalid_argument("volume must be positive")) {}

double Bucket::getVolume() const noexcept
{
    return volume;
}

std::ostream& Bucket::print(std::ostream& os, char delim, bool readable) const
{
    return Item::print(os << "Bucket" << delim, delim, readable) << delim << volume;
}

Bucket* Bucket::clone() const&
{
    return new Bucket(*this);
}

Bucket* Bucket::clone() &&
{
    return new Bucket(std::move(*this));
}

Bucket Bucket::create(std::istream& is)
{
    std::string name, description;
    double price, volume;
    std::getline(is, name);
    std::getline(is, description) >> price >> volume;
    return {name, description, price, volume};
}
