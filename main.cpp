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


    void call_price()
    {
        Space_boundaries* sb = new Sboundaries();
        Time_boundaries* tb = new Tboundaries();
        
        // It would have been more consistent to have the strike
        // with other inputs rather than asking the user to
        // enter it (and only this one).œ
        std::cout << "Please enter your strike " << std::endl;
        double user_strike = 0;
        std::cin >> user_strike;
        payoff* c = new call(user_strike);

        
      
        
        volatility* vol = new vol_cst(sb, tb);
        rate* r = new rate_cst(sb, tb);
       
        pde* eq = new bs_pde(vol, r);
        fdm_interface* f = new fdm(eq, c);
        
        
            
        std::cout << "Payoff: " << c->get_payoff(spot) << std::endl;
        

        std::vector<std::vector<double>> price_list = f->get_price_list();
       
//                //Print Price List
//                std::cout << "Price List: " << std::endl;
//                    for (std::size_t i=0; i<price_list[price_list.size()-1].size(); i++)
//                { //we print the price list at the last time step.
//                    std::cout << price_list[price_list.size()-1][i];
//                    std::cout << "\t";
//                }
//                std::cout<<std::endl;



//                //Price Surface
//                std::cout << "Price Surface: " << std::endl;
//                for(int t =  0; t<price_list.size();t++){
//                    std::cout<<t<<"\t";
//                    for (std::size_t i=0; i<price_list[t].size(); i++)
//                    {
//                        std::cout << price_list[t][i] << "\t";
//                    }
//                    std::cout<<std::endl;
//                }
//                std::cout<<std::endl;
        
        std::cout << "Price at the input Spot: " << f->get_price(price_list[price_list.size()-1]) << std::endl;
            
        //std::cout << "BS Price: " << bs_price(spot, user_strike, initial_sigma, maturity, true) << std::endl;
        // The bs_price formula is the non discouted function of the forward.
        double df = std::exp(-initial_rate * maturity);
        std::cout << "BS Price: " << df * bs_price(spot / df, user_strike, initial_sigma, maturity, true) << std::endl;
        
//        //Printing the delta curve
//        std::vector<double> delta_curve = f->get_delta_curve();
//        std::cout << "Delta: " << std::endl;
//        for (std::size_t i=0; i<delta_curve.size(); i++)
//        {
//            std::cout << delta_surface[i] << std::endl;
//
//        }
        
        
        
//        //EXAMPLE of printing out a GREEK SURFACE, in this case Delta.
//        std::vector<std::vector<double>> delta_surface = f->get_delta_surface();
//        std::cout << "Delta Surface: " << std::endl;
//        for(int t =  0; t<delta_surface.size();t++){
//            std::cout<<t<<"\t";
//            for (std::size_t i=0; i<delta_surface[t].size(); i++)
//            {
//                std::cout << delta_surface[t][i] << "\t";
//            }
//            std::cout<<std::endl;
//        }
        
        std::cout << "Delta Spot: " << f->get_delta() << std::endl;
        
    

        //Gamma curve
//        std::vector<double> gamma_curve = f->get_gamma_curve();
//        std::cout << "Gamma: " << std::endl;
//        for (std::size_t i=0; i<gamma_curve.size(); i++)
//        {
//            std::cout << gamma_curve[i] << std::endl;
//
//        }

        std::cout << "Gamma Spot: " << f->get_gamma() << std::endl;
        
        //Theta curve
//        std::vector<double> theta_curve = f->get_theta_curve();
//        std::cout << "Theta: " << std::endl;
//        for (std::size_t i=0; i<theta_surface.size(); i++)
//        {
//            std::cout << theta_curve[i] << std::endl;
//
//        }
        
        
        std::cout << "Theta Spot: " << f->get_theta() << std::endl;

//        std::vector<double> vega_curve = f->get_vega_curve();
        
//        std::cout << "Vega: " << std::endl;
//        for (std::size_t i=0; i<vega_curve.size(); i++)
//        {
//            std::cout << vega_curve[i] << std::endl;
//
//        }
        
        std::cout << "Vega Spot: " << f->get_vega() << std::endl;
        


        
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
    dauphine::call_price();
    return 0;
}



