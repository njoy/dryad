// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/ReactionProduct.hpp"

// namespace aliases
namespace python = pybind11;

void wrapReactionProduct( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::ReactionProduct;
  using ParticleID = njoy::dryad::id::ParticleID;
  using Multiplicity = njoy::dryad::ReactionProduct::Multiplicity;
  using DistributionData = njoy::dryad::ReactionProduct::DistributionData;
  using TabulatedAverageEnergy = njoy::dryad::TabulatedAverageEnergy;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

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

    python::init< ParticleID, Multiplicity,
                  std::optional< DistributionData >,
                  std::optional< TabulatedAverageEnergy >,
                  bool >(),
    python::arg( "id" ), python::arg( "multiplicity" ),
    python::arg( "distribution" ) = std::nullopt,
    python::arg( "average_energy" ) = std::nullopt,
    python::arg( "normalise" ) = false,
    "Initialise the reaction\n\n"
    "Arguments:\n"
    "    self             the reaction\n"
    "    id               the reaction product identifier\n"
    "    multiplicity     the reaction product multiplicity\n"
    "    distribution     the optional reaction product distribution data\n"
    "    average_energy   the optional average reaction product energy\n"
    "    normalise        option to indicate whether or not to normalise\n"
    "                     all probability data (default: no normalisation)"
  )
  .def_property(

    "identifier",
    python::overload_cast<>( &Component::identifier, python::const_ ),
    python::overload_cast< ParticleID >( &Component::identifier ),
    "The reaction product identifier"
  )
  .def_property(

    "multiplicity",
    python::overload_cast<>( &Component::multiplicity, python::const_ ),
    python::overload_cast< Multiplicity >( &Component::multiplicity ),
    "The multiplicity"
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
}
