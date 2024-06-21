#ifndef BANKACCOUT_H
#define BANKACCOUT_H

#include "Person.h"
#include <iosfwd>

class BankAccount
{
    Person owner;
    double balance;
public:
    BankAccount(const Person& owner, double initialBalance = 0);
    BankAccount(Person&& owner, double initialBalance = 0);
    const Person& getOwner() const;
    bool sendMoney(BankAccount& receiver, double amount);
    double checkBalance() const noexcept;
    bool deposit(double amount);
    bool withdraw(double amount);
    static BankAccount read(std::istream& is);
};

std::ostream& operator<<(std::ostream& os, const BankAccount& acc);

#endif // BANKACCOUT_H
