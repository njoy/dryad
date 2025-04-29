// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/covariance/LinearCombinationCovariance.hpp"

// namespace aliases
namespace python = pybind11;

namespace covariance {

void wrapLinearCombinationCovariance( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::LinearCombinationCovariance;
  using ReactionID = njoy::dryad::id::ReactionID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "LinearCombinationCovariance",
    "Covariance data for a reaction defined as a linear combination of other "
    "reactions\' covariance data"
  );

  // wrap the component
  component
  .def(

    python::init< double, double, std::vector< ReactionID >, std::vector< double > >(),
    python::arg( "lower" ), python::arg( "upper" ),
    python::arg( "reactions" ), python::arg( "coefficients" ),
    "Initialise the derived covariance\n\n"
    "Arguments:\n"
    "    self           the derived covariance\n"
    "    lower          the lower energy limit\n"
    "    upper          the upper energy limit\n"
    "    reactions      the reactions in the linear combination\n"
    "    coefficients   the coefficients of the linear combination"
  )
  .def_property_readonly(

    "lower_energy_limit",
    &Component::lowerEnergyLimit,
    "The lower energy limit"
  )
  .def_property_readonly(

    "upper_energy_limit",
    &Component::upperEnergyLimit,
    "The upper energy limit"
  )
  .def_property_readonly(

    "reactions",
    &Component::reactions,
    "The reactions in the linear combination"
  )
  .def_property_readonly(

    "coefficients",
    &Component::coefficients,
    "The coefficients for the linear combination"
  )
  .def_property_readonly(

    "number_reactions",
    &Component::numberReactions,
    "The number of reactions"
  );
}

} // covariance namespace
