#ifndef PDE_HPP
#define PDE_HPP

#include <cstddef>
#include <vector>

namespace dauphine
{

    class pde    
    {
    public:
        
        pde();
        virtual ~pde();
        
        // PDE Coefficients
        virtual double first_coeff() const = 0;
        virtual double diff_coeff() const = 0;
        virtual double conv_coeff() const = 0;
        virtual double zero_coeff() const = 0; 
        virtual double source_coeff() const = 0; //utile?

    };

    class bs_pde : public pde
    {
        
    public:
        
        explicit bs_pde();
        virtual ~bs_pde();
        
        double first_coeff() const;
        double diff_coeff() const;
        double conv_coeff() const;
        double zero_coeff() const;
        double source_coeff() const;
    
    private:
        
        interface* opt;
    };

}

#endif
