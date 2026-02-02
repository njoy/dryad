#ifndef NJOY_DRYAD_PYTHON_DEFINITIONS
#define NJOY_DRYAD_PYTHON_DEFINITIONS

// system includes
#include <complex>

// other includes
#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"

namespace python = pybind11;

namespace dryad {

/**
 *  @brief Add standard copy and deepcopy definitions
 *
 *  This adds the following standard functions:
 *    __copy__
 *    __deepcopy__
 *
 *  @param[in] component   the component to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardCopyDefinitions( PythonClass& component ) {

  component
  .def(

    "__copy__",
    [] ( const Component& self ) -> Component {

      return Component( self );
    }
  )
  .def(

    "__deepcopy__",
    [] ( const Component& self, python::dict ) -> Component {

      return Component( self );
    }
  );
}

/**
 *  @brief Add standard equal and not equal comparison definitions
 *
 *  This adds the following standard properties:
 *    - operator==
 *    - operator!=
 *
 *  @param[in] component   the component to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardEqualityComparisonDefinitions( PythonClass& component ) {

  component
  .def( python::self == python::self )
  .def( python::self != python::self );
}

/**
 *  @brief Add standard comparison definitions
 *
 *  This adds the following standard properties:
 *    - operator==
 *    - operator!=
 *    - operator<
 *    - operator>
 *    - operator<=
 *    - operator>=
 *
 *  @param[in] component   the component to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardComparisonDefinitions( PythonClass& component ) {

  component
  .def( python::self == python::self )
  .def( python::self != python::self )
  .def( python::self > python::self )
  .def( python::self < python::self )
  .def( python::self >= python::self )
  .def( python::self <= python::self );
}

/**
 *  @brief Add standard print definitions
 *
 *  This adds the following standard functions:
 *    __str__
 *
 *  @param[in] component   the component to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardPrintDefinitions( PythonClass& component ) {

  component
  .def(

    "__str__",
    [] ( const Component& self ) { return self.symbol(); },
    "Convenience function for printing the identifier"
  );
}

/**
 *  @brief Add standard math definitions
 *
 *  This adds the following standard properties:
 *    - arithmetic operators
 *
 *  @param[in] component   the component to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardMathOperatorDefinitions( PythonClass& component ) {

  component
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

/**
 *  @brief Add standard interpolation table definitions
 *
 *  This adds the following standard properties:
 *    - boundaries, interpolants
 *    - number_points, number_regions
 *
 *  @param[in] component   the component to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardInterpolationTableDefinitions( PythonClass& component ) {

  component
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
  );
}

/**
 *  @brief Add standard tabulated data definitions
 *
 *  This adds the following standard properties:
 *    - linearise
 *    - boundaries, interpolants
 *    - number_points, number_regions
 *    - is_linearised
 *    - arithmetic operators
 *
 *  @param[in] component   the component to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardTabulatedDefinitions( PythonClass& component ) {

  component
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    "Linearise the table\n\n"
    "Parameters\n"
    "----------\n"
    "    tolerance : float, default 0.001\n"
    "         the linearisation tolerance"
  )
  .def_property_readonly(

    "is_linearised",
    [] ( const Component& self ) -> decltype(auto)
       { return self.isLinearised(); },
    "Flag indicating whether or not the table is linearised"
  );

  // add math operators
  addStandardInterpolationTableDefinitions< Component >( component );
  addStandardMathOperatorDefinitions< Component >( component );
}

/**
 *  @brief Add standard series expansion definitions
 *
 *  This adds the following standard properties:
 *    - order and coefficients
 *    - linearise
 *    - arithmetic operators
 *
 *  @param[in] component   the component to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardSeriesDefinitions( PythonClass& component ) {

  component
  .def_property_readonly(

    "coefficients",
    [] ( const Component& self ) -> decltype(auto)
       { return self.coefficients(); },
    "The series coefficients"
  )
  .def_property_readonly(

    "order",
    [] ( const Component& self ) -> decltype(auto)
       { return self.order(); },
    "The series order"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    "Linearise the series\n\n"
    "Parameters\n"
    "----------\n"
    "    tolerance : float, default 0.001\n"
    "         the linearisation tolerance"
  );

  // add math operators
  addStandardMathOperatorDefinitions< Component >( component );
}

} // dryad namespace

#endif
