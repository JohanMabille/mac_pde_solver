#ifndef FDM_INTERFACE_HPP
#define FDM_INTERFACE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>  
#include <functional>
#include "pde.hpp"
#include "payoff.hpp"

namespace dauphine
{
	class fdm_interface
	{
	public:
		fdm_interface(); //explict?
		virtual ~fdm_interface();
		virtual double a1(pde* pde, double s, double t) const;
		virtual double a2(pde* pde, double s, double t) const;
		virtual double a3(pde* pde, double s, double t) const;			
		virtual double b1(pde* pde, double s, double t) const;
		virtual double b2(pde* pde, double s, double t) const;
		virtual double b3(pde* pde, double s, double t) const;			
    	protected:
        	pde* m_pde;
        	payoff* m_payoff;
        	rate* r;
        	double boundary_f0;
        	double boundary_fN;
        	int m_dt = 1;
        	int m_dx;
        	double theta; 
	};
	
	class fdm : public fdm_interface
	{
	public:
		fdm(pde* pde, payoff* payoff, const double f0, const double fN, const int dt, const int dx);
		~fdm();

		std::vector<double> time_mesh(const double lower_T, const double upper_T, const int dt = 1) const;
		std::vector<double> space_mesh(const double lower_N, const double upper_N, const int dx = 1) const;

		std::vector<double> thomas(const std::vector<double> a, const std::vector<double> b, const std::vector<double> c, std::vector<double> x,  std::vector<double> d);
		double get_price(pde* pde, interface* opt, payoff* payoff, const double f0, const double fN, const int dt, const int dx);
	
    };

}

#endif
