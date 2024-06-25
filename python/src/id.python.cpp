// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace id {

  // declarations - ACE data components
  void wrapElementID( python::module&, python::module& );
}

void wrapID( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "id",
    "Identifiers for particles, elements, etc."
  );

  id::wrapElementID( submodule, viewmodule );
}