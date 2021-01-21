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
        interface(double spot, rate* r, double T, volatility* sig, payoff* pay);
        ~interface();
        
        double get_rate();
        double get_maturity();
        double get_vol();
        double get_spot();
        payoff* get_payoff();
        
        void set_spot(double spot);
        void set_maturity(double t);
	        
    protected:
        payoff* m_payoff;
        rate* m_rate;
        double m_maturity;
        volatility* m_vol;
        double m_spot;
	};

}

#endif

