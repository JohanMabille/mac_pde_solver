#ifndef GLOBAL_HPP
#define GLOBAL_HPP

namespace dauphine
{

    // This is not flexible, you cannot run
    // the pricer many times with different
    // values for instance.
    // Besides, changing a value here
    // makes compiling the whole program

    static double initial_sigma = 0.20;
    static double initial_rate = 0.0;
    static double spot = 100.;
    static double maturity = 0.25;
    static double f0 = 1.;
    static double fN = 250.;
    static double dt = 0.01;
    static double dx = 0.01;
    static double theta = 0.5;



}

#endif
