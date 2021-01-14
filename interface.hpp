#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#include "payoff.hpp"

namespace dauphine
{

	class interface
	{
    public:
        interface();     // a quoi il sert ?
        interface(/*double K,*/ double r, double T, double sig, payoff* pay);
        ~interface();
        
        double get_rate() const;
        double get_maturity() const;
        double get_vol() const;
	
        
    private:
        payoff* payoff;
        
        //const double strike; //utile pour des options plus complexes?
        const double rate; //a adapter
        const double maturity;
        const double vol; //a adapter

        const double theta;
        const double mesh; //necessaire?
    };

}

#endif

