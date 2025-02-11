// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/DistributionDataType.hpp"

// namespace aliases
namespace python = pybind11;

void wrapDistributionDataType( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::DistributionDataType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "DistributionDataType",
    "The distribution data type for a reaction product",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "TwoBody",      Component::TwoBody )
  .value( "Uncorrelated", Component::Uncorrelated )
  .value( "Coherent",     Component::Coherent )
  .value( "Incoherent",   Component::Incoherent );
}
