#include "interface.hpp"


namespace dauphine
{

	interface::interface(payoff* pay)
    :  m_payoff(pay)
	{
        	std::cout<<"interface constructor"<<std::endl;
	}

    interface::~interface()
    {
        m_payoff = nullptr;
        std::cout<<"interface destructor"<<std::endl;
    }

//    double interface::get_rate()
//    {
  //      double s = 0;
    //    double t = 0;
    
      //  return m_rate->get_rate(s, t);
    //}

//    double interface::get_maturity()
//    {
//        return m_maturity;
//    }

//    double interface::get_vol(double s, double t)
//    {
//        return m_vol->get_sigma(s, t);
//    }

//    double interface::get_spot()
//    {
//        return m_spot;
//    }

    payoff* interface::get_payoff()
    {
        return m_payoff;
    }

    void interface::set_spot(double spot)
    {
        this->m_spot = spot;
    }
//
//    void interface::set_maturity(double t)
//    {
//        this->m_maturity = t;
//    }

//    void interface::set_vol(volatility* sig)
//    {
//        this->m_vol = sig;
//    }


	
}

