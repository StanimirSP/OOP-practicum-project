#ifndef CANDIES_H
#define CANDIES_H

#include "Date.h"
#include "Item.h"

class Candies: public Item
{
    unsigned count;
    Date expirationDate;
public:
    Candies(const std::string& name, const std::string& description, double price, unsigned count, Date expirationDate);
    Candies(std::string&& name, std::string&& description, double price, unsigned count, Date expirationDate);
    unsigned getCount() const noexcept;
    Date getExpirationDate() const noexcept;
    std::ostream& print(std::ostream& os, char delim = '\n', bool readable = true) const override;
    [[nodiscard]] Candies* clone() const& override;
    [[nodiscard]] Candies* clone() && override;
    static Candies create(std::istream& is);
};

#endif // CANDIES_H
