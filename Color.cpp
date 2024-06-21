#include "Color.h"
#include <iostream>

Color RGB(std::uint8_t red, std::uint8_t green, std::uint8_t blue) noexcept
{
    return static_cast<Color>(red << 16 | green << 8 | blue);
}

std::ostream& operator<<(std::ostream& os, Color c)
{
    switch(c)
    {
    case Color::RED:
        os << "Red";
        break;
    case Color::GREEN:
        os << "Green";
        break;
    case Color::BLUE:
        os << "Blue";
        break;
    case Color::BLACK:
        os << "Black";
        break;
    case Color::YELLOW:
        os << "Yellow";
        break;
    case Color::MAGENTA:
        os << "Magenta";
        break;
    case Color::CYAN:
        os << "Cyan";
        break;
    case Color::WHITE:
        os << "White";
        break;
    case Color::GREY:
        os << "Grey";
        break;
    case Color::PURPLE:
        os << "Purple";
        break;
    default:
        os << "Other";
    }
    return os;
}
