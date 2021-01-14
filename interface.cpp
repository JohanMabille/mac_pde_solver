#include "interface.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

namespace dauphine
{
	interface::interface() //Nécessaire?
	{
	}

	interface::interface(/*double K,*/ double r, double T, double sig, payoff* pay):
		: /*K(strike),*/ rate(r), maturity(T), vol(sig), payoff(pay)
	{
        std::cout<<"interface constructor"<<std::endl;
	}

	interface::~interface()

    const double interface::get_rate() const
    {
        std::cout<<"interface::get_rate()"<<std::endl;
        return rate;
    }
    
    const double interface::get_maturity() const
    {
        std::cout<<"interface::get_mat()"<<std::endl;
        return maturity;
    }
    
    const double interface::get_vol() const
    {
        std::cout<<"interface::get_vol()"<<std::endl;
        return vol;
    }

}

