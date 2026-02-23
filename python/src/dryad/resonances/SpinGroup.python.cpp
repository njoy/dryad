// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapSpinGroup( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::SpinGroup;
  using ChannelData = njoy::dryad::resonances::SpinGroup::ChannelData;
  using Channel = njoy::dryad::resonances::Channel;
  using ResonanceTable = njoy::dryad::resonances::ResonanceTable;
  using Formalism = njoy::dryad::resonances::Formalism;
  using BoundaryCondition = njoy::dryad::resonances::BoundaryCondition;
  using ReactionID = njoy::dryad::id::ReactionID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "SpinGroup",
    "A spin group corresponding to a Jpi quantum number set"
   );

  // wrap the component
  component
  .def(

    python::init< std::vector< Channel >, ResonanceTable,
                  Formalism, BoundaryCondition >(),
    python::arg( "channels" ), python::arg( "resonances" ),
    python::arg( "formalism" ), python::arg( "boundary" ),
    "Initialise the spin group\n\n"
    "If the channels are not sorted, they will get sorted through the order\n"
    "of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical\n"
    "sorting order).\n\n"
    "Arguments:\n"
    "    self         the spin group\n"
    "    channels     the channels in the spin group\n"
    "    resonances   the resonance table of the spin group\n"
    "    formalism    the r matrix formalism option to be applied\n"
    "    boundary     the boundary condition option to be applied"
  )
  .def(

    python::init< std::vector< ChannelData >,
                  Formalism, BoundaryCondition >(),
    python::arg( "channels" ),
    python::arg( "formalism" ),
    python::arg( "boundary" ),
    "Initialise the spin group\n\n"
    "If the channels are not sorted, they will get sorted through the order\n"
    "of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical\n"
    "sorting order).\n\n"
    "Arguments:\n"
    "    self       the spin group\n"
    "    channels   the channel data in the spin group\n"
    "    formalism    the r matrix formalism option to be applied\n"
    "    boundary     the boundary condition option to be applied"
  )
  .def_property(

    "channels",
    python::overload_cast<>( &Component::channels, python::const_ ),
    python::overload_cast< std::vector< Channel > >( &Component::channels ),
    "The channels in the spin group"
  )
  .def_property(

    "resonance_table",
    python::overload_cast<>( &Component::resonanceTable, python::const_ ),
    python::overload_cast< ResonanceTable >( &Component::resonanceTable ),
    "The resonance table of the spin group"
  )
  .def_property_readonly(

    "formalism",
    python::overload_cast<>( &Component::formalism, python::const_ ),
    "The formalism"
  )
  .def_property_readonly(

    "boundary_condition",
    python::overload_cast<>( &Component::boundaryCondition, python::const_ ),
    "The boundary condition option"
  )
  .def_property_readonly(

    "total_angular_momentum",
    &Component::totalAngularMomentum,
    "The total angular momentum J of the channels"
  )
  .def_property_readonly(

    "parity",
    &Component::parity,
    "The parity"
  )
  .def_property_readonly(

    "reactions",
    python::overload_cast<>( &Component::reactions, python::const_ ),
    "The reactions to which this spin group contributes"
  )
  .def(

    "cross_sections",
    [] ( Component& self, double energy ) -> std::map< ReactionID, double > {

      std::map< ReactionID, double > xs;
      self.crossSections( energy, xs );
      return xs;
    },
    python::arg( "energy" ),
    "Calculate the cross section values at a given energy\n\n"
    "Arguments:\n"
    "    self     the spin group\n"
    "    energy   the energy"
  )
  .def(

    "cross_sections",
    [] ( Component& self, std::vector<double> energies ) -> std::map< ReactionID, std::vector<double> > {

      std::map< ReactionID, std::vector<double> > xs;
      self.crossSections( energies, xs );
      return xs;
    },
    python::arg( "energies" ),
    "Calculate the cross section values for a list of energies\n\n"
    "Arguments:\n"
    "    self      the spin group\n"
    "    energies  the list of energies"
  )
  .def(

    "r_l_matrix",
    &Component::r_l_matrix,
    python::arg( "energy" ),
    "Calculate the R_L matrix at a given energy\n\n"
    "The R_L matrix is defined as ( 1 - RL )^-1 R in which R is the\n"
    "R matrix and L is a diagonal matrix defined as S - B + iP with\n"
    "S the shift factor and B the boundary condition of the channel.\n\n"
    "Arguments:\n"
    "    self     the spin group\n"
    "    energy   the energy"
  )
  .def(

    "t_matrix",
    &Component::t_matrix,
    python::arg( "energy" ),
    "Calculate the T or X matrix at a given energy\n\n"
    "The T or X matrix is defined as P^1/2 ( 1 - RL )^-1 R P^1/2 in which\n"
    "P is a diagonal matrix of the penetrabilities of each channel, R is the\n"
    "R matrix and L is a diagonal matrix defined as S - B + iP with S the shift\n"
    "factor and B the boundary condition of the channel.\n\n"
    "Arguments:\n"
    "    self     the spin group\n"
    "    energy   the energy"
  )
  .def(

    "w_matrix",
    &Component::w_matrix,
    python::arg( "energy" ),
    "Calculate the W matrix at a given energy\n\n"
    "The W matrix is defined as I + 2 i P^1/2 ( 1 - RL )^-1 R P^1/2 in which\n"
    "I is the identity matrix, P is a diagonal matrix of the penetrabilities of\n"
    "each channel, R is the R matrix and L is a diagonal matrix defined as\n"
    "S - B + iP with S the shift factor and B the boundary condition of the\n"
    "channel.\n\n"
    "Arguments:\n"
    "    self     the spin group\n"
    "    energy   the energy"
  )
  .def(

    "u_matrix",
    &Component::u_matrix,
    python::arg( "energy" ),
    "Calculate the U or S matrix at a given energy\n\n"
    "The U or S matrix is defined as omega W omega in which omega is a diagonal\n"
    "matrix equal to exp( i ( w - phi ) ) with w the Coulomb phase shift difference\n"
    "and phi the phase shift.\n\n"
    "Arguments:\n"
    "    self     the spin group\n"
    "    energy   the energy"
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
