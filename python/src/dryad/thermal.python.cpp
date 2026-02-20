// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

  // declarations - components
  void wrapTabulatedDebyeWallerIntegral( python::module& );
  void wrapTabulatedEffectiveTemperature( python::module& );
  void wrapTabulatedScatteringFunction( python::module& );

  void wrapIncoherentElasticScattering( python::module& );
}

void wrapThermal( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "thermal",
    "Thermal scattering data"
  );

  // components
  thermal::wrapTabulatedDebyeWallerIntegral( submodule );
  thermal::wrapTabulatedEffectiveTemperature( submodule );
  thermal::wrapTabulatedScatteringFunction( submodule );

  thermal::wrapIncoherentElasticScattering( submodule );
}

} // dryad namespace
