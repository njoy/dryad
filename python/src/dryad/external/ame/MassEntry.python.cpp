// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/external/ame/MassEntry.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace external {
namespace ame {

void wrapMassEntry( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::external::ame::MassEntry;
  using ParticleID = njoy::dryad::id::ParticleID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "MassEntry",
    "Mass entry information from the Atomic Mass Evaluation\n\n"
    "The MassEntry class contains specific information from the atomic mass\n"
    "evaluations:\n\n"
    "  - a particle identifier\n"
    "  - mass excess and uncertainty (in eV)\n"
    "  - binding energy per nucleon and uncertainty (in eV)\n"
    "  - beta decay energy and uncertainty (in eV)\n"
    "  - atomic mass and uncertainty (in amu)\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ParticleID\n"
    "        the particle identifier\n"
    "    mass_excess : float, default None\n"
    "        the mass excess (default: None)\n"
    "    mass_excess_uncertainty : float, default None\n"
    "        the mass excess uncertainty (default: None)\n"
    "    binding_energy : float, default None\n"
    "        the binding energy per nucleon (default: None)\n"
    "    binding_energy_uncertainty : float, default None\n"
    "        the binding energy per nucleon uncertainty (default: None)\n"
    "    beta_decay_energy : float, default None\n"
    "        the beta decay energy (default: None)\n"
    "    beta_decay_energy_uncertainty : float, default None\n"
    "        the beta decay energy uncertainty (default: None)\n"
    "    mass : float, default None\n"
    "        the atomic mass (default: None)\n"
    "    mass_uncertainty : float, default None\n"
    "        the atomic mass uncertainty (default: None)"
  );

  // wrap the component
  component
  .def(

    python::init< ParticleID,
                  std::optional< double >,
                  std::optional< double >,
                  std::optional< double >,
                  std::optional< double >,
                  std::optional< double >,
                  std::optional< double >,
                  std::optional< double >,
                  std::optional< double > >(),
    python::arg( "id" ),
    python::arg( "mass_excess" ) = std::nullopt,
    python::arg( "mass_excess_uncertainty" ) = std::nullopt,
    python::arg( "binding_energy" ) = std::nullopt,
    python::arg( "binding_energy_uncertainty" ) = std::nullopt,
    python::arg( "beta_decay_energy" ) = std::nullopt,
    python::arg( "beta_decay_energy_uncertainty" ) = std::nullopt,
    python::arg( "mass" ) = std::nullopt,
    python::arg( "mass_uncertainty" ) = std::nullopt,
    "Initialise the mass entry information"
  )
  .def_property(

    "identifier",
    python::overload_cast<>( &Component::identifier, python::const_ ),
    python::overload_cast< ParticleID >( &Component::identifier ),
    "The particle identifier"
  )
  .def_property(

    "mass_excess",
    python::overload_cast<>( &Component::massExcess, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::massExcess ),
    "The mass excess"
  )
  .def_property(

    "mass_excess_uncertainty",
    python::overload_cast<>( &Component::massExcessUncertainty, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::massExcessUncertainty ),
    "The mass excess uncertainty"
  )
  .def_property(

    "binding_energy",
    python::overload_cast<>( &Component::bindingEnergy, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::bindingEnergy ),
    "The binding energy per nucleon"
  )
  .def_property(

    "binding_energy_uncertainty",
    python::overload_cast<>( &Component::bindingEnergyUncertainty, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::bindingEnergyUncertainty ),
    "The binding energy per nucleon uncertainty"
  )
  .def_property(

    "beta_decay_energy",
    python::overload_cast<>( &Component::betaDecayEnergy, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::betaDecayEnergy ),
    "The beta decay energy"
  )
  .def_property(

    "beta_decay_energy_uncertainty",
    python::overload_cast<>( &Component::betaDecayEnergyUncertainty, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::betaDecayEnergyUncertainty ),
    "The beta decay energy uncertainty"
  )
  .def_property(

    "atomic_mass",
    python::overload_cast<>( &Component::atomicMass, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::atomicMass ),
    "The atomic mass"
  )
  .def_property(

    "atomic_mass_uncertainty",
    python::overload_cast<>( &Component::atomicMassUncertainty, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::atomicMassUncertainty ),
    "The atomic mass uncertainty"
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // ame namespace
} // external namespace
} // dryad namespace
