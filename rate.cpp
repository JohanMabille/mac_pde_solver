#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>
#include <functional>
#include <stdio.h>
#include "rate.hpp"

namespace dauphine{

	rate::rate()
	{
		std::cout << "constructeur rate" << std::endl;
	}

	rate::~rate()
	{
		std::cout << "destructeur rate" << std::endl;
	}

	rate_cst::rate_cst(double initial_rate)
		: rate(initial_rate)
	{
        	std::cout << "constructeur rate cst" << std::endl;
    	}

	rate_cst::~rate_cst
	{
		std::cout << "destructeur rate cst" << std::endl;
	}

	rate_cst::r(double s, double t) //?
	{
    		return rate;
	}

}
