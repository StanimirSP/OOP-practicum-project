#include "EGN.h"
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include "string_helper.h"

EGN::EGN(const std::string& egn)
{
    if(egn.size()!=10 || !containsOnlyDigits(egn)) throw std::invalid_argument("invalid EGN");
    std::strcpy(this->egn, egn.c_str());
    if(checksum()!=egn[9]-'0') throw std::invalid_argument("invalid EGN");
    try {
        birthdate();
    }
    catch(...) {
        throw std::invalid_argument("invalid EGN");
    }
}

int EGN::checksum() const
{
    int res = 0;
    for(int i=8; i>=0; i--)
        res = (res + egn[i] - '0') * 2;
    return res % 11 % 10;
}

const char* EGN::getEGN() const noexcept
{
    return egn;
}

Date EGN::birthdate() const
{
    unsigned year = 1900 + 10*egn[0] + egn[1] - 11*'0',
             month = 10*egn[2] + egn[3] - 11*'0',
             day = 10*egn[4] + egn[5] - 11*'0';
    if(month>40)
    {
        month-=40;
        year+=100;
    }
    else if(month>20)
    {
        month-=20;
        year-=100;
    }
    return {year, month, day};
}

char EGN::gender() const noexcept
{
    return egn[8]%2? 'F': 'M';
}
