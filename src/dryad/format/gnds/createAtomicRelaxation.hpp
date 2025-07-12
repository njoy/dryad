#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEATOMICRELAXATION
#define NJOY_DRYAD_FORMAT_GNDS_CREATEATOMICRELAXATION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/atomic/createElectronSubshellConfiguration.hpp"
#include "dryad/AtomicRelaxation.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create an AtomicRelaxation from a GNDS xml document
   *
   *  @param[in] document    the GNDS xml document
   *  @param[in] normalise   option to indicate whether or not to normalise
   *                         all probability data
   */
  static AtomicRelaxation createAtomicRelaxation( const pugi::xml_document& document,
                                                  bool normalise ) {

    //! @todo verify validity of the file

    pugi::xml_node element = document.child( "PoPs" ).child( "chemicalElements" ).
                                      child( "chemicalElement" );

    if ( element ) {

      id::ElementID id( element.attribute( "Z" ).as_int() );

      std::vector< dryad::atomic::ElectronSubshellConfiguration > subshells;
      pugi::xml_node shells = element.child( "atomic" ).child( "configurations" );
      for ( pugi::xml_node subshell = shells.child( "configuration" );
            subshell; subshell = subshell.next_sibling(  "configuration"  ) ) {

        subshells.push_back( gnds::atomic::createElectronSubshellConfiguration( id, subshell, normalise ) );
      }

      return AtomicRelaxation( std::move( id ), std::move( subshells ) );
    }
    else {

      Log::error( "The GNDS file does not contain atomic relaxation data" );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
