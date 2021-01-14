//
//  rate.hpp
//  mac_pde_solver
//
//  Created by Meriem Hrittane on 11/01/2021.
//

#ifndef rate_hpp
#define rate_hpp

#include <stdio.h>

namespace dauphine
{

class rate
{
    public:
    virtual ~rate();
    virtual double r(double s, double t) = 0;
    
}


class rate_cst: public rate{
private:
    double rate = 0;
public:
    rate_cst(double initial_sigma);
    double r(double s, double t);



#endif /* rate_hpp */
