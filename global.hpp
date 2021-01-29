#ifndef GLOBAL_HPP
#define GLOBAL_HPP

namespace dauphine
{


    static double initial_sigma = 0.15;
    static double initial_rate = 0.02;
    static double spot = 100.;
    static double maturity = 7.; // in years
    static double f0 = 1.;
    static double fN = 250.;
    static double dt = 0.05;
    static double dx = 0.2;     //fix for smaller values
    static double theta = 0.5;

}

#endif
