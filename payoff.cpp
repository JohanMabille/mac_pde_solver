#include "payoff.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

namespace dauphine
{

	payoff:payoff()
	{
	}

	payoff::~payoff()
	{
	}

	call::payoff(const double K) const 
		: K(strike)
	{
	}

	double call::operator payoff() (const double S) const
	{
		retunr std::max(S-K, 0);
	}

	put::payoff(const double K) const
		: K(strike)
	{
	}

	double put::operator payoff() (const double S) const
	{
		retunr std::max(K-S, 0);
	}

	
}

