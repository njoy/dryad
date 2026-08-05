// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

// declarations - constants
void wrapConstants( python::module& );

// declarations - matrix functions
void wrapMatrix( python::module& );

// declarations - components and modules
void wrapAcer( python::module& );
void wrapFormat( python::module& );
void wrapDryad( python::module& );
void wrapPsychic( python::module& );
void wrapReconr( python::module& );
void wrapMedic( python::module& );

/**
 *  @brief njoy python bindings
 *
 *  The name given here (njoy) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( njoy, module ) {

  // wrap constants
  wrapConstants( module );

  // wrap matrix functions
  wrapMatrix( module );

  // wrap format
  wrapFormat( module );

  // wrap dryad
  wrapDryad( module );

  // wrap reconr
  wrapReconr( module );

  // wrap psychic
  wrapPsychic( module );

  // wrap medic
  wrapMedic( module );

  // wrap acer
  wrapAcer( module );
}
