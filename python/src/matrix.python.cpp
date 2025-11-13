// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

// local includes
#include "njoy/matrix.hpp"

// namespace aliases
namespace python = pybind11;

namespace matrix {

/**
 *  @brief Wrap matrix test function for a specific template type
 *
 *  @param[in,out] module   the python module
 */
template < typename T >
void wrapFunctionsForMatrix( python::module& module ) {

  module
  .def( "is_square",
        [] ( const njoy::matrix::Matrix< T >& matrix )
           { return njoy::matrix::isSquare( matrix ); },
        "Return whether or not a matrix is square" )
  .def( "is_symmetric",
        [] ( const njoy::matrix::Matrix< T >& matrix )
           { return njoy::matrix::isSymmetric( matrix ); },
        "Return whether or not a matrix is symmetric" );
}

} // matrix namespace

void wrapMatrix( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "matrix",
    "Matrix functions"
  );

  matrix::wrapFunctionsForMatrix< double >( submodule );
}
