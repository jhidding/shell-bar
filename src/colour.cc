 #include "colour.hh"

using namespace ShellBar;

std::array<double,3> ShellBar::rgb_to_hsv(double r, double g, double b)
{
    double h = 0., s = 0., v;

    if ((r > g) and (r > b))
    {
        double min_rgb = std::min(g, b);

        if ((r - min_rgb) > 1e-6)
        {
            h = ((g - b) / (r - min_rgb)) / 3.;
            s = (r - min_rgb) / r;
        }

        v = r;
    }
    else if ((g > r) and (g > b))
    {
        double min_rgb = std::min(b, r);

        if ((g - min_rgb) > 1e-6)
        {
            h = ((b - r) / (g - min_rgb) + 1.) / 3.;
            s = (g - min_rgb) / g;
        }

        v = g;
    }
    else
    {
        double min_rgb = std::min(r, g);

        if ((b - min_rgb) > 1e-6)
        {
            h = ((r - g) / (b - min_rgb) + 2.) / 3;
            s = (b - min_rgb) / b;
        }

        v = b;
    }

    return { h, s, v };
}


std::array<double,3> ShellBar::hsv_to_rgb(double h, double s, double v)
{
    double r, g, b;
    int Hi = modulo(static_cast<int>(floor(h * 6)), 6);
    double f = (modulo(h, 1.0) * 6) - Hi;

    double k = (Hi % 2 == 0 ? 1 - f : f),
           l = v * (1 - s),
           m = v * (1 - k*s);

    switch (Hi)
    {
        case 0: r = v; g = m; b = l; break;
        case 1: r = m; g = v; b = l; break;
        case 2: r = l; g = v; b = m; break;
        case 3: r = l; g = m; b = v; break;
        case 4: r = m; g = l; b = v; break;
        case 5: r = v; g = l; b = m; break;
    }

    return { r, g, b };
}

