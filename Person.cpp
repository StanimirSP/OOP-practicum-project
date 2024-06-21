#include "Person.h"
#include <iostream>
#include "string_helper.h"

Person::Person(const std::string& egn, const std::string& name, const std::string& address, const std::string& phoneNumber): egn(egn), name(name), address(address)
{
    changePhoneNumber(phoneNumber);
}

Person::Person(const std::string& egn, std::string&& name, std::string&& address, std::string&& phoneNumber): egn(egn), name(std::move(name)), address(std::move(address))
{
    changePhoneNumber(std::move(phoneNumber));
}

void Person::changeAddress(const std::string& newAddress)
{
    address = newAddress;
}

void Person::changeAddress(std::string&& newAddress)
{
    address = std::move(newAddress);
}

void Person::changePhoneNumber(const std::string& newPhoneNumber)
{
    if(!containsOnlyDigits(newPhoneNumber)) throw std::invalid_argument("invalid phone number"); // assuming no '+' sign in phone numbers
    phoneNumber = newPhoneNumber;
}

void Person::changePhoneNumber(std::string&& newPhoneNumber)
{
    if(!containsOnlyDigits(newPhoneNumber)) throw std::invalid_argument("invalid phone number"); // assuming no '+' sign in phone numbers
    phoneNumber = std::move(newPhoneNumber);
}

std::string Person::getEGN() const
{
    return egn.getEGN();
}

const std::string& Person::getName() const noexcept
{
    return name;
}

const std::string& Person::getAdress() const noexcept
{
    return address;
}

const std::string& Person::getPhoneNumber() const noexcept
{
    return phoneNumber;
}

Date Person::birthdate() const
{
    return egn.birthdate();
}

char Person::gender() const noexcept
{
    return egn.gender();
}

Person Person::read(std::istream& is)
{
    std::string EGN, name, address, phone;
    is >> EGN;
    is.ignore();
    std::getline(is, name);
    std::getline(is, address);
    is >> phone;
    is.ignore();
    return {EGN, name, address, phone};
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    return os << p.getEGN() << '\n' << p.getName() << '\n' << p.getAdress() << '\n' << p.getPhoneNumber();
}
