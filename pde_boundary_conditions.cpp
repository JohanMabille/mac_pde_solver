#include "pde_boundary_conditions.hpp"


namespace dauphine
{

	double Sboundaries::s_boundary_left(double i_spot, double i_maturity) const
	{
    		double lower_boundary = log(i_spot) - 5*initial_sigma*sqrt(i_maturity);
    		return lower_boundary;
	}

	double Sboundaries::s_boundary_right(double i_spot, double i_maturity) const
	{
    		double upper_boundary = log(i_spot) + 5*initial_sigma*sqrt(i_maturity);
    		return upper_boundary;
	}
		
	double Sboundaries::space_mesh(double i_spot, double i_maturity) const
	{
		double S_max = s_boundary_right(i_spot, i_maturity);
		double S_min = s_boundary_left(i_spot, i_maturity);
		return floor((S_max-S_min)/dx);	
	}


	double Tboundaries::t_boundary_left(double t) const
	{
    		return 0.;
	}

	double Tboundaries::t_boundary_right(double t) const
	{
    		return t;
	}

	double Tboundaries::time_mesh(double i_maturity) const
	{
		double T_max = t_boundary_right(i_maturity);
		double T_min = t_boundary_left(T_max);
		return (T_max-T_min)/dt;
	
	}


     
 }

