// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

// declarations
void wrapTabulatedCrossSection( python::module&, python::module& );
void wrapReaction( python::module&, python::module& );
void wrapProjectileTarget( python::module&, python::module& );

/**
 *  @brief dryad python bindings
 *
 *  The name given here (dryad) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( dryad, module ) {

  auto scion_interpolation = python::module::import( "scion.interpolation" );
  auto scion_linearisation = python::module::import( "scion.linearisation" );

  module.attr( "InterpolationType" ) = scion_interpolation.attr( "InterpolationType" );
  module.attr( "ToleranceConvergence" ) = scion_linearisation.attr( "ToleranceConvergence" );

  // create the views submodule
  python::module viewmodule = module.def_submodule(

    "sequence",
    "sequence - dryad sequences (internal use only)"
  );

  // wrap components
  wrapTabulatedCrossSection( module, viewmodule );
  wrapReaction( module, viewmodule );
  wrapProjectileTarget( module, viewmodule );
}
