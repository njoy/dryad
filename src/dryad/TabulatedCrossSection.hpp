#ifndef NJOY_DRYAD_CROSSSECTION
#define NJOY_DRYAD_CROSSSECTION

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A cross section table
   */
  class TabulatedCrossSection :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* constructor */
    #include "dryad/TabulatedCrossSection/src/ctor.hpp"

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
     *  @brief Return a linearised cross section table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedCrossSection linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedCrossSection( InterpolationTable::linearise( tolerance ) );
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
