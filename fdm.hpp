#ifndef FDM_INTERFACE_HPP
#define FDM_INTERFACE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>
#include <functional>


namespace dauphine
{
	class fdm_interface
	{
		public:
			fdm_interface(); //explict?
			virtual ~fdm_interface();

			virtual double time_step(double lower_T, double upper_T, int nb_steps) const = 0;
			virtual double space_step(double lower_T, double upper_T, int nb_steps) const = 0;

			virtual double alpha(double dx, double sig); //facilite le calcul des coeffs
			virtual double beta(double dx, double sig, double r); //facilite le calcul des coeffs

			virtual double a1(double theta, double dt, double dx, double sig, double r);
			virtual double a2(double theta, double dt, double dx, double sig, double r);

			virtual double a3(double theta, double dt, double dx, double sig, double r);

			virtual double b1(double theta, double dt, double dx, double sig, double r);

			virtual double b2(double theta, double dt, double dx, double sig, double r);

			virtual double b3(double theta, double dt, double dx, double sig, double r);
		
			std::vector<double> old_storage;
			std::vector<double> new_storage;

	};

	class fdm : public fdm_interface
	{
		public:
			fdm(pde* pde, double f0, double fN, double lower_T, double upper_T,double lower_N, double upper_N);
			~fdm();

			std::vector<double> time_mesh(double lower_T, double upper_T, int dt = 1);
			std::vector<double> space_mesh(double lower_N, double upper_N, int dx = 1);
			
			std::vector<double> fdm_calcul(pde* pde /*?*/);

			std::vector<double> thomas(std::vector<double> coeffs, std::vector<double> x, std::vector<double> d);
	

		private:
			pde* pd_e;
			double boundary_f0;
			double boundary_fN;
			double uT;
			double lT;
			double uN;
			double lN;
	
	
    };




}

#endif
