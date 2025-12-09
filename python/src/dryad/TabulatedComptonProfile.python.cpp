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
    "external sources."
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
    python::arg( "identifier" ), python::arg( "momentum" ),
    python::arg( "values" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ),
    python::arg( "normalise" ) = false,
    "Initialise the compton profile\n\n"
    "Arguments:\n"
    "    self           the compton profile\n"
    "    identifier     the electron subshell identifier\n"
    "    momentum       the momentum values\n"
    "    values         the probability values\n"
    "    boundaries     the boundaries of the interpolation regions\n"
    "    interpolants   the interpolation types of the interpolation regions,\n"
    "                   see InterpolationType for all interpolation types\n"
    "    normalise      option to indicate whether or not to normalise\n"
    "                   all probability data (default: no normalisation)"
  )
  .def(

    python::init< ElectronSubshellID,
                  std::vector< double >,
                  std::vector< double >,
                  InterpolationType, bool >(),
    python::arg( "identifier" ), python::arg( "momentum" ),
    python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    python::arg( "normalise" ) = false,
    "Initialise the compton profile\n\n"
    "Arguments:\n"
    "    self           the compton profile\n"
    "    identifier     the electron subshell identifier\n"
    "    momentum       the momentum values\n"
    "    values         the probability values\n"
    "    interpolant    the interpolation type (default lin-lin),\n"
    "                   see InterpolationType for all interpolation types\n"
    "    normalise      option to indicate whether or not to normalise\n"
    "                   all probability data (default: no normalisation)"
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
    "Evaluate the pdf of the distribution for a given momentum value\n\n"
    "Arguments:\n"
    "    self        the distribution\n"
    "    momentum    the momentum value"
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
    "Linearise the distribution\n\n"
    "Arguments:\n"
    "    self        the compton profile\n"
    "    tolerance   the linearisation tolerance\n"
    "    normalise   option to indicate whether or not to normalise\n"
    "                all probability data (default: no normalisation)"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
