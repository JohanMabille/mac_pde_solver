#include "interface.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>


#include "rate.hpp"
#include "volatility.hpp"

namespace dauphine
{
	interface::interface()
	{
	}

	interface::interface(double spot, rate* r, double T, volatility* sig, class payoff* pay):
		 m_spot(spot), m_rate(r), maturity(T), m_vol(sig), payoff(pay)
	{
        	std::cout<<"interface constructor"<<std::endl;
	}

    	interface::~interface(){}

    	double interface::get_rate()
    	{
        	double s = 0;
        	double t = 0;
        
        	return m_rate->get_rate(s, t);
    	}
    
    	double interface::get_maturity()
    	{
        	return maturity;
    	}
    
    	double interface::get_vol()
    	{
        	double s = 0;
        	double t = 0;
        	return m_vol->get_sigma(s, t);
    	}

	double interface::get_spot()
    	{
        	return m_spot;
	}

	
}

