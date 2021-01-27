#ifndef volatility_hpp
#define volatility_hpp

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>
#include <functional>
#include <stdio.h>

#include "pde_boundary_conditions.hpp"
#include "global.hpp"


namespace dauphine
{
    class volatility
     {
     public:
         explicit volatility(Space_boundaries* sb,
                             Time_boundaries* tb);
         virtual ~volatility();
         virtual double get_sigma(double s, double t) const;
         virtual void vol_build() = 0;
         
     protected:
         std::vector<double> m_volatility;
         int nb_rows;
         int nb_cols;
     };


     class vol_cst: public volatility
     {
     public:
         vol_cst(Space_boundaries* sb,
                 Time_boundaries* tb);
         ~vol_cst();
         void vol_build() override;
     };
}

#endif
