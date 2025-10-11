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
