#include "Item.h"
#include <utility>
#include <stdexcept>
#include <iostream>

Item::Item(Type t, const std::string& name, const std::string& description, double price): t(t), name(name), description(description)
{
    changePrice(price);
}

Item::Item(Type t, std::string&& name, std::string&& description, double price): t(t), name(std::move(name)), description(std::move(description))
{
    changePrice(price);
}

Item::Item(const Item& it): Item(it.t, it.name, it.description, it.price) {}

Item::Item(Item&& it): Item(it.t, std::move(it.name), std::move(it.description), it.price) {}

Item& Item::operator=(const Item& it)
{
    if(this != &it)
    {
        id = idCounter++;
        t = it.t;
        name = it.name;
        description = it.description;
        price = it.price;
    }
    return *this;
}

Item& Item::operator=(Item&& it)
{
    id = idCounter++;
    t = it.t;
    name = std::move(it.name);
    description = std::move(it.description);
    price = it.price;
    return *this;
}

void Item::changeName(const std::string& newName)
{
    name = newName;
}

void Item::changeName(std::string&& newName)
{
    name = std::move(newName);
}

void Item::changeDescription(const std::string& newDescription)
{
    description = newDescription;
}

void Item::changeDescription(std::string&& newDescription)
{
    description = std::move(newDescription);
}

void Item::changePrice(double newPrice)
{
    if(newPrice < 0) throw std::invalid_argument("newPrice should be non-negative");
    price = newPrice;
}

std::size_t Item::getID() const noexcept
{
    return id;
}

Item::Type Item::type() const noexcept
{
    return t;
}

const std::string& Item::getName() const noexcept
{
    return name;
}

const std::string& Item::getDescription() const noexcept
{
    return description;
}

double Item::getPrice() const noexcept
{
    return price;
}

std::ostream& Item::print(std::ostream& os, char delim, bool readable [[maybe_unused]]) const
{
    return os << name << delim << description << delim << price;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
    return item.print(os);
}
