#include "closed_form.hpp"
#include "payoff.hpp"
#include "pde.hpp"
#include "pde_boundary_conditions.hpp"
#include "fdm.hpp"
#include "rate.hpp"
#include "volatility.hpp"
#include "global.hpp"


// Guidelines:
//
// 1] Equation
// Even if the volatility and the rate are constant in the BS model,
// we can prove that, under certain assumptions, we can use the same
// PDE equation with volatility surface and rate curves. We could also
// want to take into account the repo (even if it could theoretically
// be part of the r factor). Therefore, it is more generic to solve
// the following generic equation;
// df/dt = a(x,t)d2f/dx2 + b(x,t)df/dx + c(x, t)f + d(x, t).
// The pricer should ask the coefficients a, b, c and d to an
// abstract class that will be inherited by classes implementing
// different models.
//
// 2] Payoff
// The pricer should be able to price exotic options, such as
// barriers or asian options. To do so, the pricer must be able
// to call an external function between each step. Define an API
// that allows to register a function or an abstract class modeling
// a payoff.


namespace dauphine {

    void test()
    {
        std::cout << "Please enter the strike: " << std::endl;
        double user_strike = 0;
        std::cin >> user_strike;
        
        Space_boundaries* sb = new Sboundaries();
        Time_boundaries* tb = new Tboundaries();
        
        payoff* c = new call(user_strike);

        volatility* vol = new vol_cst(sb, tb);
        rate* r = new rate_cst(sb, tb);
       
        pde* eq = new bs_pde(vol, r);
        fdm_interface* f = new fdm(eq, c);
  
	        
        std::cout << "Payoff: " << c->get_payoff(spot) << std::endl;
        
        std::vector<double> price_list = f->get_price_list(spot, maturity);

    //	std::vector<std::vector<double>> price_list = f->get_price_list();       //delete redundancy of eq, c and r
    //    std::cout << "Price List: " << std::endl;
    //        for (std::size_t i=0; i<price_list[price_list.size()-1].size(); i++)
    //	{
    //        std::cout << price_list[price_list.size()-1][i] << std::endl;
    //
    //	}
        
        std::vector<std::vector<double>> price_list = f->get_price_list();
        std::cout << "Price at the input Spot: " << f->get_price(price_list[price_list.size()-1]) << std::endl;
            
        std::cout << "BS Price: " << bs_price(spot, user_strike, initial_sigma, maturity, true) << std::endl;
        
            std::vector<double> delta_surface = f->get_delta_curve();
        std::cout << "Delta: " << f->get_price(delta_surface) << std::endl;
            
        
        

        
    
//
//        std::cout << "Delta: " << std::endl;
//        for (std::size_t i=0; i<delta_surface.size(); i++)
//        {
//            std::cout << delta_surface[i] << std::endl;
//
//        }
        
        std::vector<double> gamma_curve = f->get_gamma_curve();
        std::cout << "Gamma Spot: " << f->get_price(gamma_curve) << std::endl;
        
//        std::cout << "Gamma: " << std::endl;
//        for (std::size_t i=0; i<gamma_curve.size(); i++)
//        {
//            std::cout << gamma_curve[i] << std::endl;
//
//        }
        
        std::vector<double> theta_surface = f->get_theta_curve();
        
//        std::cout << "Theta: " << std::endl;
//        for (std::size_t i=0; i<theta_surface.size(); i++)
//        {
//            std::cout << theta_surface[i] << std::endl;
//
//        }
        
        
        std::cout << "Theta Spot: " << f->get_price(theta_surface) << std::endl;

        std::vector<double> vega_curve = f->get_vega_curve();
//        std::cout << "Vega: " << std::endl;
//        for (std::size_t i=0; i<vega_curve.size(); i++)
//        {
//            std::cout << vega_curve[i] << std::endl;
//
//        }
        
        std::cout << "Vega Spot: " << f->get_price(vega_curve) << std::endl;
        
        
        delete f;
        delete eq;
        delete c;
        delete tb;
        delete sb;
        delete r;
        delete vol;

    }
}



int main(int argc, const char * argv[])
{
    dauphine::test();
    return 0;
}



