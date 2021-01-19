#ifndef PDE_BOUNDARY_CONDITIONS_HPP
#define PDE_BOUNDARY_CONDITIONS_HPP

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "interface.hpp"
namespace dauphine
{
	class Space_boundaries
    	{
   	public:
		//Constructeurs/Destructeurs?
		
    		virtual double s_boundary_left(double s, double sigma, double t) const = 0;
        	virtual double s_boundary_right(double s, double sigma, double t) const = 0;
		virtual double space_mesh(const int dx, interface* option) const = 0;
            
    	};

	class Sboundaries: public Space_boundaries
	{
    	public:
        	double s_boundary_left(double s, double sigma, double t) const override;
		double s_boundary_right(double s, double sigma, double t) const override;
		double space_mesh(const int dx, interface* option) const override;      
    	};

	class Time_boundaries
   	{
       	public:
           	virtual double t_boundary_left(double t) const=0;
        	virtual double t_boundary_right(double t) const = 0;
	  	virtual double time_mesh(const int dt, interface* option) const =0;
   	};


   	class Tboundaries: public Time_boundaries
   	{
       	public:
           	double t_boundary_left(double t) const override;
           	double t_boundary_right(double t) const override;
	   	double time_mesh(const int dt, interface* option) const override;
   	};

}
#endif
