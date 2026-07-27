// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace external {

  // declarations - components
  void wrapComptonProfiles( python::module& );

  // ripl3 data
  void wrapRipl3( python::module& );

  // ame data
  void wrapAme( python::module& );
}

void wrapExternal( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "external",
    "External data and models"
  );

  // components
  external::wrapComptonProfiles( submodule );

  // ripl3
  external::wrapRipl3( submodule );

  // Ame
  external::wrapAme( submodule );
}

} // dryad namespace
