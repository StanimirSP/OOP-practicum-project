#include "BankAccout.h"
#include <utility>
#include <iostream>

BankAccount::BankAccount(const Person& owner, double initialBalance):
    owner(owner),
    balance(initialBalance >= 0? initialBalance: throw std::invalid_argument("initialBalance should be non-negative")) {}

BankAccount::BankAccount(Person&& owner, double initialBalance):
    owner(std::move(owner)),
    balance(initialBalance >= 0? initialBalance: throw std::invalid_argument("initialBalance should be non-negative")) {}

const Person& BankAccount::getOwner() const
{
    return owner;
}

bool BankAccount::sendMoney(BankAccount& receiver, double amount)
{
    if(amount < 0) throw std::invalid_argument("amount should be non-negative");
    if(amount > balance) return false;
    balance -= amount;
    receiver.balance += amount;
    return true;
}

double BankAccount::checkBalance() const noexcept
{
    return balance;
}

bool BankAccount::deposit(double amount)
{
    if(amount < 0) throw std::invalid_argument("amount should be non-negative");
    // get the money and add them to the account
    balance += amount;
    return true;
}

bool BankAccount::withdraw(double amount)
{
    if(amount < 0) throw std::invalid_argument("amount should be non-negative");
    if(amount > balance) return false;
    // remove the money from the account and give them to the owner
    balance -= amount;
    return true;
}

BankAccount BankAccount::read(std::istream& is)
{
    auto p = Person::read(is);
    double balance;
    is >> balance;
    is.ignore();
    return {p, balance};
}

std::ostream& operator<<(std::ostream& os, const BankAccount& acc)
{
    return os << acc.getOwner() << '\n' << acc.checkBalance();
}
