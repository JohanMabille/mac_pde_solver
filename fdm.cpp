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

	fdm_interface::fdm_interface(pde* pde, payoff* pay, rate* r, double f0, double fN, int dt, int dx, double theta)
		: m_pde(pde), m_payoff(pay), m_r(r), m_f0(f0), m_fN(fN), m_dt(dt), m_dx(dx), m_theta(theta)
	{
	}

	fdm_interface::~fdm_interface()
	{
		delete m_pde; //destruction du pointeur
		delete m_r;
		delete m_payoff;

	}

	double fdm_interface::a1(pde* pde,double s, double t) const
	{		
        double alpha = (pde->diff_coeff())/(pow(m_dx, 2));
		double beta = (pde->conv_coeff())/(2*m_dx);
		
		return m_dt*(1-m_theta)*(beta-alpha);
	}

	double fdm_interface::a2(pde* pde, double s, double t) const
	{
 		double alpha = (pde->diff_coeff())/(pow(m_dx,2));
        return (1 - (1 - m_theta)*m_dt*(m_r->get_rate(s, t) - 2*alpha));
	}

	double fdm_interface::a3(pde* pde, double s, double t) const
	{
		double alpha = (pde->diff_coeff())/(pow(m_dx, 2));
		double beta=(pde->conv_coeff())/(2*m_dx);
		
		return (-m_dt*(1-m_theta)*(beta+alpha));
	}

	double fdm_interface::b1(pde* pde, double s, double t) const
	{
		double alpha = (pde->diff_coeff())/(pow(m_dx, 2));
		double beta=(pde->conv_coeff())/(2*m_dx);
		
		return m_dt*m_theta*(alpha - beta);
	}

	double fdm_interface::b2(pde* pde, double s, double t) const
	{
        double alpha = (pde->diff_coeff())/(pow(m_dx, 2));
			
        return (1 + m_theta*m_dt*(m_r->get_rate(s, t) - 2*alpha));
	}

	double fdm_interface::b3(pde* pde, double s, double t) const
	{
		double alpha = (pde->diff_coeff())/(pow(m_dx, 2));
		double beta=(pde->conv_coeff())/(2*m_dx);

		return m_dt*m_theta*(beta+alpha);
	}

	fdm::fdm(pde* pde, payoff* payoff, rate * r, double f0, double fN, int dt, int dx, double theta)
		: fdm_interface(pde, payoff, r, f0, fN, dt, dx, theta)
    {
    }

	fdm::~fdm()
	{
		m_pde = nullptr;
		m_r = nullptr;
		m_payoff = nullptr;
	}

	std::vector<double> fdm::get_price(pde* pde, interface* opt, payoff* payoff, Space_boundaries* sb, Time_boundaries* tb) const
	{
		//Calcul avec FDM
		//1. On discretise le temps et l'espace
		double T = tb->time_mesh(m_dt, opt);
		double N = sb->space_mesh(m_dx, opt);
		double r0 = opt->get_rate(); //dependency in t & s?

//		std::cout << "wesh 1" <<std::endl;

		//2. Calcul des f intermédiaires
			
		//Calcul de la matrice F en T
        std::vector<double> F(N-1, payoff->get_payoff(opt->get_spot()));
        	
//		std::cout << "wesh 2" <<std::endl;
		//Calcul des coeffs des matrices tridiagonales en T
		double mat = opt->get_maturity(); 
		//def matrice des coeffs pour avoir les coeffs en tt pt de l espace
		std::vector<double> A1(N-1, 0.0);
		std::vector<double> A2(N-1, 0.0);
		std::vector<double> A3(N-1, 0.0);
		std::vector<double> B1(N-1, 0.0);
		std::vector<double> B2(N-1, 0.0);
		std::vector<double> B3(N-1, 0.0);
				
		double Smax = sb->s_boundary_right(opt->get_spot(), opt->get_vol(), opt->get_maturity());
		double Tmax =  tb->t_boundary_right(opt->get_maturity());
		double Tmin =  tb->t_boundary_left(opt->get_maturity());

		double s = exp(Smax);

		for (int i=0; i < N-1; i++)
		{
			A1[i] = a1(pde, s, mat);
//            std::cout << "A1 = " << A1[i] << std::endl;
			A2[i] = a2(pde, s, mat);
//            std::cout << "A2 = " << A2[i] << std::endl;
			A3[i] = a3(pde, s, mat);
//            std::cout << "A3 = " << A3[i] << std::endl;
			B1[i] = b1(pde, s, mat);
//            std::cout << "B1 = " << B1[i] << std::endl;
			B2[i] = b2(pde, s, mat);
//            std::cout << "B2 = " << B2[i] << std::endl;
			B3[i] = b3(pde, s, mat);
//            std::cout << "B3 = " << B3[i] << std::endl;

			s -= m_dx;
		}

		std::cout << N <<std::endl;

		//Calcul du terme constant que l'on extrait pour avoir une matrice tridiagonale
		std::vector<double> C(N-1, 0.0);
//		std::cout << "wesh 3" <<std::endl;

		C[0] = (A1[0] - B1[0]*exp(-r0*m_dt))*m_f0;
//		std::cout << "C0: " << C[0] <<std::endl;

		C[N-2] = (A3[N-2] - B3[N-2]*exp(-r0*m_dt))*m_fN;
//        std::cout << "CN-2: " << C[N-2] <<std::endl;
//		std::cout << "wesh 4" <<std::endl;

		//Calcul de la matrice D en T
		std::vector<double> D(N-1,0.0);
		D[0] = A2[0]*F[0] + A3[0]*F[1] + C[0];
		D[N-2] = A1[N-2]*F[N-2] + A2[N-2]*F[N-2] + C[N-2];
//        std::cout << "D0: " << D[0] <<std::endl;
//        std::cout << "DN2: " << D[N-2] <<std::endl;
		
		for (int i=1; i < N-2; i++)
		{
			D[i] = A1[i]*F[i-1] + A2[i]*F[i] + A3[i]*F[i+1];
//            std::cout << "D: " << D[i] <<std::endl;
		}

//		std::cout << "wesh 5" <<std::endl;


		//On remonte via l'algorithme de Thomas
		s = exp(Smax);

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

				s -= m_dx;
			}


			//On calcule la matrice F en t, et on fait Ft1=Ft
      			F = thomas(B1, B2, B3, D);
            
            for (int i = 0; i<F.size(); ++i)
            {
//                std::cout << i << " " << F[i] << std::endl;
            }
            
			//On recalcule la nouvelle matrice D
			D[0] = A2[0]*F[0] + A3[0]*F[1] + C[0];
			D[N-2] = A1[N-2]*F[N-2] + A2[N-2]*F[N-2] + C[N-2];
		
			for (int i=1; i < N-2; i++)
			{
				D[i] = A1[i]*F[i-1] + A2[i]*F[i] + A3[i]*F[i+1];
			}
		}

//		std::cout << "wesh end" <<std::endl;

		return F;
	}


	std::vector<double> fdm::thomas(const std::vector<double> a,
                                    const std::vector<double> b,
                                    const std::vector<double> c,
                                    std::vector<double> d) const
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
			new_d[i] = (d[i]-a[i] * new_d[i-1]) / (b[i]-a[i] * new_coeffs[i-1]);
		}
		
		//Back substitution
        std::vector<double> y(n, 0.0);
		y[n-1] = new_d[n-1];

		for (int i=n-2; i>=0; i--)
		{
			y[i] = new_d[i] - new_coeffs[i]*y[i+1];
//            std::cout << "y: " << y[i] <<std::endl;
		}
        std::cout << "\n\n" <<std::endl;

		return y;
	}

}
