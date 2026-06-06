// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace external {
namespace ame {

  // declarations - components
  void wrapMassEntry( python::module& );
//  void wrapMasses( python::module& );
} // ame namespace

void wrapAme( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "ame",
    "Atomic mass evaluation data"
  );

  // components
  external::ame::wrapMassEntry( submodule );
//  external::ame::wrapMasses( submodule );
}

} // external namespace
} // dryad namespace
