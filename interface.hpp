#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#include "payoff.hpp"
//#include "rate.hpp"
//#include "volatility.hpp"
#include "global.hpp"

namespace dauphine
{

	class interface
	{
    public:
        interface(payoff* pay);
        ~interface();
        
        double get_rate();
//        double get_maturity();
//        double get_spot();
        payoff* get_payoff();
        
//        void set_spot(double spot);
//        void set_maturity(double t);
//        void set_vol(volatility* sig);

	        
    protected:
        payoff* m_payoff;
      
	};

}

#endif

