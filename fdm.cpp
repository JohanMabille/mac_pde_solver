#include "fdm.hpp"

namespace dauphine
{

	fdm_interface::fdm_interface(pde* pde, payoff* pay)
		: m_pde(pde), m_payoff(pay)
	{
	}

	fdm_interface::~fdm_interface()
	{
		delete m_pde; //destruction du pointeur
		delete m_payoff;

	}

	double fdm_interface::a1(pde* pde, double s, double t) const
	{		
        double alpha = (pde->diff_coeff(s, t))/(pow(dx, 2));
		double beta = (pde->conv_coeff(s, t))/(2*dx);
		
		return dt*(1-theta)*(beta-alpha);
	}

	double fdm_interface::a2(pde* pde, double s, double t, rate* r) const
	{
 		double alpha = (pde->diff_coeff(s, t))/(pow(dx,2));
        return (1 - (1 - theta)*dt*(r->get_rate(s,t) - 2*alpha));
	}

	double fdm_interface::a3(pde* pde, double s, double t) const
	{
		double alpha = (pde->diff_coeff(s, t))/(pow(dx, 2));
		double beta=(pde->conv_coeff(s, t))/(2*dx);
		
		return (-dt*(1-theta)*(beta+alpha));
	}

	double fdm_interface::b1(pde* pde, double s, double t) const
	{
		double alpha = (pde->diff_coeff(s, t))/(pow(dx, 2));
		double beta=(pde->conv_coeff(s, t))/(2*dx);
		
		return dt*theta*(alpha - beta);
	}

	double fdm_interface::b2(pde* pde, double s, double t, rate* r) const
	{
        double alpha = (pde->diff_coeff(s, t))/(pow(dx, 2));
			
        return (1 + theta*dt*(r->get_rate(s,t) - 2*alpha));
	}

	double fdm_interface::b3(pde* pde, double s, double t) const
	{
		double alpha = (pde->diff_coeff(s, t))/(pow(dx, 2));
		double beta=(pde->conv_coeff(s, t))/(2*dx);

		return dt*theta*(beta+alpha);
	}

	fdm::fdm(pde* pde, payoff* payoff)
		: fdm_interface(pde, payoff)
    {
    }

	fdm::~fdm()
	{
		m_pde = nullptr;
		m_payoff = nullptr;
	}

	std::vector<double> fdm::get_price_list() const
	{
        pde* pde = fdm::m_pde;
        payoff* payoff = fdm::m_payoff;
        rate* r = pde->get_rate();
        Space_boundaries* sb =pde->get_volatility()->get_sboundaries();
        Time_boundaries* tb=  pde->get_volatility()->get_tboundaries();
        double Smax = exp(sb->s_boundary_right()); // do the same as before, remove boudaries from parameters, they already exist within fdm
        double Smin = exp(sb->s_boundary_left());
        //double Smax = exp(sb->s_boundary_right());
        //double Smin = exp(sb->s_boundary_left());
//        double Tmax = tb->t_boundary_right(maturity);   //unused?
//        double Tmin = tb->t_boundary_left(maturity);
//
		//Calcul avec FDM
		//1. On discretise le temps et l'espace
        std::size_t T = tb->time_mesh();
        std::size_t N = sb->space_mesh();
	double r0 = initial_rate;

		//2. Calcul des f intermédiaires
			
		//Calcul de la matrice F en T
        
	std::vector<double> F(N-1);
	double S = Smin;
	
	for (std::size_t i = 0; i < F.size(); i++)      //why strictly smaller?
        { 
	
            F[i] = payoff->get_payoff(S);
	    S = S * exp(dx);
  	}
        
        	
		//Calcul des coeffs des matrices tridiagonales en T
		double mat = maturity;
		//def matrice des coeffs pour avoir les coeffs en tt pt de l espace
		std::vector<double> A1(N-1, 0.0);
		std::vector<double> A2(N-1, 0.0);
		std::vector<double> A3(N-1, 0.0);
		std::vector<double> B1(N-1, 0.0);
		std::vector<double> B2(N-1, 0.0);
		std::vector<double> B3(N-1, 0.0);

		S = Smax;

		for (std::size_t i=0; i < N-1; i++)
		{
			A1[i] = a1(pde, S, mat);
			A2[i] = a2(pde, S, mat, r);
			A3[i] = a3(pde, S, mat);
			B1[i] = b1(pde, S, mat);
			B2[i] = b2(pde, S, mat, r);
			B3[i] = b3(pde, S, mat);
		
			S = S *exp(-dx);
		}

		//Calcul du terme constant que l'on extrait pour avoir une matrice tridiagonale
		std::vector<double> C(N-1, 0.0);

		C[0] = (A1[0] - B1[0]*exp(-r0*dt))*f0;

		C[N-2] = (A3[N-2] - B3[N-2]*exp(-r0*dt))*fN;

		//Calcul de la matrice D en T
		std::vector<double> D(N-1,0.0);
		D[0] = A2[0]*F[0] + A3[0]*F[1] + C[0];
		D[N-2] = A1[N-2]*F[N-2] + A2[N-2]*F[N-2] + C[N-2];
		
		for (std::size_t i=1; i < N-2; i++)
		{
			D[i] = A1[i]*F[i-1] + A2[i]*F[i] + A3[i]*F[i+1];
		}

		//On remonte via l'algorithme de Thomas
		S = Smax;

		for (int t = T-1; t>=0 ; t--)
		{
			//Pour chaque x(i,t+1), en commencant par f_N, on remonte à x(i,t)
			//via l'algo de Thomas et le système trouvé
			
			//On calcule la matrice tridiagoname en t en tt pt de l'espace
			for (std::size_t i = 0; i < N-1; i++)
			{
				A1[i] = a1(pde, S, t);
				A2[i] = a2(pde, S, t, r);
				A3[i] = a3(pde, S, t);
				B1[i] = b1(pde, S, t);
				B2[i] = b2(pde, S, t, r);
				B3[i] = b3(pde, S, t);
			
				S = S * exp(-dx);
			}


			//On calcule la matrice F en t, et on fait Ft1=Ft
      			F = thomas(B1, B2, B3, D);
            
			//On recalcule la nouvelle matrice D
			D[0] = A2[0]*F[0] + A3[0]*F[1] + C[0];
			D[N-2] = A1[N-2]*F[N-2] + A2[N-2]*F[N-2] + C[N-2];
		
			for (std::size_t i=1; i < N-2; i++)
			{
				D[i] = A1[i]*F[i-1] + A2[i]*F[i] + A3[i]*F[i+1];
			}
		}

		return F;
        
	}

	double fdm::get_price(std::vector<double> price_list) const
	{
		double p = price_list[floor((price_list.size() )/2+1)];
		return p;
	
	}


	std::vector<double> fdm::thomas(const std::vector<double> a,
                                    const std::vector<double> b,
                                    const std::vector<double> c,
                                    std::vector<double> d) const
	{
		//algo de Thomas pour inverser une matrice tridiagonale dans le cas de coeffs "constant" dans l'espace		
        std::size_t n = d.size();
		std::vector<double> new_coeffs(n, 0);
		std::vector<double> new_d(n, 0);  

		//Forward sweep
		new_coeffs[0] =c[0]/b[0];
		new_d[0] = d[0]/b[0];

		for (std::size_t i=1; i<n; i++)
		{
			new_coeffs[i] = c[i] / (b[i]-a[i] * new_coeffs[i-1]);
			new_d[i] = (d[i]-a[i] * new_d[i-1]) / (b[i]-a[i] * new_coeffs[i-1]);
		}
		
		//Back substitution
        std::vector<double> y(n, 0.0);
		y[n-1] = new_d[n-1];

		for (int i = n-2; i>=0; i--)
		{
			y[i] = new_d[i] - new_coeffs[i]*y[i+1];
		}

		return y;
	}



    std::vector<double> fdm::get_delta_curve() const
    {
        //double spot_plus = spot + 0.01; //maybe add spot as a attribute in fdm (if we keep using the same definition)
        //double spot_minus = spot - 1;
        volatility* vol = m_pde->get_volatility();
        rate* rate = m_pde->get_rate();

//        interface* opt_plus = new interface(*opt);
//        opt_plus->set_spot(spot_plus);    //We either define set_spot in interface or in payoff
//
//        interface* opt_minus = new interface(*opt);
//        opt_minus->set_spot(spot_minus);
//
//
//        std::vector<double> p_plus_surface = get_price_list(opt_plus, rate);
//        std::vector<double> p_minus_surface = get_price_list(opt_minus, rate);
        
        std::vector<double> p_surface = get_price_list();

        
//        delete opt_plus;
//        delete opt_minus;
        

        // Defined a transform function to calculate the difference between the prices (vectors) divided by 0.02
        std::vector<double> result(p_surface.size()-1, 0);
        std::transform(p_surface.begin(), p_surface.end()-1, p_surface.begin()+1, result.begin(), [&](double l, double r)
        {
            return (r - l)/exp(dx);
        });

        return result;
    }

    double fdm::get_delta() const
{
    std::vector<double> alpha_curve = get_delta_curve();

    double delta = get_price(alpha_curve);


    return delta;
}


//    std::vector<double> fdm::get_gamma_curve(interface* opt) const
//    {
//        double spot_plus = spot + 0.01; //maybe add spot as a attribute in fdm
//        double spot_minus = spot - 0.01;
//        rate* rate = m_pde->get_rate();
//
//        opt->set_spot(spot);        //we probably do not need this line, just for clarity for the moment
//
//        interface* opt_plus = new interface(*opt);
//        opt_plus->set_spot(spot_plus);
//
//        interface* opt_minus = new interface(*opt);
//        opt_minus->set_spot(spot_minus);
//
//        //pde* pde_plus = new bs_pde(opt_plus);
//        //pde* pde_minus = new bs_pde(opt_minus);
//
//        std::vector<double> p_surface = get_price_list();
//        std::vector<double> p_plus_surface = get_price_list();
//        std::vector<double> p_minus_surface = get_price_list();
//
//        //double p = get_price(t_pde, opt, payoff, sb, tb);
//        //double p_plus = get_price(pde_plus, opt_plus, payoff, sb, tb);        IT IS LOGICAL THAT WE HAVE ONLY ONE PDE?
//        //double p_minus = get_price(pde_minus, opt_minus, payoff, sb, tb);
//
//        //delete opt;????
//        delete opt_plus;
//        delete opt_minus;
//
//
//        std::vector<double> sum_p_plus_minus;
//        std::transform(p_plus_surface.begin(), p_plus_surface.end(), p_minus_surface.begin(), std::back_inserter(sum_p_plus_minus), [&](double l, double r)
//        {
//            return (l + r);
//        });
//
//        std::vector<double> result;
//        std::transform(sum_p_plus_minus.begin(), sum_p_plus_minus.end(), p_surface.begin(), std::back_inserter(result), [&](double l, double r)
//        {
//            return (l - 2*r)/(0.01*0.01);       //To test
//        });
//
//        return result;

        //return (p_plus - 2*p + p_minus)/(0.01*0.01);
//    }




//
//    double fdm::get_theta(pde* t_pde,
//                          interface* opt,
//                          payoff* payoff,
//                          Space_boundaries* sb,
//                          Time_boundaries* tb) const
//    {
//        double t_plus = maturity + 0.003;
//        double t_minus = maturity - 0.003;
//
//        interface* opt_plus = new interface(*opt);
//        opt_plus->set_maturity(t_plus);
//
//        interface* opt_minus = new interface(*opt);
//        opt_minus->set_maturity(t_minus);
//
//        pde* pde_plus = new bs_pde(opt_plus);
//        pde* pde_minus = new bs_pde(opt_minus);
//
//        double p_plus = get_price(pde_plus, opt_plus, payoff, sb, tb);
//        double p_minus = get_price(pde_minus, opt_minus, payoff, sb, tb);
//        std::cout << p_plus << std::endl;
//        std::cout << p_minus << std::endl;
//
//        delete pde_plus;
//        delete pde_minus;
//        delete opt_plus;
//        delete opt_minus;
//
//        return (p_plus - p_minus)/0.006;
//    }
//
//
//    double fdm::get_vega(pde* t_pde,
//                          interface* opt,
//                          payoff* payoff,
//                          Space_boundaries* sb,
//                          Time_boundaries* tb) const
//    {
//        volatility* sig_plus = new vol_cst(opt->get_vol(0., 0.) + 0.01);
//        volatility* sig_minus = new vol_cst(opt->get_vol(0., 0.) - 0.01);
//
//        interface* opt_plus = new interface(*opt);
//        opt_plus->set_vol(sig_plus);
//
//        interface* opt_minus = new interface(*opt);
//        opt_minus->set_vol(sig_minus);
//
//        pde* pde_plus = new bs_pde(opt_plus);
//        pde* pde_minus = new bs_pde(opt_minus);
//
//        double p_plus = get_price(pde_plus, opt_plus, payoff, sb, tb);
//        double p_minus = get_price(pde_minus, opt_minus, payoff, sb, tb);
//        std::cout << p_plus << std::endl;
//        std::cout << p_minus << std::endl;
//
//        delete pde_plus;
//        delete pde_minus;
//        delete opt_plus;
//        delete opt_minus;
//
//        return (p_plus - p_minus)/0.02;
//    }


}
