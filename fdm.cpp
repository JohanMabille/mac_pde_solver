#include "fdm.hpp"
#include "pde_boundary_conditions.hpp"
#include "interface.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "math.h"
#include <numeric>
#include <functional>

namespace dauphine
{

	fdm_interface::fdm_interface()
	{
	}

	fdm_interface::~fdm_interface()
	{
	}

	double fdm_interface::a1(pde* pde,double s, double t) const
	{		
        	double alpha = (pde->first_coeff())/(pow(m_dx, 2));
		double beta=(pde->conv_coeff())/(2*fdm_interface::m_dx);
		
		return m_dt*(1-theta)*(beta-alpha);
	}

	double fdm_interface::a2(pde* pde, double s, double t) const
	{
 		double alpha = (pde->first_coeff())/(pow(m_dx,2));
        	return (1- (1-theta)*m_dt*(r->get_rate(s, t) - 2*alpha));
	}

	double fdm_interface::a3(pde* pde, double s, double t) const
	{
		double alpha = (pde->first_coeff())/(pow(m_dx, 2));
		double beta=(pde->conv_coeff())/(2*m_dx);
		
		return (-m_dt*(1-theta)*(beta+alpha));
	}

	double fdm_interface::b1(pde* pde, double s, double t) const
	{
		double alpha = (pde->first_coeff())/(pow(m_dx, 2));
		double beta=(pde->conv_coeff())/(2*m_dx);
		
		return m_dt*theta*(alpha - beta);
	}

	double fdm_interface::b2(pde* pde, double s, double t) const
	{
    		double alpha = (pde->first_coeff())/(pow(m_dx, 2));
			
       		return (1- theta*m_dt*(r->get_rate(s, t) - 2*alpha));
	}

	double fdm_interface::b3(pde* pde, double s, double t) const
	{
		double alpha = (pde->first_coeff())/(pow(m_dx, 2));
		double beta=(pde->conv_coeff())/(2*m_dx);

		return m_dt*theta*(beta+alpha);
	}

	fdm::fdm(pde* pde, payoff* payoff, const double f0, const double fN, const int dt, const int dx)
	{
       	}

	fdm::~fdm()
	{
		delete m_pde; //destruction du pointeur
	}

	double fdm::get_price(pde* pde, interface* opt, payoff* payoff, const double f0, const double fN, const int dt, const int dx)
	{
		//Calcul avec FDM
		//1. On discretise le temps et l'espace
			
		double T = time_mesh(dt, opt);
		double N = space_mesh(dx, opt);
		double r0 = opt->get_rate(); //dependency in t & s?

		//2. Calcul des f intermédiaires
			
		//Calcul de la matrice F en T
        	std::vector<double> F(N-1, payoff->get_payoff(opt->get_spot()));
        	        
		//Calcul des coeffs des matrices tridiagonales en T
		double mat = opt->get_maturity(); 
		//def matrice des coeffs pour avoir les coeffs en tt pt de l espace
		std::vector<double> A1(N-1, 0.0);
		std::vector<double> A2(N-1, 0.0);
		std::vector<double> A3(N-1, 0.0);
		std::vector<double> B1(N-1, 0.0);
		std::vector<double> B2(N-1, 0.0);
		std::vector<double> B3(N-1, 0.0);
				
		double Smax = s_boundary_right(opt->get_spot(), opt->get_vol(), opt->get_maturity());
		double Tmax =  t_boundary_right(opt->get_maturity());
		double s = Smax;
		for (int i=0; i < N-1; i++)
		{
			A1[i] = a1(pde, s, mat);
			A2[i] = a2(pde, s, mat);
			A3[i] = a3(pde, s, mat);
			B1[i] = b1(pde, s, mat);
			B2[i] = b2(pde, s, mat);
			B3[i] = b3(pde, s, mat);

			s -= dx;
		}
		//Calcul du terme constant que l'on extrait pour avoir une matrice tridiagonale
		std::vector<double> C(N-1, 0.0);
		C[0] = (A1[0] - B1[0]*exp(-r0*dt))*f0;
		C[N-2] = (A3[N-2] - B3[N-2]*exp(-r0*dt))*fN;

		//Calcul de la matrice D en T
		std::vector<double> D(N,0.0);
		D[0] = A2[0]*F[0] + A3[0]*F[1] + C[0];
		D[N-2] = A1[N-2]*F[N-2] + A2[N-2]*F[N-2] + C[N-2];
		
		for (int i=1; i < N-2; i++)
		{
			D[i] = A1[i]*F[i-1] + A2[i]*F[i] + A3[i]*F[i+1];
		}

		//On remonte via l'algorithme de Thomas
				s = Smax;

		for (int t = T-1; t>=0 ; t--)
		{
			//Pour chaque x(i,t+1), en commencant par f_N, on remonte à x(i,t)
			//via l'algo de Thomas et le système trouvé
			
			//On calcule la matrice tridiagoname en t en tt pt de l'espace
			for (int i=0; i < N-1; i++)
			{
				A1[i] = a1(pde, s, t);
				A2[i] = a2(pde, s, t);
				A3[i] = a3(pde, s, t);
				B1[i] = b1(pde, s, t);
				B2[i] = b2(pde, s, t);
				B3[i] = b3(pde, s, t);

				s -= dx;
			}


			//On calcule la matrice F en t, et on fait Ft1=Ft
      			F = thomas(B1, B2, B3, F, D);

			//On recalcule la nouvelle matrice D
			D[0] = A2[0]*F[0] + A3[0]*F[1] + C[0];
			D[N-2] = A1[N-2]*F[N-2] + A2[N-2]*F[N-2] + C[N-2];
		
			for (int i=1; i < N-2; i++)
			{
				D[i] = A1[i]*F[i-1] + A2[i]*F[i] + A3[i]*F[i+1];
			}
		}

		return F[floor(N/2)];
	}


	std::vector<double> fdm::thomas(const std::vector<double> a, const std::vector<double> b, const std::vector<double> c, std::vector<double> x,  std::vector<double> d)
	{
		//algo de Thomas pour inverser une matrice tridiagonale dans le cas de coeffs "constant" dans l'espace		
        	int n = d.size();
		std::vector<double> new_coeffs(n, 0);
		std::vector<double> new_d(n, 0);

		//Forward sweep
		new_coeffs[0] =c[0]/b[0];
		new_d[0] = d[0]/b[0];

		for (int i=1; i<n; i++)
		{
			new_coeffs[i] = c[i] / (b[i]-a[i] * new_coeffs[i-1]);
			new_d[0] = (d[i]-a[i] * new_d[i-1]) / (b[i]-a[i] * new_coeffs[i-1]);
		}
		
		//Back substitution
        	std::vector<double> y(n, 0.0); 
		y[n-1] = new_d[n-1];

		for (int i=n-2; i>=0; i--)
		{
			y[i] = new_d[i] - new_coeffs[i]*x[i+1];
		}

		return y;
	}

}
