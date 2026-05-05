#ifndef NJOY_PSYCHIC_BASE_TEST
#define NJOY_PSYCHIC_BASE_TEST

// system includes
#include <string>

// other includes
#include "njoy/psychic/TestStatus.hpp"

namespace njoy {
namespace psychic {
namespace base {

  /**
   *  @class
   *  @brief Base interface for a psychic test
   */
  template < typename Derived >
  class Test {

    /* fields */

    std::string name_;
    std::optional< TestStatus > status_;

    /* auxiliary functions */

  public:

    /* constructor */

    /**
     *  @brief Constructor
     */
    Test( std::string name ) :
      name_( std::move( name ) ),
      status_( std::nullopt ) {}

    /* methods */

    /**
     *  @brief Return the test name
     */
    const std::string& name() const {

      return this->name_;
    }

    /**
     *  @brief Return the test status
     */
    const std::optional< TestStatus >& status() const {

      return this->status_;
    }

    /**
     *  @brief Set the test status
     */
    void status( std::optional< TestStatus > status ) {

      this->status_ = status;
    }

    /**
     *  @brief Clear and reset the test
     *
     *  This resets the test status to std::nullopt and calls the reset()
     *  function on the Derived class that resets any other data stored on the
     *  test instance.
     */
    void clear() {

      this->status( std::nullopt );
      static_cast< Derived* >( this )->reset();
    }
  };

} // base namespace
} // psychic namespace
} // njoy namespace

#endif
