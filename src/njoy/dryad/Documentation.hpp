#ifndef NJOY_DRYAD_METADATA
#define NJOY_DRYAD_METADATA

// system includes
#include <optional>
#include <string>

// other includes

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Documentation associated to the dryad data
   */
  class Documentation {

    //! @todo remove once we get the particle database
    std::optional< double > awr_;

    /* fields */
    std::optional< int > library_;
    std::optional< std::pair< int, int > > version_;
    std::optional< std::string > description_;

  public:

    /* constructor */

    #include "dryad/Documentation/src/ctor.hpp"

    /**
     *  @brief Return the awr (temporary)
     */
    const std::optional< double >& awr() const {

      return this->awr_;
    }

    /**
     *  @brief Set the awr
     *
     *  @param[in] awr   the awr
     */
    void awr( std::optional< double > awr ) {

      this->awr_ = std::move( awr );
    }

    /**
     *  @brief Return the library
     */
    const std::optional< int >& library() const {

      return this->library_;
    }

    /**
     *  @brief Set the library
     *
     *  @param[in] library   the library
     */
    void library( std::optional< int > library ) {

      this->library_ = std::move( library );
    }

    /**
     *  @brief Return the version
     */
    const std::optional< std::pair< int, int > >& version() const {

      return this->version_;
    }

    /**
     *  @brief Set the version
     *
     *  @param[in] version   the version numbers
     */
    void version( std::optional< std::pair< int, int > > version ) {

      this->version_ = std::move( version );
    }

    /**
     *  @brief Return the description
     */
    const std::optional< std::string >& description() const {

      return this->description_;
    }

    /**
     *  @brief Set the description
     *
     *  @param[in] description   the description
     */
    void description( std::optional< std::string > description ) {

      this->description_ = std::move( description );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const Documentation& right ) const {

      return this->awr() == right.awr() &&
             this->library() == right.library() &&
             this->version() == right.version() &&
             this->description() == right.description();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const Documentation& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
