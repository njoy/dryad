// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace id {

  // declarations - identifiers
  void wrapElementID( python::module& );
  void wrapLevelID( python::module& );
}

void wrapID( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "id",
    "Identifiers for particles, elements, etc."
  );

  id::wrapElementID( submodule );
  id::wrapLevelID( submodule );
}
