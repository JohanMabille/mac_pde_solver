#include "pde.hpp"

namespace dauphine
{
    
    pde::pde()
    {
        std::cout<<"PDE constructor"<<std::endl;
    }

    pde::~pde()
    {
        std::cout<<"PDE destructor"<<std::endl;
    }

    bs_pde::bs_pde(interface* option, volatility* vol)
    : m_opt(option), m_vol(vol)
    {
        std::cout<<"BS PDE constructor"<<std::endl;
    }

    bs_pde::~bs_pde()
    {
        m_opt = nullptr;
        m_vol = nullptr;
        std::cout<<"BS PDE destructor"<<std::endl;
    }

    double bs_pde::first_coeff() const
    {
        return 1.;
    }

    double bs_pde::diff_coeff(double s, double t) const
    {
          double sigma = m_vol->get_sigma(s, t);
          return -0.5*sigma*sigma;
    }

    double bs_pde::conv_coeff(double s, double t) const
    {
        double sigma = m_vol->get_sigma(s, t);
        double rate = m_opt->get_rate();

        return 0.5*sigma*sigma-rate;
    }

    double bs_pde::zero_coeff() const
    {
        return m_opt->get_rate();
    }

    double bs_pde::source_coeff() const
    {
        return 0.;
    }

}
