#ifndef NJOY_DRYAD_RESONANCES_CALCULATOR_SHIFTFACTOR
#define NJOY_DRYAD_RESONANCES_CALCULATOR_SHIFTFACTOR

// system includes

// other includes
#include "njoy/matrix.hpp"

namespace njoy {
namespace dryad {
namespace resonances {
namespace calculator {

  /**
   *  @class
   *  @brief A functor to calculate the diagonal L matrix for the shift
   *         factor boundary condition
   */
  class ShiftFactor {

    /* fields */

    matrix::DiagonalMatrix< std::complex< double > > l_matrix_;

    /* auxiliary functions */

  public:

    /* constructor */

    #include "njoy/dryad/resonances/calculator/ShiftFactor/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the current value of the L matrix
     */
    const matrix::DiagonalMatrix< std::complex< double > >& matrix() const {

      return this->l_matrix_;
    }

    /**
     *  @brief Return the current value of the L matrix
     */
    matrix::DiagonalMatrix< std::complex< double > >& matrix() {

      return this->l_matrix_;
    }

    /**
     *  @brief Return the number of channels
     */
    unsigned int numberChannels() const {

      return this->matrix().cols();
    }

    /**
     *  @brief Evaluate and return the L matrix
     *
     *  @param[in] shift_factors     the shift factor value for each channel
     *  @param[in] penetrabilities   the penetrability value for each channel
     *  @param[in] boundaries        the boundary condition value for each channel
     */
    const matrix::DiagonalMatrix< std::complex< double > >&
    operator()( const std::vector< double >& penetrabilities ) {

      for ( unsigned int i = 0; i < this->numberChannels(); ++i ) {

        this->matrix().diagonal()[i] = std::complex< double >( 0., penetrabilities[i] );
      }
      return this->matrix();
    }
  };

} // calculator namespace
} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
