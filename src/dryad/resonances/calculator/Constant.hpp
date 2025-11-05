#ifndef NJOY_DRYAD_RESONANCES_CALCULATOR_CONSTANT
#define NJOY_DRYAD_RESONANCES_CALCULATOR_CONSTANT

// system includes

// other includes
#include "dryad/matrix.hpp"

namespace njoy {
namespace dryad {
namespace resonances {
namespace calculator {

  /**
   *  @class
   *  @brief A functor to calculate the diagonal L matrix for a constant
   *         boundary condition
   */
  class Constant {

    /* fields */

    matrix::DiagonalMatrix< std::complex< double > > l_matrix_;

    /* auxiliary functions */

  public:

    /* constructor */

    #include "dryad/resonances/calculator/Constant/src/ctor.hpp"

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
    operator()( const std::vector< double >& shift_factors,
                const std::vector< double >& penetrabilities,
                const std::vector< double >& boundaries ) {

      for ( unsigned int i = 0; i < this->numberChannels(); ++i ) {

        this->matrix().diagonal()[i] =
        std::complex< double >( shift_factors[i] - boundaries[i], penetrabilities[i] );
      }
      return this->matrix();
    }
  };

} // calculator namespace
} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
