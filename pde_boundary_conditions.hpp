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
    // There is a confusion with mesh boudaries.
    // Boundary conditions are the way you fill
    // the boundaries of the matrix system you
    // will solve.
    // The Space_boundaries and Time_boundaries
    // could be gathered into a single class
    // class pde_grid for instance.
	class Space_boundaries
    	{
   	public:
		//Constructeurs/Destructeurs?
		
    		virtual double s_boundary_left() const = 0;
        	virtual double s_boundary_right() const = 0;
            virtual double space_mesh() const = 0;
            
    	};

	class Sboundaries: public Space_boundaries
	{
    	public:
        	double s_boundary_left() const override;
            double s_boundary_right() const override;
            double space_mesh() const override;
    	};

	class Time_boundaries
   	{
       	public:
           	virtual double t_boundary_left(double t) const = 0;
        	virtual double t_boundary_right(double t) const = 0;
            virtual double time_mesh() const = 0;
   	};


   	class Tboundaries: public Time_boundaries
   	{
       	public:
           	double t_boundary_left(double t) const override;
           	double t_boundary_right(double t) const override;
            double time_mesh() const override;
   	};

}
#endif
