#ifndef BUCKET_H
#define BUCKET_H

#include "Item.h"

class Bucket: public Item
{
    double volume;
public:
    Bucket(const std::string& name, const std::string& description, double price, double volume);
    Bucket(std::string&& name, std::string&& description, double price, double volume);
    double getVolume() const noexcept;
    std::ostream& print(std::ostream& os, char delim = '\n', bool readable = true) const override;
    [[nodiscard]] Bucket* clone() const& override;
    [[nodiscard]] Bucket* clone() && override;
    static Bucket create(std::istream& is);
};

#endif // BUCKET_H
