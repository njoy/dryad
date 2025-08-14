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
   *
   *  @param[in] subshell   the integer denoting the subshell
   */
  id::ElectronSubshellID createElectronSubshellID( int subshell ) {

    switch ( subshell ) {

      case  1 : return id::ElectronSubshellID( "K" );
      case  2 : return id::ElectronSubshellID( "L1" );
      case  3 : return id::ElectronSubshellID( "L2" );
      case  4 : return id::ElectronSubshellID( "L3" );
      case  5 : return id::ElectronSubshellID( "M1" );
      case  6 : return id::ElectronSubshellID( "M2" );
      case  7 : return id::ElectronSubshellID( "M3" );
      case  8 : return id::ElectronSubshellID( "M4" );
      case  9 : return id::ElectronSubshellID( "M5" );
      case 10 : return id::ElectronSubshellID( "N1" );
      case 11 : return id::ElectronSubshellID( "N2" );
      case 12 : return id::ElectronSubshellID( "N3" );
      case 13 : return id::ElectronSubshellID( "N4" );
      case 14 : return id::ElectronSubshellID( "N5" );
      case 15 : return id::ElectronSubshellID( "N6" );
      case 16 : return id::ElectronSubshellID( "N7" );
      case 17 : return id::ElectronSubshellID( "O1" );
      case 18 : return id::ElectronSubshellID( "O2" );
      case 19 : return id::ElectronSubshellID( "O3" );
      case 20 : return id::ElectronSubshellID( "O4" );
      case 21 : return id::ElectronSubshellID( "O5" );
      case 22 : return id::ElectronSubshellID( "O6" );
      case 23 : return id::ElectronSubshellID( "O7" );
      case 24 : return id::ElectronSubshellID( "O8" );
      case 25 : return id::ElectronSubshellID( "O9" );
      case 26 : return id::ElectronSubshellID( "P1" );
      case 27 : return id::ElectronSubshellID( "P2" );
      case 28 : return id::ElectronSubshellID( "P3" );
      case 29 : return id::ElectronSubshellID( "P4" );
      case 30 : return id::ElectronSubshellID( "P5" );
      case 31 : return id::ElectronSubshellID( "P6" );
      case 32 : return id::ElectronSubshellID( "P7" );
      case 33 : return id::ElectronSubshellID( "P8" );
      case 34 : return id::ElectronSubshellID( "P9" );
      case 35 : return id::ElectronSubshellID( "P10" );
      case 36 : return id::ElectronSubshellID( "P11" );
      case 37 : return id::ElectronSubshellID( "Q1" );
      case 38 : return id::ElectronSubshellID( "Q2" );
      case 39 : return id::ElectronSubshellID( "Q3" );
      default: {

        Log::error( "Electron subshell number {} is not recognised", subshell );
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
