// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/ParticlePair.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapParticlePair( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::ParticlePair;
  using Particle = njoy::dryad::resonances::Particle;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ParticlePair",
    "Particle information for resonance reconstruction\n\n"
    "A ParticlePair represents the two particles involved in a entrance or exit\n"
    "reaction channel (we assume that the reaction is a two-body reaction). The\n"
    "pair consists of a \"light\" incident or outgoing particle (e.g. a neutron,\n"
    "photon, alpha, etc.) and a \"heavy\" target or residual nucleus (e.g. H1,\n"
    "He4, U235, etc.).\n\n"
    "The ParticlePair class gives us access to information related to the\n"
    "pair of particles such as the mass ratio and the reduced mass."
   );

  // wrap the component
  component
  .def(

    python::init< Particle, Particle >(),
    python::arg( "light_particle" ), python::arg( "heavy_particle" ),
    "Initialise the particle pair information\n\n"
    "Arguments:\n"
    "    self             the particle pair information\n"
    "    light_particle   the light particle\n"
    "    heavy_particle   the heavy particle"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "light_particle",
    &Component::lightParticle,
    "The light particle in the particle pair"
  )
  .def_property_readonly(

    "heavy_particle",
    &Component::heavyParticle,
    "The heavy particle in the particle pair"
  )
  .def_property_readonly(

    "reduced_mass",
    &Component::reducedMass,
    "The reduced mass of the particle pair (in atomic mass units)\n\n"
    "The reduced mass mu of the two particles is defined as follows:\n"
    "   mu = ma * mb / ( ma + mb )\n"
    "in which ma and mb are the atomic mass values of the particles in the\n"
    "particle pair."
  )
  .def_property_readonly(

    "mass_ratio",
    &Component::massRatio,
    "The mass ratio of the particle pair (dimensionless)\n\n"
    "The mass ratio of the two particles is defined as follows:\n"
    "   ratio = mb / ( ma + mb )\n"
    "in which ma and mb are the atomic mass values of the particles\n"
    "in the particle pair."
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
