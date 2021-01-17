#include "interface.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>


#include "rate.hpp"
#include "volatility.hpp"

namespace dauphine
{
	interface::interface() //Nécessaire?
	{
	}

interface::interface(/*double K,*/ rate* r, double T, volatility* sig, class payoff* pay):
		 /*K(strike),*/ m_rate(r), maturity(T), m_vol(sig), payoff(pay)
	{
        std::cout<<"interface constructor"<<std::endl;
	}

    interface::~interface(){}

    double interface::get_rate()
    {
        std::cout<<"interface::get_rate()"<<std::endl;
        double s = 0;
        double t = 0;
        
        return m_rate->get_rate(s, t);
    }
    
     double interface::get_maturity()
    {
        std::cout<<"interface::get_mat()"<<std::endl;
        return maturity;
    }
    
     double interface::get_vol()
    {
        std::cout<<"interface::get_vol()"<<std::endl;
        double s = 0;
        double t = 0;
        return m_vol->get_sigma(s, t);
    }
}

