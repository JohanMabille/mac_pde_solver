#ifndef PDE_HPP
#define PDE_HPP

#include <cstddef>
#include <vector>

namespace dauphine
{

    class pde     //a modifier si besoin
    {
    public:
        
        // PDE Coefficients
        virtual double first_coeff(double t, double x) const = 0;
        virtual double diff_coeff(double t, double x) const = 0;
        virtual double conv_coeff(double t, double x) const = 0;
        virtual double zero_coeff(double t, double x) const = 0;
        virtual double source_coeff(double t, double x) const = 0;

    };

    class bs_pde : public pde
    {
        
    public:
        double first_coeff(double t, double x) const;
        double diff_coeff(double t, double x) const;
        double conv_coeff(double t, double x) const;
        double zero_coeff(double t, double x) const;
        double source_coeff(double t, double x) const;
        
    };

}

#endif
