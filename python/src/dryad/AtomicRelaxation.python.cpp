// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "njoy/dryad/format/endf/createAtomicRelaxationFromFile.hpp"
#include "njoy/dryad/format/endf/createAtomicRelaxationEndfFile.hpp"
#include "njoy/dryad/format/gnds/createAtomicRelaxationFromFile.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapAtomicRelaxation( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::AtomicRelaxation;
  using Documentation = njoy::dryad::Documentation;
  using ElementID = njoy::dryad::id::ElementID;
  using ElectronSubshellConfiguration = njoy::dryad::atomic::ElectronSubshellConfiguration;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "AtomicRelaxation",
    "Atomic relaxation data for a given element\n\n"
    "Parameters\n"
    "----------\n"
    "    documentation : njoy.dryad.Documentation \n"
    "         the documentation \n"
    "    element : njoy.dryad.id.ElementID \n"
    "         the element identifier \n"
    "    subshells : list of njoy.dryad.atomic.ElectronSubshellConfiguration \n"
    "         the electron subshell configuration data \n"
    "    normalise : bool, default false \n"
    "        option to indicate whether or not to normalise \n"
    "        all probability data (default: no normalisation) \n\n"
  );

  // wrap the component
  component
  .def(

    python::init< Documentation, ElementID, std::vector< ElectronSubshellConfiguration >, bool >(),
    python::arg( "documentation" ), python::arg( "element" ),
    python::arg( "subshells" ), python::arg( "normalise" ) = false,
    "Initialise the atomic relaxation data with documentation\n"
  )
  .def(

    python::init< ElementID, std::vector< ElectronSubshellConfiguration >, bool >(),
    python::arg( "element" ), python::arg( "subshells" ),
    python::arg( "normalise" ) = false,
    "Initialise the atomic relaxation data without documentation\n"
  )
  .def_property(

    "documentation",
    python::overload_cast<>( &Component::documentation, python::const_ ),
    python::overload_cast< Documentation >( &Component::documentation ),
    "The documentation"
  )
  .def_property(

    "element_identifier",
    python::overload_cast<>( &Component::elementIdentifier, python::const_ ),
    python::overload_cast< ElementID >( &Component::elementIdentifier ),
    "The element identifier"
  )
  .def_property_readonly(

    "number_subshells",
    &Component::numberSubshells,
    "The number of subshells defined for this atom"
  )
  .def_property(

    "subshells",
    python::overload_cast<>( &Component::subshells, python::const_ ),
    python::overload_cast< std::vector< ElectronSubshellConfiguration > >( &Component::subshells ),
    "The electron shell configuration data"
  )
  .def(

    "has_subshell",
    &Component::hasSubshell,
    python::arg( "identifier" ),
    "Return whether or not a subshell is present \n\n"
    "Parameters\n"
    "----------\n"
    "    identifier : njoy.dryad.id.ElectronSubshellID \n"
    "         the electron subshell identifier \n"
  )
  .def(

    "subshell",
    &Component::subshell,
    python::arg( "identifier" ),
    "Return the requested subshell \n\n"
    "Parameters\n"
    "----------\n"
    "    identifier : njoy.dryad.id.ElectronSubshellID \n"
    "         the electron subshell identifier \n",
    python::return_value_policy::reference_internal
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the transition probabilities"
  )
  .def(

    "calculate_transition_energies",
    &Component::calculateTransitionEnergies,
    "Calculate the transition energies for all transitions"
  )
  .def_static(

    "from_endf_file",
    [] ( const std::string& filename, bool normalise = false ) -> decltype(auto) {

      return njoy::dryad::format::endf::createAtomicRelaxationFromFile( filename, normalise );
    },
    python::arg( "filename" ), python::arg( "normalise" ) = false,
    "Create AtomicRelaxation data from an ENDF file\n\n"
    "If there are multiple materials in the ENDF file, only the first material\n"
    "will be transformed into a AtomicRelaxation.\n\n"
    "Parameters\n"
    "----------\n"
    "    filename : str \n"
    "         the ENDF file name\n"
    "    normalise : bool, default false \n"
    "         option to indicate whether or not to normalise\n"
    "         all probability data (default: no normalisation)\n\n"
  )
  .def_static(

    "from_gnds_file",
    [] ( const std::string& filename, bool normalise = false ) -> decltype(auto) {

      return njoy::dryad::format::gnds::createAtomicRelaxationFromFile( filename, normalise );
    },
    python::arg( "filename" ), python::arg( "normalise" ) = false,
    "Create AtomicRelaxation data from a GNDS file\n\n"
    "Parameters \n"
    "---------- \n"
    "    filename : str \n"
    "         the GNDS file name\n"
    "    normalise : bool, default false \n"
    "         option to indicate whether or not to normalise\n"
    "         all probability data (default: no normalisation)\n\n"
  )
  .def(

    "to_endf_file",
    [] ( const Component& self, int mat, const std::string& filename ) {

      njoy::dryad::format::endf::createAtomicRelaxationEndfFile( self, mat, filename );
    },
    python::arg( "mat" ), python::arg( "filename" ),
    "Write the AtomicRelaxation data to an ENDF file\n\n"
    "Parameters\n"
    "----------\n"
    "    mat : int \n"
    "         the ENDF mat number to be used \n"
    "    filename : str \n"
    "         the ENDF file name \n"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
