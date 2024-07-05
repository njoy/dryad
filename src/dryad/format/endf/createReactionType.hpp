#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEREACTIONTYPE
#define NJOY_DRYAD_FORMAT_ENDF_CREATEREACTIONTYPE

// system includes
#include <unordered_set>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/ReactionIdentifiers.hpp"
#include "dryad/ReactionType.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create the reaction type based of the mt number
   */
  ReactionType createReactionType( const ENDFtk::tree::Material& material, int mt ) {

    if ( endf::ReactionIdentifiers::isPrimary( material, mt ) ) {

      return ReactionType::Primary;
    }
    else if ( endf::ReactionIdentifiers::isSummation( material, mt ) ) {

      return ReactionType::Summation;
    }
    else {

      Log::error( "{} is not an MT number that designates a valid reaction", mt );
      throw std::exception();
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
