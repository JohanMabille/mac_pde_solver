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
                      Time_boundaries* tb);
        virtual ~rate();
        // Entity semantics:
        rate(const rate&) = delete;
        rate& operator=(const rate&) = delete;
        rate(rate&&) = delete;
        rate& operator=(rate&&) = delete;

        // This should be a pure virtual function
        // (see additional comments in rate.cpp)
       	virtual double get_rate(double s, double t) const; 
        // Should not be part of the public API,
        // should be in the constructor of the inheriting
        // classes only
	virtual void rate_build() = 0;

    protected:
        // This is implementation-dependent, i.e. it should
        // be defined in inheriting classes where it makes
        // sense. For instance, a constant rate class
        // should store a single double, not a vector, nor
        // the mesh.
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
                 Time_boundaries* tb);
        ~rate_cst();
       	void rate_build() override;
    };
}


#endif
