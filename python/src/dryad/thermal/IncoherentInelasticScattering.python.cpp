// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/thermal/IncoherentInelasticScattering.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapIncoherentInelasticScattering( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::thermal::IncoherentInelasticScattering;
  using ScatteringKernel = njoy::dryad::thermal::ScatteringKernel;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "IncoherentInelasticScattering",
    "Incoherent inelastic thermal scattering data\n\n"
    "Parameters\n"
    "----------\n"
    "    lower : float\n"
    "        the lower energy limit\n"
    "    upper : float\n"
    "        the upper energy limit\n"
    "    kernels : list of njoy.dryad.thermal.ScatteringKernel\n"
    "        the scattering kernels"
  );

  // wrap the component
  component
  .def(

    python::init< double, double,
                  std::vector< ScatteringKernel > >(),
    python::arg( "lower" ), python::arg( "upper" ),
    python::arg( "kernels" ),
    "Initialise the incoherent inelastic scattering data"
  )
  .def_property(

    "lower_energy_limit",
    python::overload_cast<>( &Component::lowerEnergyLimit, python::const_ ),
    python::overload_cast< double >( &Component::lowerEnergyLimit ),
    "The lower energy limit"
  )
  .def_property(

    "upper_energy_limit",
    python::overload_cast<>( &Component::upperEnergyLimit, python::const_ ),
    python::overload_cast< double >( &Component::upperEnergyLimit ),
    "The upper energy limit"
  )
  .def_property_readonly(

    "number_moderator_temperatures",
    &Component::numberModeratorTemperatures,
    "The moderator temperature values"
  )
  .def_property_readonly(

    "moderator_temperatures",
    python::overload_cast<>( &Component::moderatorTemperatures, python::const_ ),
    "The moderator temperature values"
  )
  .def_property(

    "scattering_kernels",
    python::overload_cast<>( &Component::scatteringKernels, python::const_ ),
    python::overload_cast< std::vector< ScatteringKernel > >( &Component::scatteringKernels ),
    "The scattering kernels"
  )
  .def(

    "has_scattering_kernel",
    &Component::hasScatteringKernel,
    python::arg( "temperature" ),
    "Return whether or not there is a scattering kernel for a given temperature\n\n"
    "Parameters\n"
    "----------\n"
    "    temperature : float\n"
    "        the moderator temperature"
  )
  .def(

    "scattering_kernel",
    &Component::scatteringKernel,
    python::arg( "temperature" ),
    "Return the scattering kernel for a given temperature\n\n"
    "Parameters\n"
    "----------\n"
    "    temperature : float\n"
    "        the moderator temperature",
    python::return_value_policy::reference_internal
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
