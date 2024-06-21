#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iosfwd>
#include <cstddef>

class Item
{
public:
    enum class Type
    {
        Shoes,
        Bucket,
        Candies,
    };
private:
    inline static std::size_t idCounter = 0;
    std::size_t id = idCounter++;
    Type t;
    std::string name;
    std::string description;
    double price;
public:
    Item(Type t, const std::string& name, const std::string& description, double price);
    Item(Type t, std::string&& name, std::string&& description, double price);
    virtual ~Item() = default;
    Item(const Item& it);
    Item(Item&& it);
    Item& operator=(const Item& it);
    Item& operator=(Item&& it);
    void changeName(const std::string& newName);
    void changeName(std::string&& newName);
    void changeDescription(const std::string& newDescription);
    void changeDescription(std::string&& newDescription);
    void changePrice(double newPrice);
    std::size_t getID() const noexcept;
    Type type() const noexcept;
    const std::string& getName() const noexcept;
    const std::string& getDescription() const noexcept;
    double getPrice() const noexcept;
    virtual std::ostream& print(std::ostream& os, char delim = '\n', bool readable = true) const;
    [[nodiscard]] virtual Item* clone() const& = 0;
    [[nodiscard]] virtual Item* clone() && = 0;
};

std::ostream& operator<<(std::ostream& os, const Item& item);

#endif // ITEM_H
