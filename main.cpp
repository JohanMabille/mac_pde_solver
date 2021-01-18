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

    void test(){
        rate_cst* rate = new rate_cst(0.05);
        vol_cst* vol = new vol_cst(0.2);
        std::cout<<"Rate " << rate->get_rate(0,0)<<std::endl;
        double strike = 100;
        double spot = 150;
        double maturity = 0.25; // in years
        
        call* c = new call(strike);
        std::cout<<"Payoff " << c->get_payoff(spot)<<std::endl;
        interface* market = new interface(spot, rate, maturity, vol, c);
        std::cout<<"Price " << c->get_payoff(spot)<<std::endl;
        
    }
}



int main(int argc, const char * argv[])
{
    dauphine::test();
    return 0;
}



