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
			payoff() const =0; //explicit?
			virtual ~payoff();
			virtual double operator payoff() (const double S) const;
    };

	class call:public payoff //Classe de base pour un call
	{
		private:
			double K;
		public: //Redefinition des méthodes virtuelles pures de la classe mère
			payoff(const double strike) const; //Constructeur
		 	~payoff();
			double operator payoff() (const double S) const override; 
			//Surchage de () pour calculer payoff
			//verifier syntaxe
    };

	class put:public payoff
	{
		private:
			double K;
		public:
			payoff(const double strike) const;
		 	~payoff();
			double operator payoff() (const double S) const override;
    };

}

