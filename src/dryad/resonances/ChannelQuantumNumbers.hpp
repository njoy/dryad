#ifndef NJOY_DRYAD_RESONANCES_CHANNELQUANTUMNUMBERS
#define NJOY_DRYAD_RESONANCES_CHANNELQUANTUMNUMBERS

// system includes

// other includes

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
   */
  class ChannelQuantumNumbers {

    /* fields */

    unsigned int l_;
    double s_;
    double J_;
    short parity_;

    /* auxiliary functions */

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

      return generateValues( std::abs( std::abs( l - I ) - i ), l + I +i );
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

      return generateValues( std::abs(l - s), l + s );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ChannelQuantumNumbers& right ) const {

      return this->orbitalAngularMomentum() == right.orbitalAngularMomentum() &&
             this->spin() == right.spin() &&
             this->totalAngularMomentum() == right.totalAngularMomentum() &&
             this->parity() == right.parity();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ChannelQuantumNumbers& right ) const {

      return ! this->operator==( right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
