#ifndef NJOY_DRYAD_MULTIGROUPCROSSSECTION
#define NJOY_DRYAD_MULTIGROUPCROSSSECTION

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "scion/math/GroupedTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A multi-group cross section
   */
  class MultigroupCrossSection :
      protected scion::math::GroupedTable< double, double > {

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param[in] table   the grouped table
     */
    MultigroupCrossSection( GroupedTable< double, double > table ) :
      GroupedTable( std::move( table ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    MultigroupCrossSection() = default;

    MultigroupCrossSection( const MultigroupCrossSection& ) = default;
    MultigroupCrossSection( MultigroupCrossSection&& ) = default;

    MultigroupCrossSection& operator=( const MultigroupCrossSection& ) = default;
    MultigroupCrossSection& operator=( MultigroupCrossSection&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] boundaries   the energy group boundaries
     *  @param[in] values       the cross section values
     */
    MultigroupCrossSection( std::vector< double > boundaries,
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
    MultigroupCrossSection& operator+=( double right ) {

      GroupedTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    MultigroupCrossSection& operator-=( double right ) {

      GroupedTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    MultigroupCrossSection& operator*=( double right ) {

      GroupedTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    MultigroupCrossSection& operator/=( double right ) {

      GroupedTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief MultigroupCrossSection and scalar addition
     *
     *  @param[in] right    the scalar
     */
    MultigroupCrossSection operator+( double right ) const {

      return GroupedTable::operator+( right );
    }

    /**
     *  @brief MultigroupCrossSection and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    MultigroupCrossSection operator-( double right ) const {

      return GroupedTable::operator-( right );
    }

    /**
     *  @brief MultigroupCrossSection and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    MultigroupCrossSection operator*( double right ) const {

      return GroupedTable::operator*( right );
    }

    /**
     *  @brief MultigroupCrossSection and scalar division
     *
     *  @param[in] right    the scalar
     */
    MultigroupCrossSection operator/( double right ) const {

      return GroupedTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    MultigroupCrossSection operator-() const {

      return GroupedTable::operator-();
    }

    /**
     *  @brief Inplace MultigroupCrossSection addition
     *
     *  @param[in] right    the table
     */
    MultigroupCrossSection& operator+=( const MultigroupCrossSection& right ) {

      GroupedTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace MultigroupCrossSection subtraction
     *
     *  @param[in] right    the table
     */
    MultigroupCrossSection& operator-=( const MultigroupCrossSection& right ) {

      GroupedTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief MultigroupCrossSection and MultigroupCrossSection addition
     *
     *  @param[in] right    the table
     */
    MultigroupCrossSection operator+( const MultigroupCrossSection& right ) const {

      return GroupedTable::operator+( right );
    }

    /**
     *  @brief MultigroupCrossSection and MultigroupCrossSection subtraction
     *
     *  @param[in] right    the table
     */
    MultigroupCrossSection operator-( const MultigroupCrossSection& right ) const {

      return GroupedTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const MultigroupCrossSection& right ) const {

      return GroupedTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const MultigroupCrossSection& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and MultigroupCrossSection addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline MultigroupCrossSection operator+( double left, const MultigroupCrossSection& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and MultigroupCrossSection subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline MultigroupCrossSection operator-( double left, const MultigroupCrossSection& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and MultigroupCrossSection multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline MultigroupCrossSection operator*( double left, const MultigroupCrossSection& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
