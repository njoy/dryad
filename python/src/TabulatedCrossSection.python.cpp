// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "dryad/TabulatedCrossSection.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTabulatedCrossSection( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::TabulatedCrossSection;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedCrossSection",
    "A cross section table"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "energies" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the cross section table\n\n"
    "Arguments:\n"
    "    self           the cross section table\n"
    "    energies       the energy values\n"
    "    values         the cross section values\n"
    "    boundaries     the boundaries of the interpolation regions\n"
    "    interpolants   the interpolation types of the interpolation regions"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType >(),
    python::arg( "energies" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the cross section table\n\n"
    "Arguments:\n"
    "    self           the cross section table\n"
    "    energies       the energy values\n"
    "    values         the cross section values\n"
    "    interpolant    the interpolation type (default lin-lin)"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The energy values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The cross section values"
  )
  .def_property_readonly(

    "lower_energy_limit",
    &Component::lowerEnergyLimit,
    "The lower energy limit"
  )
  .def_property_readonly(

    "upper_energy_limit",
    &Component::upperEnergyLimit,
    "The upper energy limit"
  )
  .def(

    "__call__",
    [] ( const Component& self, double energy ) -> decltype(auto)
       { return self( energy ); },
    python::arg( "energy" ),
    "Evaluate the cross section for a given energy value\n\n"
    "Arguments:\n"
    "    self      the cross section table\n"
    "    energy    the energy value"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the cross section\n\n"
    "Arguments:\n"
    "    self        the cross section table\n"
    "    tolerance   the linearisation tolerance"
  )
  .def_property_readonly(

    "boundaries",
    [] ( const Component& self ) -> decltype(auto)
       { return self.boundaries(); },
    "The boundaries of the interpolation regions"
  )
  .def_property_readonly(

    "interpolants",
    [] ( const Component& self ) -> decltype(auto)
       { return self.interpolants(); },
    "The interpolation types of the interpolation regions"
  )
  .def_property_readonly(

    "number_points",
    [] ( const Component& self ) -> decltype(auto)
       { return self.numberPoints(); },
    "The number of points in the table"
  )
  .def_property_readonly(

    "number_regions",
    [] ( const Component& self ) -> decltype(auto)
       { return self.numberRegions(); },
    "The number of interpolation regions in the table"
  )
  .def_property_readonly(

    "is_linearised",
    [] ( const Component& self ) -> decltype(auto)
       { return self.isLinearised(); },
    "Flag indicating whether or not the data is linearised"
  )
  .def( -python::self )
  .def( python::self + double() )
  .def( python::self - double() )
  .def( python::self * double() )
  .def( python::self / double() )
  .def( python::self + python::self )
  .def( python::self - python::self )
  .def( python::self += double() )
  .def( python::self -= double() )
  .def( python::self *= double() )
  .def( python::self /= double() )
  .def( python::self += python::self )
  .def( python::self -= python::self )
  .def( double() + python::self )
  .def( double() - python::self )
  .def( double() * python::self );
}
