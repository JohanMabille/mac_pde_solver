#ifndef volatility_hpp
#define volatility_hpp

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>
#include <functional>
#include <stdio.h>

namespace dauphine
{

    class volatility
    {
    public:
	explicit volatility();
        virtual ~volatility();
        virtual double get_sigma() const = 0; // à quoi ça sert ?
        
    };


    class vol_cst: public volatility
    {
    private:
        double sigma;
        
    public:
        vol_cst(double initial_sigma const);
        ~vol_cst();
        double get_sigma() const override; // à quoi ça sert ?

    };

}

#endif
