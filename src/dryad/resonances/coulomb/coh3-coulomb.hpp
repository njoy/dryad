#ifndef NJOY_DRYAD_RESONANCES_COH3_COULOMB
#define NJOY_DRYAD_RESONANCES_COH3_COULOMB

//const double HBAR       =  6.582119514e-22; /* Planck's constant/2pi [MeV sec]*/
//const double VLIGHT     =  2.99792458e+23 ; /* light velocty [fm/sec]         */
//const double AMUNIT     =  931.4943335    ; /* MeV = 1amu                     */
//const double COULOMB    =  1.60217733e-19 ; /* J = 1eV                        */
//const double COULOMBSQ  =  2.56697220e-38 ; /* COULOMB*COULOMB                */
//const double PERMITTIV  =  5.60958617e+37 ; /* permittivity [MeV fm /C^2]     */

const double CRIT_WRONSK   =  1.0e-06; /* wronskian satisfaction criterion    */
const double CRIT_LMAX     =  1.0e-10; /* maximum angular momentum criterion  */
const double CRIT_ITER     =  1.0e-16; /* infinit iteration criterion         */
const int MAX_ITER         =  100;     /* maximum iteration number            */
const int MAX_L            =   60;     /* maximum angular momentum + 2        */
const int MAX_L0           =  100;     /* maximum iteration for F function    */

#include "coh3-asympt.hpp"
#include "coh3-extwave.hpp"

void coulombWaveFunctions( int l, double ratio, double eta,
                           std::complex<double>& gf,
                           std::complex<double>& dgf ) {

  double y2 = eta*eta;
  double y3 = 16.0 + y2;
  double y4 = y3*y3;
  double sigma0 = -eta+eta*std::log(y3)/2.+3.5*std::atan(eta/4.)
                  -(std::atan(eta)+std::atan(eta/2.)+std::atan(eta/3.))
                  -eta*(1.+(y2-48.)/(30.*y4)+(y2*y2-160.*y2+1280.)/(105.*y4*y4))
                  /(12.*y3);

  std::complex<double> *Cou0 = new std::complex<double>[MAX_L]; // G + iF
  std::complex<double> *Cou1 = new std::complex<double>[MAX_L]; // G'+ iF'
  omExternalFunction(l ,ratio, eta, sigma0, Cou0, Cou1);

  gf  = Cou0[l];
  dgf = Cou1[l];
  delete [] Cou0;
  delete [] Cou1;
}

#endif
