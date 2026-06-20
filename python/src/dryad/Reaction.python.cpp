// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/Reaction.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapReaction( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::Reaction;
  using ReactionID = njoy::dryad::id::ReactionID;
  using ParticleID = njoy::dryad::id::ParticleID;
  using ReactionProduct = njoy::dryad::ReactionProduct;
  using TabulatedCrossSection = njoy::dryad::TabulatedCrossSection;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Reaction",
    "The data associated to a single reaction\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ReactionID\n"
    "        the reaction identifier\n"
    "    xs : njoy.dryad.TabulatedCrossSection\n"
    "        the cross section of the reaction\n"
    "    products : list of njoy.dryad.ReactionProduct, default []\n"
    "        the reaction products\n"
    "    mass_q : float, default None\n"
    "        the mass difference Q value (default: None)\n"
    "    reaction_q : float, default None\n"
    "        the reaction Q value (default: None)\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)\n\n"
    "    partials : list of njoy.dryad.id.ReactionID\n"
    "        the identifiers of the partials of the reaction"
  );

  // wrap the component
  component
  .def(

    python::init< ReactionID, TabulatedCrossSection,
                  std::vector< ReactionProduct >,
                  std::optional< double >, std::optional< double >,
                  bool >(),
    python::arg( "id" ), python::arg( "xs" ),
    python::arg( "products" ) = std::vector< ReactionProduct >{},
    python::arg( "mass_q" ) = std::nullopt,
    python::arg( "reaction_q" ) = std::nullopt,
    python::arg( "normalise" ) = false,
    "Initialise a primary reaction"
  )
  .def(

    python::init< ReactionID,
                  std::vector< ReactionID >,
                  TabulatedCrossSection,
                  std::vector< ReactionProduct >,
                  bool >(),
    python::arg( "id" ), python::arg( "partials" ), python::arg( "xs" ),
    python::arg( "products" ) = std::vector< ReactionProduct >{},
    python::arg( "normalise" ) = false,
    "Initialise a summation reaction\n\n"
    "Summation reactions do not have Q values associated to them. A cross section\n"
    "weighted Q value could be calculated using the partial reactions making\n"
    "up the summation reaction."
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
    "The number of reaction products of a given type regardless of the chain index"
  )
  .def(

    "number_products",
    python::overload_cast< const ParticleID&, std::size_t >( &Component::numberProducts, python::const_ ),
    python::arg( "type" ),
    python::arg( "chain" ),
    "The number of reaction products of a given type for a given chain index"
  )
  .def(

    "has_product",
    python::overload_cast< const ParticleID& >( &Component::hasProduct, python::const_ ),
    python::arg( "type" ),
    "Return whether or not a reaction product type is present regardless of chain index\n\n"
    "Parameters\n"
    "----------\n"
    "    type : njoy.dryad.id.ParticleID\n"
    "        the reaction product type"
  )
  .def(

    "has_product",
    python::overload_cast< const ParticleID&, std::size_t >( &Component::hasProduct, python::const_ ),
    python::arg( "type" ),
    python::arg( "chain" ),
    "Return whether or not a reaction product type is present for a given chain index\n\n"
    "Parameters\n"
    "----------\n"
    "    type : njoy.dryad.id.ParticleID\n"
    "        the reaction product type\n"
    "    chain : int\n"
    "        the reaction product chain index"
  )
  .def(

    "product",
    python::overload_cast< const ParticleID&, std::size_t >( &Component::product, python::const_ ),
    python::arg( "type" ),
    python::arg( "index" ) = 0,
    "Return a reaction product with a given type and index regardless of the chain index\n\n"
    "Parameters\n"
    "----------\n"
    "    type : njoy.dryad.id.ParticleID\n"
    "        the reaction product type\n"
    "    index : int, default 0\n"
    "        the reaction product index",
    python::return_value_policy::reference_internal
  )
  .def(

    "product",
    python::overload_cast< const ParticleID&, std::size_t, std::size_t >( &Component::product, python::const_ ),
    python::arg( "type" ),
    python::arg( "chain" ),
    python::arg( "index" ),
    "Return a reaction product with a given type, chain index and index\n\n"
    "Parameters\n"
    "----------\n"
    "    type : njoy.dryad.id.ParticleID\n"
    "        the reaction product type\n"
    "    chain : int\n"
    "        the reaction product chain index\n"
    "    index : int\n"
    "        the reaction product index",
    python::return_value_policy::reference_internal
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the distribution data"
  )
  .def(

    "calculate_average_energy",
    &Component::calculateAverageEnergy,
    python::arg( "tolerance" ) = njoy::constants::integration::tolerance,
    "Calculate average outgoing energies for all reaction products\n\n"
    "Parameters\n"
    "----------\n"
    "    tolerance : float, default 1e-8\n"
    "        the integration tolerance"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
