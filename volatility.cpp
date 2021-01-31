#include "volatility.hpp"

namespace dauphine
{
	
	volatility::volatility(Space_boundaries* sb,
                           Time_boundaries* tb)
    : m_volatility(sb->space_mesh()*tb->time_mesh())
    ,s_boundaries(sb)
    ,t_boundaries(tb)
    , nb_cols(tb->time_mesh())
    , nb_rows(sb->space_mesh())
    {
		std::cout << "constructeur vol" << std::endl;
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
        std::cout << "destructeur vol" << std::endl;
	}
    
    double volatility::get_sigma(double s, double t) const
    {
        double  s_left = s_boundaries->s_boundary_left();
        int s_index = (log(s) - s_boundaries->s_boundary_left())/ dx;
        int t_index;
        if(t==0){
            t_index = 0;
        }
        else{
            t_index = (log(t) - t_boundaries->t_boundary_left(t))/dt;
        }
            return m_volatility[s_index*nb_cols + t_index];
    }
    double volatility::get_sigma_by_index(int row, int column) const{
        return m_volatility[row*nb_cols+column];
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

    void vol_cst::vol_build(double eps)
    {
        for (int i = 0; i < nb_rows; ++i)
        {
            for (int j = 0; j < nb_cols; ++j)
            {
                m_volatility[i*nb_cols + j] = initial_sigma*(1+eps/100);
		
            }
        }
    }

}


