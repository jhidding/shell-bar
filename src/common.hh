#pragma once
#include <sstream>
#include <array>
#include <experimental/array>
#include <experimental/tuple>
#include <experimental/optional>
#include <cmath>

// I know this is very naughty
namespace std {
    using std::experimental::make_array;
    using std::experimental::apply;
    using std::experimental::optional;
    using std::experimental::nullopt;
}

/* Compute the integer modulo `x` following:
 *   a = k·b + x, k∈ ℤ
 */
inline int modulo(int a, int b)
{
    if (a < 0) return b + (a %  b);
    else return (a % b);
}

/* Compute the real modulo `x` following:
 *   a = k·b + x, k∈ ℤ
 */
inline double modulo(double a, double b)
{
    if (a < 0) return a - static_cast<int>(a / b - 1) * b;
    else return a - static_cast<int>(a / b) * b;
}

/* Convert a string to a value using the std::istream methods of conversion.
 * Returns `std::nullopt` if the conversion failed.
 */
template <typename T>
std::optional<T> string_to(std::string const &s)
{
    T value;
    std::istringstream iss(s);

    try {
        iss >> value;
        if (iss.fail()) {
            return std::nullopt;
        }
    }
    catch (std::istream::failure const &e) {
        return std::nullopt;
    }

    return value;
}
