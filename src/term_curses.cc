#include "term.hh"

/* curses.h and term.h introduce all kinds of global variables and macros. I
 * don't want to infest my namespace with those, which is why these libraries
 * are isolated into this file.
 */

#include <curses.h>
#include <term.h>

void Term::setup()
{
    setupterm(NULL, 1, NULL);
}

int Term::tigetnum(std::string const &s)
{
    return ::tigetnum(s.c_str());
}

