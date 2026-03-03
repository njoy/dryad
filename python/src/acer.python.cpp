// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace acer {

  // declarations - ace file processing
  void wrapProcessElectronPhotonRelaxation( python::module& );

} // acer namespace

void wrapAcer( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "acer",
    "Monte Carlo transport data file processing"
  );

  // wrap components - ace file processing
  acer::wrapProcessElectronPhotonRelaxation( submodule );
}
