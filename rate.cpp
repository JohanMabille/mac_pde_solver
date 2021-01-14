//
//  rate.cpp
//  mac_pde_solver
//
//  Created by Meriem Hrittane on 11/01/2021.
//

#include "rate.hpp"
namespace dauphine{

rate::~rate()
{
}

rate_cst::rate_cst(double initial_rate){
        rate = initial_rate;
    }

vol_cst::r(double s, double t)
{
    return rate;
}

}
