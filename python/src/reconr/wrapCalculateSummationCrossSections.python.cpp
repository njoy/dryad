// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>
#include <iomanip>

// local includes
#include "njoy/constants.hpp"
#include "njoy/reconr/calculateSummationCrossSections.hpp"

// namespace aliases
namespace python = pybind11;

namespace reconr {

  void wrapCalculateSummationCrossSections( python::module& module ) {

    // constants
    std::ostringstream tolerance;
    tolerance << std::setprecision( 4 ) << njoy::constants::linearisation::tolerance;

    // type aliases

    // wrap the function
    module
    .def(

      "calculate_summation_cross_sections",
      &njoy::reconr::calculateSummationCrossSections,
      python::arg( "pt" ),
      python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
      std::string( "Calculate summation cross sections\n\n"
                   "This function recalculates the cross section of all summation reactions of\n"
                   "a ProjectileTarget instance. It does so by linearising the cross sections of\n"
                   "the partials (if required) and summing them together.\n\n"
                   "Parameters\n"
                   "----------\n"
                   "    pt : njoy.dryad.ProjectileTarget\n"
                   "        the projectile-target data to be modified\n"
                   "    tolerance : float, default " + tolerance.str() + "\n"
                   "        the absolute linearisation tolerance" ).c_str()
    );
  }

} // reconr namespace
