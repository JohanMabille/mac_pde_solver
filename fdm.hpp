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
        // fdm_solver (or even pde_pricer) could be a better name
        // Not sure an abstract class makes sense here, unless
        // you want the pde pricer to inherit from a more abstract
        // pricer class (but in this case, only the price and greeks
        // methods should be virtual, others methods specific to PDEs
        // should be non virtual in the private section of the class).
	class fdm_interface
	{
	public:
		fdm_interface(pde* pde, payoff* pay);
		virtual ~fdm_interface();
                // Entity semantics:
                fdm_interface(const fdm_interface&) = delete;
                fdm_interface& operator=(const fdm_interface&) = delete;
                fdm_interface(fdm_interface&&) = delete;
                fdm_interface& operator=(fdm_interface&&) = delete;

                // These methods should be private
		virtual double a1(pde* pde, double s, double t) const;
		virtual double a2(pde* pde, double s, double t, rate* r) const;
		virtual double a3(pde* pde, double s, double t) const;			
		virtual double b1(pde* pde, double s, double t) const;
		virtual double b2(pde* pde, double s, double t, rate* r) const;
		virtual double b3(pde* pde, double s, double t) const;
		
        // This should be private
        // Also, even if the algorithm is known as the Thomas' algorithm,
        // a name more expressive about that the method is doing would be more
        // helpful for future you reading the code in 6 months. Could be
        // solve_tridiag.
        virtual std::vector<double> thomas(const std::vector<double>& a, const std::vector<double>& b, const std::vector<double>& c,  std::vector<double>& d) const = 0;
        
        virtual std::vector<std::vector<double>> get_price_list(double volatility_eps=0) const = 0;

        virtual double get_price(std::vector<double>& price_list) const = 0;

        
        virtual std::vector<std::vector<double>> get_delta_surface() const  =0;
        virtual std::vector<double> get_delta_curve() const = 0;
        virtual double get_delta() const = 0 ;
        
        virtual std::vector<std::vector<double>> get_gamma_surface() const = 0;
        virtual std::vector<double> get_gamma_curve() const = 0;
        virtual double get_gamma() const = 0 ;
        
        // Should be private
        std::vector<std::vector<double>> transpose(std::vector<std::vector<double>> b) const;

        virtual std::vector<std::vector<double>> get_theta_surface() const = 0;
        virtual std::vector<double> get_theta_curve() const = 0;
        virtual double get_theta() const = 0 ;
        
        virtual std::vector<double> get_vega_curve() const =0;
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

		std::vector<double> thomas(const std::vector<double>& a,
                                   const std::vector<double>& b,
                                   const std::vector<double>& c,
                                   std::vector<double>& d) const override;
		
		std::vector<std::vector<double>> get_price_list(double volatility_eps=0) const override; //optional parameter

		double get_price(std::vector<double>& price_list) const override;
        
        
        std::vector<std::vector<double>> get_delta_surface() const override;
        std::vector<double> get_delta_curve()const override;
        double get_delta()const override;
        
        std::vector<std::vector<double>> get_gamma_surface() const override;
        std::vector<double> get_gamma_curve() const override;
        double get_gamma()const override;

        std::vector<std::vector<double>> get_theta_surface() const override;
        std::vector<double> get_theta_curve() const override;
        double get_theta() const override;
        
        std::vector<double> get_vega_curve() const override;
        double get_vega() const override;
	
    };

}

#endif
