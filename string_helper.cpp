#include "string_helper.h"

bool containsOnlyDigits(const std::string& s)
{
    for(char c: s)
        if(c<'0' || c>'9')
            return false;
    return true;
}
