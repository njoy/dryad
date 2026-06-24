#ifndef NJOY_FORMAT_ENDF_READ_ATOMIC_CREATEELECTRONSUBSHELLID
#define NJOY_FORMAT_ENDF_READ_ATOMIC_CREATEELECTRONSUBSHELLID

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ElectronSubshellID.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace atomic {

  /**
   *  @brief Create an ElectronSubshellID
   *
   *  @param[in] subshell   the integer denoting the subshell
   */
  inline dryad::id::ElectronSubshellID createElectronSubshellID( int subshell ) {

    switch ( subshell ) {

      case  1 : return dryad::id::ElectronSubshellID( "K" );
      case  2 : return dryad::id::ElectronSubshellID( "L1" );
      case  3 : return dryad::id::ElectronSubshellID( "L2" );
      case  4 : return dryad::id::ElectronSubshellID( "L3" );
      case  5 : return dryad::id::ElectronSubshellID( "M1" );
      case  6 : return dryad::id::ElectronSubshellID( "M2" );
      case  7 : return dryad::id::ElectronSubshellID( "M3" );
      case  8 : return dryad::id::ElectronSubshellID( "M4" );
      case  9 : return dryad::id::ElectronSubshellID( "M5" );
      case 10 : return dryad::id::ElectronSubshellID( "N1" );
      case 11 : return dryad::id::ElectronSubshellID( "N2" );
      case 12 : return dryad::id::ElectronSubshellID( "N3" );
      case 13 : return dryad::id::ElectronSubshellID( "N4" );
      case 14 : return dryad::id::ElectronSubshellID( "N5" );
      case 15 : return dryad::id::ElectronSubshellID( "N6" );
      case 16 : return dryad::id::ElectronSubshellID( "N7" );
      case 17 : return dryad::id::ElectronSubshellID( "O1" );
      case 18 : return dryad::id::ElectronSubshellID( "O2" );
      case 19 : return dryad::id::ElectronSubshellID( "O3" );
      case 20 : return dryad::id::ElectronSubshellID( "O4" );
      case 21 : return dryad::id::ElectronSubshellID( "O5" );
      case 22 : return dryad::id::ElectronSubshellID( "O6" );
      case 23 : return dryad::id::ElectronSubshellID( "O7" );
      case 24 : return dryad::id::ElectronSubshellID( "O8" );
      case 25 : return dryad::id::ElectronSubshellID( "O9" );
      case 26 : return dryad::id::ElectronSubshellID( "P1" );
      case 27 : return dryad::id::ElectronSubshellID( "P2" );
      case 28 : return dryad::id::ElectronSubshellID( "P3" );
      case 29 : return dryad::id::ElectronSubshellID( "P4" );
      case 30 : return dryad::id::ElectronSubshellID( "P5" );
      case 31 : return dryad::id::ElectronSubshellID( "P6" );
      case 32 : return dryad::id::ElectronSubshellID( "P7" );
      case 33 : return dryad::id::ElectronSubshellID( "P8" );
      case 34 : return dryad::id::ElectronSubshellID( "P9" );
      case 35 : return dryad::id::ElectronSubshellID( "P10" );
      case 36 : return dryad::id::ElectronSubshellID( "P11" );
      case 37 : return dryad::id::ElectronSubshellID( "Q1" );
      case 38 : return dryad::id::ElectronSubshellID( "Q2" );
      case 39 : return dryad::id::ElectronSubshellID( "Q3" );
      default: {

        Log::error( "Electron subshell number {} is not recognised", subshell );
        throw std::exception();
      }
    }
  }

} // atomic namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
