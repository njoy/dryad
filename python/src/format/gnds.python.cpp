// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace format {
namespace gnds {

  // declarations - enums
  void wrapStyleType( python::module& );
}

void wrapResonances( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "gnds",
    "GNDS format related functions and components"
  );

  // enums
  gnds::wrapStyleType( submodule );
}

} // dryad namespace
