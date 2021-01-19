#include "interface.hpp"
#include "closed_form.hpp"
#include "payoff.hpp"
#include "pde.hpp"
#include "pde_boundary_conditions.hpp"
#include "fdm.hpp"
#include "rate.hpp"
#include "volatility.hpp"
// #include "volatility.hpp"


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
        double strike = 100;
        double spot = 100;
        double maturity = 10; // in years
        double f0 = 1.;
        double fN = 200.;
        int dt = 1;
        int dx = 1;
        double theta = 0.5;

        rate* rate = new rate_cst(0.01);
        volatility* vol = new vol_cst(0.2);
                
        payoff* c = new call(strike);
        interface* option = new interface(spot, rate, maturity, vol, c);
        pde* eq = new bs_pde(option);
        Space_boundaries* sb = new Sboundaries();
        Time_boundaries* tb = new Tboundaries();
        fdm_interface* f = new fdm(eq, c, rate, f0, fN, dt, dx, theta);

        std::cout << "Rate: " << rate->get_rate(0,0)<< std::endl;
        std::cout << "Payoff: " << c->get_payoff(spot)<< std::endl;
//        std::cout << "FDM Price: " << f->get_price(eq, option, c, sb, tb) << std::endl;
        
        std::vector<double> p = f->get_price(eq, option, c, sb, tb);
        
        for (int i = 0; i<p.size(); ++i)
        {
            std::cout << p[i] << std::endl;
        }
        std::cout << "BS Price: " << bs_price(spot, strike, vol->get_sigma(0., 0.), maturity, true) << std::endl;
        
        //ajouter destrcuteur

    }
}



int main(int argc, const char * argv[])
{
    dauphine::test();
    return 0;
}



