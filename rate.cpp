#include "rate.hpp"

namespace dauphine{

	rate::rate(Space_boundaries* sb,Time_boundaries* tb)
    		: m_rate(sb->space_mesh()*tb->time_mesh())
            ,s_boundaries(sb)
            ,t_boundaries(tb)
                // These values can be retrieved via
                // s_boundaries and t_boundaries, no need
                // to store them as data members
    		, nb_cols(tb->time_mesh())
    		, nb_rows(sb->space_mesh())

	{
	}

	rate::~rate()
	{
	}


     double rate::get_rate(double s, double t) const
    {   
        // This implementation is specific to interpolated
        // non-const rates, it should not be implemented in
        // the base class.
        double  s_left = s_boundaries->s_boundary_left();
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
                     Time_boundaries* tb)
    	: rate(sb, tb)
    	{
        	rate_build();
    	}

    	rate_cst::~rate_cst()
    	{
    	}

        // 
    	void rate_cst::rate_build()
    	{
            // No need to fill a vector here (actually no need for
            // the rate_build method, just override get_rate and return
            // the constant value
        	for (int i = 0; i < nb_rows; ++i)
        	{
            		for (int j = 0; j < nb_cols; ++j)
            		{
                		m_rate[i*nb_cols + j] = initial_rate;
				
            		}
        	}
    	}

}
