// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

// declarations - identifiers
void wrapID( python::module&, python::module& );

// declarations - enumerators
void wrapDistributionDataType( python::module&, python::module& );
void wrapInteractionType( python::module&, python::module& );
void wrapReactionType( python::module&, python::module& );
void wrapReferenceFrame( python::module&, python::module& );

// declarations - components
void wrapIsotropicAngularDistributions( python::module&, python::module& );
void wrapLegendreAngularDistribution( python::module&, python::module& );
void wrapLegendreAngularDistributions( python::module&, python::module& );
void wrapTabulatedAngularDistribution( python::module&, python::module& );
void wrapTabulatedAngularDistributions( python::module&, python::module& );
void wrapTabulatedEnergyDistribution( python::module&, python::module& );
void wrapTabulatedEnergyDistributions( python::module&, python::module& );
void wrapTabulatedCrossSection( python::module&, python::module& );
void wrapTabulatedMultiplicity( python::module&, python::module& );
void wrapTabulatedAverageEnergy( python::module&, python::module& );
void wrapTabulatedFormFactor( python::module&, python::module& );
void wrapTabulatedScatteringFunction( python::module&, python::module& );
void wrapTwoBodyDistributionData( python::module&, python::module& );
void wrapUncorrelatedDistributionData( python::module&, python::module& );
void wrapReactionProduct( python::module&, python::module& );
void wrapReaction( python::module&, python::module& );
void wrapProjectileTarget( python::module&, python::module& );

/**
 *  @brief dryad python bindings
 *
 *  The name given here (dryad) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( dryad, module ) {

  auto scion_interpolation = python::module::import( "scion.interpolation" );
  auto scion_linearisation = python::module::import( "scion.linearisation" );

  module.attr( "InterpolationType" ) = scion_interpolation.attr( "InterpolationType" );
  module.attr( "ToleranceConvergence" ) = scion_linearisation.attr( "ToleranceConvergence" );

  // create the views submodule
  python::module viewmodule = module.def_submodule(

    "sequence",
    "sequence - dryad sequences (internal use only)"
  );

  // wrap components - identifiers
  wrapID( module, viewmodule );

  // wrap components - enumerators
  wrapDistributionDataType( module, viewmodule );
  wrapInteractionType( module, viewmodule );
  wrapReactionType( module, viewmodule );
  wrapReferenceFrame( module, viewmodule );

  // wrap components - reaction products
  wrapTabulatedMultiplicity( module, viewmodule );
  wrapTabulatedAverageEnergy( module, viewmodule );
  wrapIsotropicAngularDistributions( module, viewmodule );
  wrapLegendreAngularDistribution( module, viewmodule );
  wrapLegendreAngularDistributions( module, viewmodule );
  wrapTabulatedAngularDistribution( module, viewmodule );
  wrapTabulatedAngularDistributions( module, viewmodule );
  wrapTabulatedEnergyDistribution( module, viewmodule );
  wrapTabulatedEnergyDistributions( module, viewmodule );
  wrapTabulatedFormFactor( module, viewmodule );
  wrapTabulatedScatteringFunction( module, viewmodule );
  wrapTwoBodyDistributionData( module, viewmodule );
  wrapUncorrelatedDistributionData( module, viewmodule );
  wrapReactionProduct( module, viewmodule );

  // wrap components - reactions
  wrapTabulatedCrossSection( module, viewmodule );
  wrapReaction( module, viewmodule );

  // wrap components - top level
  wrapProjectileTarget( module, viewmodule );
}
