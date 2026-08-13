#ifndef NJOY_DRYAD_MULTIGROUPAVERAGECOSINE
#define NJOY_DRYAD_MULTIGROUPAVERAGECOSINE

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "scion/math/GroupedTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A multi-group average cosine
   */
  class MultigroupAverageCosine :
      protected scion::math::GroupedTable< double, double > {

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param[in] table   the grouped table
     */
    MultigroupAverageCosine( GroupedTable< double, double > table ) :
      GroupedTable( std::move( table ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    MultigroupAverageCosine() = default;

    MultigroupAverageCosine( const MultigroupAverageCosine& ) = default;
    MultigroupAverageCosine( MultigroupAverageCosine&& ) = default;

    MultigroupAverageCosine& operator=( const MultigroupAverageCosine& ) = default;
    MultigroupAverageCosine& operator=( MultigroupAverageCosine&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] boundaries   the energy group boundaries
     *  @param[in] values       the average cosine values
     */
    MultigroupAverageCosine( std::vector< double > boundaries,
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
    MultigroupAverageCosine& operator+=( double right ) {

      GroupedTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageCosine& operator-=( double right ) {

      GroupedTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageCosine& operator*=( double right ) {

      GroupedTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageCosine& operator/=( double right ) {

      GroupedTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief MultigroupAverageCosine and scalar addition
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageCosine operator+( double right ) const {

      return GroupedTable::operator+( right );
    }

    /**
     *  @brief MultigroupAverageCosine and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageCosine operator-( double right ) const {

      return GroupedTable::operator-( right );
    }

    /**
     *  @brief MultigroupAverageCosine and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageCosine operator*( double right ) const {

      return GroupedTable::operator*( right );
    }

    /**
     *  @brief MultigroupAverageCosine and scalar division
     *
     *  @param[in] right    the scalar
     */
    MultigroupAverageCosine operator/( double right ) const {

      return GroupedTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    MultigroupAverageCosine operator-() const {

      return GroupedTable::operator-();
    }

    /**
     *  @brief Inplace MultigroupAverageCosine addition
     *
     *  @param[in] right    the table
     */
    MultigroupAverageCosine& operator+=( const MultigroupAverageCosine& right ) {

      GroupedTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace MultigroupAverageCosine subtraction
     *
     *  @param[in] right    the table
     */
    MultigroupAverageCosine& operator-=( const MultigroupAverageCosine& right ) {

      GroupedTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief MultigroupAverageCosine and MultigroupAverageCosine addition
     *
     *  @param[in] right    the table
     */
    MultigroupAverageCosine operator+( const MultigroupAverageCosine& right ) const {

      return GroupedTable::operator+( right );
    }

    /**
     *  @brief MultigroupAverageCosine and MultigroupAverageCosine subtraction
     *
     *  @param[in] right    the table
     */
    MultigroupAverageCosine operator-( const MultigroupAverageCosine& right ) const {

      return GroupedTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const MultigroupAverageCosine& right ) const {

      return GroupedTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const MultigroupAverageCosine& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and MultigroupAverageCosine addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline MultigroupAverageCosine operator+( double left, const MultigroupAverageCosine& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and MultigroupAverageCosine subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline MultigroupAverageCosine operator-( double left, const MultigroupAverageCosine& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and MultigroupAverageCosine multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline MultigroupAverageCosine operator*( double left, const MultigroupAverageCosine& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
