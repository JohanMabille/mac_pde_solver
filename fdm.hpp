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
#include "global.hpp"
#include "rate.hpp"


namespace dauphine
{
	class fdm_interface
	{
	public:
		fdm_interface(pde* pde, payoff* pay);
		virtual ~fdm_interface();
		virtual double a1(pde* pde, double s, double t) const;
		virtual double a2(pde* pde, double s, double t, rate* r) const;
		virtual double a3(pde* pde, double s, double t) const;			
		virtual double b1(pde* pde, double s, double t) const;
		virtual double b2(pde* pde, double s, double t, rate* r) const;
		virtual double b3(pde* pde, double s, double t) const;
		
        virtual std::vector<double> thomas(const std::vector<double> a, const std::vector<double> b, const std::vector<double> c,  std::vector<double> d) const = 0;
        
        virtual std::vector<double> get_price_list(double i_spot, double i_maturity) const = 0;

        virtual double get_price(std::vector<double> price_list) const = 0;

        
        virtual std::vector<double> get_delta_curve(double i_spot, double i_maturity) const = 0;
        virtual double get_delta() const = 0 ;

        virtual std::vector<double> get_gamma_curve(double i_spot, double i_maturity) const = 0;
        virtual double get_gamma() const = 0 ;

        virtual std::vector<double> get_theta_curve(double i_spot, double i_maturity) const = 0;
        virtual double get_theta() const = 0;

        virtual std::vector<double> get_vega_curve() const = 0;
        virtual double get_vega() const = 0;

	
    	protected:
        	pde* m_pde;
        	payoff* m_payoff;
  	};
	
	class fdm : public fdm_interface
	{
	public:
		fdm(pde* pde, payoff* payoff);
		~fdm();

		std::vector<double> thomas(const std::vector<double> a,
                                   const std::vector<double> b,
                                   const std::vector<double> c,
                                   std::vector<double> d) const override;
		
		std::vector<double> get_price_list(double i_spot, double i_maturity) const override;

		double get_price(std::vector<double> price_list) const override;
        
        
        std::vector<double> get_delta_curve(double i_spot, double i_maturity) const override;
        double get_delta() const override;
        
        std::vector<double> get_gamma_curve(double i_spot, double i_maturity) const override;
        double get_gamma() const override;
        
        std::vector<double> get_theta_curve(double i_spot, double i_maturity) const override;
        double get_theta() const override;

        std::vector<double> get_vega_curve() const override;
        double get_vega() const override;

	
    };

}

#endif
