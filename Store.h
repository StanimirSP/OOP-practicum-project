#ifndef STORE_H
#define STORE_H

#include <vector>
#include "BankAccout.h"
#include "Item.h"
#include "User.h"
#include <cstddef>
#include <iosfwd>
#include <limits>

class Store
{
    BankAccount bankAcc;
    std::vector<Item*> items;
    static void destroyAllItems(std::vector<Item*>& items);
    static void cloneAllItems(std::vector<Item*>& dest, const std::vector<Item*>& src);
public:
    Store(const BankAccount& bankAcc);
    Store(BankAccount&& bankAcc);
    Store(const Store& s);
    Store(Store&& s) = default;
    Store& operator=(const Store& s);
    Store& operator=(Store&& s);
    ~Store();
    std::size_t itemsCount() const;
    bool addItemToCart(std::size_t index, User& u) const;
    void printCartOfUser(std::ostream& os, const User& u) const;
    bool checkout(User& u);
    std::ostream& filterByName(std::ostream& os, const std::string& nameContains = "") const;
    std::ostream& filterByType(std::ostream& os, Item::Type type) const;
    std::ostream& filterByPrice(std::ostream& os, double minPrice = 0, double maxPrice = std::numeric_limits<double>::max()) const;
    std::ostream& showAllItems(std::ostream& os, bool readable = true) const;
    std::istream& loadItems(std::istream& is);
};

#endif // STORE_H
