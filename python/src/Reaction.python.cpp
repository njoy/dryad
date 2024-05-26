// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/Reaction.hpp"

// namespace aliases
namespace python = pybind11;

void wrapReaction( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::Reaction;
  using ReactionID = njoy::dryad::ReactionID;
  using TabulatedCrossSection = njoy::dryad::TabulatedCrossSection;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Reaction",
    "A cross section table"
  );

  // wrap the component
  component
  .def(

    python::init< ReactionID, double, double, TabulatedCrossSection >(),
    python::arg( "id" ), python::arg( "mass_q" ),
    python::arg( "reaction_q" ), python::arg( "xs" ),
    "Initialise the reaction\n\n"
    "Arguments:\n"
    "    self         the reaction\n"
    "    id           the reaction identifier\n"
    "    mass_q       the mass difference Q value\n"
    "    reaction_q   the reaction Q value\n"
    "    xs           the cross section of the reaction"
  )
  .def_property_readonly(

    "identifier",
    &Component::identifier,
    "The reaction identifier"
  )
  .def_property_readonly(

    "mass_difference_qvalue",
    &Component::massDifferenceQValue,
    "The mass difference Q value"
  )
  .def_property_readonly(

    "reaction_qvalue",
    &Component::reactionQValue,
    "The reaction Q value"
  )
  .def_property_readonly(

    "cross_section",
    &Component::crossSection,
    "The cross section"
  )
  .def_property_readonly(

    "is_linearised",
    &Component::isLinearised,
    "Flag indicating whether or not the data is linearised"
  )
  .def(

    "linearise",
    [] ( const Component& self, const ToleranceConvergence& tolerance )
       { return self.linearise( tolerance ); },
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the reaction data and return a new reaction\n\n"
    "Arguments:\n"
    "    self        the reaction\n"
    "    tolerance   the linearisation tolerance"
  )
  .def(

    "linearise_inplace",
    [] ( Component& self, const ToleranceConvergence& tolerance )
       { return self.lineariseInplace( tolerance ); },
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the reaction data inplace\n\n"
    "Arguments:\n"
    "    self        the reaction\n"
    "    tolerance   the linearisation tolerance"
  );
}
