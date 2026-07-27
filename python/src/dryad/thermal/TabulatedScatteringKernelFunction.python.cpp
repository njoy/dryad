// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/thermal/TabulatedScatteringKernelFunction.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapTabulatedScatteringKernelFunction( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::thermal::TabulatedScatteringKernelFunction;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedScatteringKernelFunction",
    "A tabulated scattering function S(alpha)\n\n"
    "Parameters\n"
    "----------\n"
    "    momentum_transfers : list of float\n"
    "        the momentum transfer values\n"
    "    values : list of float\n"
    "        the scattering function values\n"
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

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "momentum_transfers" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the scattering function table with multiple interpolation zones"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType >(),
    python::arg( "momentum_transfers" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the scattering function table with a single interpolation zone"
  )
  .def_property_readonly(

    "momentum_transfers",
    &Component::momentumTransfers,
    "The momentum transfer values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The scattering function values"
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
    [] ( const Component& self, double momentumTransfer ) -> decltype(auto)
       { return self( momentumTransfer ); },
    python::arg( "momentum_transfer" ),
    "Evaluate the scattering function for a given momentum transfer value\n\n"
    "Parameters\n"
    "----------\n"
    "    momentum_transfer : float\n"
    "        the momentum transfer value"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardTabulatedDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
