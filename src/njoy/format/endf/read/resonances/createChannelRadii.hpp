#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_CREATECHANNELRADII
#define NJOY_FORMAT_ENDF_READ_RESONANCES_CREATECHANNELRADII

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/resonances/ChannelRadii.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {

  /**
   *  @brief Create the channel radii based on ENDF information
   *
   *  @param[in] naps   the channel radius option as given in the ENDF file
   *  @param[in] nro    the energy dependent scattering radius (if defined, given in fm)
   *  @param[in] ap     the l-dependent scattering radius (if defined, given in fm)
   *  @param[in] awr    the atomic weight ratio as given in the ENDF file
   */
  inline auto createChannelRadii( int naps,
                                  const std::optional< dryad::resonances::TabulatedRadius >& nro,
                                  double ap,
                                  double awri ) {

    // see equation D.14 from the ENDF manual
    // ENDF-6 Formats Manual, CSEWG Document ENDF-102, NNDC, Brookhaven National Laboratory
    // https://www.nndc.bnl.gov/endf

    double a = ( 0.123 * std::pow( awri * constants::neutron_mass, 1. / 3. ) + 0.08 ) * constants::deca;

    if ( nro.has_value() ) {

      switch ( naps ) {

        // use a for P and S, energy dependent scattering radius for phi
        case 0 : return dryad::resonances::ChannelRadii( a, nro.value() );
        // use energy dependent scattering radius for P, S and phi
        case 1 : return dryad::resonances::ChannelRadii( nro.value() );
        // use ap for P and S and energy dependent scattering radius for phi
        case 2 : return dryad::resonances::ChannelRadii( ap, nro.value() );
        default : {

          Log::error( "Encountered unknown value for NAPS = {} with NRO = {}", naps, nro.has_value() );
          throw std::exception();
        }
      }
    }
    else {

      switch ( naps ) {

        // use a for P and S, ap for phi
        case 0 : return dryad::resonances::ChannelRadii( a, ap );
        // use ap for P, S and phi
        case 1 : return dryad::resonances::ChannelRadii( ap );
        default : {

          Log::error( "Encountered unknown value for NAPS = {} with NRO = {}", naps, nro.has_value() );
          throw std::exception();
        }
      }
    }
  }

} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
