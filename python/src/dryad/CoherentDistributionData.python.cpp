// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/CoherentDistributionData.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

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
    "the form factors in MF27 MT505 and MT506.\n\n"
    "Parameters \n"
    "---------- \n"
    "    frame : njoy.dryad.ReferenceFrame \n"
    "         the reference frame of the distribution data\n"
    "    scattering : njoy.dryad.TabulatedScatteringFunction \n"
    "         the scatteirng function \n"
    "    real : njoy.dryad.TabulatedFormFactor \n "
    "         the real part of the anamolous form factor\n"
    "    imaginary : njoy.dryad.TabulatedFormFactor \n"
    "         the imaginary part of the anamolous form factor\n"
  );

  // wrap the component
  component
  .def(

    python::init< ReferenceFrame, TabulatedScatteringFunction >(),
    python::arg( "frame" ), python::arg( "scattering" ),
    "Initialise the coherent distribution data without anomolous form factors\n\n"
  )
  .def(

    python::init< ReferenceFrame, TabulatedScatteringFunction,
                  TabulatedFormFactor, TabulatedFormFactor >(),
    python::arg( "frame" ), python::arg( "scattering" ),
    python::arg( "real" ), python::arg( "imaginary" ),
    "Initialise the coherent distribution data with anomolous form factors\n\n"
  )
  .def_property_readonly(

    // static constexpr function needs lambda
    "type",
    [] ( const Component& self ) -> decltype(auto)
       { return self.type(); },
    "The distribution data type"
  )
  .def_property(

    "frame",
    python::overload_cast<>( &Component::frame, python::const_ ),
    python::overload_cast< ReferenceFrame >( &Component::frame ),
    "The reference frame"
  )
  .def_property_readonly(

    "has_anomolous_form_factor",
    &Component::hasAnomolousFormFactor,
    "Flag indicating whether or not the coherent distribution data has an anomolous\n"
    "form factor"
  )
  .def_property(

    "scattering_function",
    python::overload_cast<>( &Component::scatteringFunction, python::const_ ),
    python::overload_cast< TabulatedScatteringFunction >( &Component::scatteringFunction ),
    "The scattering function"
  )
  .def_property(

    "real_anomolous_form_factor",
    python::overload_cast<>( &Component::realAnomolousFormFactor, python::const_ ),
    python::overload_cast< std::optional< TabulatedFormFactor > >( &Component::realAnomolousFormFactor ),
    "The real part of the anomolous form factor"
  )
  .def_property(

    "imaginary_anomolous_form_factor",
    python::overload_cast<>( &Component::imaginaryAnomolousFormFactor, python::const_ ),
    python::overload_cast< std::optional< TabulatedFormFactor > >( &Component::imaginaryAnomolousFormFactor ),
    "The imaginary part of the anomolous form factor"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
