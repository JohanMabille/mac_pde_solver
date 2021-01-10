//
//  pde_boundary_conditions.cpp
//  PDE
//
//  Created by Meriem Hrittane on 10/01/2021.
//  Copyright © 2021 Meriem Hrittane. All rights reserved.
//

#include "pde_boundary_conditions.hpp"
#include <math.h>
namespace dauphine
{

double Sboundaries::boundary_left(double s,double sigma, double t) {
    double lower_boundary = log (s) - 5*sigma*sqrt(t);
    return lower_boundary;
}

double Sboundaries::boundary_right(double s, double sigma, double t) {
    double upper_boundary = log (s) + 5*sigma*sqrt(t);
    return upper_boundary;
}

double Tboundaries::boundary_left(double t) {
    return 0.;
}

double Tboundaries::boundary_right(double t) {
    return t;
}
     
     
 }

