#include "pde_boundary_conditions.hpp"
#include <math.h>
namespace dauphine
{

	double Sboundaries::s_boundary_left(double s,double sigma, double t) const
	{
    		double lower_boundary = log (s) - 5*sigma*sqrt(t);
    		return lower_boundary;
	}

	double Sboundaries::s_boundary_right(double s, double sigma, double t) const
	{
    		double upper_boundary = log (s) + 5*sigma*sqrt(t);
    		return upper_boundary;
	}
		
	double Sboundaries::space_mesh(const int dx, interface* option)
	{
		double nbN;
		S_max = boundary_right(option.m_spot, option->get_vol(), option->get_maturity());
		S_min = boundary_left(option.m_spot, option->get_vol(), option->get_maturity());
		nbN = floor((S_max-S_min)/dx);

		return nbN;	
	}


	double Tboundaries::t_boundary_left(double t) const //argu nécessaire?
	{
    		return 0.;
	}

	double Tboundaries::t_boundary_right(double t) const
	{
    		return t;
	}

	double Tboundaries::time_mesh(const int dt, interface* option) const
	{
		double nbT;
		T_max = boundary_right(option->get_maturity());
		T_min = boundary_left(T_max); //argu nécessaire dans la fonction?
		nbT = floor((T_max-T_min)/dt);

		return nbT;	
	}


     
 }

