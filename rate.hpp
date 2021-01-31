#ifndef rate_hpp
#define rate_hpp

#include "global.hpp"
#include "pde_boundary_conditions.hpp"
#include <stdio.h>

namespace dauphine
{

    class rate
    {
    public:
	explicit rate(Space_boundaries* sb,
                  Time_boundaries* tb,
                  double i_spot,
                  double i_maturity);
        virtual ~rate();
       	virtual double get_rate(double s, double t) const; 
	virtual void rate_build() = 0;

    protected:
	std::vector<double> m_rate;
        int nb_rows;
        int nb_cols;
        Space_boundaries* s_boundaries;
        Time_boundaries* t_boundaries;
    };


    class rate_cst: public rate
    {
  
    public:
        rate_cst(Space_boundaries* sb,
                 Time_boundaries* tb,
                 double i_spot,
                 double i_maturity);
        ~rate_cst();
       	void rate_build() override;
    };
}


#endif
