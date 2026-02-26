#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEENDFFILE2SECTION
#define NJOY_DRYAD_FORMAT_ENDF_CREATEENDFFILE2SECTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
// #include "njoy/dryad/resonances"
// #include "njoy/dryad/resonances/Isotopes.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfParticlePairs.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfSpinGroups.hpp"
#include "ENDFtk/section/2.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create an ENDF MF2 section object from a Reaction object
   *
   *  @param[in] reaction   the reaction data
   */
  inline ENDFtk::section::Type< 2, 151 >
    createEndfFile2Section( int za, double awr, const njoy::dryad::resonances::ResonanceParameters& parameters ) {
    
    std::vector< ENDFtk::section::Type< 2, 151 >::ResonanceRange > ranges;

    for( const auto& rrr : parameters.resolved() ) {
      
      bool IFG = true; // Dryad always stores reduced widths
      
      bool KRL = false; // Default non-relativistic treatment
      if ( rrr.spinGroups()[0].channels()[0].kinematicsType() == njoy::dryad::resonances::Kinematics::Relativistic ) {
        KRL = true;
      }

      int KRM = 3;
      if ( rrr.spinGroups()[0].formalism() ==  njoy::dryad::resonances::Formalism::GeneralRMatrix ) {
        KRM = 4;
      }

      ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs ppairs = resonances::lrf7::createEndfParticlePairs( rrr );

      auto spingroups = resonances::lrf7::createEndfSpinGroups( rrr.spinGroups(), ppairs );

      ENDFtk::section::Type< 2, 151 >::RMatrixLimited rml(  true,
                                                            KRL,
                                                            KRM,
                                                            std::move(ppairs),
                                                            std::move(spingroups) );

      ranges.emplace_back( rrr.lowerEnergyLimit(), rrr.upperEnergyLimit(), 0, rml );
    };
      
      //! @todo 
      // for( const auto& urr : parameters.unresolved() ) {
      // }

    ENDFtk::section::Type< 2, 151 >::Isotope isotope( za, 1.0, true, std::move(ranges) );

    auto isotopes = {isotope};

    return ENDFtk::section::Type< 2, 151 >(za, awr, std::move( isotopes ) );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
