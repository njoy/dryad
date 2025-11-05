// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

  // declarations - scion objects
  void wrapToleranceConvergence( python::module& );

  // declarations - matrix functions
  void wrapMatrix( python::module& );

  // declarations - identifiers
  void wrapID( python::module& );

  // declarations - enumerators
  void wrapInterpolationType( python::module& );
  void wrapDistributionDataType( python::module& );
  void wrapInteractionType( python::module& );
  void wrapReactionCategory( python::module& );
  void wrapReferenceFrame( python::module& );
  void wrapUniformDistributionType( python::module& );

  // declarations - resonances
  void wrapResonances( python::module& );

  // declarations - covariance data
  void wrapCovariance( python::module& );

  // declarations - atomic data
  void wrapAtomic( python::module& );
  void wrapAtomicRelaxation( python::module& );

  // declarations - documentation
  void wrapDocumentation( python::module& );

  // declarations - components
  void wrapIsotropicAngularDistributions( python::module& );
  void wrapLegendreAngularDistributionFunction( python::module& );
  void wrapLegendreAngularDistribution( python::module& );
  void wrapLegendreAngularDistributions( python::module& );
  void wrapTabulatedAngularDistributionFunction( python::module& );
  void wrapTabulatedAngularDistribution( python::module& );
  void wrapTabulatedAngularDistributions( python::module& );
  void wrapUniformAngularDistribution( python::module& );
  void wrapUniformAngularDistributions( python::module& );
  void wrapTabulatedEnergyDistributionFunction( python::module& );
  void wrapTabulatedEnergyDistribution( python::module& );
  void wrapTabulatedEnergyDistributions( python::module& );
  void wrapUniformEnergyDistribution( python::module& );
  void wrapUniformEnergyDistributions( python::module& );
  void wrapMultiEnergyDistributions( python::module& );
  void wrapTabulatedCrossSection( python::module& );
  void wrapPolynomialMultiplicity( python::module& );
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

void wrapDryad( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "dryad",
    "Format agnostic nuclear data interface"
  );

  // wrap components - documentation
  wrapDocumentation( submodule );

  // wrap components - scion objects
  wrapToleranceConvergence( submodule );

  // wrap components - enumerators
  wrapInterpolationType( submodule );
  wrapDistributionDataType( submodule );
  wrapInteractionType( submodule );
  wrapReactionCategory( submodule );
  wrapReferenceFrame( submodule );
  wrapUniformDistributionType( submodule );

  // wrap components - matrix functions
  wrapMatrix( submodule );

  // wrap components - identifiers
  wrapID( submodule );

  // wrap components - resonances
  wrapResonances( submodule );

  // wrap components - covariance data
  wrapCovariance( submodule );

  // wrap components - atomic data
  wrapAtomic( submodule );

  // wrap components - reaction products
  wrapTabulatedMultiplicity( submodule );
  wrapPolynomialMultiplicity( submodule );
  wrapTabulatedAverageCosine( submodule );
  wrapTabulatedAverageEnergy( submodule );
  wrapIsotropicAngularDistributions( submodule );
  wrapTabulatedAngularDistributionFunction( submodule );
  wrapTabulatedAngularDistribution( submodule );
  wrapTabulatedAngularDistributions( submodule );
  wrapLegendreAngularDistributionFunction( submodule );
  wrapLegendreAngularDistribution( submodule );
  wrapLegendreAngularDistributions( submodule );
  wrapUniformAngularDistribution( submodule );
  wrapUniformAngularDistributions( submodule );
  wrapTabulatedEnergyDistributionFunction( submodule );
  wrapTabulatedEnergyDistribution( submodule );
  wrapTabulatedEnergyDistributions( submodule );
  wrapUniformEnergyDistribution( submodule );
  wrapUniformEnergyDistributions( submodule );
  wrapMultiEnergyDistributions( submodule );
  wrapTabulatedFormFactor( submodule );
  wrapTabulatedScatteringFunction( submodule );
  wrapTwoBodyDistributionData( submodule );
  wrapUncorrelatedDistributionData( submodule );
  wrapCoherentDistributionData( submodule );
  wrapIncoherentDistributionData( submodule );
  wrapReactionProduct( submodule );

  // wrap components - reactions
  wrapTabulatedCrossSection( submodule );
  wrapReaction( submodule );

  // wrap components - top level
  wrapProjectileTarget( submodule );
  wrapAtomicRelaxation( submodule );
}
