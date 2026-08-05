// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/format/gnds/StyleType.hpp"

// namespace aliases
namespace python = pybind11;

namespace format {
namespace gnds {

void wrapStyleType( python::module& module ) {

  // type aliases
  using Component = njoy::format::gnds::StyleType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "StyleType",
    "The style type of a GNDS file",
    python::arithmetic()
  );

  // wrap the component
  component
  .value(

    "Evaluation",
    Component::Evaluation,
    "The style type is evaluation"
  );
}

} // format namespace
} // gnds namespace
