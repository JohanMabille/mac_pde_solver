#ifndef PDE_HPP
#define PDE_HPP

#include <cstddef>
#include <vector>
#include "volatility.hpp"
#include "global.hpp"
#include "rate.hpp"


namespace dauphine
{

    class pde    
    {
    public:
        
        explicit pde();
        virtual ~pde();
        
        // PDE Coefficients
        virtual double first_coeff() const = 0;
        virtual double diff_coeff(double s, double t) const = 0;
        virtual double conv_coeff(double s, double t) const = 0;
        virtual double zero_coeff(double s, double t) const = 0; 
        virtual double source_coeff() const = 0;
        virtual volatility* get_volatility() const = 0;
        virtual rate* get_rate() const = 0;

    };

    class bs_pde : public pde
    {
        
    public:
        
        bs_pde(volatility* vol, rate* r); //added to match the cpp file, please review
        bs_pde(interface* inter);
        virtual ~bs_pde();
        
        double first_coeff() const override;
        double diff_coeff(double s, double t) const override;
        double conv_coeff(double s, double t) const override;
        double zero_coeff(double s, double t) const override;
        double source_coeff() const override;
        volatility* get_volatility() const override;
        rate* get_rate() const override;
    
    private:
        
        volatility* m_vol;
        rate* m_rate;
    };

}

#endif
