// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

// declarations - enumerators
void wrapInteractionType( python::module&, python::module& );
void wrapReactionType( python::module&, python::module& );
void wrapReferenceFrame( python::module&, python::module& );

// declarations - subpackages
void wrapID( python::module&, python::module& );

// declarations - components
void wrapLegendreAngularDistribution( python::module&, python::module& );
void wrapTabulatedAngularDistribution( python::module&, python::module& );
void wrapTabulatedCrossSection( python::module&, python::module& );
void wrapTabulatedMultiplicity( python::module&, python::module& );
void wrapReactionProduct( python::module&, python::module& );
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

  // wrap enumerators
  wrapInteractionType( module, viewmodule );
  wrapReactionType( module, viewmodule );
  wrapReferenceFrame( module, viewmodule );

  // wrap subpackages
  wrapID( module, viewmodule );

  // wrap components
  wrapLegendreAngularDistribution( module, viewmodule );
  wrapTabulatedAngularDistribution( module, viewmodule );
  wrapTabulatedCrossSection( module, viewmodule );
  wrapTabulatedMultiplicity( module, viewmodule );
  wrapReactionProduct( module, viewmodule );
  wrapReaction( module, viewmodule );
  wrapProjectileTarget( module, viewmodule );
}
