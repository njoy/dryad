// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace format {

  // declarations - enumerators
  void wrapGnds( python::module& );

} // format namespace

void wrapFormat( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "format",
    "Nuclear data format related functions and components"
  );

  // wrap formats
  format::wrapGnds( submodule );
}
