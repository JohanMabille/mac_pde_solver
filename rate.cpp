#include "rate.hpp"

namespace dauphine{

	rate::rate(Space_boundaries* sb,Time_boundaries* tb)
    		: m_rate(sb->space_mesh()*tb->time_mesh())
            ,s_boundaries(sb)
            ,t_boundaries(tb)
    		, nb_cols(tb->time_mesh())
    		, nb_rows(sb->space_mesh())

	{
	}

	rate::~rate()
	{
	}


     double rate::get_rate(double s, double t) const
    {       double  s_left = s_boundaries->s_boundary_left();
            int s_index = (log(s) - s_boundaries->s_boundary_left())/ dx;
            int t_index;
        if(t==0){
            t_index = 0;
        }
        else{
            t_index = (log(t) - t_boundaries->t_boundary_left(t))/dt;
        }
            return m_rate[s_index*nb_cols + t_index];
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
                		m_rate[i*nb_cols + j] = initial_rate;
				
            		}
        	}
    	}

}
