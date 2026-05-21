// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace psychic {

  // declarations - enumerators
  void wrapTestStatus( python::module& );

  // declarations
  void wrapCovariance( python::module& );
} // psychic namespace

void wrapPsychic( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "psychic",
    "Data verification and physics checking"
  );

  // wrap enumerators
  psychic::wrapTestStatus( submodule );

  // wrap components
  psychic::wrapCovariance( submodule );
}
