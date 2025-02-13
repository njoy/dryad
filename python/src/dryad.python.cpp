// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

// declarations - scion objects
void wrapToleranceConvergence( python::module& );

// declarations - identifiers
void wrapID( python::module& );

// declarations - enumerators
void wrapInterpolationType( python::module& );
void wrapDistributionDataType( python::module& );
void wrapInteractionType( python::module& );
void wrapReactionType( python::module& );
void wrapReferenceFrame( python::module& );

// declarations - covariance data
void wrapCovariance( python::module& );

// declarations - atomic data
void wrapAtomic( python::module& );
void wrapAtomicRelaxation( python::module& );

// declarations - components
void wrapIsotropicAngularDistributions( python::module& );
void wrapLegendreAngularDistributionFunction( python::module& );
void wrapLegendreAngularDistribution( python::module& );
void wrapLegendreAngularDistributions( python::module& );
void wrapTabulatedAngularDistributionFunction( python::module& );
void wrapTabulatedAngularDistribution( python::module& );
void wrapTabulatedAngularDistributions( python::module& );
void wrapTabulatedEnergyDistributionFunction( python::module& );
void wrapTabulatedEnergyDistribution( python::module& );
void wrapTabulatedEnergyDistributions( python::module& );
void wrapTabulatedCrossSection( python::module& );
void wrapTabulatedMultiplicity( python::module& );
void wrapTabulatedAverageCosine( python::module& );
void wrapTabulatedAverageEnergy( python::module& );
void wrapTabulatedFormFactor( python::module& );
void wrapTabulatedScatteringFunction( python::module& );
void wrapTwoBodyDistributionData( python::module& );
void wrapUncorrelatedDistributionData( python::module& );
void wrapCoherentDistributionData( python::module& );
void wrapIncoherentDistributionData( python::module& );
void wrapReactionProduct( python::module& );
void wrapReaction( python::module& );
void wrapProjectileTarget( python::module& );

/**
 *  @brief dryad python bindings
 *
 *  The name given here (dryad) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( dryad, module ) {

  // wrap components - scion objects
  wrapToleranceConvergence( module );

  // wrap components - identifiers
  wrapID( module );

  // wrap components - enumerators
  wrapInterpolationType( module );
  wrapDistributionDataType( module );
  wrapInteractionType( module );
  wrapReactionType( module );
  wrapReferenceFrame( module );

  // wrap components - covariance data
  wrapCovariance( module );

  // wrap components - atomic data
  wrapAtomic( module );

  // wrap components - reaction products
  wrapTabulatedMultiplicity( module );
  wrapTabulatedAverageCosine( module );
  wrapTabulatedAverageEnergy( module );
  wrapIsotropicAngularDistributions( module );
  wrapLegendreAngularDistributionFunction( module );
  wrapLegendreAngularDistribution( module );
  wrapLegendreAngularDistributions( module );
  wrapTabulatedAngularDistributionFunction( module );
  wrapTabulatedAngularDistribution( module );
  wrapTabulatedAngularDistributions( module );
  wrapTabulatedEnergyDistributionFunction( module );
  wrapTabulatedEnergyDistribution( module );
  wrapTabulatedEnergyDistributions( module );
  wrapTabulatedFormFactor( module );
  wrapTabulatedScatteringFunction( module );
  wrapTwoBodyDistributionData( module );
  wrapUncorrelatedDistributionData( module );
  wrapCoherentDistributionData( module );
  wrapIncoherentDistributionData( module );
  wrapReactionProduct( module );

  // wrap components - reactions
  wrapTabulatedCrossSection( module );
  wrapReaction( module );

  // wrap components - top level
  wrapProjectileTarget( module );
  wrapAtomicRelaxation( module );
}
