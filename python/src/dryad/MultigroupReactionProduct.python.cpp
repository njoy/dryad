// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/MultigroupReactionProduct.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapMultigroupReactionProduct( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::MultigroupReactionProduct;
  using ParticleID = njoy::dryad::id::ParticleID;
  using Multiplicity = njoy::dryad::MultigroupReactionProduct::Multiplicity;
  using MultigroupAverageCosine = njoy::dryad::MultigroupAverageCosine;
  using MultigroupAverageEnergy = njoy::dryad::MultigroupAverageEnergy;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "MultigroupReactionProduct",
    "The multigroup data associated to a single reaction product\n\n"
    "Parameters\n"
    "----------\n"
    "    product : njoy.dryad.id.ParticleID\n"
    "        the reaction product identifier\n"
    "    multiplicity : int or njoy.dryad.MultigroupMultiplicity\n"
    "        the reaction product multiplicity\n"
    "    average_cosine : njoy.dryad.MultigroupAverageCosine, default None\n"
    "        the average reaction product cosine (default: None)\n"
    "    average_energy : njoy.dryad.MultigroupAverageEnergy, default None\n"
    "        the average reaction product energy (default: None)\n"
    "    parent : njoy.dryad.id.ParticleID, default None\n"
    "        the parent reaction product (default: None)\n"
    "    chain : int, default 0\n"
    "        the chain index of the reaction product (default: 0)"
  );

  // wrap the component
  component
  .def(

    python::init< ParticleID,
                  Multiplicity,
                  std::optional< MultigroupAverageCosine >,
                  std::optional< MultigroupAverageEnergy >,
                  std::optional< ParticleID >,
                  std::size_t >(),
    python::arg( "product" ), python::arg( "multiplicity" ),
    python::arg( "average_cosine" ) = std::nullopt,
    python::arg( "average_energy" ) = std::nullopt,
    python::arg( "parent" ) = std::nullopt,
    python::arg( "chain" ) = 0,
    "Initialise the multigroup reaction product"
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
    python::overload_cast< std::optional< MultigroupAverageCosine > >( &Component::averageCosine ),
    "The average reaction product cosine"
  )
  .def_property(

    "average_energy",
    python::overload_cast<>( &Component::averageEnergy, python::const_ ),
    python::overload_cast< std::optional< MultigroupAverageEnergy > >( &Component::averageEnergy ),
    "The average reaction product energy"
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
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
