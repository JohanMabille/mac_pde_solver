#include "interface.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

namespace dauphine
{
	interface::interface()
	{
	}

	interface::interface(/*double K,*/ double r, double T, double sig, payoff* pay):
		: /*K(strike),*/ r(rate), T(maturity), sig(vol), pay(payoff)
	{
	}

	interface::~interface() //Nécessaire?

}

