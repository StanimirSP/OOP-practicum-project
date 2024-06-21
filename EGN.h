#ifndef EGN_H
#define EGN_H

#include <string>
#include "Date.h"

class EGN
{
    char egn[11];
    int checksum() const;
public:
    EGN(const std::string& egn);
    const char* getEGN() const noexcept;
    Date birthdate() const;
    char gender() const noexcept;
};

#endif // EGN_H
