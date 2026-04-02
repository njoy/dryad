// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/Particle.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapParticle( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::Particle;
  using ParticleID = njoy::dryad::id::ParticleID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Particle",
    "Particle information\n\n"
    "The Particle class contains specific information for a particle:\n"
    "  - the atomic mass value (always for the ground state) and an optional\n"
    "    uncertainty\n"
    "  - the excited state energy value and an optional uncertainty\n"
    "  - the spin and parity (which is either + or -)\n\n"
    "The data is stored in the following units:\n"
    "  - atomic mass values are in atomic mass units\n"
    "  - energy values are in eV\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ParticleID\n"
    "         the particle identifier\n"
    "    mass : float\n"
    "        the atomic mass\n"
    "    spin : float\n"
    "        the particle spin\n"
    "    parity : int\n"
    "        the particle spin parity\n"
    "    energy : float, default 0\n"
    "        the excited state energy (default: 0)\n"
    "    mass_uncertainty : float, default None\n"
    "        the uncertainty on the atomic mass value (default: None)\n"
    "    energy_uncertainty : float, default None\n"
    "        the uncertainty on the ecited level energy value (default: None)"
  );

  // wrap the component
  component
  .def(

    python::init< ParticleID, double, double, short,
                  double, std::optional< double >,
                  std::optional< double > >(),
    python::arg( "id" ), python::arg( "mass" ),
    python::arg( "spin" ), python::arg( "parity" ),
    python::arg( "energy" ) = 0.,
    python::arg( "mass_uncertainty" ) = std::nullopt,
    python::arg( "energy_uncertainty" ) = std::nullopt,
    "Initialise the particle information"
  )
  .def_property(

    "identifier",
    python::overload_cast<>( &Component::identifier, python::const_ ),
    python::overload_cast< ParticleID >( &Component::identifier ),
    "The particle identifier"
  )
  .def_property_readonly(

    "charge",
    &Component::charge,
    "The electrical charge of the particle"
  )
  .def_property_readonly(

    "excited_state",
    &Component::excitedState,
    "The excited state number of the particle"
  )
  .def_property(

    "mass",
    python::overload_cast<>( &Component::mass, python::const_ ),
    python::overload_cast< double >( &Component::mass ),
    "The atomic mass of the particle in the ground state"
  )
  .def_property(

    "energy",
    python::overload_cast<>( &Component::energy, python::const_ ),
    python::overload_cast< double >( &Component::energy ),
    "The excited state energy value of the particle"
  )
  .def_property(

    "spin",
    python::overload_cast<>( &Component::spin, python::const_ ),
    python::overload_cast< double >( &Component::spin ),
    "The spin of the particle"
  )
  .def_property(

    "parity",
    python::overload_cast<>( &Component::parity, python::const_ ),
    python::overload_cast< short >( &Component::parity ),
    "The particle spin parity"
  )
  .def_property(

    "mass_uncertainty",
    python::overload_cast<>( &Component::massUncertainty, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::massUncertainty ),
    "The atomic mass uncertainty"
  )
  .def_property(

    "energy_uncertainty",
    python::overload_cast<>( &Component::energyUncertainty, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::energyUncertainty ),
    "The excited state energy uncertainty"
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
