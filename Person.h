#ifndef PERSON_H
#define PERSON_H

#include "EGN.h"
#include <string>
#include <iosfwd>

class Person
{
    EGN egn;
    std::string name;
    std::string address;
    std::string phoneNumber;
public:
    Person(const std::string& egn, const std::string& name, const std::string& address, const std::string& phoneNumber);
    Person(const std::string& egn, std::string&& name, std::string&& address, std::string&& phoneNumber);
    void changeAddress(const std::string& newAddress);
    void changeAddress(std::string&& newAddress);
    void changePhoneNumber(const std::string& newPhoneNumber);
    void changePhoneNumber(std::string&& newPhoneNumber);
    std::string getEGN() const;
    const std::string& getName() const noexcept;
    const std::string& getAdress() const noexcept;
    const std::string& getPhoneNumber() const noexcept;
    Date birthdate() const;
    char gender() const noexcept;
    static Person read(std::istream& is);
};

std::ostream& operator<<(std::ostream& os, const Person& p);

#endif // PERSON_H
