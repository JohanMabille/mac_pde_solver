#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#include "payoff.hpp"
#include "rate.hpp"
#include "volatility.hpp"

namespace dauphine
{

	class interface
	{
    public:
        interface();     // a quoi il sert ?
        interface(/*double K,*/ rate* r, double T, volatility* sig, payoff* pay);
        ~interface();
        
        double get_rate();
        double get_maturity();
        double get_vol();
	        
    protected:
        payoff* payoff;
        
        //const double strike; //utile pour des options plus complexes?
        rate* m_rate;
        double maturity;
        volatility* m_vol;
	};

}

#endif

