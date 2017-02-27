#pragma once
#include <string>
#include <utility>
#include <cmath>
#include "format.hh"

/*! Talk to the terminal. These commands should work on any modern terminal
 * emulator with true-colour support.
 */

namespace Term
{
    using Misc::format;

    // To avoid ncurses cluttering the namespace, this function is reached via
    // function pointer.
    namespace Curses
    {
        extern char *(*tiparm)(const char *str, ...);
    }

    /* Wrappers for NCurses/TermInfo functions. */
    extern void setup();
    extern int tigetnum(std::string const &);
    extern std::string tigetstr(std::string const &capname);

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

    template <typename ...Args>
    std::string tiparm(std::string const &str, Args &&...args)
    {
        return Curses::tiparm(str.c_str(), std::forward<Args>(args)...);
    }

    inline std::string setaf(int c)
    {
        return tiparm(tigetstr("setaf"), c);
    }

    template <typename Number>
    inline Number clip(Number a, Number b, Number x)
    {
        if (x < a) return a;
        if (x > b) return b;
        return x;
    }

    inline std::string setaf_rgb(double r, double g, double b)
    {
        int ri = clip(0, 5, static_cast<int>(floor(r*6.0)));
        int gi = clip(0, 5, static_cast<int>(floor(g*6.0)));
        int bi = clip(0, 5, static_cast<int>(floor(b*6.0)));
        return setaf(16 + bi + gi*6 + ri*36);
    }
}
