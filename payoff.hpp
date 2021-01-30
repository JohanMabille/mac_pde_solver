#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include "global.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

namespace dauphine
{

	class payoff
	{
        
	public:
        explicit payoff();
        virtual ~payoff();
        virtual double get_payoff(const double S) = 0;
    };

	class call: public payoff
	{
	private:
		double K;
	public: 
		call(double strike); 
		~call();
		double get_payoff(const double S) override;
		double strike;
	
		
    	};

	class put: public payoff
	{
	private:
		double K;
	public:
		put(double strike);
		~put();
		double get_payoff(const double S) override;
    };

}

#endif
