#ifndef NJOY_DRYAD_RESONANCES_CHANNELQUANTUMNUMBERS
#define NJOY_DRYAD_RESONANCES_CHANNELQUANTUMNUMBERS

// system includes
#include <algorithm>
#include <cmath>
#include <tuple>

// other includes
#include "tools/split.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief The l,S,Jpi quantum numbers of a reaction channel
   *
   *  The ChannelQuantumNumbers class contains the quantum numbers associated to
   *  a given reaction channel. Only channels that have the same Jpi contribute
   *  to the cross section of a given reaction.
   *
   *  When using comparison on the quantum numbers, we use a Jpi,l,s ordering.
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class ChannelQuantumNumbers {

    /* fields */

    double J_;
    short parity_;
    unsigned int l_;
    double s_;

    /* auxiliary functions */

    static std::tuple< unsigned int, double, double, short >
    parseNumbers( const std::string& numbers ) {

      std::tuple< unsigned int, double, double, short > tuple;

      auto convert_ratio = [] ( const std::string& string ) -> double {

        auto fractions = tools::split( string, '/' );
        if ( fractions.size() == 1 || fractions.size() == 2 ) {

          auto value = std::stoi( fractions.front() );
          if ( fractions.size() == 1 ) {

            return value;
          }
          else {

            if ( fractions.back() == "2" ) {

              return 0.5 * static_cast< double >( value );
            }
          }
        }

        throw std::exception();
      };

      if ( numbers.front() == '{' && numbers.back() == '}' ) {

        auto entries = tools::split( numbers.substr( 1, numbers.size() - 2 ), ',' );
        if ( entries.size() == 3 ) {

          if ( entries[2].back() == '+' || entries[2].back() == '-' ) {

            std::get< 3 >( tuple ) = entries[2].back() == '+' ? +1 : -1;
            entries[2].erase( entries[2].size() - 1 );

            try {

              std::get< 0 >( tuple ) = std::stoi( entries[0] );
              std::get< 1 >( tuple ) = convert_ratio( entries[1] );
              std::get< 2 >( tuple ) = convert_ratio( entries[2] );
            }
            catch ( ... ) {

              // if you get to this point, this is not a numbers string
              throw std::invalid_argument( "\'" + numbers + "\' does not define "
                                           "channel quantum numbers" );
            }

            return tuple;
          }
        }
      }

      // if you get to this point, this is not a numbers string
      throw std::invalid_argument( "\'" + numbers + "\' does not define "
                                   "channel quantum numbers" );
    }

    static std::vector< double > generateValues( double min, double max ) {

      std::vector< double > values = { min };
      while ( max > values.back() ) {

        values.push_back( values.back() + 1.0 );
      }
      return values;
    }

  public:

    /* constructor */
    #include "dryad/resonances/ChannelQuantumNumbers/src/ctor.hpp"

    /**
     *  @brief Return the orbital angular momentum l of the channel
     */
    unsigned int orbitalAngularMomentum() const { return this->l_; }

    /**
     *  @brief Return the channel spin
     */
    double spin() const { return this->s_; }

    /**
     *  @brief Return the total angular momentum J of the channel
     */
    double totalAngularMomentum() const { return this->J_; }

    /**
     *  @brief Return the parity
     */
    short parity() const { return this->parity_; }

    /**
     *  @brief Calculate allowed values for the channel spin s
     *
     *  The channel spin s can only have values between abs(i - I) and i + I
     *  where i is the spin of the incident particle (for a neutron that
     *  would be 0.5) and I is the spin of the target nucleus.
     *
     *  @param[in] i   the spin of the incident particle
     *  @param[in] I   the spin of the target nucleus
     */
    static std::vector< double >
    allowedChannelSpinValues( double i, double I ) {

      return generateValues( std::abs( i - I ), i + I );
    }

    /**
     *  @brief Calculate allowed values for the total angular momentum J
     *
     *  The total angular momentum J for a channel can only have values between
     *  abs(abs(l - I) - i) and l + I +i where l is the orbital angular momentum
     *  of the incoming wave, i is the spin of the incident particle and I is the
     *  spin of the target nucleus.
     *
     *  @param[in] l   the orbital angular momentum
     *  @param[in] i   the spin of the incident particle
     *  @param[in] I   the spin of the target nucleus
     */
    static std::vector< double >
    allowedTotalAngularMomentumValues( unsigned int l, double i, double I ) {

      return generateValues( std::abs( std::abs( l - I ) - i ), l + I + i );
    }

    /**
     *  @brief Calculate possible values for the total angular momentum J
     *
     *  The total angular momentum J for a channel can only have values between
     *  abs(l - s) and l + s where l is the orbital momentum of the incoming wave
     *  and s is the channel spin (which in turn depends on the spin i of the
     *  incident particle and spin I of the target nucleus).
     *
     *  @param[in] l   the orbital angular momentum
     *  @param[in] s   the channel spin
     */
    static std::vector< double >
    allowedTotalAngularMomentumValues( unsigned int l, double s ) {

      return generateValues( std::abs( l - s ), l + s );
    }

    /**
     *  @brief Calculate possible combinations of channel quantum numbers
     *
     *  @param[in] i      the spin of the incident particle
     *  @param[in] I      the spin of the target nucleus
     *  @param[in] lmax   the max value of the orbital angular momentum
     */
    static std::vector< ChannelQuantumNumbers >
    allowedChannelQuantumNumbers( double i, double I, unsigned int lmax ) {

      std::vector< ChannelQuantumNumbers > numbers;
      auto s_values = allowedChannelSpinValues( i, I );

      for ( unsigned int l = 0; l <= lmax; ++l ) {

        for ( unsigned int s = 0; s < s_values.size(); ++s ) {

          auto j_values = allowedTotalAngularMomentumValues( l, s_values[s] );
          for ( unsigned int j = 0; j < j_values.size(); ++j ) {

            numbers.emplace_back( l, s_values[s], j_values[j],
                                  l%2 == 0 ? +1 : -1 );
          }
        }
      }
      std::sort( numbers.begin(), numbers.end() );
      return numbers;
    }

    /**
     *  @brief Return a string representation of the quantum numbers
     */
    std::string symbol() const {

      auto toHalfIntegerString = [] ( const double a ) {

        double half;
        return std::modf( a, &half ) == 0. ?
                   // a is a full integer
                   std::to_string( static_cast< int >( half ) ) :
                   // a is a half integer value
                   std::to_string( 2 * static_cast< int >( half ) + 1 ) + "/2";
      };

      return "{" + std::to_string( this->orbitalAngularMomentum() ) + ","
                 + toHalfIntegerString( this->spin() ) + ","
                 + toHalfIntegerString( this->totalAngularMomentum() )
                 + ( this->parity() > 0 ? "+" : "-" ) + "}";
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const ChannelQuantumNumbers& left,
                            const ChannelQuantumNumbers& right ) {

      return std::tie( left.J_, left.parity_, left.l_, left.s_ ) ==
             std::tie( right.J_, right.parity_, right.l_, right.s_ );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const ChannelQuantumNumbers& left,
                            const ChannelQuantumNumbers& right ) {

      return ! ( left == right );
    }

    /**
     *  @brief Less than comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator<( const ChannelQuantumNumbers& left,
                           const ChannelQuantumNumbers& right ) {

      return std::tie( left.J_, left.parity_, left.l_, left.s_ ) <
             std::tie( right.J_, right.parity_, right.l_, right.s_ );
    }

    /**
     *  @brief Greater than comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend auto operator>( const ChannelQuantumNumbers& left,
                           const ChannelQuantumNumbers& right ) {

      return right < left;
    }

    /**
     *  @brief Less than or equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend auto operator<=( const ChannelQuantumNumbers& left,
                            const ChannelQuantumNumbers& right ) {

      return ! ( right < left );
    }

    /**
     *  @brief Greater than or equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend auto operator>=( const ChannelQuantumNumbers& left,
                            const ChannelQuantumNumbers& right ) {

      return ! ( left < right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
