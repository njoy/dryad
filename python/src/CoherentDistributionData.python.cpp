// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/CoherentDistributionData.hpp"

// namespace aliases
namespace python = pybind11;

void wrapCoherentDistributionData( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::CoherentDistributionData;
  using ReferenceFrame = njoy::dryad::ReferenceFrame;
  using TabulatedFormFactor = njoy::dryad::TabulatedFormFactor;
  using TabulatedScatteringFunction = njoy::dryad::TabulatedScatteringFunction;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CoherentDistributionData",
    "The distribution data for coherent scattering in photoatomic interactions\n\n"
    "In this representation, a scattering function S(x,Z) and two optional form factor\n"
    "functions are defined which together with the Thompson cross section determine the\n"
    "double differential cross section.\n\n"
    "This corresponds with the coherent scattering function data given in MF27 MT502 and\n"
    "the form factors in MF27 MT505 and MT506."
  );

  // wrap the component
  component
  .def(

    python::init< ReferenceFrame, TabulatedScatteringFunction >(),
    python::arg( "frame" ), python::arg( "scattering" ),
    "Initialise the coherent distribution data without anomolous form factors\n\n"
    "Arguments:\n"
    "    self         the reaction product distribution data\n"
    "    frame        the reference frame of the distribution data\n"
    "    scattering   the scattering function"
  )
  .def(

    python::init< ReferenceFrame, TabulatedScatteringFunction,
                  TabulatedFormFactor, TabulatedFormFactor >(),
    python::arg( "frame" ), python::arg( "scattering" ),
    python::arg( "real" ), python::arg( "imaginary" ),
    "Initialise the coherent distribution data with anomolous form factors\n\n"
    "Arguments:\n"
    "    self         the reaction product distribution data\n"
    "    frame        the reference frame of the distribution data\n"
    "    scattering   the scattering function\n"
    "    real         the real part of the anamolous form factor\n"
    "    imaginary    the imaginary part of the anamolous form factor"
  )
  .def_property_readonly(

    // static constexpr function needs lambda
    "type",
    [] ( const Component& self ) -> decltype(auto)
       { return self.type(); },
    "The distribution data type"
  )
  .def_property_readonly(

    "frame",
    &Component::frame,
    "The reference frame"
  )
  .def_property_readonly(

    "has_anomolous_form_factor",
    &Component::hasAnomolousFormFactor,
    "Flag indicating whether or not the coherent distribution data has an anomolous\n"
    "form factor"
  )
  .def_property_readonly(

    "scattering_function",
    &Component::scatteringFunction,
    "The scattering function"
  )
  .def_property_readonly(

    "real_anomolous_form_factor",
    &Component::realAnomolousFormFactor,
    "The real part of the anomolous form factor"
  )
  .def_property_readonly(

    "imaginary_anomolous_form_factor",
    &Component::imaginaryAnomolousFormFactor,
    "The imaginary part of the anomolous form factor"
  );
}
