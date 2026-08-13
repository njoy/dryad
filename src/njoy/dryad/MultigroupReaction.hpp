#ifndef NJOY_DRYAD_MULTIGROUPREACTION
#define NJOY_DRYAD_MULTIGROUPREACTION

// system includes
#include <algorithm>
#include <optional>
#include <variant>
#include <vector>

// other includes
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/ReactionCategory.hpp"
#include "njoy/dryad/MultigroupReactionProduct.hpp"
#include "njoy/dryad/MultigroupCrossSection.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The multigroup data associated to a single reaction
   */
  class MultigroupReaction {

    /* fields */
    id::ReactionID id_;

    //! @todo if in the end there are only 2 categories, we may want to remove this
    ReactionCategory category_;
    std::optional< std::vector< id::ReactionID > > partials_;

    std::optional< double > mass_difference_qvalue_;
    std::optional< double > reaction_qvalue_;

    MultigroupCrossSection xs_;
    std::vector< MultigroupReactionProduct > products_;

    /* auxiliary functions */

    auto lower_iterator( const id::ParticleID& type ) const {

      auto compare = [] ( auto&& left, auto&& right ) { return left.productIdentifier() < right; };
      return std::lower_bound( this->products().begin(), this->products().end(), type, compare );
    }

    auto lower_iterator( const id::ParticleID& type, std::size_t chain ) const {

      auto compare = [] ( auto&& left, auto&& right ) {

        std::size_t leftChain = left.chainIndex();
        return std::tie( left.productIdentifier(), leftChain ) < right;
      };
      return std::lower_bound( this->products().begin(), this->products().end(),
                               std::tie( type, chain ), compare );
    }

    auto upper_iterator( const id::ParticleID& type ) const {

      auto compare = [] ( auto&& left, auto&& right ) { return left < right.productIdentifier(); };
      return std::upper_bound( this->products().begin(), this->products().end(), type, compare );
    }

    auto upper_iterator( const id::ParticleID& type, std::size_t chain ) const {

      auto compare = [] ( auto&& left, auto&& right ) {

        std::size_t rightChain = right.chainIndex();
        return left < std::tie( right.productIdentifier(), rightChain );
      };
      return std::upper_bound( this->products().begin(), this->products().end(),
                               std::tie( type, chain ), compare );
    }

    auto iterator( const id::ParticleID& type, std::size_t index ) const {

      auto iter = lower_iterator( type );
      if ( iter != this->products().end() && iter->productIdentifier() == type ) {

        if ( index != 0 ) {

          auto upper = this->upper_iterator( type );
          if ( index < std::distance( iter, upper ) ) {

            return std::next( iter, index );
          }
        }
        else {

          return iter;
        }
      }

      return this->products().end();
    }

    auto iterator( const id::ParticleID& type, std::size_t chain, std::size_t index ) const {

      auto iter = lower_iterator( type, chain );
      if ( iter != this->products().end()
           && iter->productIdentifier() == type && iter->chainIndex() == chain ) {

        if ( index != 0 ) {

          auto upper = this->upper_iterator( type, chain );
          if ( index < std::distance( iter, upper ) ) {

            return std::next( iter, index );
          }
        }
        else {

          return iter;
        }
      }

      return this->products().end();
    }

    /**
     *  @brief Sort the reaction products
     */
    void sortProducts() {

      auto compare = [] ( auto&& left, auto&& right ) {

        std::size_t leftChain = left.chainIndex();
        std::size_t rightChain = right.chainIndex();
        return std::tie( left.productIdentifier(), leftChain ) <
               std::tie( right.productIdentifier(), rightChain );
      };

      std::sort( this->products().begin(), this->products().end(), compare );
    }

    /* constructor */

    /**
     *  @brief Private constructor
     */
    MultigroupReaction( id::ReactionID&& id,
                        ReactionCategory&& type,
                        std::optional< std::vector< id::ReactionID > >&& partials,
                        MultigroupCrossSection&& xs,
                        std::vector< MultigroupReactionProduct >&& products,
                        std::optional< double >&& mass_q,
                        std::optional< double >&& reaction_q ) :
        id_( std::move( id ) ), category_( std::move( type ) ),
        partials_( std::move( partials ) ),
        mass_difference_qvalue_( mass_q ),
        reaction_qvalue_( reaction_q ),
        xs_( std::move( xs ) ),
        products_( std::move( products ) ) {

      this->sortProducts();
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    MultigroupReaction() = default;

    MultigroupReaction( const MultigroupReaction& ) = default;
    MultigroupReaction( MultigroupReaction&& ) = default;

    MultigroupReaction& operator=( const MultigroupReaction& ) = default;
    MultigroupReaction& operator=( MultigroupReaction&& ) = default;

    /**
     *  @brief Constructor for primary reactions
     *
     *  @param[in] id           the reaction identifier
     *  @param[in] xs           the cross section of the reaction
     *  @param[in] products     the reaction products
     *  @param[in] mass_q       the mass difference Q value
     *  @param[in] reaction_q   the reaction Q value
     */
    MultigroupReaction( id::ReactionID id,
                        MultigroupCrossSection xs,
                        std::vector< MultigroupReactionProduct > products = {},
                        std::optional< double > mass_q = std::nullopt,
                        std::optional< double > reaction_q = std::nullopt ) :
        MultigroupReaction( std::move( id ),
                            ReactionCategory::Primary,
                            std::nullopt,
                            std::move( xs ),
                            std::move( products ),
                            std::move( mass_q ),
                            std::move( reaction_q ) ) {}

    /**
     *  @brief Constructor for summation reactions
     *
     *  Summation reactions do not have Q values associated to them. A cross section
     *  weighted Q value could be calculated using the partial reactions making up
     *  the summation reaction.
     *
     *  @param[in] id          the reaction identifier
     *  @param[in] partials    the identifiers of the partials of the reaction
     *  @param[in] xs          the cross section of the reaction
     *  @param[in] products    the reaction products associated to the summation reaction
     *                         (defaults to no reaction products)
     */
    MultigroupReaction( id::ReactionID id,
                        std::vector< id::ReactionID > partials,
                        MultigroupCrossSection xs,
                        std::vector< MultigroupReactionProduct > products = {} ) :
        MultigroupReaction( std::move( id ),
                            ReactionCategory::Summation,
                            std::move( partials ),
                            std::move( xs ),
                            std::move( products ),
                            std::nullopt,
                            std::nullopt ) {}

    /* methods */

    /**
     *  @brief Return the reaction identifier
     */
    const id::ReactionID& identifier() const {

      return this->id_;
    }

    /**
     *  @brief Set the reaction identifier
     *
     *  @param[in] id  the reaction identifier
     */
    void identifier( id::ReactionID id ) {

      this->id_ = std::move( id );
    }

    /**
     *  @brief Return the reaction category
     */
    const ReactionCategory& category() const {

      return this->category_;
    }

    /**
     *  @brief Return the partial reaction identifiers (not defined if this is
     *         a primary reaction)
     */
    const std::optional< std::vector< id::ReactionID > >&
    partialReactionIdentifiers() const {

      return this->partials_;
    }

    /**
     *  @brief Return the partial reaction identifiers (not defined if this is
     *         a primary reaction)
     */
    std::optional< std::vector< id::ReactionID > >&
    partialReactionIdentifiers() {

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
    void partialReactionIdentifiers( std::optional< std::vector< id::ReactionID > > partials ) {

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
    bool isSummationReaction() const {

      return this->partialReactionIdentifiers().has_value();
    }

    /**
     *  @brief Return whether or not the reaction is a primary reaction
     */
    bool isPrimaryReaction() const {

      return ! this->isSummationReaction();
    }

    /**
     *  @brief Return the number of partial reactions that make up this reaction
     */
    std::size_t numberPartialReactions() const {

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
    const std::optional< double >& massDifferenceQValue() const {

      return this->mass_difference_qvalue_;
    }

    /**
     *  @brief Set the mass difference Q value
     *
     *  @param[in] mass_q   the mass difference Q value
     */
    void massDifferenceQValue( std::optional< double > mass_q ) {

      this->mass_difference_qvalue_ = std::move( mass_q );
    }

    /**
     *  @brief Return the reaction Q value
     */
    const std::optional< double >& reactionQValue() const {

      return this->reaction_qvalue_;
    }

    /**
     *  @brief Set the reaction Q value
     *
     *  @param[in] reaction_q   the reaction Q value
     */
    void reactionQValue( std::optional< double > reaction_q ) {

      this->reaction_qvalue_ = std::move( reaction_q );
    }

    /**
     *  @brief Return the cross section
     */
    const MultigroupCrossSection& crossSection() const {

      return this->xs_;
    }

    /**
     *  @brief Return the cross section
     */
    MultigroupCrossSection& crossSection() {

      return this->xs_;
    }

    /**
     *  @brief Set the cross section
     *
     *  @param[in] xs   the new multigroup cross section
     */
    void crossSection( MultigroupCrossSection xs ) {

      this->xs_ = std::move( xs );
    }

    /**
     *  @brief Return the number of reaction products
     */
    std::size_t numberProducts() const {

      return this->products().size();
    }

    /**
     *  @brief Return whether or not the reaction has reaction products
     */
    bool hasProducts() const {

      return this->numberProducts() != 0;
    }

    /**
     *  @brief Return the reaction products
     */
    const std::vector< MultigroupReactionProduct >& products() const {

      return this->products_;
    }

    /**
     *  @brief Return the reaction products
     */
    std::vector< MultigroupReactionProduct >& products() {

      return this->products_;
    }

    /**
     *  @brief Set the reaction products
     *
     *  @param[in] products   the reaction products
     */
    void products( std::vector< MultigroupReactionProduct > products ) {

      this->products_ = std::move( products );
      this->sortProducts();
    }

    /**
     *  @brief Return whether or not a given reaction product type is present
     *         regardless of chain index
     *
     *  @param[in] type   the reaction product type
     */
    bool hasProduct( const id::ParticleID& type ) const {

      auto iter = this->iterator( type, 0 );
      return iter != this->products().end();
    }

    /**
     *  @brief Return whether or not a given reaction product type is present
     *         for a given chain index
     *
     *  @param[in] type    the reaction product type
     *  @param[in] chain   the reaction product chain index
     */
    bool hasProduct( const id::ParticleID& type,
                     std::size_t chain ) const {

      auto iter = this->iterator( type, chain, 0 );
      return iter != this->products().end();
    }

    /**
     *  @brief Return the total number of reaction products of a given type
     *         regardless of their chain index
     *
     *  @param[in] type   the reaction product type
     */
    std::size_t numberProducts( const id::ParticleID& type ) const {

      return std::distance( this->lower_iterator( type ), this->upper_iterator( type ) );
    }

    /**
     *  @brief Return the number of reaction products of a given type
     *         for a given chain index
     *
     *  @param[in] type    the reaction product type
     *  @param[in] chain   the reaction product chain index
     */
    std::size_t numberProducts( const id::ParticleID& type,
                                std::size_t chain ) const {

      return std::distance( this->lower_iterator( type, chain ), this->upper_iterator( type, chain ) );
    }

    /**
     *  @brief Return a reaction product with a given type and index
     *         regardless of chain index
     *
     *  @param[in] type    the reaction product type
     *  @param[in] index   the reaction product index (default is zero)
     */
    const MultigroupReactionProduct& product( const id::ParticleID& type,
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
     *         regardless of chain index
     *
     *  @param[in] type    the reaction product type
     *  @param[in] index   the reaction product index (default is zero)
     */
    MultigroupReactionProduct& product( const id::ParticleID& type,
                                        std::size_t index = 0 ) {

      return const_cast< MultigroupReactionProduct& >(
                 const_cast< const MultigroupReaction& >( *this ).product( type, index ) );
    }

    /**
     *  @brief Return a reaction product with a given type, chain index
     *         and index
     *
     *  @param[in] type    the reaction product type
     *  @param[in] chain   the reaction product chain index
     *  @param[in] index   the reaction product index in the given chain index
     */
    const MultigroupReactionProduct& product( const id::ParticleID& type,
                                              std::size_t chain,
                                              std::size_t index ) const {

      auto iter = this->iterator( type, chain, index );
      if ( iter != this->products().end() ) {

        return *iter;
      }
      else {

        Log::error( "There is no reaction product of type \'{}\' with chain index \'{}\' "
                    "and index \'{}\' present",
                    type.symbol(), chain, index );
        throw std::exception();
      }
    }

    /**
     *  @brief Return a reaction product with a given type, chain index
     *         and index
     *
     *  @param[in] type    the reaction product type
     *  @param[in] chain   the reaction product chain index
     *  @param[in] index   the reaction product index in the given chain index
     */
    MultigroupReactionProduct& product( const id::ParticleID& type,
                                        std::size_t chain,
                                        std::size_t index ) {

      return const_cast< MultigroupReactionProduct& >(
                 const_cast< const MultigroupReaction& >( *this ).product( type, chain, index ) );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const MultigroupReaction& right ) const {

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
    bool operator!=( const MultigroupReaction& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
