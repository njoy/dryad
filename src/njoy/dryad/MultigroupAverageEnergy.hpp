#ifndef NJOY_DRYAD_MULTIGROUPAVERAGEENERGY
#define NJOY_DRYAD_MULTIGROUPAVERAGEENERGY

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "scion/math/GroupedTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A multi-group average reaction product energy
   */
  class MultigroupAverageEnergy :
      protected scion::math::GroupedTable< double, double > {

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param[in] table   the grouped table
     */
    MultigroupAverageEnergy( GroupedTable< double, double > table ) :
      GroupedTable( std::move( table ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    MultigroupAverageEnergy() = default;

    MultigroupAverageEnergy( const MultigroupAverageEnergy& ) = default;
    MultigroupAverageEnergy( MultigroupAverageEnergy&& ) = default;

    MultigroupAverageEnergy& operator=( const MultigroupAverageEnergy& ) = default;
    MultigroupAverageEnergy& operator=( MultigroupAverageEnergy&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] boundaries   the energy group boundaries
     *  @param[in] values       the average energy values
     */
    MultigroupAverageEnergy( std::vector< double > boundaries,
                            std::vector< double > values ) :
      GroupedTable( std::move( boundaries ), std::move( values ) ) {}

    /* methods */

    using GroupedTable::numberGroups;
    using GroupedTable::boundaries;
    using GroupedTable::values;

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return this->boundaries().front();
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const {

      return this->boundaries().back();
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageEnergy& operator+=( double right ) {

      GroupedTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageEnergy& operator-=( double right ) {

      GroupedTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageEnergy& operator*=( double right ) {

      GroupedTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageEnergy& operator/=( double right ) {

      GroupedTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief MultigroupAverageEnergy and scalar addition
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageEnergy operator+( double right ) const {

      return GroupedTable::operator+( right );
    }

    /**
     *  @brief MultigroupAverageEnergy and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageEnergy operator-( double right ) const {

      return GroupedTable::operator-( right );
    }

    /**
     *  @brief MultigroupAverageEnergy and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageEnergy operator*( double right ) const {

      return GroupedTable::operator*( right );
    }

    /**
     *  @brief MultigroupAverageEnergy and scalar division
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageEnergy operator/( double right ) const {

      return GroupedTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    MultigroupAverageEnergy operator-() const {

      return GroupedTable::operator-();
    }

    /**
     *  @brief Inplace MultigroupAverageEnergy addition
     *
     *  @param[in] right    the table
     */
    MultigroupAverageEnergy& operator+=( const MultigroupAverageEnergy& right ) {

      GroupedTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace MultigroupAverageEnergy subtraction
     *
     *  @param[in] right    the table
     */
    MultigroupAverageEnergy& operator-=( const MultigroupAverageEnergy& right ) {

      GroupedTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief MultigroupAverageEnergy and MultigroupAverageEnergy addition
     *
     *  @param[in] right    the table
     */
    MultigroupAverageEnergy operator+( const MultigroupAverageEnergy& right ) const {

      return GroupedTable::operator+( right );
    }

    /**
     *  @brief MultigroupAverageEnergy and MultigroupAverageEnergy subtraction
     *
     *  @param[in] right    the table
     */
    MultigroupAverageEnergy operator-( const MultigroupAverageEnergy& right ) const {

      return GroupedTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const MultigroupAverageEnergy& right ) const {

      return GroupedTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const MultigroupAverageEnergy& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and MultigroupAverageEnergy addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline MultigroupAverageEnergy operator+( double left, const MultigroupAverageEnergy& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and MultigroupAverageEnergy subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline MultigroupAverageEnergy operator-( double left, const MultigroupAverageEnergy& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and MultigroupAverageEnergy multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline MultigroupAverageEnergy operator*( double left, const MultigroupAverageEnergy& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
