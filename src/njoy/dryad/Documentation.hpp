#ifndef NJOY_DRYAD_DOCUMENTATION
#define NJOY_DRYAD_DOCUMENTATION

// system includes
#include <optional>
#include <string>
#include <tuple>

// other includes

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Documentation associated to the dryad data
   */
  class Documentation {

    /* fields */
    std::optional< int > library_;
    std::optional< std::pair< int, int > > version_;
    std::optional< std::string > description_;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    Documentation() = default;

    Documentation( const Documentation& ) = default;
    Documentation( Documentation&& ) = default;

    Documentation& operator=( const Documentation& ) = default;
    Documentation& operator=( Documentation&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] library       the library number
     *  @param[in] version       the version numbers (major and minor)
     *  @param[in] description   the description
     */
    Documentation( std::optional< int > library,
                   std::optional< std::pair< int, int > > version,
                   std::optional< std::string > description ) :
        library_( std::move( library ) ),
        version_( std::move( version ) ),
        description_( std::move( description ) ) {}

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

      return std::tie( this->library(), this->version(), this->description() ) ==
             std::tie( right.library(), right.version(), right.description() );
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
