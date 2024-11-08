#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATETABULATEDCROSSSECTION
#define NJOY_DRYAD_FORMAT_GNDS_CREATETABULATEDCROSSSECTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/gnds/createInterpolationType.hpp"
#include "dryad/format/gnds/readXYs1d.hpp"
#include "dryad/format/gnds/convertEnergies.hpp"
#include "dryad/format/gnds/convertCrossSections.hpp"
#include "dryad/TabulatedCrossSection.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a TabulatedCrossSection from a parsed ENDF section
   */
  TabulatedCrossSection createTabulatedCrossSection( const pugi::xml_node& xs ) {

    Log::info( "Reading cross section data" );

    std::vector< double > energies;
    std::vector< double > values;
    std::vector< std::size_t > boundaries;
    std::vector< InterpolationType > interpolants;

    auto xys1d = xs.child( "XYs1d" );
    if ( xys1d ) {

      // read the cross section data
      auto data = readXYs1D( xys1d );

      // get the interpolation type
      auto interpolant = createInterpolationType( std::get< 6 >( data ) );

      // convert units - if necessary
      convertEnergies( std::get< 2 >( data ), std::get< 3 >( data ) );
      convertCrossSections( std::get< 4 >( data ), std::get< 5 >( data ) );

      // assign data
      energies = std::move( std::get< 2 >( data ) );
      values = std::move( std::get< 4 >( data ) );
      boundaries.emplace_back( energies.size() - 1 );
      interpolants.emplace_back( interpolant );
    }
    else {

      auto regions1d = xs.child( "regions1d" );
      if ( regions1d ) {

        auto units = readAxes( regions1d.child( "axes" ) );

        pugi::xml_node function1ds = regions1d.child( "function1ds" );
        for ( pugi::xml_node xys1d = function1ds.child( "XYs1d" ); 
              xys1d; xys1d = xys1d.next_sibling(  "XYs1d"  ) ) {

          // read the current interpolation region
          auto data = readXYs1D( xys1d );

          // get the interpolation type
          auto interpolant = createInterpolationType( std::get< 6 >( data ) );

          // convert units - if necessary
          convertEnergies( std::get< 2 >( data ), std::get< 3 >( data ) == "" ? units[0] : std::get< 3 >( data ) );
          convertCrossSections( std::get< 4 >( data ), std::get< 5 >( data ) == "" ? units[1] : std::get< 5 >( data ) );

          // check for duplicate points at interpolation region boundaries
          std::size_t offset = 0;
          if ( energies.size() > 0 ) {

            if ( energies.back() == std::get< 2 >( data ).front() &&
                 values.back() == std::get< 4 >( data ).front() ) {

              offset = 1;
            }
          }

          // grow the data accordingly
          energies.insert( energies.end(), std::get< 2 >( data ).begin() + offset, std::get< 2 >( data ).end() );
          values.insert( values.end(), std::get< 4 >( data ).begin() + offset, std::get< 4 >( data ).end() );
          boundaries.emplace_back( energies.size() - 1 );
          interpolants.emplace_back( interpolant );
        }
      }
      else {

        Log::error( "Expected either an XYs1d or regions1d for cross section data" );
        throw std::exception();
      }
    }

    return TabulatedCrossSection(
             std::move( energies ), std::move( values ),
             std::move( boundaries ), std::move( interpolants ) );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
