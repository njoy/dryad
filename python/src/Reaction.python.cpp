// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/Reaction.hpp"

// namespace aliases
namespace python = pybind11;

void wrapReaction( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::Reaction;
  using ReactionID = njoy::dryad::id::ReactionID;
  using ParticleID = njoy::dryad::id::ParticleID;
  using ReactionCategory = njoy::dryad::ReactionCategory;
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

    python::init< ReactionID, TabulatedCrossSection,
                  std::vector< ReactionProduct >,
                  std::optional< double >, std::optional< double > >(),
    python::arg( "id" ), python::arg( "xs" ),
    python::arg( "products" ) = std::vector< ReactionProduct >{},
    python::arg( "mass_q" ) = std::nullopt,
    python::arg( "reaction_q" ) = std::nullopt,
    "Initialise a primary reaction\n\n"
    "Arguments:\n"
    "    self         the reaction\n"
    "    id           the reaction identifier\n"
    "    xs           the cross section of the reaction\n"
    "    products     the reaction products\n"
    "    mass_q       the mass difference Q value (optional)\n"
    "    reaction_q   the reaction Q value (optional)"
  )
  .def(

    python::init< ReactionID,
                  std::vector< ReactionID >,
                  TabulatedCrossSection,
                  std::vector< ReactionProduct > >(),
    python::arg( "id" ), python::arg( "partials" ), python::arg( "xs" ),
    python::arg( "products" ) = std::vector< ReactionProduct >{},
    "Initialise a summation reaction\n\n"
    "Summation reactions do not have Q values associated to them. A cross section\n"
    "weighted Q value could be calculated using the partial reactions making\n"
    "up the summation reaction.\n\n"
    "Arguments:\n"
    "    self        the reaction\n"
    "    id          the reaction identifier\n"
    "    partials    the identifiers of the partials of the reaction\n"
    "    xs          the cross section of the reaction\n"
    "    products    the reaction products associated to the summation reaction\n"
    "                (defaults to no reaction products)"
  )
  .def_property(

    "identifier",
    python::overload_cast<>( &Component::identifier, python::const_ ),
    python::overload_cast< ReactionID >( &Component::identifier ),
    "The reaction identifier"
  )
  .def_property_readonly(

    "category",
    &Component::category,
    "The reaction category"
  )
  .def_property_readonly(

    "is_summation_reaction",
    &Component::isSummationReaction,
    "Flag to indicate whether or not the reaction is a summation reaction"
  )
  .def_property_readonly(

    "is_primary_reaction",
    &Component::isPrimaryReaction,
    "Flag to indicate whether or not the reaction is a primary reaction"
  )
  .def_property(

    "partial_reaction_identifiers",
    python::overload_cast<>( &Component::partialReactionIdentifiers, python::const_ ),
    python::overload_cast< std::optional< std::vector< ReactionID > > >( &Component::partialReactionIdentifiers ),
    "The summation reaction identifiers (not defined if this is a primary\n"
    "reaction)"
  )
  .def_property_readonly(

    "number_partial_reactions",
    &Component::numberPartialReactions,
    "The number of partial reactions that make up this reaction"
  )
  .def_property(

    "mass_difference_qvalue",
    python::overload_cast<>( &Component::massDifferenceQValue, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::massDifferenceQValue ),
    "The mass difference Q value"
  )
  .def_property(

    "reaction_qvalue",
    python::overload_cast<>( &Component::reactionQValue, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::reactionQValue ),
    "The reaction Q value"
  )
  .def_property(

    "cross_section",
    python::overload_cast<>( &Component::crossSection, python::const_ ),
    python::overload_cast< TabulatedCrossSection >( &Component::crossSection ),
    "The cross section"
  )
  .def_property_readonly(

    "has_products",
    &Component::hasProducts,
    "Flag indicating whether or not there are reaction products defined"
  )
  .def_property(

    "products",
    python::overload_cast<>( &Component::products, python::const_ ),
    python::overload_cast< std::vector< ReactionProduct > >( &Component::products ),
    "The reaction products"
  )
  .def(

    "number_products",
    python::overload_cast<>( &Component::numberProducts, python::const_ ),
    "The total number of reaction products"
  )
  .def(

    "number_products",
    python::overload_cast< const ParticleID& >( &Component::numberProducts, python::const_ ),
    python::arg( "type" ),
    "The number of reaction products of a given type"
  )
  .def(

    "has_product",
    &Component::hasProduct,
    python::arg( "type" ),
    "Return whether or not a reaction product type is present\n\n"
    "Arguments:\n"
    "    self   the reaction\n"
    "    type   the reaction product type"
  )
  .def(

    "product",
    python::overload_cast< const ParticleID&, std::size_t >( &Component::product, python::const_ ),
    python::arg( "type" ),
    python::arg( "index" ) = 0,
    "Return a reaction product with a given type and index\n\n"
    "Arguments:\n"
    "    self    the reaction\n"
    "    type    the reaction product type\n"
    "    index   the reaction product index (default is zero)",
    python::return_value_policy::reference_internal
 );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}
