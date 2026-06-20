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
    "This representation is only available for a photoatomic ProjectileTarget.\n\n"
    "In this representation, a scattering function S(x,Z) and two optional form factor\n"
    "functions are defined which together with the Thompson cross section determine the\n"
    "double differential cross section. The optional form factors are the real and\n"
    "complex part of the anomalous form factor. These are defined as optional because\n"
    "photoatomic MCNP data files produced in 2024 or earlier do not contain these form\n"
    "factors even though the photoatomic ENDF evaluations define them.\n\n"
    "This corresponds with the coherent scattering function data given in\n"
    "MF27 MT502 and the form factors in MF27 MT505 and MT506.\n\n"
    "Parameters\n"
    "----------\n"
    "    frame : njoy.dryad.ReferenceFrame\n"
    "         the reference frame of the distribution data\n"
    "    scattering : njoy.dryad.TabulatedScatteringFunction\n"
    "         the scattering function\n"
    "    real : njoy.dryad.TabulatedFormFactor\n"
    "         the real part of the anomalous form factor\n"
    "    imaginary : njoy.dryad.TabulatedFormFactor\n"
    "         the imaginary part of the anomalous form factor"
  );

  // wrap the component
  component
  .def(

    python::init< ReferenceFrame, TabulatedScatteringFunction >(),
    python::arg( "frame" ), python::arg( "scattering" ),
    "Initialise the coherent distribution data without anomalous form factors"
  )
  .def(

    python::init< ReferenceFrame, TabulatedScatteringFunction,
                  TabulatedFormFactor, TabulatedFormFactor >(),
    python::arg( "frame" ), python::arg( "scattering" ),
    python::arg( "real" ), python::arg( "imaginary" ),
    "Initialise the coherent distribution data with anomalous form factors"
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

    "has_anomalous_form_factor",
    &Component::hasAnomalousFormFactor,
    "Flag indicating whether or not the coherent distribution data has an anomalous\n"
    "form factor"
  )
  .def_property(

    "scattering_function",
    python::overload_cast<>( &Component::scatteringFunction, python::const_ ),
    python::overload_cast< TabulatedScatteringFunction >( &Component::scatteringFunction ),
    "The scattering function"
  )
  .def_property(

    "real_anomalous_form_factor",
    python::overload_cast<>( &Component::realAnomalousFormFactor, python::const_ ),
    python::overload_cast< std::optional< TabulatedFormFactor > >( &Component::realAnomalousFormFactor ),
    "The real part of the anomalous form factor"
  )
  .def_property(

    "imaginary_anomalous_form_factor",
    python::overload_cast<>( &Component::imaginaryAnomalousFormFactor, python::const_ ),
    python::overload_cast< std::optional< TabulatedFormFactor > >( &Component::imaginaryAnomalousFormFactor ),
    "The imaginary part of the anomalous form factor"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
