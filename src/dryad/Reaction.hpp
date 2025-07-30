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

    //! @todo if in the end there are only 2 categories, we may want to remove this
    ReactionCategory category_;
    std::optional< std::vector< id::ReactionID > > partials_;

    std::optional< double > mass_difference_qvalue_;
    std::optional< double > reaction_qvalue_;

    TabulatedCrossSection xs_;
    std::vector< ReactionProduct > products_;

    /* auxiliary functions */

    #include "dryad/Reaction/src/iterator.hpp"

  public:

    /* constructor */
    #include "dryad/Reaction/src/ctor.hpp"

    /* methods */

    //! @todo add insertion, removal of individual reaction products

    /**
     *  @brief Return the reaction identifier
     */
    const id::ReactionID& identifier() const noexcept {

      return this->id_;
    }

    /**
     *  @brief Set the reaction identifier
     *
     *  @param id.  the reaction identifier
     */
    void identifier( id::ReactionID id ) noexcept {

      this->id_ = std::move( id );
    }

    /**
     *  @brief Return the reaction category
     */
    const ReactionCategory& category() const noexcept {

      return this->category_;
    }

    /**
     *  @brief Return the partial reaction identifiers (not defined if this is
     *         a primary reaction)
     */
    const std::optional< std::vector< id::ReactionID > >&
    partialReactionIdentifiers() const noexcept {

      return this->partials_;
    }

    /**
     *  @brief Return the partial reaction identifiers (not defined if this is
     *         a primary reaction)
     */
    std::optional< std::vector< id::ReactionID > >&
    partialReactionIdentifiers() noexcept {

      return this->partials_;
    }

    /**
     *  @brief Set the partial reaction identifiers
     *
     *  This will also reset the reaction category to summation or primary
     *  as required. Using std::nullopt or an empty vector of identifiers will
     *  thus erase the partial identifiers and make the reaction a primary
     *  reaction if it wasn't a primary one already.
     *
     *  Summation reactions do not have q values associated to them, so it is
     *  up to the user to update the q values seperately when changing the
     *  partial identifiers causes the reaction category to change.
     *
     *  @param[in] partials   the partial reaction identifiers
     */
    void partialReactionIdentifiers( std::optional< std::vector< id::ReactionID > > partials ) noexcept {

      this->partials_ = std::move( partials );
      if ( this->partials_.has_value() && this->partials_.value().size() == 0 ) {

        this->partials_ = std::nullopt;
      }
      this->category_ = this->isPrimaryReaction()
                        ? ReactionCategory::Primary
                        : ReactionCategory::Summation;
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
     *  @brief Return the number of partial reactions that make up this reaction
     */
    std::size_t numberPartialReactions() const noexcept {

      return this->isSummationReaction() ? this->partialReactionIdentifiers()->size() : 0;
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
     *  @brief Set the mass difference Q value
     *
     *  @param[in] mass_q   the mass difference Q value
     */
    void massDifferenceQValue( std::optional< double > mass_q ) noexcept {

      this->mass_difference_qvalue_ = std::move( mass_q );
    }

    /**
     *  @brief Return the reaction Q value
     */
    const std::optional< double >& reactionQValue() const noexcept {

      return this->reaction_qvalue_;
    }

    /**
     *  @brief Set the reaction Q value
     *
     *  @param[in] reaction_q   the reaction Q value
     */
    void reactionQValue( std::optional< double > reaction_q ) noexcept {

      this->reaction_qvalue_ = std::move( reaction_q );
    }

    /**
     *  @brief Return the cross section
     */
    const TabulatedCrossSection& crossSection() const noexcept {

      return this->xs_;
    }

    /**
     *  @brief Set the cross section
     *
     *  @param[in] xs   the new tabulated cross section
     */
    void crossSection( TabulatedCrossSection xs ) noexcept {

      this->xs_ = std::move( xs );
    }

    /**
     *  @brief Return the number of reaction products
     */
    std::size_t numberProducts() const noexcept {

      return this->products().size();
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
     *  @brief Return the reaction products
     */
    std::vector< ReactionProduct >& products() noexcept {

      return this->products_;
    }

    /**
     *  @brief Set the reaction products
     *
     *  @param[in] products   the reaction products
     */
    void products( std::vector< ReactionProduct > products ) noexcept {

      this->products_ = std::move( products );
    }

    /**
     *  @brief Return whether or not a given reaction product type is present
     *
     *  @param[in] type   the reaction product type
     */
    bool hasProduct( const id::ParticleID& type ) const {

      auto iter = this->iterator( type );
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

      auto iter = this->iterator( type, index );
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
     *  @brief Return a reaction product with a given type and index
     *
     *  @param[in] type    the reaction product type
     *  @param[in] index   the reaction product index (default is zero)
     */
    ReactionProduct& product( const id::ParticleID& type,
                              std::size_t index = 0 ) {

      return const_cast< ReactionProduct& >( const_cast< const Reaction& >( *this ).product( type, index ) );
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
