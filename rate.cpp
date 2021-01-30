#include "rate.hpp"

namespace dauphine{

	rate::rate(Space_boundaries* sb,Time_boundaries* tb, double i_spot, double i_maturity)
    		: m_rate(sb->space_mesh(i_spot, i_maturity)*tb->time_mesh(i_maturity))
    		, nb_cols(tb->time_mesh(i_maturity))
    		, nb_rows(sb->space_mesh(i_spot, i_maturity))

	{
	}

	rate::~rate()
	{
	}

	double rate::get_rate(double s, double t) const
    	{
       		return m_rate[s*nb_rows + t];
   	}

	rate_cst::rate_cst(Space_boundaries* sb,
                       Time_boundaries* tb,
                       double i_spot,
                       double i_maturity)
    	: rate(sb, tb, i_spot, i_maturity)
    	{
        	rate_build();
    	}

    	rate_cst::~rate_cst()
    	{
    	}

    	void rate_cst::rate_build()
    	{
        	for (int i = 0; i < nb_rows; ++i)
        	{
            		for (int j = 0; j < nb_cols; ++j)
            		{
                		m_rate[i*nb_rows + j] = initial_rate;
				
            		}
        	}
    	}

}
