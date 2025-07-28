// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/Metadata.hpp"

// namespace aliases
namespace python = pybind11;

void wrapMetadata( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::Metadata;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Metadata",
    "Metadata associated to the dryad data"
   );

  // wrap the component
  component
  .def(

    python::init< std::optional< double >,
                  std::optional< int >,
                  std::optional< std::pair< int, int > >,
                  std::optional< double >,
                  std::optional< std::string > >(),
    python::arg( "awr" ), python::arg( "library" ),
    python::arg( "version" ), python::arg( "temperature" ),
    python::arg( "description" ),
    "Initialise the metadata\n\n"
    "Arguments:\n"
    "    self          the metadata\n"
    "    awr           the atomic weight ratio\n"
    "    library       the library number\n"
    "    version       the version number\n"
    "    temperature   the temperature\n"
    "    description   the description"
  )
  .def_property(

    "awr",
    python::overload_cast<>( &Component::awr, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::awr ),
    "The atomic weight ratio"
  )
  .def_property(

    "library",
    python::overload_cast<>( &Component::library, python::const_ ),
    python::overload_cast< std::optional< int > >( &Component::library ),
    "The library"
  )
  .def_property(

    "version",
    python::overload_cast<>( &Component::version, python::const_ ),
    python::overload_cast< std::optional< std::pair< int, int > > >( &Component::version ),
    "The version"
  )
  .def_property(

    "temperature",
    python::overload_cast<>( &Component::temperature, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::temperature ),
    "The temperature"
  )
  .def_property(

    "description",
    python::overload_cast<>( &Component::description, python::const_ ),
    python::overload_cast< std::optional< std::string > >( &Component::description ),
    "The description"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}
