#ifndef NJOY_PSYCHIC_TESTSTATUS
#define NJOY_PSYCHIC_TESTSTATUS

// system includes

// other includes

namespace njoy {
namespace psychic {

/**
 *  @enum
 *  @brief The test status
 *
 *  @todo add an exception state?
 *
 *  This enum is used to differentiate between various test states. We currently
 *  distinguish four different states: skipped, success, pass but with warnings and
 *  failed.
 */
enum class TestStatus : short {

  Skipped = -1,  /**< The test has been skipped */
  Success =  0,  /**< The test passes successfully without issues */
  Warning =  1,  /**< The test passed but there are issues */
  Fail    =  2   /**< The test fails */
};

inline TestStatus operator&&( const TestStatus& left, const TestStatus& right ) {

  return std::max( left, right );
}

} // psychic namespace
} // njoy namespace

#endif
