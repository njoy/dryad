// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace external {
namespace ripl3 {

  // declarations - components
  void wrapLevelEntry( python::module& );
  void wrapLevels( python::module& );
} // ripl3 namespace

void wrapRipl3( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "ripl3",
    "RIPL-3 data"
  );

  // components
  external::ripl3::wrapLevelEntry( submodule );
  external::ripl3::wrapLevels( submodule );
}

} // external namespace
} // dryad namespace
