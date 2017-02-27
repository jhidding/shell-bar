#include <iostream>
#include <cstdlib>

#include "colour.hh"
#include "term.hh"
#include "format.hh"

#define VERSION "0.1.0"

using Misc::format;
using namespace ShellBar;

/* Print a bit of usage info on this program.
 */
void usage(std::string const &exec_name)
{
    std::cout
        << "Shell-bar " << VERSION << " © 2017 Johannes Hidding\n"
        << "Licensed under Apache v2, see README.md\n\n"
        << "usage:\n"
        << "    " << exec_name << " [-oldterm] bar | prompt <hue> [args]\n\n"
        << "Additional arguments will only be read in case of a bar call.\n";
}

/* Convert a floating point based colour to 8-bit rgb, for subsequent
 * terminalisation.
 */
std::string const print_colour(Colour const &c)
{
    return Term::fg(
        static_cast<int>(c.rgb()[0]*255),
        static_cast<int>(c.rgb()[1]*255),
        static_cast<int>(c.rgb()[2]*255));
}

std::string const print_colour_oldterm(Colour const &c)
{
    return Term::setaf_rgb(c.rgb()[0], c.rgb()[1], c.rgb()[2]);
}

/* Return a string with colours added, and wrapped in paretheses. If the string
 * contains any colons, those are given a different colour.
 */
std::string const print_box(
        std::string const &text,
        std::string const &paren_c,
        std::string const &text_c)
{
    std::ostringstream oss;
    oss << paren_c << "(";

    size_t i = 0;
    while (true) {
        size_t j = text.find(':', i);
        oss << text_c << text.substr(i, j-i);
        if (j != std::string::npos) {
            oss << paren_c << ":";
        } else {
            break;
        }
        i = j+1;
    }
    oss << paren_c << ")";
    return oss.str();
}

/* Bash keeps a tally of the number of printed characters on the prompt, so as
 * to know when newlines happen etc.  Enclosing strings in \[ ... \] prevents
 * those characters from entering this tally.
 */
std::string const guard_escapes(std::string const &s)
{
    return format("\\[", s, "\\]");
}

/* Gets the length of a string, approximately. In the one and true shell-bar,
 * this should actually measure the printing width of the string, accounting
 * for wide characters.
 */
size_t utf8_length(char const *s)
{
    size_t len = 0;
    while (*s) len += (*s++ & 0xc0) != 0x80;
    return len;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    std::function<std::string (Colour const &)> set_colour = print_colour;

    int argp = 1;
    while (argv[argp] != std::string("bar")
            && argv[argp] != std::string("prompt"))
    {
        if (argv[argp] == std::string("-oldterm"))
        {
            set_colour = print_colour_oldterm;
        }
        ++argp;
    }

    auto hue = string_to<double>(argv[argp + 1]);
    if (not hue) {
        std::cout
            << "Error: Could not read a hue value from \""
            << argv[2] << "\".\nExpected floating point.\n\n";
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    Term::setup();
    int columns = Term::columns();

    // create a palette based on the given hue value
    auto bar_colour = set_colour(Colour::HSV(*hue, 0.5, 0.5)),
         paren_colour = set_colour(Colour::HSV(*hue + 0.1, 0.5, 0.7)),
         text_colour = set_colour(Colour::HSV(*hue - 0.1, 0.3, 0.8));

    // short-hand
    auto pbox = [&] (std::string const &s) {
        return print_box(s, paren_colour, text_colour);
    };

    // paint the top bar, this part is run every prompt
    if (argv[argp] == std::string("bar")) {
        std::cout << bar_colour << "╭";
        for (int i = 0; i < columns - 1; ++i)
            std::cout << "─";

        for (int i = argp+2; i < argc; ++i)
        {
            unsigned w = utf8_length(argv[i]);
            std::cout
                << Term::move_left(w + 3)
                << pbox(argv[i])
                << Term::move_left(w + 3);
        }

        return EXIT_SUCCESS;
    }

    // paint the lower bit, this part is run only once in bashrc.
    if (argv[argp] == std::string("prompt")) {
        std::cout << bar_colour << "\r" << Term::move_right(2) << pbox("\\#")
            << Term::move_right(1) << pbox("\\u@\\h") << "\n"
            << guard_escapes(bar_colour) << "╰─"
            << guard_escapes(text_colour) << "\\w\\$"
            << guard_escapes(Term::reset()) << " ";
        return EXIT_SUCCESS;
    }

    usage(argv[0]);
    return EXIT_FAILURE;
}

