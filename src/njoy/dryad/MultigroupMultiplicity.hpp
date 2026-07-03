#ifndef NJOY_DRYAD_MULTIGROUPMULTIPLICITY
#define NJOY_DRYAD_MULTIGROUPMULTIPLICITY

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "scion/math/GroupedTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A multi-group multiplicity
   */
  class MultigroupMultiplicity :
      protected scion::math::GroupedTable< double, double > {

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param[in] table   the grouped table
     */
    MultigroupMultiplicity( GroupedTable< double, double > table ) :
      GroupedTable( std::move( table ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    MultigroupMultiplicity() = default;

    MultigroupMultiplicity( const MultigroupMultiplicity& ) = default;
    MultigroupMultiplicity( MultigroupMultiplicity&& ) = default;

    MultigroupMultiplicity& operator=( const MultigroupMultiplicity& ) = default;
    MultigroupMultiplicity& operator=( MultigroupMultiplicity&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] boundaries   the energy group boundaries
     *  @param[in] values       the multiplicity values
     */
    MultigroupMultiplicity( std::vector< double > boundaries,
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
    MultigroupMultiplicity& operator+=( double right ) {

      GroupedTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    MultigroupMultiplicity& operator-=( double right ) {

      GroupedTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    MultigroupMultiplicity& operator*=( double right ) {

      GroupedTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    MultigroupMultiplicity& operator/=( double right ) {

      GroupedTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief MultigroupMultiplicity and scalar addition
     *
     *  @param[in] right    the scalar
     */
    MultigroupMultiplicity operator+( double right ) const {

      return GroupedTable::operator+( right );
    }

    /**
     *  @brief MultigroupMultiplicity and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    MultigroupMultiplicity operator-( double right ) const {

      return GroupedTable::operator-( right );
    }

    /**
     *  @brief MultigroupMultiplicity and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    MultigroupMultiplicity operator*( double right ) const {

      return GroupedTable::operator*( right );
    }

    /**
     *  @brief MultigroupMultiplicity and scalar division
     *
     *  @param[in] right    the scalar
     */
    MultigroupMultiplicity operator/( double right ) const {

      return GroupedTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    MultigroupMultiplicity operator-() const {

      return GroupedTable::operator-();
    }

    /**
     *  @brief Inplace MultigroupMultiplicity addition
     *
     *  @param[in] right    the table
     */
    MultigroupMultiplicity& operator+=( const MultigroupMultiplicity& right ) {

      GroupedTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace MultigroupMultiplicity subtraction
     *
     *  @param[in] right    the table
     */
    MultigroupMultiplicity& operator-=( const MultigroupMultiplicity& right ) {

      GroupedTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief MultigroupMultiplicity and MultigroupMultiplicity addition
     *
     *  @param[in] right    the table
     */
    MultigroupMultiplicity operator+( const MultigroupMultiplicity& right ) const {

      return GroupedTable::operator+( right );
    }

    /**
     *  @brief MultigroupMultiplicity and MultigroupMultiplicity subtraction
     *
     *  @param[in] right    the table
     */
    MultigroupMultiplicity operator-( const MultigroupMultiplicity& right ) const {

      return GroupedTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const MultigroupMultiplicity& right ) const {

      return GroupedTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const MultigroupMultiplicity& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and MultigroupMultiplicity addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline MultigroupMultiplicity operator+( double left, const MultigroupMultiplicity& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and MultigroupMultiplicity subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline MultigroupMultiplicity operator-( double left, const MultigroupMultiplicity& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and MultigroupMultiplicity multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline MultigroupMultiplicity operator*( double left, const MultigroupMultiplicity& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
