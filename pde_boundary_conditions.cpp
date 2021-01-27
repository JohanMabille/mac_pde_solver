#include "pde_boundary_conditions.hpp"


namespace dauphine
{

	double Sboundaries::s_boundary_left() const
	{
    		double lower_boundary = log(spot) - 5*initial_sigma*sqrt(maturity);
    		return lower_boundary;
	}

	double Sboundaries::s_boundary_right() const
	{
    		double upper_boundary = log(spot) + 5*initial_sigma*sqrt(maturity);
    		return upper_boundary;
	}
		
	double Sboundaries::space_mesh() const
	{
		double S_max = s_boundary_right();
		double S_min = s_boundary_left();
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

	double Tboundaries::time_mesh() const
	{
		double T_max = t_boundary_right(maturity);
		double T_min = t_boundary_left(T_max); //argu nécessaire dans la fonction?
		return (T_max-T_min)/dt;
	
	}


     
 }

