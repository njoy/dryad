// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace resonances {

  // declarations - components
  void wrapTabulatedRadius( python::module& );
  void wrapChannelRadii( python::module& );
  void wrapHardSpherePenetrability( python::module& );
  void wrapHardSphereShiftFactor( python::module& );
  void wrapTabulatedWaveFunction( python::module& );

  void wrapResonanceParameters( python::module& );
}

void wrapResonances( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "resonances",
    "Resonance data"
  );

  // components
  resonances::wrapTabulatedRadius( submodule );
  resonances::wrapChannelRadii( submodule );
  resonances::wrapHardSpherePenetrability( submodule );
  resonances::wrapHardSphereShiftFactor( submodule );
  resonances::wrapTabulatedWaveFunction( submodule );

  resonances::wrapResonanceParameters( submodule );
}
