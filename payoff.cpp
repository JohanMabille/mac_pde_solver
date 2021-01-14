#include "payoff.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

namespace dauphine
{

	payoff:payoff()
	{
        std::cout<< "payoff constructor" << std::endl;
	}

	payoff::~payoff()
	{
        std::cout<< "payoff destructor" << std::endl;
	}

	call::call(const double K) const
		: strike(K)
	{
        std::cout<< "call consructor" << std::endl;
	}

    call::~call()
    {
        strike = 0;
        std::cout<< "call destructor" << std::endl;
    }

	double call::get_payoff() (const double S) const
	{
		return std::max(S-K, 0);
	}

	put::put(const double K) const
		: K(strike)
	{
        std::cout<< "put constructor" << std::endl;
	}

    put::~put()
    {
        strike = 0;
        std::cout<< "put destructor" << std::endl;
    }

	double put::get_payoff() (const double S) const
	{
		return std::max(K-S, 0);
	}

	
}

