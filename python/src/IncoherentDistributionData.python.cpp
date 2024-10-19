// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/IncoherentDistributionData.hpp"

// namespace aliases
namespace python = pybind11;

void wrapIncoherentDistributionData( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::IncoherentDistributionData;
  using ReferenceFrame = njoy::dryad::ReferenceFrame;
  using TabulatedScatteringFunction = njoy::dryad::TabulatedScatteringFunction;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "IncoherentDistributionData",
    "The distribution data for incoherent scattering in photoatomic interactions\n\n"
    "This representation is only available for a photoatomic ProjectileTarget.\n\n"
    "In this representation, a scattering function S(x,Z) is defined that\n"
    "together with the Klein-Nishina cross section determines the double\n"
    "differential cross section.\n\n"
    "This corresponds with the incoherent scattering function data given in MF27 MT504."
  );

  // wrap the component
  component
  .def(

    python::init< ReferenceFrame, TabulatedScatteringFunction >(),
    python::arg( "frame" ), python::arg( "scattering" ),
    "Initialise the incoherent distribution data\n\n"
    "Arguments:\n"
    "    self         the reaction product distribution data\n"
    "    frame        the reference frame of the distribution data\n"
    "    scattering   the scattering function"
  )
  .def_property_readonly(

    // static constexpr function needs lambda
    "type",
    [] ( const Component& self ) { return self.type(); },
    "The distribution data type"
  )
  .def_property_readonly(

    "frame",
    &Component::frame,
    "The reference frame"
  )
  .def_property_readonly(

    "scattering_function",
    &Component::scatteringFunction,
    "The scattering function"
  );
}
