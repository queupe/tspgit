
#include <random>
#include <chrono>

#ifndef _UTIL_H
#define	_UTIL_H

class TUtils
{
   public:

      /************************************************************************************
      No lugar de utilizar uma função de n multiplcações em um algorítmo genético,
      será utilizado a aproximação de Stirling para agilizar o algoritmo, pois
      neste caso a aproximação será satisfatóra e utilizando pouco esforço computacional.
      ************************************************************************************/
      static double fatorialStirling (int n);

      static void initRnd ();
		static void set_calibraRndD(unsigned max);
      static int rnd(unsigned low, unsigned high);
		static double rndd(double low, double high);
		static double rndd(double low, double high, unsigned calibracao);
        static bool flip(float prob);
    
    template <class T1, class T2, class Pred = std::less<T2> >
    struct compare_pair_second {
        bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
            Pred p;
            return p(left.second, right.second);
        }
    };
};
#endif	/* _UTIL_H */
