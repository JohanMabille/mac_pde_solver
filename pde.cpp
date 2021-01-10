#include "pde.hpp"

namespace dauphine
{

    double bs_pde::first_coeff(double t, double x) const {
        return 1.;
    }
    double bs_pde::diff_coeff(double t, double x) const {
      double vol = option->sigma;
      return 0.5*vol*vol*x*x;
    }

    double bs_pde::conv_coeff(double t, double x) const {
      return (option->r)*x;
    }

    double bs_pde::zero_coeff(double t, double x) const {
      return -(option->r);
    }

    double bs_pde::source_coeff(double t, double x) const {
      return 0.;
    }

    //call bondary conditions?
    }

}
