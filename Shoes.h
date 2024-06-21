#ifndef SHOES_H
#define SHOES_H

#include "Item.h"
#include "Color.h"

class Shoes: public Item
{
    Color color;
    unsigned short size;
public:
    Shoes(const std::string& name, const std::string& description, double price, Color color, unsigned short size);
    Shoes(std::string&& name, std::string&& description, double price, Color color, unsigned short size);
    Color getColor() const noexcept;
    unsigned short getSize() const noexcept;
    std::ostream& print(std::ostream& os, char delim = '\n', bool readable = true) const override;
    [[nodiscard]] Shoes* clone() const& override;
    [[nodiscard]] Shoes* clone() && override;
    static Shoes create(std::istream& is);
};

#endif // SHOES_H
