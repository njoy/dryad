#ifndef NJOY_DRYAD_REACTION
#define NJOY_DRYAD_REACTION

// system includes
#include <algorithm>
#include <optional>
#include <variant>
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/id/ReactionID.hpp"
#include "dryad/ReactionCategory.hpp"
#include "dryad/ReactionProduct.hpp"
#include "dryad/TabulatedCrossSection.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The data associated to a single reaction
   */
  class Reaction {

    /* fields */
    id::ReactionID id_;

    ReactionCategory category_;
    std::optional< std::vector< id::ReactionID > > partials_;

    std::optional< double > mass_difference_qvalue_;
    std::optional< double > reaction_qvalue_;

    TabulatedCrossSection xs_;
    std::vector< ReactionProduct > products_;

    bool linearised_;

  public:

    /* constructor */
    #include "dryad/Reaction/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the reaction identifier
     */
    const id::ReactionID& identifier() const noexcept {

      return this->id_;
    }

    /**
     *  @brief Return the reaction category
     */
    const ReactionCategory& category() const noexcept {

      return this->category_;
    }

    /**
     *  @brief Return the summation reaction identifiers (not defined if this is
     *         a primary reaction)
     */
    const std::optional< std::vector< id::ReactionID > >&
    partialReactionIdentifiers() const noexcept {

      return this->partials_;
    }

    /**
     *  @brief Return whether or not the reaction is a summation reaction
     */
    bool isSummationReaction() const noexcept {

      return this->partialReactionIdentifiers().has_value();
    }

    /**
     *  @brief Return whether or not the reaction is a primary reaction
     */
    bool isPrimaryReaction() const noexcept {

      return ! this->isSummationReaction();
    }

    /**
     *  @brief Return the mass difference Q value
     *
     *  The mass difference Q value is defined as the energy equivalence of the
     *  difference in the initial atomic mass (the projectile and target mass)
     *  and the final atomic mass (the residual mass and all reactor product
     *  masses). All particles involved are supposed to be in the ground state.
     */
    const std::optional< double >& massDifferenceQValue() const noexcept {

      return this->mass_difference_qvalue_;
    }

    /**
     *  @brief Return the reaction Q value
     */
    const std::optional< double >& reactionQValue() const noexcept {

      return this->reaction_qvalue_;
    }

    /**
     *  @brief Return the cross section
     */
    const TabulatedCrossSection& crossSection() const noexcept {

      return this->xs_;
    }

    /**
     *  @brief Return the number of reaction products
     */
    std::size_t numberProducts() const noexcept {

      return this->products_.size();
    }

    /**
     *  @brief Return whether or not the reaction has reaction products
     */
    bool hasProducts() const noexcept {

      return this->numberProducts() != 0;
    }

    /**
     *  @brief Return the reaction products
     */
    const std::vector< ReactionProduct >& products() const noexcept {

      return this->products_;
    }

    /**
     *  @brief Return whether or not a given reaction product type is present
     *
     *  @param[in] type   the reaction product type
     */
    bool hasProduct( const id::ParticleID& type ) const {

      auto functor = [&type] ( auto&& product )
                             { return product.identifier() == type; };

      auto iter = std::find_if( this->products().begin(),
                                this->products().end(),
                                functor );
      return iter != this->products().end();
    }

    /**
     *  @brief Return the number of reaction products of a given type
     *
     *  @param[in] type   the reaction product type
     */
    std::size_t numberProducts( const id::ParticleID& type ) const noexcept {

      auto functor = [&type] ( auto&& product )
                             { return product.identifier() == type; };

      return std::count_if( this->products().begin(),
                            this->products().end(),
                            functor );
    }

    /**
     *  @brief Return a reaction product with a given type and index
     *
     *  @param[in] type    the reaction product type
     *  @param[in] index   the reaction product index (default is zero)
     */
    const ReactionProduct& product( const id::ParticleID& type,
                                    std::size_t index = 0 ) const {

      auto functor = [&type] ( auto&& product )
                             { return product.identifier() == type; };

      auto iter = std::find_if( this->products().begin(), this->products().end(), functor );
      std::size_t current = index;
      while ( current != 0 && iter != this->products().end() ) {

        iter = std::find_if( iter + 1, this->products().end(), functor );
        --current;
      }

      if ( iter != this->products().end() ) {

        return *iter;
      }
      else {

        Log::error( "There is no reaction product of type \'{}\' with index \'{}\' present",
                    type.symbol(), index );
        throw std::exception();
      }
    }

    /**
     *  @brief Return whether or not the reaction data is linearised
     */
    bool isLinearised() const noexcept {

      return this->linearised_;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const Reaction& right ) const noexcept {

      return this->identifier() == right.identifier() &&
             this->category() == right.category() &&
             this->massDifferenceQValue() == right.massDifferenceQValue() &&
             this->reactionQValue() == right.reactionQValue() &&
             this->partialReactionIdentifiers() == right.partialReactionIdentifiers() &&
             this->crossSection() == right.crossSection() &&
             this->products() == right.products();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const Reaction& right ) const noexcept {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
