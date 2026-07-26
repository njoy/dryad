// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/thermal/ScatteringKernel.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapScatteringKernel( python::module& module ) {

  // constants
  std::ostringstream tolerance;
  tolerance << std::setprecision( 4 ) << njoy::constants::linearisation::tolerance;

  // type aliases
  using Component = njoy::dryad::thermal::ScatteringKernel;
  using TabulatedScatteringKernel = njoy::dryad::thermal::TabulatedScatteringKernel;
  using TabulatedScatteringKernelFunction = njoy::dryad::thermal::TabulatedScatteringKernelFunction;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ScatteringKernel",
    "An S(a,b) scattering kernel using the short collision time approximation\n\n"
    "Parameters\n"
    "----------\n"
    "    moderator_temperature : float\n"
    "        the moderator temperature\n"
    "    effective_temperature : float\n"
    "        the effective temperature\n"
    "    table : njoy.dryad.thermal.TabulatedScatteringKernel\n"
    "        the tabulated S(a,b) scattering kernel\n"
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

    python::init< double,
                  double,
                  TabulatedScatteringKernel >(),
    python::arg( "moderator_temperature" ),
    python::arg( "effective_temperature" ),
    python::arg( "table" ),
    "Initialise the scattering kernel with a tabulated scattering kernel"
  )
  .def(

    python::init< double,
                  double,
                  std::vector< double >,
                  std::vector< TabulatedScatteringKernelFunction >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "moderator_temperature" ),
    python::arg( "effective_temperature" ),
    python::arg( "energy_transfers" ),
    python::arg( "functions" ),
    python::arg( "boundaries" ),
    python::arg( "interpolants" ),
    "Initialise the scattering kernel with multiple interpolation zones"
  )
  .def(

    python::init< double,
                  double,
                  std::vector< double >,
                  std::vector< TabulatedScatteringKernelFunction >,
                  InterpolationType >(),
    python::arg( "moderator_temperature" ),
    python::arg( "effective_temperature" ),
    python::arg( "energy_transfers" ),
    python::arg( "functions" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the scattering kernel with a single interpolation zone"
  )
  .def_property_readonly(

    "moderator_temperature",
    &Component::moderatorTemperature,
    "The moderator temperature"
  )
  .def_property_readonly(

    "effective_temperature",
    &Component::effectiveTemperature,
    "The effective temperature"
  )
  .def_property_readonly(

    "short_collision_time",
    python::overload_cast<>( &Component::shortCollisionTime, python::const_ ),
    "The short collision time approximation"
  )
  .def_property_readonly(

    "tabulated_scattering_kernel",
    python::overload_cast<>( &Component::tabulatedScatteringKernel, python::const_ ),
    "The tabulated scattering kernel"
  )
  .def_property_readonly(

    "is_energy_transfer_symmetric",
    &Component::isEnergyTransferSymmetric,
    "Flag to indicate whether or not the scattering kernel is symmetric along the energy transfer axis"
  )
  .def(

    "momentum_transfer",
    &Component::momentumTransfer,
    python::arg( "incident" ),
    python::arg( "outgoing" ),
    python::arg( "cosine" ),
    python::arg( "ratio" ),
    "Evaluate the momentum transfer for a given incident energy, outgoing energy\n"
    "and cosine value\n\n"
    "Parameters\n"
    "----------\n"
    "    incident : float\n"
    "        the incident energy value\n"
    "    outgoing : float\n"
    "        the outgoing energy value\n"
    "    cosine : float\n"
    "        the cosine value"
    "    ratio : float\n"
    "        the atomic mass ratio of the target to the projectile"
  )
  .def(

    "energy_transfer",
    &Component::energyTransfer,
    python::arg( "incident" ),
    python::arg( "outgoing" ),
    "Evaluate the energy transfer for a given incident and outgoing energy\n\n"
    "Parameters\n"
    "----------\n"
    "    incident : float\n"
    "        the incident energy value\n"
    "    outgoing : float\n"
    "        the outgoing energy value"
  )
  .def(

    "__call__",
    [] ( const Component& self,
         double incident, double outgoing,
         double cosine, double ratio ) -> decltype(auto)
       { return self( incident, outgoing, cosine, ratio ); },
    python::arg( "incident" ),
    python::arg( "outgoing" ),
    python::arg( "cosine" ),
    python::arg( "ratio" ),
    "Evaluate the scattering kernel for a given incident energy, outgoing energy\n"
    "and cosine value\n\n"
    "Parameters\n"
    "----------\n"
    "    incident : float\n"
    "        the incident energy value\n"
    "    outgoing : float\n"
    "        the outgoing energy value\n"
    "    cosine : float\n"
    "        the cosine value"
    "    ratio : float\n"
    "        the atomic mass ratio of the target to the projectile\n"
    "    a : float\n"
    "        the momentum transfer value\n"
    "    b : float\n"
    "        the energy transfer value"
  )
  .def(

    "__call__",
    [] ( const Component& self, double a, double b ) -> decltype(auto)
       { return self( a, b ); },
    python::arg( "a" ),
    python::arg( "b" ),
    "Evaluate the scattering kernel for a given momentum and energy transfer value"
  )
  .def(

    "angular_distribution",
    &Component::angularDistribution,
    python::arg( "incident" ),
    python::arg( "outgoing" ),
    python::arg( "ratio" ),
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    std::string( "Return the incoherent inelastic scattering angular distribution for a\n"
                 "given incident and outgoing energy\n\n"
                 "Parameters\n"
                 "----------\n"
                 "    incident : float\n"
                 "        the incident energy value\n"
                 "    outgoing : float\n"
                 "        the outgoing energy value\n"
                 "    ratio : float\n"
                 "        the atomic mass ratio of the target to the projectile"
                 "    tolerance : float, default " + tolerance.str() + "\n"
                 "        the linearisation tolerance" ).c_str()
  )
  .def(

    "energy_distribution",
    &Component::energyDistribution,
    python::arg( "incident" ),
    python::arg( "ratio" ),
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    std::string( "Return the incoherent inelastic scattering energy distribution for a\n"
                 "given incident energy\n\n"
                 "Parameters\n"
                 "----------\n"
                 "    incident : float\n"
                 "        the incident energy value\n"
                 "    ratio : float\n"
                 "        the atomic mass ratio of the target to the projectile"
                 "    tolerance : float, default " + tolerance.str() + "\n"
                 "        the linearisation tolerance" ).c_str()
  )
  .def(

    "cross_section_value",
    &Component::crossSectionValue,
    python::arg( "incident" ),
    python::arg( "xs" ),
    python::arg( "ratio" ),
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    std::string( "Return the incoherent inelastic scattering cross section for a\n"
                 "given incident energy\n\n"
                 "Parameters\n"
                 "----------\n"
                 "    incident : float\n"
                 "        the incident energy value\n"
                 "    xs : float\n"
                 "        the bound cross section value\n"
                 "    ratio : float\n"
                 "        the atomic mass ratio of the target to the projectile"
                 "    tolerance : float, default " + tolerance.str() + "\n"
                 "        the linearisation tolerance" ).c_str()
  )
  .def(

    "cross_section",
    &Component::crossSection,
    python::arg( "lower" ),
    python::arg( "upper" ),
    python::arg( "xs" ),
    python::arg( "ratio" ),
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    std::string( "Return the incoherent inelastic scattering cross section\n\n"
                 "Parameters\n"
                 "----------\n"
                 "    lower : float\n"
                 "        the lower energy limit\n"
                 "    upper : float\n"
                 "        the upper energy limit\n"
                 "    xs : float\n"
                 "        the bound cross section value\n"
                 "    ratio : float\n"
                 "        the atomic mass ratio of the target to the projectile"
                 "    tolerance : float, default " + tolerance.str() + "\n"
                 "        the linearisation tolerance" ).c_str()
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
