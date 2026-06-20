// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/dryad/DistributionDataType.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapDistributionDataType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::DistributionDataType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "DistributionDataType",
    "The distribution data type of a reaction product\n\n"
    "This enum is used to differentiate between the various distribution data\n"
    "types that are available for a reaction product.",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "TwoBody",      Component::TwoBody,
          "The distribution data is given as two body scattering" )
  .value( "Uncorrelated", Component::Uncorrelated,
          "The distribution data is uncorrelated" )
  .value( "Coherent",     Component::Coherent,
          "The distribution data is for coherent scattering for photoatomic interactions" )
  .value( "Incoherent",   Component::Incoherent,
          "The distribution data is for incoherent scattering for photoatomic interactions" );
}

} // dryad namespace
