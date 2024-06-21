#ifndef USER_H
#define USER_H

#include "BankAccout.h"
#include <string>
#include <vector>
#include <cstddef>
#include <iosfwd>

class User
{
    friend class Store;
    BankAccount bankAcc;
    std::string username;
    std::string password;
    std::vector<std::size_t> cart;
    bool isLoggedIn = false;
public:
    User(const BankAccount& bankAcc, const std::string& username, const std::string& password);
    User(BankAccount&& bankAcc, std::string&& username, std::string&& password) noexcept;
    const std::string& getUsername() const noexcept;
    bool login(const std::string& user, const std::string& pass);
    void logout();
    void deleteCart();
    static User read(std::istream& is);
    friend std::ostream& operator<<(std::ostream& os, const User& u);
};

#endif // USER_H
