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

    std::vector<std::vector<double>> fdm::get_price_list(double volatility_eps) const
	{
        pde* pde = fdm::m_pde;
        payoff* payoff = fdm::m_payoff;
        rate* r = pde->get_rate();
        pde->get_volatility()->vol_build(volatility_eps); // recalculating the volatility matrix due to the fact that we might have a change in volatility_eps
        Space_boundaries* sb =pde->get_volatility()->get_sboundaries();
        Time_boundaries* tb=  pde->get_volatility()->get_tboundaries();
        double Smax = exp(sb->s_boundary_right());
        double Smin = exp(sb->s_boundary_left());
        
        
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
            //maybe store the spots?
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
		
			S = S *exp(-dx);        //check again
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
		//S = Smax;
        std::vector<std::vector<double>> return_F;
		for (int t = T-1; t>=0 ; t--)
		{   S = Smax;
			//Pour chaque x(i,t+1), en commencant par f_N, on remonte à x(i,t)
			//via l'algo de Thomas et le système trouvé
			
			//On calcule la matrice tridiagonale en t en tt pt de l'espace
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
            return_F.push_back(F);
			//On recalcule la nouvelle matrice D
			D[0] = A2[0]*F[0] + A3[0]*F[1] + C[0];
			D[N-2] = A1[N-2]*F[N-2] + A2[N-2]*F[N-2] + C[N-2];
		
			for (std::size_t i=1; i < N-2; i++)
			{
				D[i] = A1[i]*F[i-1] + A2[i]*F[i] + A3[i]*F[i+1];
			}
            //add F's
		}

		return return_F;
        
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


    std::vector<std::vector<double>> fdm::get_delta_surface() const
    {
        
        
        std::vector<std::vector<double>> p_surface = get_price_list();

        // Defined a transform function to calculate the difference between the prices (vectors) divided by dx
        std::vector<std::vector<double>> delta_surface;
        for(int i=0; i < p_surface.size(); i++){ // iterating over the time axis of the price surface
            std::vector<double> p_curve = p_surface[i];
            std::vector<double> d_curve(p_curve.size()-1, 0);
            std::transform(p_curve.begin(), p_curve.end()-1, p_curve.begin()+1, d_curve.begin(), [&](double l, double r)
            {
                return (r - l)/exp(dx);
            });
            delta_surface.push_back(d_curve);
        }
        return delta_surface;
    }
    std::vector<double> fdm::get_delta_curve() const
    {
        return fdm::get_delta_surface().back(); //get the last one with back()
    }

    double fdm::get_delta() const
{
    std::vector<double> delta_curve = get_delta_curve();

    double delta = get_price(delta_curve);


    return delta;
}

std::vector<std::vector<double>> fdm::get_gamma_surface() const{
    std::vector<std::vector<double>> delta_surface = get_delta_surface();
    std::vector<std::vector<double>> gamma_surface;
    for(int t=0; t<delta_surface.size(); t++){
        std::vector<double> delta_curve = delta_surface[t];
        std::vector<double> gamma_curve(delta_curve.size()-1, 0);
        std::transform(delta_curve.begin(), delta_curve.end()-1, delta_curve.begin()+1, gamma_curve.begin(), [&](double l, double r)
        {
            return (r - l)/exp(dx);
        });
        gamma_surface.push_back(gamma_curve);
    }
    return gamma_surface;
}
    std::vector<double> fdm::get_gamma_curve() const
    {
        return fdm::get_gamma_surface().back();
    }


       double fdm::get_gamma() const
    {
        std::vector<double> gamma_curve = get_gamma_curve();

        double gamma = get_price(gamma_curve);


        return gamma;
    }

std::vector<std::vector<double> > fdm_interface::transpose(std::vector<std::vector<double>> b) const
{
    if (b.size() == 0)
        return std::vector<std::vector<double> >();

    std::vector<std::vector<double> > trans_vec(b[0].size(), std::vector<double>());

    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < b[i].size(); j++)
        {
            trans_vec[j].push_back(b[i][j]);
        }
    }

    return trans_vec;    // <--- reassign here
}

std::vector<std::vector<double>> fdm::get_theta_surface() const
{
    
    std::vector<std::vector<double>> p_surface = get_price_list();
    p_surface = fdm_interface::transpose(p_surface);
    // Defined a transform function to calculate the difference between the prices (vectors) divided by dx
    std::vector<std::vector<double>> theta_surface;
    for(int i=0; i < p_surface.size(); i++){ // iterating over the space axis of the price surface
        std::vector<double> p_curve = p_surface[i];
        std::vector<double> t_curve(p_curve.size()-1, 0);
        std::transform(p_curve.begin(), p_curve.end()-1, p_curve.begin()+1, t_curve.begin(), [&](double l, double r)
        {
            return (r - l)/exp(dx);
        });
        theta_surface.push_back(t_curve);
    }
    return theta_surface;
}
std::vector<double> fdm::get_theta_curve() const // we always last time step
{
    return fdm::get_theta_surface().back(); //get the last one with back()
}

double fdm::get_theta() const
{
    std::vector<double> theta_curve = get_theta_curve();
    double theta = get_price(theta_curve);
    return theta;
}

std::vector<double> fdm::get_vega_curve() const
{
    std::vector<double> prices;
    std::vector<double> vol;
    for (int eps = -10; eps<10; eps++){
        std::vector<std::vector<double>> p_surface = get_price_list(eps);
        int t = p_surface.size()-1;
        int s = floor((p_surface[t].size() )/2+1);
        prices.push_back(p_surface[t][s]);
        vol.push_back(fdm::m_pde->get_volatility()->get_sigma_by_index(s, t));
    }
    std::vector<double> vega_curve;
    for(int i =  0; i<prices.size()-1;i++){
        vega_curve.push_back((prices[i+1]-prices[i])/(vol[i+1]-vol[i]));
    }
    
    return vega_curve;
}

    double fdm::get_vega() const
      {
          std::vector<double> vega_curve = get_vega_curve();
          double vega = get_price(vega_curve);
          return vega;
      }

}
