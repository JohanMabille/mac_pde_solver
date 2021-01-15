#include "fdm_interface.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
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

	double fdm_interface::a1(pde* pde) const
	{		
		double alpha = (pde->first_coeff())/(dx**2);
		double beta=(pde->conv_coeff())/(2*dx);
		
		return dt*(1-theta)*(beta-alpha);
	}

	double fdm_interface::a2(pde* pde) const
	{
		double alpha = (pde->first_coeff())/(dx**2);
		return (1- (1-theta)*dt*(r - 2*alpha));
	}

	double fdm_interface::a3(pde* pde) const
	{
		double alpha = (pde->first_coeff())/(dx**2);
		double beta=(pde->conv_coeff())/(2*dx);
		
		return (-dt*(1-theta)*(beta+alpha));
	}

	double fdm_interface::b1(pde* pde) const
	{
		double alpha = (pde->first_coeff())/(dx**2);
		double beta=(pde->conv_coeff())/(2*dx);
		
		return dt*theta*(alpha - beta);
	}

	double fdm_interface::b2(pde* pde) const
	{
		double alpha = (pde->first_coeff())/(dx**2);
			
		return (1- theta*dt*(r - 2*alpha));
	}

	double fdm_interface::b3(pde* pde) const
	{
		double alpha = (pde->first_coeff())/(dx**2);
		double beta=(pde->conv_coeff())/(2*dx);

		return dt*theta*(beta+alpha);
	}

	fdm::fdm(pde* pde, payoff* payoff, const double f0, const double fN, const double lower_T, const double upper_T, const double lower_N, const double upper_N)
		:m_pde(pde), m_payoff(payoff), boundary_f0(f0), boundary_fN(fN), lT(lower_T), uT(upper_T), lN(lower_N), uN(upper_N), m_dt(dt), m_dx(dx)
	{
		
		//Calcul avec FDM
		//1. On discretise le temps et l'espace
		//ajouter dt et dx en argument
		//std::vector<double> liste_t = time_mesh(lower_T, upper_T); // Utile ?
		//std::vector<double> liste_S = space_mesh(lower_N, upper_N); 	

		T = floor((upper_T-lower_T)/dt);
		N = floor((upper_N-lower_N)/dt);
	
		//2. Calcul des f intermédiaires
		//Calcul du nb de steps en tps et en espace: T et N
		
		//Calcul de la matrice F en T
		std::vector<double> F = std::fill(1,N-1, payoff);

		//Calcul des coeffs des matrices tridiagonales
		a1 = a1(pde); 
		a2 = a2(pde);
		a3 = a3(pde);
		b1 = b1(pde);
		b2 = b2(pde);
		b3 = b3(pde);

		//Calcul du terme constant que l'on extrait pour avoir une matrice tridiagonale
		std::vector<double> c = std::fill(1, N-1, 0); 
		r = pde->zero_coeff()
		c[0]= (a1 - b1*exp(-r*dt))*f0; 
		c[N-2]= (a3 - b3*exp(-r*dt))*f0; 

		//Calcul de la matrice D en T
		std::vector<double> D = std::fill(1,N-1,0);
		D[0] = a2*F[0] + a3*F[1] + c[0];
		D[N-2] = a1*F[N-2] + a2*F[N-2] + c[N-2];
		for (int i=1; i<N-2; i++)
		{
			D[i] = a1*F[i-1] + a2*F[i] + a3*F[i+1];
		}

		//On remonte via l'algorithme de Thomas
		std::vector<double> coeffs = std::fill(0,2,0);
		coeffs[0] = b1;
		coeffs[1] = b2;	
		coeffs[2] = b3;

		for (int t = T-1; t>=0 ; t--)
		{
			//Pour chaque x(i,t+1), en commencant par f_N, on remonte à x(i,t)
			//via l'algo de Thomas et le système trouvé

			//On calcule la matrice F en t, et on fait Ft1=Ft
			F = thomas(coeffs, D);

			//On recalcule la nouvelle matrice D
			D[0] = a2*F[0] + a3*F[1] + c[0];
			D[N-2] = a1*F[N-2] + a2*F[N-2] + c[N-2];
			for (int i=1; i<N-2; i++)
			{
				D[i] = a1*F[i-1] + a2*F[i] + a3*F[i+1];
			}
		}

		return F[floor(N/2)];
	}

	
	fdm::~fdm()
	{
		delete pde; //destruction du pointeur
	}

	std::vector<double> fdm::time_mesh(const double lower_T, const double upper_T, const int dt = 1) const
	{
		int T = floor((upper_T-lower_T)/dt);
		std::vector<float> v = std::fill(0, T, 0);
		v[0]=lower_T;
		v[T-1]=upper_T;

		for (int c=1; c<T-1; c++) //Ou avec un functor?
		{
			v[c] = v[c-1] + dt;
		}

		return v;	
	}
	
	std::vector<double> fdm::space_mesh(const double lower_N, const double upper_N, const int dx = 1) const
	{
		int N = floor((upper_N-lower_N)/dx);
		std::vector<float> v = std::fill(0, N, 0);
		v[0]=lower_N;
		v[N-1]=upper_N;

		for (int c=1; c<N-1; c++) //Ou avec un functor?
		{
			v[c] = v[c-1] + dx;
		}
		
		return v;
	}

	std::vector<double> fdm::thomas(const std::vector<double> coeffs, std::vector<double> d)
	{
		//algo de Thomas pour inverser une matrice tridiagonale dans le cas de coeffs "constant" dans l'espace
		a=coeffs[0];
		b=coeffs[1];
		c=coeffs[2];
		
		int n = d.size()
		std::vector<double> new_coeffs = std::fill(0, n, 0);
		std::vector<double> new_d = std::fill(0, n, 0);

		//Forward sweep
		new_coeffs[0]=c/b;
		new_d[0]= d[0]/b;

		for (int i=1; i<n-1; i++)
		{
			new_coeffs[i]=c/(b-a*new_coeffs[i-1]);
			new_d[0]= (d[i]-a*new_d[i-1])/(b-a*new_coeffs[i-1]);
		}
		
		//Back substitution
		std::vector<double> x = std::fill(0, n, 0);
		x[n-1]=new_d[n-1];

		for (int i=n-2; i>=0; i--)
		{
			x[i]=new_d[i] - new_coeffs[i]*x[i+1];
		}

		return x;
	}

}
