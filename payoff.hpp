#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include "interface.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

namespace dauphine
{

	class payoff //Classe qui encapsule les payoffs
		//Logique de sémantique d'entité car payoff different pour chaque option
	{
		public: //Constructeurs et destructeurs virtuels
			explicit payoff();
			virtual ~payoff();
			virtual double get_payoff(const double S) const = 0;
    };

	class call: public payoff //Classe de base pour un call
	{
		private:
			double K;
		public: //Redefinition des méthodes virtuelles pures de la classe mère
			call(const double strike); //Constructeur
		 	~call();
			double get_payoff(const double S) const override;
			//calcul du payoff
		
    	};

	class put: public payoff
	{
		private:
			double K;
		public:
			put(const double strike);
		 	~put();
			double get_payoff(const double S) const override;
    };

}

#endif
