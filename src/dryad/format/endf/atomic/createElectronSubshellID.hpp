#ifndef NJOY_DRYAD_FORMAT_ENDF_ATOMIC_CREATEELECTRONSUBSHELLID
#define NJOY_DRYAD_FORMAT_ENDF_ATOMIC_CREATEELECTRONSUBSHELLID

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ElectronSubshellID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace atomic {

  /**
   *  @brief Create an ElectronSubshellID
   */
  id::ElectronSubshellID createElectronSubshellID( double subshell ) {

    int number = static_cast< int >( std::round( subshell ) );
    switch ( number ) {

      case  1 : return "K";
      case  2 : return "L1";
      case  3 : return "L2";
      case  4 : return "L3";
      case  5 : return "M1";
      case  6 : return "M2";
      case  7 : return "M3";
      case  8 : return "M4";
      case  9 : return "M5";
      case 10 : return "N1";
      case 11 : return "N2";
      case 12 : return "N3";
      case 13 : return "N4";
      case 14 : return "N5";
      case 15 : return "N6";
      case 16 : return "N7";
      case 17 : return "O1";
      case 18 : return "O2";
      case 19 : return "O3";
      case 20 : return "O4";
      case 21 : return "O5";
      case 22 : return "O6";
      case 23 : return "O7";
      case 24 : return "O8";
      case 25 : return "O9";
      case 26 : return "P1";
      case 27 : return "P2";
      case 28 : return "P3";
      case 29 : return "P4";
      case 30 : return "P5";
      case 31 : return "P6";
      case 32 : return "P7";
      case 33 : return "P8";
      case 34 : return "P9";
      case 35 : return "P10";
      case 36 : return "P11";
      case 37 : return "Q1";
      case 38 : return "Q2";
      case 39 : return "Q3";
      default: {

        Log::error( "Electron subshell number {} is not recognised", number );
        throw std::exception();
      }
    }
  }

} // atomic namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
