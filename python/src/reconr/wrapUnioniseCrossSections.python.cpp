// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/reconr/unioniseCrossSections.hpp"

// namespace aliases
namespace python = pybind11;

namespace reconr {

  void wrapUnioniseCrossSections( python::module& module ) {

    // type aliases

    // wrap the function
    module
    .def(

      "unionise_cross_sections",
      &njoy::reconr::unioniseCrossSections,
      python::arg( "pt" ),
      python::arg( "exclude_summation" ) = false,
      "Unionise cross section data in a ProjectileTarget instance\n\n"
      "This function takes all cross section data in the ProjectileTarget\n"
      "instance and unionises the cross section grids. It does not linearise\n"
      "the data but reevaluates the data using the proper interpolation types\n"
      "of the cross section data.\n\n"
      "By default, summation cross sections are included in the unionisation process.\n"
      "unless explicitly excluded by the user. Switching on the exclusion of summation\n"
      "cross sections may be useful when the user is going to recalculate the summation\n"
      "cross sections after unionisation.\n\n"
      "pt                  the projectile-target data to be modified\n"
      "exclude_summation   option to exclude summation reactions in the\n"
      "                    unionisation (default: false)"
    );
  }
} // reconr namespace
