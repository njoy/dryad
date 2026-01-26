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
}

void wrapExternal( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "external",
    "External data and models"
  );

  // components
  external::wrapComptonProfiles( submodule );
}

} // dryad namespace
