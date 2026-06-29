// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/thermal/TabulatedScatteringKernel.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapTabulatedScatteringKernel( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::thermal::TabulatedScatteringKernel;
  using TabulatedScatteringKernelFunction = njoy::dryad::thermal::TabulatedScatteringKernelFunction;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedScatteringKernel",
    "An S(a,b) scattering kernel using tabulated scattering kernel functions\n\n"
    "Parameters\n"
    "----------\n"
    "    moderator_temperature : float\n"
    "        the moderator temperature\n"
    "    effective_temperature : float\n"
    "        the effective temperature used in the SCT approximation\n"
    "    energy_transfers : list of float\n"
    "        the energy transfer values\n"
    "    functions : list of njoy.dryad.thermal.TabulatedScatteringKernelFunction\n"
    "        the tabulated S(a) scattering functions\n"
    "    boundaries : list of int\n"
    "        the boundaries of the interpolation regions\n"
    "    interpolants : list of njoy.dryad.InterpolationType\n"
    "        the interpolation types of the interpolation regions\n"
    "    interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear\n"
    "        the interpolation type (default lin-lin)"
  );

  // wrap the component
  component
  .def(

    python::init< double, double,
                  std::vector< double >,
                  std::vector< TabulatedScatteringKernelFunction >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "moderator_temperature" ), python::arg( "effective_temperature" ),
    python::arg( "energy_transfers" ), python::arg( "functions" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the S(a,b) scattering kernel with multiple interpolation zones"
  )
  .def(

    python::init< double, double,
                  std::vector< double >,
                  std::vector< TabulatedScatteringKernelFunction >,
                  InterpolationType >(),
    python::arg( "moderator_temperature" ), python::arg( "effective_temperature" ),
    python::arg( "energy_transfers" ), python::arg( "functions" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the S(a,b) scattering kernel with a single interpolation zone"
  )
  .def_property_readonly(

    "moderator_temperature",
    &Component::moderatorTemperature,
    "The moderator temperature"
  )
  .def_property_readonly(

    "effective_temperature",
    &Component::effectiveTemperature,
    "The effective temperature used for the short collision time approximation"
  )
  .def_property_readonly(

    "energy_transfers",
    [] ( const Component& self ) -> decltype(auto)
       { return self.energyTransfers(); },
    "The energy transfer values for which scattering functions are given"
  )
  .def_property_readonly(

    "functions",
    [] ( const Component& self ) -> decltype(auto)
       { return self.functions(); },
    "The associated scattering functions"
  )
  .def(

    "__call__",
    [] ( const Component& self, double b, double a ) -> decltype(auto)
       { return self( b, a ); },
    python::arg( "value" ), python::arg( "cosine" ),
    "Evaluate the S(a,b) scattering kernel for a given energy and momentum transfer value\n\n"
    "Parameters\n"
    "----------\n"
    "    b : float\n"
    "        the energy transfer value\n"
    "    a : float\n"
    "        the momentum transfer value"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    "Linearise the S(a,b) scattering kernel\n\n"
    "Parameters\n"
    "----------\n"
    "    tolerance : float, default 0.001\n"
    "        the linearisation tolerance"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardInterpolationTableDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
