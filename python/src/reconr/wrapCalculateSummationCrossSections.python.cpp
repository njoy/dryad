// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/reconr/calculateSummationCrossSections.hpp"

// namespace aliases
namespace python = pybind11;

namespace reconr {

  void wrapCalculateSummationCrossSections( python::module& module ) {

    // type aliases

    // wrap the function
    module
    .def(

      "calculate_summation_cross_sections",
      &njoy::reconr::calculateSummationCrossSections,
      python::arg( "pt" ),
      python::arg( "tolerance" ) = njoy::dryad::ToleranceConvergence(),
      "This function recalculates the cross section of all summation reactions of\n"
      "a ProjectileTarget instance. It does so by linearising the cross sections of\n"
      "the partials (if required) and summing them together.\n\n"
      "Arguments:\n"
      "    pt          the projectile-target data to be modified\n"
      "    tolerance   the linearisation tolerance"
    );
  }
} // medic namespace
