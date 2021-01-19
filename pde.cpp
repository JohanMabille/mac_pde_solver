#include "pde.hpp"
#include "interface.hpp"
#include <iostream>

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

    bs_pde::bs_pde(interface* option)
    : opt(option)
    {
        std::cout<<"BS PDE constructor"<<std::endl;
    }

    bs_pde::~bs_pde()
    {
        
        std::cout<<"BS PDE destructor"<<std::endl;
    }

    double bs_pde::first_coeff() const
    {
        return 1.;
    }

    double bs_pde::diff_coeff() const
    {
      double sigma = opt->get_vol();
      return -0.5*sigma*sigma;
    }

    double bs_pde::conv_coeff() const
    {
	double sigma = opt->get_vol();
	double rate = opt->get_rate();

      	return 0.5*sigma*sigma-rate;
    }

    double bs_pde::zero_coeff() const
    {
      return opt->get_rate();
    }

    double bs_pde::source_coeff() const
    {
      return 0.;
    }

    //call bondary conditions?

}
