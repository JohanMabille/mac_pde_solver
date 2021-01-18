#ifndef PDE_BOUNDARY_CONDITIONS_HPP
#define PDE_BOUNDARY_CONDITIONS_HPP

#include <stdio.h>
namespace dauphine
{
	class Space_boundaries
    	{
   	public:
		//Constructeurs/Destructeurs?
		
    		virtual double s_boundary_left(double s, double sigma, double t) const=0;
        	virtual double s_boundary_right(double s, double sigma, double t) const = 0;
		virtual double space_mesh(const int dx, interface* option) const = 0;
            
    	};

	class Sboundaries: public Space_boundaries
	{
    	public:
        	double s_boundary_left(double s, double sigma, double t) const;
		double s_boundary_right(double s, double sigma, double t) const;
		double space_mesh(const int dx, interface* option);      
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
           	double t_boundary_left(double t);
           	double t_boundary_right(double t);
	   	double time_mesh(const int dt, interface* option);
   	};

}
#endif
