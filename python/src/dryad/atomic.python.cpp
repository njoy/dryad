// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace atomic {

  // declarations - enumerators
  void wrapTransitionType( python::module& );

  // declarations - atomic data components
  void wrapRadiativeTransitionData( python::module& );
  void wrapNonRadiativeTransitionData( python::module& );
  void wrapElectronSubshellConfiguration( python::module& );
}

void wrapAtomic( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "atomic",
    "Atomic relaxation data components"
  );

  // wrap components - enumerators
  atomic::wrapTransitionType( submodule );

  // declarations - atomic data components
  atomic::wrapRadiativeTransitionData( submodule );
  atomic::wrapNonRadiativeTransitionData( submodule );
  atomic::wrapElectronSubshellConfiguration( submodule );
}
