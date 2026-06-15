#ifndef NJOY_FORMAT_GNDS_READ_CREATEATOMICRELAXATION
#define NJOY_FORMAT_GNDS_READ_CREATEATOMICRELAXATION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "njoy/format/gnds/read/atomic/createElectronSubshellConfiguration.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create an AtomicRelaxation from a GNDS xml document
   *
   *  @param[in] document    the GNDS xml document
   *  @param[in] normalise   option to indicate whether or not to normalise
   *                         all probability data
   */
  inline dryad::AtomicRelaxation
  createAtomicRelaxation( const pugi::xml_document& document, bool normalise ) {

    //! @todo verify validity of the file

    pugi::xml_node element = document.child( "PoPs" ).child( "chemicalElements" ).
                                      child( "chemicalElement" );

    if ( element ) {

      dryad::id::ElementID id( element.attribute( "Z" ).as_int() );

      std::vector< dryad::atomic::ElectronSubshellConfiguration > subshells;
      pugi::xml_node shells = element.child( "atomic" ).child( "configurations" );
      for ( pugi::xml_node subshell = shells.child( "configuration" );
            subshell; subshell = subshell.next_sibling(  "configuration"  ) ) {

        subshells.emplace_back( atomic::createElectronSubshellConfiguration( id, subshell, normalise ) );
      }

      return dryad::AtomicRelaxation( std::move( id ), std::move( subshells ) );
    }
    else {

      Log::error( "The GNDS file does not contain atomic relaxation data" );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
