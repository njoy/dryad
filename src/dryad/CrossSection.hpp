#ifndef NJOY_DRYAD_CROSSSECTION
#define NJOY_DRYAD_CROSSSECTION

// system includes
#include <vector>

// other includes
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A cross section table
   *
   *  Assumptions: energies are given in eV and cross section values in barn.
   */
  class CrossSection : protected scion::math::InterpolationTable< double, double > {

  public:

    using Interpolation = scion::interpolation::InterpolationType;
    using Tolerance = scion::linearisation::ToleranceConvergence< double, double >;

    /* constructor */
    #include "dryad/CrossSection/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const noexcept {

      return this->x();
    }

    /**
     *  @brief Return the cross section values
     */
    const std::vector< double >& values() const noexcept {

      return this->y();
    }

    using InterpolationTable::x;
    using InterpolationTable::y;
    using InterpolationTable::boundaries;
    using InterpolationTable::interpolants;
    using InterpolationTable::numberPoints;
    using InterpolationTable::numberRegions;
    using InterpolationTable::isLinearised;

    using InterpolationTable::operator();

    /**
     *  @brief Return a linearised CrossSection
     *
     *  @param[in] convergence   the linearisation convergence criterion (default 0.1 %)
     */
    CrossSection linearise( Tolerance convergence = Tolerance() ) const {

      return CrossSection( InterpolationTable::linearise( convergence ) );
    }

    //! @todo add arithmetic
    // using InterpolationTable::operator+=;
    // using InterpolationTable::operator-=;
    // using InterpolationTable::operator*=;
    // using InterpolationTable::operator/=;
    //
    // using InterpolationTable::operator+;
    // using InterpolationTable::operator-;
    // using InterpolationTable::operator*;
    // using InterpolationTable::operator/;
  };

} // dryad namespace
} // njoy namespace

#endif
