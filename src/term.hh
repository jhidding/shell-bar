#pragma once
#include <string>
#include "format.hh"

/*! Talk to the terminal. These commands should work on any modern terminal
 * emulator with true-colour support.
 */
namespace Term
{
    using Misc::format;

    /* Wrappers for NCurses/TermInfo functions. */
    extern void setup();
    extern int tigetnum(std::string const &);

    inline int columns()
    {
        return tigetnum("cols");
    }

    inline std::string fg(int r, int g, int b)
    {
        return format("\033[38;2;", r, ";", g, ";", b, "m");
    }

    inline std::string reset()
    {
        return "\033[m";
    }

    inline std::string move_left(int n)
    {
        return format("\033[", n, "D");
    }

    inline std::string move_right(int n)
    {
        return format("\033[", n, "C");
    }
}
