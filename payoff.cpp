#include "payoff.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

namespace dauphine
{

	payoff::payoff()
	{
        std::cout<< "payoff constructor" << std::endl;
	}

	payoff::~payoff()
	{
        std::cout<< "payoff destructor" << std::endl;
	}

	call::call(double strike)
		: K(strike)
	{
        std::cout<< "call constructor" << std::endl;
	}

    	call::~call()
    	{
        strike = 0;
        std::cout<< "call destructor" << std::endl;
   	 }

	double call::get_payoff(double S)
	{
		return fmax(S-K, 0); // std max didnt work
	}

	put::put(double strike)
		: K(strike)
	{
        std::cout<< "put constructor" << std::endl;
	}

    put::~put()
    	{
        K=0;
        std::cout<< "put destructor" << std::endl;
    	}

	double put::get_payoff(const double S)
	{
		return fmax(K-S, 0); //std max didnt work
	}

	
}

