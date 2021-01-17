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

			virtual std::vector<double> time_mesh(const double lower_T, const double upper_T, const int nb_steps) const = 0; //utile?
			virtual std::vector<double> space_mesh(const double lower_T, const double upper_T, const int nb_steps) const = 0;

			virtual double a1(pde* pde) const;
			virtual double a2(pde* pde) const;
			virtual double a3(pde* pde) const;
			virtual double b1(pde* pde) const;
			virtual double b2(pde* pde) const;
			virtual double b3(pde* pde) const;			
    protected:
        pde* m_pde;
        payoff* m_payoff;
        rate* r;
        double boundary_f0;
        double boundary_fN;
        double uT;
        double lT;
        double uN;
        double lN;
        int m_dt = 1;
        int m_dx;
        double theta; 
	};
	
	class fdm : public fdm_interface
	{
		public:
			fdm(pde* pde, payoff* payoff, const double f0, const double fN, const double lower_T, const double upper_T, const double lower_N, const double upper_N, const int dt, const int dx);
			~fdm();

			std::vector<double> time_mesh(const double lower_T, const double upper_T, const int dt = 1) const;
			std::vector<double> space_mesh(const double lower_N, const double upper_N, const int dx = 1) const;

			std::vector<double> thomas(const std::vector<double> coeffs, std::vector<double> x, std::vector<double> d);
	

		private:
			
	
	
    };




}

#endif
