//
//  volatility.cpp
//  mac_pde_solver
//
//  Created by Meriem Hrittane on 11/01/2021.
//

#include "volatility.hpp"
namespace dauphine{

volatility::~volatility()
{
}



vol_cst::vol_cst(double initial_sigma){
        sigma = initial_sigma;
    }

vol_cst::sigma(double s, double t)
{
    return sigma;
}

}


