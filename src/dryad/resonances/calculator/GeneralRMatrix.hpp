#ifndef NJOY_DRYAD_RESONANCES_CALCULATOR_GENERALRMATRIX
#define NJOY_DRYAD_RESONANCES_CALCULATOR_GENERALRMATRIX

// system includes
#include <variant>
#include <vector>

// other includes
#include "dryad/matrix.hpp"
#include "dryad/resonances/calculator/Constant.hpp"
#include "dryad/resonances/calculator/ShiftFactor.hpp"

namespace njoy {
namespace dryad {
namespace resonances {
namespace calculator {

  /**
   *  @class
   *  @brief A matrix and cross section calculator for the general R-matrix formalism
   */
  class GeneralRMatrix {

    using LMatrix = std::variant< calculator::Constant, calculator::ShiftFactor >;

    /* fields */

    LMatrix l_matrix_;

    matrix::Matrix< std::complex< double > > t_matrix_;
    matrix::Matrix< std::complex< double > > w_matrix_;
    matrix::Matrix< std::complex< double > > u_matrix_;
    matrix::DiagonalMatrix< double > sqrt_p_matrix_;
    matrix::DiagonalMatrix< std::complex< double > > omega_matrix_;

    std::vector< double > penetrabilities_;
    std::vector< double > shift_factors_;
    std::vector< double > phase_shifts_;
    std::vector< double > coulomb_phase_shifts_;
    std::vector< double > boundaries_;
    std::vector< bool > below_threshold_;

    /* auxiliary functions */

    // blatantly copied from Reich-Moore
    #include "dryad/resonances/calculator/ReichMoore/src/selectLMatrix.hpp"

    /* auxiliary functions */

  public:

    /* constructor */

    /* methods */

    void crossSections( double energy,
                        const std::vector< Channel >& channels,
                        const ResonanceTable& table,
                        std::map< id::ReactionID, double >& xs ) {


    }
  };

} // calculator namespace
} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
