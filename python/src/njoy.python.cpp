// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

// declarations
void wrapDryad( python::module& );

/**
 *  @brief njoy python bindings
 *
 *  The name given here (njoy) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( njoy, module ) {

  // wrap dryad
  wrapDryad( module );
}
