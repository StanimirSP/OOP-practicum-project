#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <iosfwd>

enum class Color: std::uint32_t
{
    RED     = 0xFF0000,
    GREEN   = 0x00FF00,
    BLUE    = 0x0000FF,
    BLACK   = 0x000000,
    YELLOW  = 0xFFFF00,
    MAGENTA = 0xFF00FF,
    CYAN    = 0x00FFFF,
    WHITE   = 0xFFFFFF,
    GREY    = 0x808080,
    PURPLE  = 0x800080,
};

Color RGB(std::uint8_t red, std::uint8_t green, std::uint8_t blue) noexcept;
std::ostream& operator<<(std::ostream& os, Color c);

#endif // COLOR_H
