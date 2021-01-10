//
//  pde_boundary_conditions.hpp
//  PDE
//
//  Created by Meriem Hrittane on 10/01/2021.
//  Copyright © 2021 Meriem Hrittane. All rights reserved.
//

#ifndef pde_boundary_conditions_hpp
#define pde_boundary_conditions_hpp

#include <stdio.h>
namespace dauphine
{

    class Space_boundaries
    {
        public:
            virtual double boundary_left(double s, double sigma, double t) const=0;
            virtual double boundary_right(double s, double sigma, double t) const = 0;
        
            
    };


    class Sboundaries: public Space_boundaries
    {
        public:
            double boundary_left(double s, double sigma, double t);
            double boundary_right(double s, double sigma, double t);
        
            
    };


class Time_boundaries
   {
       public:
           virtual double boundary_left(double t) const=0;
           virtual double boundary_right(double t) const = 0;
   };


   class Tboundaries: public Time_boundaries
   {
       public:
           double boundary_left(double t);
           double boundary_right(double t);
   };

}
#endif /* pde_boundary_conditions_hpp */
