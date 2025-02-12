// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/type-aliases.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

template < typename X, typename Y = X >
void wrapToleranceConvergenceFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::linearisation::ToleranceConvergence< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "A convergence functor using a single tolerance\n\n"
    "This functor class can be used to ensure convergence of the linearisation\n"
    "process using a relative tolerance and absolute difference threshold.\n"
    "With this functor, a trial value and reference value are considered\n"
    "converged if:\n"
    "  abs( trial - reference ) < ( abs( trial ) + abs( reference ) ) * tolerance\n\n"
    "For very small values (when ( abs( trial ) + abs( reference ) ) * tolerance\n"
    "is smaller than the threshold value), a trial value and reference value\n"
    "are considered converged if:\n"
    "  abs( trial - reference ) < threshold"
  );

  // wrap the component
  component
  .def(

    python::init< const Y&, const Y& >(),
    python::arg( "tolerance" ) = Y( 0.001 ),
    python::arg( "threshold" ) = Y( 1e-10 ),
    "Initialise the convergence functor\n\n"
    "Arguments:\n"
    "    self        the functor\n"
    "    tolerance   the linearisation tolerance (default 0.1 %)\n"
    "    threshold   the lowest allowed absolute difference (default 1e-10)"
  )
  .def_property_readonly(

    "tolerance",
    &Component::tolerance,
    "The linearisation tolerance"
  )
  .def_property_readonly(

    "threshold",
    &Component::threshold,
    "The linearisation threshold"
  )
  .def(

    "__call__",
    [] ( const Component& self,
         const Y& trial, const Y& reference,
         const X& xLeft, const X& xRight,
         const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return self( trial, reference, xLeft, xRight, yLeft, yRight ); },
    python::arg( "trial" ), python::arg( "reference" ),
    python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Test the convergence of the linearisation\n\n"
    "Arguments:\n"
    "    self         the convergence functor\n"
    "    trial        the trial value to be tested\n"
    "    reference    the reference value to be tested against\n"
    "    xLeft        the left value on the x interval\n"
    "    xRight       the right value on the x interval\n"
    "    yLeft        the left value on the y interval\n"
    "    yRight       the right value on the y interval"
  );
}

void wrapToleranceConvergence( python::module& module ) {

  wrapToleranceConvergenceFor< double >( module, "ToleranceConvergence" );
}
