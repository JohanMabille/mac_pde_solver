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
    // These hsould be part of the boundary condition
    static double f0 = 1.;
    static double fN = 250.;
    // It's more common to pass the number
    // of points in the mesh and compute
    // dx and dt. This avoids rounding
    // computation in the solver and interpolation
    // to get the price at the given spot.
    // We usually pass an odd number of points
    // for the space mesh (so log(S) does not
    // have to be interpolated)
    static double dt = 0.01;
    static double dx = 0.01;
    static double theta = 0.5;



}

#endif
