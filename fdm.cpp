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

	double fdm_interface::alpha(double dx, double sig)
	{
		return -0.5*sig**2*1/(dx**2);
	}

	double fdm_interface::beta(double dx, double sig, double r)
	{
		return (-0.5*sig**2 - r)*1/(2*dx);
	}

	double fdm_interface::a1(double theta, double dt, double dx, double sig, double r)
	{
		double alpha =alpha(dx, sig);
		double beta=beta(dx, sig, r);
		
		return dt*(1-theta)*(beta-alpha);
	}

	double fdm_interface::a2(double theta, double dt, double dx, double sig, double r)
	{
		double alpha =alpha(dx, sig);
			
		return (1- (1-theta)*dt*(r - 2*alpha));
	}

	double fdm_interface::a3(double theta, double dt, double dx, double sig, double r)
	{
		double alpha =alpha(dx, sig);
		double beta=beta(dx, sig, r);
		
		return (-dt*(1-theta)*(beta+alpha));
	}

	double fdm_interface::b1(double theta, double dt, double dx, double sig, double r)
	{
		double alpha =alpha(dx, sig);
		double beta=beta(dx, sig, r);
		
		return dt*theta*(alpha - beta);
	}

	double fdm_interface::b2(double theta, double dt, double dx, double sig, double r)
	{
		double alpha =alpha(dx, sig);
			
		return (1- theta*dt*(r - 2*alpha));
	}

	double fdm_interface::b3(double theta, double dt, double dx, double sig, double r)
	{
		double alpha =alpha(dx, sig);
		double beta=beta(dx, sig, r);
		
		return dt*theta*(beta+alpha);
	}

	fdm::fdm(pde* pde, double f0, double fN,  double lower_T, double upper_T,double lower_N, double upper_N)
		:pde(pd_e), f0(boundary_f0), fN(boundary_fN), lower_T(lT), upper_T(uT), lower_N(lN), upper_N(uN)
	{
		//Lien avec PDE??
		
		//Calcul avec FDM
		//1. On discretise le temps et l'espace
		std::vector<double> t_mesh = time_mesh(lower_T, upper_T);
		std::vector<double> s_mesh = space_mesh(lower_N, upper_N);
		
		//2. Calcul des f intermédiaires
		T = floor((upper_T-lower_T)/dt);
		N = floor((upper_N-lower_N)/dt);

		std::vector<double> f_N = std::fill(1,N-1,fN); //Boundary condition at t=T
		//Necessaire?						// N-1 inclus?
		std::vector<double> f_0 = std::fill(1,N-1,f0); 

		for (int t = 1; N-1; t++)
		{
			//Pour chaque t+1, en commencant par f_N, on remonte à t
			//via l'ago de thomas et le systeme trouvé
		
		}

		return ; //A compléter
	}

	
	fdm::~fdm()
	{
		delete pde; //destruction du pointeur
	}

	std::vector<double> fdm::time_mesh(double lower_T, double upper_T, int dt = 1)
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
	
	std::vector<double> fdm::space_mesh(double lower_N, double upper_N, int dx = 1)
	{
		int N = floor((upper_N-lower_N)/dx);
		std::vector<float> v = std::fill(0, N, 0);
		v[0]=lower_N;
		v[T-1]=upper_N;

		for (int c=1; c<N-1; c++) //Ou avec un functor?
		{
			v[c] = v[c-1] + dx;
		}
		
		return v;
	}

	std::vector<double> fdm::thomas(std::vector<double> coeffs, std::vector<double> x, std::vector<double> d)
	{
		//algo de Thomas pour inverser une matrice tridiagonale
	}






}
