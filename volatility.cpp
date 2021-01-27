#include "volatility.hpp"

namespace dauphine
{
	
	volatility::volatility(Space_boundaries* sb,
                           Time_boundaries* tb)
    : m_volatility(sb->space_mesh()*tb->time_mesh())
    , nb_cols(tb->time_mesh())
    , nb_rows(sb->space_mesh())
    {
		std::cout << "constructeur vol" << std::endl;
	}
	
	volatility::~volatility()
	{
        m_volatility.clear();
        std::cout << "destructeur vol" << std::endl;
	}

    double volatility::get_sigma(double s, double t) const
    {
        return m_volatility[s*nb_rows + t];
    }

	vol_cst::vol_cst(Space_boundaries* sb,
                     Time_boundaries* tb)
    : volatility(sb, tb)
    {
        vol_build();
        std::cout << "constructeur vol cst" << std::endl;
    }

    vol_cst::~vol_cst()
    {
        std::cout << "destructeur vol cst" << std::endl;
    }

    void vol_cst::vol_build()
    {
        for (int i = 0; i < nb_rows; ++i)
        {
            for (int j = 0; j < nb_cols; ++j)
            {
                m_volatility[i*nb_rows + j] = initial_sigma;
            }
        }
    }

}


