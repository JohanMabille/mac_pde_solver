//
//  volatility.hpp
//  mac_pde_solver
//
//  Created by Meriem Hrittane on 11/01/2021.
//

#ifndef volatility_hpp
#define volatility_hpp

#include <stdio.h>

namespace dauphine
{

class volatility
{
    public:
    virtual ~volatility();
    virtual double sigma(double s, double t) = 0;
    
}


class vol_cst: public volatility{
private:
    double sigma = 0;
public:
    vol_cst(double initial_sigma);
    double sigma(double s, double t);

}

#endif /* volatility_hpp */
