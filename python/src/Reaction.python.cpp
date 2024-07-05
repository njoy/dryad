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
  using ReactionType = njoy::dryad::ReactionType;
  using ReactionProduct = njoy::dryad::ReactionProduct;
  using TabulatedCrossSection = njoy::dryad::TabulatedCrossSection;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Reaction",
    "The data associated to a single reaction"
  );

  // wrap the component
  component
  .def(

    python::init< ReactionID, ReactionType, TabulatedCrossSection,
                  std::vector< ReactionProduct >,
                  std::optional< double >, std::optional< double > >(),
    python::arg( "id" ), python::arg( "type" ), python::arg( "xs" ),
    python::arg( "products" ) = std::vector< ReactionProduct >{},
    python::arg( "mass_q" ) = std::nullopt,
    python::arg( "reaction_q" ) = std::nullopt,
    "Initialise the reaction\n\n"
    "Arguments:\n"
    "    self         the reaction\n"
    "    id           the reaction identifier\n"
    "    type         the reaction type\n"
    "    xs           the cross section of the reaction\n"
    "    products     the reaction products\n"
    "    mass_q       the mass difference Q value (optional)\n"
    "    reaction_q   the reaction Q value (optional)\n"
  )
  .def_property_readonly(

    "identifier",
    &Component::identifier,
    "The reaction identifier"
  )
  .def_property_readonly(

    "type",
    &Component::type,
    "The reaction type"
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

    "has_products",
    &Component::hasProducts,
    "Flag indicating whether or not there are reaction products defined"
  )
  .def_property_readonly(

    "products",
    &Component::products,
    "The reaction products"
  )
  .def_property_readonly(

    "is_linearised",
    &Component::isLinearised,
    "Flag indicating whether or not the data is linearised"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the reaction data and return a new reaction\n\n"
    "Arguments:\n"
    "    self        the reaction\n"
    "    tolerance   the linearisation tolerance"
  )
  .def(

    "linearise_inplace",
    &Component::lineariseInplace,
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the reaction data inplace\n\n"
    "Arguments:\n"
    "    self        the reaction\n"
    "    tolerance   the linearisation tolerance"
  );
}
