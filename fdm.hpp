#ifndef FDM_INTERFACE_HPP
#define FDM_INTERFACE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>  
#include <functional>
#include "pde.hpp"
#include "payoff.hpp"
#include "pde_boundary_conditions.hpp"
#include "interface.hpp"
#include "global.hpp"


namespace dauphine
{
	class fdm_interface
	{
	public:
		fdm_interface(pde* pde, payoff* pay, rate* r);
		virtual ~fdm_interface();
		virtual double a1(pde* pde, double s, double t) const;
		virtual double a2(pde* pde, double s, double t) const;
		virtual double a3(pde* pde, double s, double t) const;			
		virtual double b1(pde* pde, double s, double t) const;
		virtual double b2(pde* pde, double s, double t) const;
		virtual double b3(pde* pde, double s, double t) const;
		
        virtual std::vector<double> thomas(const std::vector<double> a, const std::vector<double> b, const std::vector<double> c,  std::vector<double> d) const = 0;
        
		virtual double get_price(pde* pde, interface* opt, payoff* payoff, Space_boundaries* sb, Time_boundaries* tb) const = 0;
        
//        virtual double get_delta(pde* pde,
//                                 interface* opt,
//                                 payoff* payoff,
//                                 Space_boundaries* sb,
//                                 Time_boundaries* tb) const = 0;
//
//        virtual double get_gamma(pde* pde,
//                              interface* opt,
//                              payoff* payoff,
//                              Space_boundaries* sb,
//                              Time_boundaries* tb) const = 0;
//
//        virtual double get_theta(pde* t_pde,
//                         interface* opt,
//                         payoff* payoff,
//                         Space_boundaries* sb,
//                         Time_boundaries* tb) const = 0;
//
//        virtual double get_vega(pde* t_pde,
//                         interface* opt,
//                         payoff* payoff,
//                         Space_boundaries* sb,
//                         Time_boundaries* tb) const = 0;

	
    	protected:
        	pde* m_pde;
        	payoff* m_payoff;
        	rate* m_r;
	};
	
	class fdm : public fdm_interface
	{
	public:
		fdm(pde* pde, payoff* payoff, rate * r);
		~fdm();

		std::vector<double> thomas(const std::vector<double> a,
                                   const std::vector<double> b,
                                   const std::vector<double> c,
                                   std::vector<double> d) const override;
		
        double get_price(pde* t_pde,
                         interface* opt,
                         payoff* payoff,
                         Space_boundaries* sb,
                         Time_boundaries* tb) const override;
        
//        double get_delta(pde* t_pde,
//                         interface* opt,
//                         payoff* payoff,
//                         Space_boundaries* sb,
//                         Time_boundaries* tb)const override;
//        
//        double get_gamma(pde* t_pde,
//                         interface* opt,
//                         payoff* payoff,
//                         Space_boundaries* sb,
//                         Time_boundaries* tb) const override;
//
//        double get_theta(pde* t_pde,
//                         interface* opt,
//                         payoff* payoff,
//                         Space_boundaries* sb,
//                         Time_boundaries* tb) const override;
//
//	double get_vega(pde* t_pde,
//                         interface* opt,
//                         payoff* payoff,
//                         Space_boundaries* sb,
//                         Time_boundaries* tb) const override;

	
    };

}

#endif
