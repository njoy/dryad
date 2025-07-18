// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/AtomicRelaxation.hpp"
#include "dryad/format/endf/createAtomicRelaxationFromFile.hpp"
#include "dryad/format/gnds/createAtomicRelaxationFromFile.hpp"

// namespace aliases
namespace python = pybind11;

void wrapAtomicRelaxation( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::AtomicRelaxation;
  using ElementID = njoy::dryad::id::ElementID;
  using ElectronSubshellConfiguration = njoy::dryad::atomic::ElectronSubshellConfiguration;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "AtomicRelaxation",
    "Atomic relaxation data for a given element"
  );

  // wrap the component
  component
  .def(

    python::init< ElementID, std::vector< ElectronSubshellConfiguration > >(),
    python::arg( "element" ), python::arg( "subshells" ),
    "Initialise the atomic relaxation data\n\n"
    "Arguments:\n"
    "    self         the reaction\n"
    "    element      the element identifier\n"
    "    subshells    the electron subshell configuration data"
  )
  .def_property_readonly(

    "element_identifier",
    &Component::elementIdentifier,
    "The element identifier"
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
    "Return whether or not a subshell is present\n\n"
    "Arguments:\n"
    "    self   the AtomicRelaxation data\n"
    "    id     the electron subshell identifier"
  )
  .def(

    "subshell",
    &Component::subshell,
    "Return the requested subshell\n\n"
    "Arguments:\n"
    "    self   the AtomicRelaxation data\n"
    "    id     the electron subshell identifier",
    python::return_value_policy::reference_internal
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the transition probabilities"
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
    "Arguments:\n"
    "    filename    the ENDF file name\n"
    "    normalise   option to indicate whether or not to normalise\n"
    "                all probability data (default: no normalisation)"
  )
  .def_static(

    "from_gnds_file",
    [] ( const std::string& filename, bool normalise = false ) -> decltype(auto) {

      return njoy::dryad::format::gnds::createAtomicRelaxationFromFile( filename, normalise );
    },
    python::arg( "filename" ), python::arg( "normalise" ) = false,
    "Create AtomicRelaxation data from a GNDS file\n\n"
    "Arguments:\n"
    "    filename    the GNDS file name\n"
    "    normalise   option to indicate whether or not to normalise\n"
    "                all probability data (default: no normalisation)"
  );
}
