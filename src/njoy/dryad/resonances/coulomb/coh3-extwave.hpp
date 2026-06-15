#ifndef NJOY_DRYAD_RESONANCES_COULOMB_COH3_EXTWAVE
#define NJOY_DRYAD_RESONANCES_COULOMB_COH3_EXTWAVE

#include "tools/Log.hpp"

/******************************************************************************/
/*  extwave.cpp                                                               */
/*        wave functions in free space                                        */
/******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <complex>

/**********************************************************/
/*      Coulomb Function -- G at Matching Radius          */
/**********************************************************/
inline double omGfunction(int l, double eta, double rho, double g1, double g2)
{
  double j  = (double)l;
  double j1 = (double)(l+1);
  return( ((j+j1)*(eta+j*j1/rho)*g2-j1*std::sqrt(j*j+eta*eta)*g1)
          /(j*std::sqrt(j1*j1+eta*eta)) );
}

/**********************************************************/
/*      Coulomb Function -- F at Matching Radius          */
/**********************************************************/
inline double omFfunction(int l, double eta, double rho, double g1, double g2)
{
  double j  = (double)l;
  double j1 = (double)(l+1);
  return( ((j+j1)*(eta+j*j1/rho)*g2-j*std::sqrt(j1*j1+eta*eta)*g1)
          /(j1*std::sqrt(j*j+eta*eta)) );
}

/**********************************************************/
/*      Derivarive of Coulomb Function at Matching Radius */
/**********************************************************/
inline double omDfunction(int l, double eta, double rho, double g1, double g2)
{
  double j1 = (double)(l+1);
  return( ((eta+j1*j1/rho)*g1-std::sqrt(j1*j1+eta*eta)*g2)/j1 );
}

/**********************************************************/
/*      I.A.Stegun and M.Abramowitz                       */
/*      Phys. Rev. 98, 1851(1955)                         */
/**********************************************************/
inline int omExternalFunction(int lmax, double rho_match, double coulomb, double coulomb_scat0, std::complex<double>* wfn, std::complex<double>* dfn)
{
  double g0,g1,p1,p2,p3;
  int    l;

  if(coulomb == 0.0){
    g0 = p1 = cos(rho_match);
    g1 = p2 = g0/rho_match+sin(rho_match);
    wfn[0] = std::complex<double>(g0,0.0);
    wfn[1] = std::complex<double>(g1,0.0);
  }
  else{
    omAsymptotic(rho_match, coulomb, coulomb_scat0, &p1, &p2);
    if((p1 == 0.0) && (p2 == 0.0)){
      wfn[0] = std::complex<double>(0.0,0.0);
      return(-1);
    }
    g0 = p1;
    g1 = p2 = ((coulomb+1.0/rho_match)*p1-p2)/(std::sqrt(1.0+coulomb*coulomb));
    wfn[0] = std::complex<double>(g0,0.0);
     wfn[1] = std::complex<double>(g1,0.0);
  }

  double a = (coulomb==0.0) ? 1.0 : fmax(g0*g0,g1*g1);

  for(l=1 ; l<MAX_L-1 ; l++){
    p3 = omGfunction(l,coulomb,rho_match,p1,p2);
    wfn[l+1] = std::complex<double>(p3, 0.0);
    if( (a/(p3*p3)) < CRIT_LMAX && (l >= lmax) ) break;
    p1 = p2;  p2 = p3;
  }

  lmax = (l==MAX_L-1) ? l-1 : l;

  int  l0   = lmax+10;
  bool flag = false;
  do{
    flag = false;
    p1 = 0.0; p2 = 1.0e-36;
    for(l=l0 ; l>0 ; l--){
      p3 = omFfunction(l,coulomb,rho_match,p1,p2);
      if(l <= lmax+2) wfn[l-1].imag(p3);
      p1 = p2;  p2 = p3;
    }

    double f0 = wfn[0].imag();
    double f1 = wfn[1].imag();
    a =1.0/((f0*g1-g0*f1)*std::sqrt(1.0+coulomb*coulomb));

    for(l=0 ; l<=lmax+1 ; l++) wfn[l].imag(wfn[l].imag()*a);
    for(l=0 ; l<=lmax   ; l++){
      double wr = omDfunction(l,coulomb,rho_match,wfn[l  ].real(),
                                                  wfn[l+1].real() );
      double wi = omDfunction(l,coulomb,rho_match,wfn[l  ].imag(),
                                                  wfn[l+1].imag() );
      dfn[l] = std::complex<double>(wr,wi);
      a = dfn[l].imag() * wfn[l].real()
         -dfn[l].real() * wfn[l].imag();

      if( std::fabs(a-1.0) > CRIT_WRONSK ){
        flag = true;
        l0 += 10;
        break;
      }
    }
    if(l0 > MAX_L0){
      njoy::Log::error( "angular momentum too large {}", l0 );
      throw std::exception();
    }
  }while(flag);

  return(lmax);
}

/**********************************************************/
/*      Coulomb Function for Negative Energy              */
/**********************************************************/
inline int omExternalClosed(int lmax, double rho_match, double coulomb, std::complex<double> *wfn, std::complex<double>*dfn)
{
  double p1, p2, p3;

  if(coulomb == 0.0){

    /*** recurrence form, f[n+1] = [2n+1]/x f[n] + f[n-1] */
    p1 = 1.0/rho_match;
    p2 = p1+1.0/(rho_match*rho_match);
    wfn[0] = std::complex<double>(p1,0.0);
    wfn[1] = std::complex<double>(p2,0.0);

    for(int l=1 ; l<lmax ; l++){
      p3 = (2.0*l+1.0)/rho_match*p2 + p1;
      wfn[l+1] = std::complex<double>(p3,0.0);
      p1 = p2;  p2 = p3;
    }

    /*** convert into k[n], by multiplying exp(-x) */
    double e = exp(-rho_match);
    for(int l=0 ; l<=lmax ; l++){
      wfn[l] *= e;
      wfn[l].imag(0.0);
    }

    /*** derivative, (xk[n])' = -n k[n] -x k[n-1] */
    dfn[0].real(-exp(-rho_match));
    dfn[0].imag(0.0);

    for(int l=1 ; l<=lmax ; l++){
      double wr = -l*wfn[l].real() - rho_match*wfn[l-1].real();
      dfn[l] = std::complex<double>(wr,0.0);
    }
    /*** covert k[n] into x k[n] */
    for(int l=0 ; l<=lmax ; l++){
      double wr = rho_match*wfn[l].real();
      wfn[l].real(wr);
    }
  }
  else{
    /*** closed Coulomb function, F' at rho */
    double f1 = omAsymptoticClosed(rho_match, coulomb);

    int lp = lmax + 24 + (int)(5.0*coulomb);
    double x = 1.0;
    for(int l=lp ; l>=0 ; l--){
      double a = coulomb/(l+1.0);
      double b = a + (l+1.0)/rho_match;
      x  = -(a*a - 1.0)/(b + x) + b;
      if(l <= lmax) dfn[l] = std::complex<double>(x, 0.0);
    }

    for(int l=0 ; l<=lmax ; l++){
      double g1 = dfn[l].real();
      double d  = 1.0/std::sqrt(std::abs(g1 - f1));
      wfn[l] = std::complex<double>(d,d);
      dfn[l] = std::complex<double>(g1*d,f1*d);

      double a = coulomb/(l+1.0);
      double b = a + (l+1.0)/rho_match;
      f1 = (a*a - 1.0)/(b - f1) - b;
    }
  }

  return(lmax);
}



/**********************************************************/
/*     Coulomb Parameters                                 */
/**********************************************************/
//void omCoulombParameter(int zz, double mu, double e, double *eta, double *sig0)
//{
//  double y1,y2,y3,y4;
//
//  *eta = y1 = PERMITTIV*COULOMBSQ * zz * std::sqrt(AMUNIT*mu/(2.0*e))/VLIGHT/HBAR;
//  y2 = y1*y1;
//  y3 = 16.0 + y2;
//  y4 = y3*y3;
//  *sig0 = -y1+y1*log(y3)/2.+3.5*atan(y1/4.)-(atan(y1)+atan(y1/2.)+atan(y1/3.))
//          -y1*(1.+(y2-48.)/(30.*y4)+(y2*y2-160.*y2+1280.)/(105.*y4*y4))
//          /(12.*y3);
//}

#endif
