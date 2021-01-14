//
//  volatility.hpp
//  mac_pde_solver
//
//  Created by Meriem Hrittane on 11/01/2021.
//

#ifndef volatility_hpp
#define volatility_hpp

#include <stdio.h>

namespace dauphine
{

    class volatility
    {
        public:
        //ajouter constructeur
        virtual ~volatility();
        virtual double get_sigma(double s, double t) const = 0; // à quoi ça sert ?
        
    };


    class vol_cst: public volatility
    {
    private:
        double sigma;
        
    public:
        vol_cst(double initial_sigma);
        ~vol_cst();
        double get_sigma(double s, double t) const override; // à quoi ça sert ?

    };

}

#endif /* volatility_hpp */
