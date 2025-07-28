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
   *  @brief Metadata associated to the dryad data
   */
  class Metadata {

    //! @todo remove once we get the particle database
    std::optional< double > awr_;

    /* fields */
    std::optional< int > library_;
    std::optional< std::pair< int, int > > version_;
    std::optional< double > temperature_;
    std::optional< std::string > description_;

  public:

    /* constructor */

    #include "dryad/Metadata/src/ctor.hpp"

    /**
     *  @brief Return the awr (temporary)
     */
    const std::optional< double >& awr() const noexcept {

      return this->awr_;
    }

    /**
     *  @brief Set the awr
     *
     *  @param[in] awr   the awr
     */
    void awr( std::optional< double > awr ) noexcept {

      this->awr_ = std::move( awr );
    }

    /**
     *  @brief Return the library
     */
    const std::optional< int >& library() const noexcept {

      return this->library_;
    }

    /**
     *  @brief Set the library
     *
     *  @param[in] library   the library
     */
    void library( std::optional< int > library ) noexcept {

      this->library_ = std::move( library );
    }

    /**
     *  @brief Return the temperature
     */
    const std::optional< std::pair< int, int > >& version() const noexcept {

      return this->version_;
    }

    /**
     *  @brief Set the version
     *
     *  @param[in] version   the version numbers
     */
    void version( std::optional< std::pair< int, int > > version ) noexcept {

      this->version_ = std::move( version );
    }

    /**
     *  @brief Return the temperature
     */
    const std::optional< double >& temperature() const noexcept {

      return this->temperature_;
    }

    /**
     *  @brief Set the temperature
     *
     *  @param[in] temperature   the temperature
     */
    void temperature( std::optional< double > temperature ) noexcept {

      this->temperature_ = std::move( temperature );
    }

    /**
     *  @brief Return the description
     */
    const std::optional< std::string >& description() const noexcept {

      return this->description_;
    }

    /**
     *  @brief Set the description
     *
     *  @param[in] description   the description
     */
    void description( std::optional< std::string > description ) noexcept {

      this->description_ = std::move( description );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const Metadata& right ) const noexcept {

      return this->awr() == right.awr() && this->library() == right.library() &&
             this->version() == right.version() && this->temperature() == right.temperature() &&
             this->description() == right.description();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const Metadata& right ) const noexcept {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
