#ifndef rate_hpp
#define rate_hpp

#include <stdio.h>

namespace dauphine
{

    class rate
    {
    public:
	explicit rate();
        virtual ~rate();
       	virtual double get_rate(double s, double t) = 0; // returns the rate at space point s and time t
        
    };


    class rate_cst: public rate
    {
    private:
      	double rate = 0;

        
    public:
        rate_cst(double initial_rate);
	~rate_cst();
       	double get_rate(double s, double t);
    };
}


#endif
