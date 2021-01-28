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
        //Classe qui encapsule les payoffs
        //Logique de sémantique d'entité car payoff different pour chaque option
	public: //Constructeurs et destructeurs virtuels
        explicit payoff();
	virtual ~payoff();
	virtual double get_payoff(const double S) = 0;
    };

	class call: public payoff //Classe de base pour un call
	{
	private:
		double K;
	public: //Redefinition des méthodes virtuelles pures de la classe mère
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
