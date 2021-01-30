#include "volatility.hpp"

namespace dauphine
{
	
	volatility::volatility(Space_boundaries* sb,
                           Time_boundaries* tb,
                           double i_spot,
                           double i_maturity)
    : m_volatility(sb->space_mesh(i_spot, i_maturity)*tb->time_mesh(i_maturity))
    , s_boundaries(sb)
    , t_boundaries(tb)
    , nb_cols(tb->time_mesh(i_maturity))
    , nb_rows(sb->space_mesh(i_spot, i_maturity))
    {
	}

    Space_boundaries* volatility::get_sboundaries(){
        return s_boundaries;
    }

    Time_boundaries* volatility::get_tboundaries(){
        return t_boundaries;
    }
	
	volatility::~volatility()
	{
        m_volatility.clear();
	}

    double volatility::get_sigma(double s, double t) const
    {
        return m_volatility[s*nb_rows + t];
    }

	vol_cst::vol_cst(Space_boundaries* sb,
                     Time_boundaries* tb,
                     double i_spot,
                     double i_maturity,
                     double i_sigma)
    : volatility(sb, tb, i_spot, i_maturity)
    {
        vol_build(i_sigma);
    }

    vol_cst::~vol_cst()
    {
    }

    void vol_cst::vol_build(double i_sigma)
    {
        for (int i = 0; i < nb_rows; ++i)
        {
            for (int j = 0; j < nb_cols; ++j)
            {
                m_volatility[i*nb_rows + j] = i_sigma;
		
            }
        }
    }

}


