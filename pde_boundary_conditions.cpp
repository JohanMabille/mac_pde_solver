#include "pde_boundary_conditions.hpp"
#include "interface.hpp"

#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

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
		
	double Sboundaries::space_mesh(const int dx, interface* option) const
	{
		double S_max = s_boundary_right(option->get_spot(), option->get_vol(), option->get_maturity());
		double S_min = s_boundary_left(option->get_spot(), option->get_vol(), option->get_maturity());
		return floor((S_max-S_min)/dx);	
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
		double T_max = t_boundary_right(option->get_maturity());
		double T_min = t_boundary_left(T_max); //argu nécessaire dans la fonction?
		return (T_max-T_min)/dt;
	
	}


     
 }

