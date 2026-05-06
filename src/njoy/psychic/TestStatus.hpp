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

  Success,   /**< The test passes successfully without issues */
  Warning,   /**< The test passed but there are issues */
  Fail,      /**< The test fails */
  Skipped    /**< The test has been skipped */
};

} // psychic namespace
} // njoy namespace

#endif
