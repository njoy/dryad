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

  // constants
  std::ostringstream tolerance;
  tolerance << std::setprecision( 4 ) << njoy::constants::linearisation::tolerance;

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

    python::init< std::vector< double >,
                  std::vector< TabulatedScatteringKernelFunction >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "energy_transfers" ),
    python::arg( "functions" ),
    python::arg( "boundaries" ),
    python::arg( "interpolants" ),
    "Initialise the tabulated S(a,b) scattering kernel with multiple interpolation zones"
  )
  .def(

    python::init< std::vector< double >,
                  std::vector< TabulatedScatteringKernelFunction >,
                  InterpolationType >(),
    python::arg( "energy_transfers" ),
    python::arg( "functions" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the tabulated S(a,b) scattering kernel with a single interpolation zone"
  )
  .def_property_readonly(

    "energy_transfers",
    python::overload_cast<>( &Component::energyTransfers, python::const_ ),
    "The energy transfer values for which scattering functions are given"
  )
  .def_property_readonly(

    "functions",
    python::overload_cast<>( &Component::functions, python::const_ ),
    "The associated scattering functions"
  )
  .def_property_readonly(

    "lower_energy_transfer_limit",
    &Component::lowerEnergyTransferLimit,
    "The lower energy transfer limit"
  )
  .def_property_readonly(

    "upper_energy_transfer_limit",
    &Component::upperEnergyTransferLimit,
    "The upper energy transfer limit"
  )
  .def_property_readonly(

    "lower_momentum_transfer_limit",
    &Component::lowerMomentumTransferLimit,
    "The lower momentum transfer limit"
  )
  .def_property_readonly(

    "upper_momentum_transfer_limit",
    &Component::upperMomentumTransferLimit,
    "The upper momentum transfer limit"
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
    std::string( "Linearise the S(a,b) scattering kernel\n\n"
                 "Parameters\n"
                 "----------\n"
                 "    tolerance : float, default " + tolerance.str() + "\n"
                 "        the linearisation tolerance" ).c_str()
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
