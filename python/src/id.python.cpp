// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace id {

  // declarations - identifiers
  void wrapEnergyGroup( python::module& );
  void wrapElectronSubshellID( python::module& );
  void wrapElementID( python::module& );
  void wrapLevelID( python::module& );
  void wrapParticleID( python::module& );
  void wrapReactionType( python::module& );
  void wrapReactionID( python::module& );
}

void wrapID( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "id",
    "Identifiers for particles, elements, etc."
  );

  id::wrapEnergyGroup( submodule );
  id::wrapElectronSubshellID( submodule );
  id::wrapElementID( submodule );
  id::wrapLevelID( submodule );
  id::wrapParticleID( submodule );
  id::wrapReactionType( submodule );
  id::wrapReactionID( submodule );
}
