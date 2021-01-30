#ifndef PDE_BOUNDARY_CONDITIONS_HPP
#define PDE_BOUNDARY_CONDITIONS_HPP

#include "global.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>


namespace dauphine
{
	class Space_boundaries
    	{
   	public:

		
    		virtual double s_boundary_left(double i_spot, double i_maturity) const = 0;
        	virtual double s_boundary_right(double i_spot, double i_maturity) const = 0;
            virtual double space_mesh(double i_spot, double i_maturity) const = 0;
            
    	};

	class Sboundaries: public Space_boundaries
	{
    	public:
        	double s_boundary_left(double i_spot, double i_maturity) const override;
            double s_boundary_right(double i_spot, double i_maturity) const override;
            double space_mesh(double i_spot, double i_maturity) const override;
    	};

	class Time_boundaries
   	{
       	public:
           	virtual double t_boundary_left(double t) const = 0;
        	virtual double t_boundary_right(double t) const = 0;
            virtual double time_mesh(double i_maturity) const = 0;
   	};


   	class Tboundaries: public Time_boundaries
   	{
       	public:
           	double t_boundary_left(double t) const override;
           	double t_boundary_right(double t) const override;
            double time_mesh(double i_maturity) const override;
   	};

}
#endif
