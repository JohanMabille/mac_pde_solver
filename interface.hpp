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
			payoff* payoff;

			const double strike;
			const double rate;
			const double maturity;
			const double vol;
			const double theta;
			const double mesh;
						
			
			interface();
			interface(double K, double r, double T, double sig, payoff* pay);
			~interface();
	
	}

}

