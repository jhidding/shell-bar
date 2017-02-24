#pragma once
#include <array>
#include "common.hh"

namespace ShellBar
{
    extern std::array<double, 3> rgb_to_hsv(double r, double g, double b);
    extern std::array<double, 3> hsv_to_rgb(double h, double s, double v);

    /*! Converts between RGB and HSV colour spaces.
     *
     * Values are stored in `std::optional`, so they are only generated
     * when needed.
     *
     * All stored values should lie in the range [0.0, 1.0]. This is also
     * true for the hue, in contrast to some conventions where the hue is
     * expressed as a value between 0 and 360. A hue of 0 means red,
     * 1/6 is yellow, 1/3 green, 1/2 cyan, 2/3 blue, and 5/6 magenta.
     *
     * The saturation is the fraction max(r,g,b)/min(r,g,b), and the value
     * simply equals max(r,g,b). 
     */
    class Colour
    {
        std::optional<std::array<double,3>> mutable rgb_;
        std::optional<std::array<double,3>> mutable hsv_;

        public:
            /*! Factory for HSV space.
             */
            static Colour HSV(double h, double s, double v) {
                Colour c;
                c.hsv_ = std::make_array(h, s, v);
                return c;
            }

            /*! Factory for RGB space.
             */
            static Colour RGB(double r, double g, double b) {
                Colour c;
                c.rgb_ = std::make_array(r, g, b);
                return c;
            }

            /*! Return an array with RGB values. */
            std::array<double,3> const &rgb() const {
                if (not rgb_)
                    rgb_ = std::apply(hsv_to_rgb, *hsv_);
                return *rgb_;
            }

            /*! Return an array with HSV values. */
            std::array<double,3> const &hsv() const {
                if (not hsv_)
                    hsv_ = std::apply(rgb_to_hsv, *rgb_);
                return *hsv_;
            }

        private:
            Colour() {}
    };
}

