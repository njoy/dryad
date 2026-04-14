// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/ReactionProduct.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapReactionProduct( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::ReactionProduct;
  using ParticleID = njoy::dryad::id::ParticleID;
  using Multiplicity = njoy::dryad::ReactionProduct::Multiplicity;
  using DistributionData = njoy::dryad::ReactionProduct::DistributionData;
  using TabulatedAverageCosine = njoy::dryad::TabulatedAverageCosine;
  using TabulatedAverageEnergy = njoy::dryad::TabulatedAverageEnergy;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ReactionProduct",
    "The data associated to a single reaction product"
  );

  // wrap the component
  component
  .def(

    python::init< ParticleID,
                  Multiplicity,
                  std::optional< DistributionData >,
                  std::optional< TabulatedAverageCosine >,
                  std::optional< TabulatedAverageEnergy >,
                  std::optional< ParticleID >,
                  std::size_t,
                  bool >(),
    python::arg( "product" ), python::arg( "multiplicity" ),
    python::arg( "distribution" ) = std::nullopt,
    python::arg( "average_cosine" ) = std::nullopt,
    python::arg( "average_energy" ) = std::nullopt,
    python::arg( "parent" ) = std::nullopt,
    python::arg( "chain" ) = 0,
    python::arg( "normalise" ) = false,
    "Initialise the reaction\n\n"
    "Arguments:\n"
    "    self             the reaction\n"
    "    product          the reaction product identifier\n"
    "    multiplicity     the reaction product multiplicity\n"
    "    distribution     the optional reaction product distribution data\n"
    "    average_cosine   the optional average reaction product cosine\n"
    "    average_energy   the optional average reaction product energy\n"
    "    parent           the optional parent reaction product\n"
    "    chain            the chain index of the reaction product\n"
    "    normalise        option to indicate whether or not to normalise\n"
    "                     all probability data (default: no normalisation)"
  )
  .def_property(

    "product_identifier",
    python::overload_cast<>( &Component::productIdentifier, python::const_ ),
    python::overload_cast< ParticleID >( &Component::productIdentifier ),
    "The reaction product identifier"
  )
  .def_property(

    "parent_identifier",
    python::overload_cast<>( &Component::parentIdentifier, python::const_ ),
    python::overload_cast< std::optional< ParticleID > >( &Component::parentIdentifier ),
    "The parent product identifier"
  )
  .def_property(

    "chain_index",
    python::overload_cast<>( &Component::chainIndex, python::const_ ),
    python::overload_cast< std::size_t >( &Component::chainIndex ),
    "The chain index of the reaction product"
  )
  .def_property(

    "multiplicity",
    python::overload_cast<>( &Component::multiplicity, python::const_ ),
    python::overload_cast< Multiplicity >( &Component::multiplicity ),
    "The multiplicity"
  )
  .def_property(

    "average_cosine",
    python::overload_cast<>( &Component::averageCosine, python::const_ ),
    python::overload_cast< std::optional< TabulatedAverageCosine > >( &Component::averageCosine ),
    "The average reaction product cosine"
  )
  .def_property(

    "average_energy",
    python::overload_cast<>( &Component::averageEnergy, python::const_ ),
    python::overload_cast< std::optional< TabulatedAverageEnergy > >( &Component::averageEnergy ),
    "The average reaction product energy"
  )
  .def_property(

    "distribution_data",
    python::overload_cast<>( &Component::distributionData, python::const_ ),
    python::overload_cast< std::optional< DistributionData > >( &Component::distributionData ),
    "The distribution data"
  )
  .def_property_readonly(

    "has_average_cosine",
    &Component::hasAverageCosine,
    "Flag indicating whether or not the reaction product has average reaction "
    "product cosine data"
  )
  .def_property_readonly(

    "has_average_energy",
    &Component::hasAverageEnergy,
    "Flag indicating whether or not the reaction product has average reaction "
    "product energy data"
  )
  .def_property_readonly(

    "has_distribution_data",
    &Component::hasDistributionData,
    "Flag indicating whether or not the reaction product has distribution data"
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the distribution data"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
