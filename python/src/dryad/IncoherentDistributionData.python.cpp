// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/IncoherentDistributionData.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapIncoherentDistributionData( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::IncoherentDistributionData;
  using ReferenceFrame = njoy::dryad::ReferenceFrame;
  using TabulatedScatteringFunction = njoy::dryad::TabulatedScatteringFunction;
  using TabulatedComptonProfile = njoy::dryad::TabulatedComptonProfile;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "IncoherentDistributionData",
    "The distribution data for incoherent scattering in photoatomic interactions\n\n"
    "This representation is only available for a photoatomic ProjectileTarget.\n\n"
    "In this representation, a scattering function S(x,Z) is defined that\n"
    "together with the Klein-Nishina cross section determines the double\n"
    "differential cross section.\n\n"
    "This corresponds with the incoherent scattering function data given in MF27 MT504,\n"
    "supplemented with optional external Compton profile data. \n\n"
    "Parameters \n"
    "---------- \n"
    "    frame : njoy.dryad.ReferenceFrame \n"
    "         the reference frame of the distribution data\n"
    "    scattering : njoy.dryad.TabulatedScatteringFunction \n"
    "         the scatteirng function \n"
    "    profiles : list of njoy.dryad.TabulatedCOmptonProfile \n"
    "         the optional Compton profiles"
  );

  // wrap the component
  component
  .def(

    python::init< ReferenceFrame, TabulatedScatteringFunction,
                  std::optional< std::vector< TabulatedComptonProfile > > >(),
    python::arg( "frame" ), python::arg( "scattering" ),
    python::arg( "profiles" ) = std::nullopt,
    ""
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
  .def_property(

    "scattering_function",
    python::overload_cast<>( &Component::scatteringFunction, python::const_ ),
    python::overload_cast< TabulatedScatteringFunction >( &Component::scatteringFunction ),
    "The scattering function"
  )
  .def_property(

    "compton_profiles",
    python::overload_cast<>( &Component::comptonProfiles, python::const_ ),
    python::overload_cast< std::optional< std::vector< TabulatedComptonProfile > > >( &Component::comptonProfiles ),
    "The scattering function"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
