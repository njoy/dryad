#ifndef NJOY_FORMAT_ACE_READ_CREATETABULATEDSCATTERINGFUNCTION
#define NJOY_FORMAT_ACE_READ_CREATETABULATEDSCATTERINGFUNCTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedScatteringFunction.hpp"
#include "njoy/format/createVector.hpp"
#include "ACEtk/photoatomic/CoherentFormFactorBlock.hpp"
#include "ACEtk/photoatomic/IncoherentScatteringFunctionBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {

  /**
   *  @brief Create a TabulatedScatteringFunction from a CoherentFormFactorBlock
   *
   *  @param[in] coherent   the coherent form factor block from a photoatomic ace file
   */
  inline dryad::TabulatedScatteringFunction
  createTabulatedScatteringFunction( const njoy::ACEtk::photoatomic::CoherentFormFactorBlock& coherent ) {

    try {

      Log::info( "Reading scattering function data" );
      auto x = createVector( coherent.momentum() );
      auto values = createVector( coherent.formFactors() );
      std::vector< std::size_t > boundaries = { x.size() - 1 };
      std::vector< dryad::InterpolationType > interpolants = { dryad::InterpolationType::LinearLinear };
      return dryad::TabulatedScatteringFunction(
               std::move( x ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated scattering function" );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedScatteringFunction from a CoherentFormFactorBlock
   *
   *  @param[in] incoherent   the incoherent form factor block from a photoatomic ace file
   */
  inline dryad::TabulatedScatteringFunction
  createTabulatedScatteringFunction( const njoy::ACEtk::photoatomic::IncoherentScatteringFunctionBlock& incoherent ) {

    try {

      Log::info( "Reading scattering function data" );
      auto x = createVector( incoherent.momentum() );
      auto values = createVector( incoherent.values() );
      std::vector< std::size_t > boundaries = { x.size() - 1 };
      std::vector< dryad::InterpolationType > interpolants = { dryad::InterpolationType::LinearLinear };
      return dryad::TabulatedScatteringFunction(
               std::move( x ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated scattering function" );
      throw;
    }
  }

} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
