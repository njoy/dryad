// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/TabulatedComptonProfile.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapTabulatedComptonProfile( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedComptonProfile;
  using ElectronSubshellID = njoy::dryad::id::ElectronSubshellID;
  using TabulatedComptonProfileFunction = njoy::dryad::TabulatedComptonProfileFunction;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedComptonProfile",
    "A Compton profile for an electron subshell defined by a pdf and cdf using tabulated data\n\n"
    "Compton profiles are not available in standard evaluated nuclear data files. They are used for\n"
    "photoatomic transport data in Monte Carlo codes like MCNP, which currently get this data form\n"
    "external sources. \n\n"
    "Parameters\n"
    "----------\n"
    "    subshell_identifier : njoy.dryad.id.ElectronSubshellID\n"
    "         the electron subshell identifier\n"
    "    momentum : list of float\n"
    "         the momentum values\n"
    "    values : list of float\n"
    "         the probability values\n"
    "    boundaries : list of int\n"
    "         the boundaries of the interpolation regions\n"
    "    interpolants : list of njoy.dryad.InterpolationType\n"
    "         the interpolation types of the interpolation regions\n"
    "    interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear\n"
    "         the interpolation type (default lin-lin)\n"
    "    normalise : bool, default false\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  );

  // wrap the component
  component
  .def(

    python::init< ElectronSubshellID,
                  std::vector< double >,
                  std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType >,
                  bool >(),
    python::arg( "subshell_identifier" ),
    python::arg( "momentum" ),
    python::arg( "values" ),
    python::arg( "boundaries" ),
    python::arg( "interpolants" ),
    python::arg( "normalise" ) = false,
    "Initialise the compton profile with multiple interpolation zones"
  )
  .def(

    python::init< ElectronSubshellID,
                  std::vector< double >,
                  std::vector< double >,
                  InterpolationType,
                  bool >(),
    python::arg( "subshell_identifier" ),
    python::arg( "momentum" ),
    python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    python::arg( "normalise" ) = false,
    "Initialise the compton profile with a single interpolation zone"
  )
  .def_property_readonly(

    "subshell_identifier",
    &Component::identifier,
    "The electron subshell identifier"
  )
  .def_property_readonly(

    "momentum",
    &Component::momentum,
    "The momentum values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The probability values"
  )
  .def_property_readonly(

    "boundaries",
    &Component::boundaries,
    "The boundaries of the interpolation regions"
  )
  .def_property_readonly(

    "interpolants",
    &Component::interpolants,
    "The interpolation types of the interpolation regions"
  )
  .def_property_readonly(

    "pdf",
    &Component::pdf,
    "The probability distribution function (pdf) of the distribution"
  )
  .def_property_readonly(

    "cdf",
    &Component::cdf,
    "The cumulative distribution function (cdf) of the distribution"
  )
  .def(

    "__call__",
    [] ( const Component& self, double momentum ) -> decltype(auto)
       { return self( momentum ); },
    python::arg( "momentum" ),
    "Evaluate the pdf of the Compton profile for a given momentum value \n\n"
    "Parameters\n"
    "----------\n"
    "    momentum : float\n"
    "        the momentum value"
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the distribution"
  )
  .def_property_readonly(

    "average_momentum",
    &Component::averageMomentum,
    "The average momentum defined by the distribution"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = ToleranceConvergence(),
    python::arg( "normalise" ) = false,
    "Linearise the distribution \n\n"
    "Parameters\n"
    "----------\n"
    "    tolerance : njoy.dryad.ToleranceConvergence\n"
    "         the linearisation tolerance\n"
    "    normalise : bool, default false\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
