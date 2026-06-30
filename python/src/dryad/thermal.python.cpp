// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

  // declarations - components
  void wrapBraggEdgeData( python::module& );
  void wrapDebyeWallerIntegralData( python::module& );
  void wrapTabulatedScatteringKernelFunction( python::module& );
  void wrapTabulatedScatteringKernel( python::module& );

  void wrapCoherentElasticScattering( python::module& );
  void wrapIncoherentElasticScattering( python::module& );
  void wrapIncoherentElasticCrossSection( python::module& );
}

void wrapThermal( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "thermal",
    "Thermal scattering data"
  );

  // components
  thermal::wrapBraggEdgeData( submodule );
  thermal::wrapDebyeWallerIntegralData( submodule );
  thermal::wrapTabulatedScatteringKernelFunction( submodule );
  thermal::wrapTabulatedScatteringKernel( submodule );

  thermal::wrapCoherentElasticScattering( submodule );
  thermal::wrapIncoherentElasticScattering( submodule );
  thermal::wrapIncoherentElasticCrossSection( submodule );
}

} // dryad namespace
