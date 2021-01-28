#include "rate.hpp"

namespace dauphine{

	rate::rate(Space_boundaries* sb,Time_boundaries* tb)
    		: m_rate(sb->space_mesh()*tb->time_mesh())
    		, nb_cols(tb->time_mesh())
    		, nb_rows(sb->space_mesh())

	{
		std::cout << "constructeur rate" << std::endl;
	}

	rate::~rate()
	{
		std::cout << "destructeur rate" << std::endl;
	}

	double rate::get_rate(double s, double t) const
    	{
       		return m_rate[s*nb_rows + t];
   	}

	rate_cst::rate_cst(Space_boundaries* sb,
                     Time_boundaries* tb)
    	: rate(sb, tb)
    	{
        	rate_build();
        	std::cout << "constructeur rate cst" << std::endl;
    	}

    	rate_cst::~rate_cst()
    	{
        	std::cout << "destructeur rate cst" << std::endl;
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
