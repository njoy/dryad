// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/resonances/ResonanceParameters.hpp"

// namespace aliases
namespace python = pybind11;

namespace resonances {

void wrapResonanceParameters( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::ResonanceParameters;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ResonanceParameters"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace