#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>
#include <functional>

#include "volatility.hpp"
namespace dauphine
{
	
	volatility::volatility()
	{
		std::cout << "constructeur vol" << std::endl;
	}
	
	volatility::~volatility()
	{
		std::cout << "destructeur vol" << std::endl;
	}


	vol_cst::vol_cst(const double initial_sigma)
		: sigma(initial_sigma)
	{
       		std::cout << "constructeur vol cst" << std::endl;
    	}

	vol_cst::~vol_cst
	{
		std::cout << "destructeur vol cst" << std::endl;
	}

	vol_cst::get_sigma() const
	{
    		return sigma;
	}

}


