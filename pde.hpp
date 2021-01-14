#ifndef PDE_HPP
#define PDE_HPP

#include <cstddef>
#include <vector>

namespace dauphine
{

    class pde     //a modifier si besoin
    {
    public:
        
        pde();
        virtual ~pde();
        
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
        
        explicit bs_pde();
        virtual ~bs_pde();
        
        double first_coeff(double t, double x) const;
        double diff_coeff(double t, double x) const;
        double conv_coeff(double t, double x) const;
        double zero_coeff(double t, double x) const;
        double source_coeff(double t, double x) const;
    
    private:
        
        interface* opt;
    };

}

#endif
