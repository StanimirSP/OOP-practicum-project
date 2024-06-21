#include "User.h"
#include <utility>
#include <iostream>

User::User(const BankAccount& bankAcc, const std::string& username, const std::string& password): bankAcc(bankAcc), username(username), password(password) {}

User::User(BankAccount&& bankAcc, std::string&& username, std::string&& password) noexcept: bankAcc(std::move(bankAcc)), username(std::move(username)), password(std::move(password)) {}

const std::string& User::getUsername() const noexcept
{
    return username;
}

bool User::login(const std::string& user, const std::string& pass)
{
    if(user == username && pass == password)
        isLoggedIn = true;
    return isLoggedIn;
}

void User::logout()
{
    isLoggedIn = false;
}

void User::deleteCart()
{
    cart.clear();
}

User User::read(std::istream& is)
{
    auto bankAcc = BankAccount::read(is);
    std::string username, password;
    std::getline(is, username);
    std::getline(is, password);
    return {bankAcc, username, password};
}

std::ostream& operator<<(std::ostream& os, const User& u)
{
    return os << u.bankAcc << '\n' << u.username << '\n' << u.password;
}
