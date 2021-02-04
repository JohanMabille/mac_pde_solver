#include "payoff.hpp"

namespace dauphine
{

	payoff::payoff()
	{
	}

	payoff::~payoff()
	{
	}

	call::call(double strike)
		: K(strike)
	{
	}

    	call::~call()
    	{
            // Not necessary, strike is
            // a stack-allocated variable
            // We usually reset heap-allocated
            // variables to state that the class
            // does not have the ownership
       		strike = 0;
   	 }

	double call::get_payoff(double S)
	{
		return fmax(S-K, 0);
	}

	put::put(double strike)
		: K(strike)
	{
	}

    put::~put()
    {
        K=0;
    }

	double put::get_payoff(const double S)
	{
		return fmax(K-S, 0);
	}

	
}

