#ifndef PDE_HPP
#define PDE_HPP

#include <cstddef>
#include <vector>
#include "interface.hpp"
namespace dauphine
{

    class pde    
    {
    public:
        
        explicit pde();
        virtual ~pde();
        
        // PDE Coefficients
        virtual double first_coeff() const = 0;
        virtual double diff_coeff() const = 0;
        virtual double conv_coeff() const = 0;
        virtual double zero_coeff() const = 0; 
        virtual double source_coeff() const = 0;

    };

    class bs_pde : public pde
    {
        
    public:
        
        bs_pde(interface* option); //added to match the cpp file, please review
        virtual ~bs_pde();
        
        double first_coeff() const override;
        double diff_coeff() const override;
        double conv_coeff() const override;
        double zero_coeff() const override;
        double source_coeff() const override;
    
    private:
        
        interface* opt;
    };

}

#endif
