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

			virtual double time_step(const double lower_T, const double upper_T, const int nb_steps) const = 0;
			virtual double space_step(const double lower_T, const double upper_T, const int nb_steps) const = 0;

			virtual double alpha(const double dx, const double sig) const; //facilite le calcul des coeffs
			virtual double beta(const double dx, const double sig, const double r) const; //facilite le calcul des coeffs
			//a adapter pour r

			virtual double a1(const double theta, const double dt, const double dx, const double sig, const double r) const;
			virtual double a2(const double theta, const double dt, const double dx, const double sig, const double r) const;

			virtual double a3(const double theta, const double dt, const double dx, const double sig, const  double r) const;

			virtual double b1(const double theta, const double dt, const double dx, const double sig, const double r) const;

			virtual double b2(const double theta, const double dt, const double dx, const double sig, const double r) const;

			virtual double b3(const double theta, const double dt, const double dx, const double sig, const double r) const;
		
			std::vector<double> old_storage; //necessaire?
			std::vector<double> new_storage; //necessaire?

	};//ajouter des const

	class fdm : public fdm_interface
	{
		public:
			fdm(pde* pde, const double f0, const double fN, const double lower_T, const double upper_T, const double lower_N, const double upper_N);
			~fdm();

			std::vector<double> time_mesh(const double lower_T, const double upper_T, const int dt = 1) const;
			std::vector<double> space_mesh(const double lower_N, const double upper_N, const int dx = 1) const;
			
			std::vector<double> fdm_calcul(pde* pde /*?*/); //necessaire?

			std::vector<double> thomas(const std::vector<double> coeffs, std::vector<double> x, std::vector<double> d);
	

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
