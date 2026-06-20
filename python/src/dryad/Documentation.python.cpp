// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/Documentation.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapDocumentation( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::Documentation;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Documentation",
    "Documentation associated to the dryad data\n\n"
    "Parameters\n"
    "----------\n"
    "    library : int, optional\n"
    "         the library number\n"
    "    version : tuple of int, optional\n"
    "         the version numbers (major and minor)\n"
    "    description : str, optional\n"
    "         the description"
   );

  // wrap the component
  component
  .def(

    python::init<>(),
    "Initialise the documentation with default values"
  )
  .def(

    python::init< std::optional< int >,
                  std::optional< std::pair< int, int > >,
                  std::optional< std::string > >(),
    python::arg( "library" ) = std::nullopt,
    python::arg( "version" ) = std::nullopt,
    python::arg( "description" ) = std::nullopt,
    "Initialise the documentation"
  )
  .def_property(

    "library",
    python::overload_cast<>( &Component::library, python::const_ ),
    python::overload_cast< std::optional< int > >( &Component::library ),
    "The library number"
  )
  .def_property(

    "version",
    python::overload_cast<>( &Component::version, python::const_ ),
    python::overload_cast< std::optional< std::pair< int, int > > >( &Component::version ),
    "The version numbers (major and minor)"
  )
  .def_property(

    "description",
    python::overload_cast<>( &Component::description, python::const_ ),
    python::overload_cast< std::optional< std::string > >( &Component::description ),
    "The description"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
