// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace dryad {

  // declarations - enumerators
  void wrapInterpolationType( python::module& );
  void wrapDistributionDataType( python::module& );
  void wrapInteractionType( python::module& );
  void wrapReactionCategory( python::module& );
  void wrapReferenceFrame( python::module& );
  void wrapUniformDistributionType( python::module& );

  // declarations - identifiers
  void wrapID( python::module& );

  // declarations - particle database
  void wrapParticle( python::module& );
  void wrapParticleDatabase( python::module& );

  // declarations - covariance data
  void wrapCovariance( python::module& );

  // declarations - resonances
  void wrapResonances( python::module& );

  // declarations - thermal
  void wrapThermal( python::module& );
  void wrapThermalScattering( python::module& );

  // declarations - atomic data
  void wrapAtomic( python::module& );
  void wrapAtomicRelaxation( python::module& );

  // declarations - documentation
  void wrapDocumentation( python::module& );

  // declarations - components
  void wrapIsotropicAngularDistributions( python::module& );
  void wrapIsotropicAngularDistributionFunction( python::module& );
  void wrapLegendreAngularDistributionFunction( python::module& );
  void wrapLegendreAngularDistribution( python::module& );
  void wrapLegendreAngularDistributions( python::module& );
  void wrapTabulatedAngularDistributionFunction( python::module& );
  void wrapTabulatedAngularDistribution( python::module& );
  void wrapTabulatedAngularDistributions( python::module& );
  void wrapMixedAngularDistribution( python::module& );
  void wrapMixedAngularDistributions( python::module& );
  void wrapTabulatedComptonProfileFunction( python::module& );
  void wrapTabulatedComptonProfile( python::module& );
  void wrapUniformAngularDistribution( python::module& );
  void wrapUniformAngularDistributions( python::module& );
  void wrapTabulatedEnergyDistributionFunction( python::module& );
  void wrapTabulatedEnergyDistribution( python::module& );
  void wrapTabulatedEnergyDistributions( python::module& );
  void wrapUniformEnergyDistribution( python::module& );
  void wrapUniformEnergyDistributions( python::module& );
  void wrapMultiEnergyDistributions( python::module& );
  void wrapMultigroupCrossSection( python::module& );
  void wrapTabulatedCrossSection( python::module& );
  void wrapMultigroupMultiplicity( python::module& );
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

  // declarations - external
  void wrapExternal( python::module& );

} // dryad namespace

void wrapDryad( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "dryad",
    "Format agnostic nuclear data interface"
  );

  // wrap components - enumerators
  dryad::wrapInterpolationType( submodule );
  dryad::wrapDistributionDataType( submodule );
  dryad::wrapInteractionType( submodule );
  dryad::wrapReactionCategory( submodule );
  dryad::wrapReferenceFrame( submodule );
  dryad::wrapUniformDistributionType( submodule );

  // wrap components - identifiers
  dryad::wrapID( submodule );

  // wrap components - particle database
  dryad::wrapParticle( submodule );
  dryad::wrapParticleDatabase( submodule );

  // wrap components - documentation
  dryad::wrapDocumentation( submodule );

  // wrap components - resonances
  dryad::wrapResonances( submodule );

  // wrap components - thermal
  dryad::wrapThermal( submodule );

  // wrap components - atomic data
  dryad::wrapAtomic( submodule );

  // wrap components - reaction products
  dryad::wrapMultigroupMultiplicity( submodule );
  dryad::wrapTabulatedMultiplicity( submodule );
  dryad::wrapPolynomialMultiplicity( submodule );
  dryad::wrapTabulatedAverageCosine( submodule );
  dryad::wrapTabulatedAverageEnergy( submodule );
  dryad::wrapIsotropicAngularDistributions( submodule );
  dryad::wrapIsotropicAngularDistributionFunction( submodule );
  dryad::wrapTabulatedAngularDistributionFunction( submodule );
  dryad::wrapTabulatedAngularDistribution( submodule );
  dryad::wrapTabulatedAngularDistributions( submodule );
  dryad::wrapMixedAngularDistribution( submodule );
  dryad::wrapMixedAngularDistributions( submodule );
  dryad::wrapTabulatedComptonProfileFunction( submodule );
  dryad::wrapTabulatedComptonProfile( submodule );
  dryad::wrapLegendreAngularDistributionFunction( submodule );
  dryad::wrapLegendreAngularDistribution( submodule );
  dryad::wrapLegendreAngularDistributions( submodule );
  dryad::wrapUniformAngularDistribution( submodule );
  dryad::wrapUniformAngularDistributions( submodule );
  dryad::wrapTabulatedEnergyDistributionFunction( submodule );
  dryad::wrapTabulatedEnergyDistribution( submodule );
  dryad::wrapTabulatedEnergyDistributions( submodule );
  dryad::wrapUniformEnergyDistribution( submodule );
  dryad::wrapUniformEnergyDistributions( submodule );
  dryad::wrapMultiEnergyDistributions( submodule );
  dryad::wrapTabulatedFormFactor( submodule );
  dryad::wrapTabulatedScatteringFunction( submodule );
  dryad::wrapTwoBodyDistributionData( submodule );
  dryad::wrapUncorrelatedDistributionData( submodule );
  dryad::wrapCoherentDistributionData( submodule );
  dryad::wrapIncoherentDistributionData( submodule );
  dryad::wrapReactionProduct( submodule );

  // wrap components - covariance data
  dryad::wrapCovariance( submodule );

  // wrap components - reactions
  dryad::wrapMultigroupCrossSection( submodule );
  dryad::wrapTabulatedCrossSection( submodule );
  dryad::wrapReaction( submodule );

  // wrap components - top level
  dryad::wrapProjectileTarget( submodule );
  dryad::wrapAtomicRelaxation( submodule );
  dryad::wrapThermalScattering( submodule );

  // wrap components - external data and models
  dryad::wrapExternal( submodule );
}
