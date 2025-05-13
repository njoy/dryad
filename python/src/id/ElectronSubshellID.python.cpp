// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "definitions.hpp"
#include "dryad/id/ElectronSubshellID.hpp"

// namespace aliases
namespace python = pybind11;

namespace id {

void wrapElectronSubshellID( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::id::ElectronSubshellID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ElectronSubshellID",
    "The electron subshell identifier\n\n"
    "For more information on how to create instances of ElectronSubshellID, see the\n"
    "Jupyter notebook dryad-identifiers.ipynb under python/examples.\n"
  );

  // wrap the component
  component
  .def(

    python::init< int >(),
    python::arg( "number" ),
    "Initialise the subshell identifier\n\n"
    "Arguments:\n"
    "    self     the identifier\n"
    "    number   the subshell number"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "string" ),
    "Initialise the subshell identifier\n\n"
    "Arguments:\n"
    "    self     the identifier\n"
    "    string   the subshell symbol, name or alternative name"
  )
  .def_property_readonly_static( "K"  ,  [] ( python::object ) { return Component::K;   }, "The K shell" )
  .def_property_readonly_static( "L1" ,  [] ( python::object ) { return Component::L1;  }, "The L1 shell" )
  .def_property_readonly_static( "L2" ,  [] ( python::object ) { return Component::L2;  }, "The L2 shell" )
  .def_property_readonly_static( "L3" ,  [] ( python::object ) { return Component::L3;  }, "The L3 shell" )
  .def_property_readonly_static( "M1" ,  [] ( python::object ) { return Component::M1;  }, "The M1 shell" )
  .def_property_readonly_static( "M2" ,  [] ( python::object ) { return Component::M2;  }, "The M2 shell" )
  .def_property_readonly_static( "M3" ,  [] ( python::object ) { return Component::M3;  }, "The M3 shell" )
  .def_property_readonly_static( "M4" ,  [] ( python::object ) { return Component::M4;  }, "The M4 shell" )
  .def_property_readonly_static( "M5" ,  [] ( python::object ) { return Component::M5;  }, "The M5 shell" )
  .def_property_readonly_static( "N1" ,  [] ( python::object ) { return Component::N1;  }, "The N1 shell" )
  .def_property_readonly_static( "N2" ,  [] ( python::object ) { return Component::N2;  }, "The N2 shell" )
  .def_property_readonly_static( "N3" ,  [] ( python::object ) { return Component::N3;  }, "The N3 shell" )
  .def_property_readonly_static( "N4" ,  [] ( python::object ) { return Component::N4;  }, "The N4 shell" )
  .def_property_readonly_static( "N5" ,  [] ( python::object ) { return Component::N5;  }, "The N5 shell" )
  .def_property_readonly_static( "N6" ,  [] ( python::object ) { return Component::N6;  }, "The N6 shell" )
  .def_property_readonly_static( "N7" ,  [] ( python::object ) { return Component::N7;  }, "The N7 shell" )
  .def_property_readonly_static( "O1" ,  [] ( python::object ) { return Component::O1;  }, "The O1 shell" )
  .def_property_readonly_static( "O2" ,  [] ( python::object ) { return Component::O2;  }, "The O2 shell" )
  .def_property_readonly_static( "O3" ,  [] ( python::object ) { return Component::O3;  }, "The O3 shell" )
  .def_property_readonly_static( "O4" ,  [] ( python::object ) { return Component::O4;  }, "The O4 shell" )
  .def_property_readonly_static( "O5" ,  [] ( python::object ) { return Component::O5;  }, "The O5 shell" )
  .def_property_readonly_static( "O6" ,  [] ( python::object ) { return Component::O6;  }, "The O6 shell" )
  .def_property_readonly_static( "O7" ,  [] ( python::object ) { return Component::O7;  }, "The O7 shell" )
  .def_property_readonly_static( "O8" ,  [] ( python::object ) { return Component::O8;  }, "The O8 shell" )
  .def_property_readonly_static( "O9" ,  [] ( python::object ) { return Component::O9;  }, "The O9 shell" )
  .def_property_readonly_static( "P1" ,  [] ( python::object ) { return Component::P1;  }, "The P1 shell" )
  .def_property_readonly_static( "P2" ,  [] ( python::object ) { return Component::P2;  }, "The P2 shell" )
  .def_property_readonly_static( "P3" ,  [] ( python::object ) { return Component::P3;  }, "The P3 shell" )
  .def_property_readonly_static( "P4" ,  [] ( python::object ) { return Component::P4;  }, "The P4 shell" )
  .def_property_readonly_static( "P5" ,  [] ( python::object ) { return Component::P5;  }, "The P5 shell" )
  .def_property_readonly_static( "P6" ,  [] ( python::object ) { return Component::P6;  }, "The P6 shell" )
  .def_property_readonly_static( "P7" ,  [] ( python::object ) { return Component::P7;  }, "The P7 shell" )
  .def_property_readonly_static( "P8" ,  [] ( python::object ) { return Component::P8;  }, "The P8 shell" )
  .def_property_readonly_static( "P9" ,  [] ( python::object ) { return Component::P9;  }, "The P9 shell" )
  .def_property_readonly_static( "P10",  [] ( python::object ) { return Component::P10; }, "The P10 shell" )
  .def_property_readonly_static( "P11",  [] ( python::object ) { return Component::P11; }, "The P11 shell" )
  .def_property_readonly_static( "Q1" ,  [] ( python::object ) { return Component::Q1;  }, "The Q1 shell" )
  .def_property_readonly_static( "Q2" ,  [] ( python::object ) { return Component::Q2;  }, "The Q2 shell" )
  .def_property_readonly_static( "Q3" ,  [] ( python::object ) { return Component::Q3;  }, "The Q3 shell" )
  .def_property_readonly_static( "Q4" ,  [] ( python::object ) { return Component::Q4;  }, "The Q4 shell" )
  .def_property_readonly_static( "Q5" ,  [] ( python::object ) { return Component::Q5;  }, "The Q5 shell" )
  .def_property_readonly_static( "Q6" ,  [] ( python::object ) { return Component::Q6;  }, "The Q6 shell" )
  .def_property_readonly_static( "Q7" ,  [] ( python::object ) { return Component::Q7;  }, "The Q7 shell" )
  .def_property_readonly_static( "Q8" ,  [] ( python::object ) { return Component::Q8;  }, "The Q8 shell" )
  .def_property_readonly_static( "Q9" ,  [] ( python::object ) { return Component::Q9;  }, "The Q9 shell" )
  .def_property_readonly_static( "Q10",  [] ( python::object ) { return Component::Q10; }, "The Q10 shell" )
  .def_property_readonly_static( "Q11",  [] ( python::object ) { return Component::Q11; }, "The Q11 shell" )
  .def_property_readonly(

    "number",
    &Component::number,
    "The subshell number"
  )
  .def_property_readonly(

    "symbol",
    &Component::symbol,
    "The subshell symbol"
  )
  .def_property_readonly(

    "name",
    &Component::name,
    "The subshell name"
  )
  .def(

    "__hash__",
    [] ( const Component& self ) { return self.number(); },
    "Hash function"
  );

  // add standard comparison definitions
  addStandardComparisonDefinitions< Component >( component );

  // add standard print definitions
  addStandardPrintDefinitions< Component >( component );
}

} // namespace id