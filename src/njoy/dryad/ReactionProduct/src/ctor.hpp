/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ReactionProduct() = default;

ReactionProduct( const ReactionProduct& ) = default;
ReactionProduct( ReactionProduct&& ) = default;

ReactionProduct& operator=( const ReactionProduct& ) = default;
ReactionProduct& operator=( ReactionProduct&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param product         the reaction product identifier
 *  @param multiplicity    the multiplicity of the reaction product
 *  @param distribution    the optional reaction product distribution data
 *  @param averageCosine   the optional average reaction product cosine
 *  @param averageEnergy   the optional average reaction product energy
 *  @param normalise       option to indicate whether or not to normalise
 *                         all probability data (default: no normalisation)
 */
ReactionProduct( id::ParticleID product,
                 Multiplicity multiplicity,
                 std::optional< DistributionData > distribution = std::nullopt,
                 std::optional< TabulatedAverageCosine > averageCosine = std::nullopt,
                 std::optional< TabulatedAverageEnergy > averageEnergy = std::nullopt,
                 std::optional< id::ParticleID > parent = std::nullopt,
                 std::size_t index = 0,
                 bool normalise = false ) :
    product_( std::move( product ) ),
    parent_( std::move( parent ) ),
    chain_index_( index ),
    multiplicity_( std::move( multiplicity ) ),
    distribution_( std::move( distribution ) ),
    average_cosine_( std::move( averageCosine ) ),
    average_energy_( std::move( averageEnergy ) ) {

  if ( normalise ) {

    this->normalise();
  }
}

/**
 *  @brief Convenience constructor
 *
 *  @param product         the reaction product identifier
 *  @param multiplicity    the reaction product multiplicity
 *  @param averageEnergy   the average reaction product energy
 */
ReactionProduct( id::ParticleID product,
                 Multiplicity multiplicity,
                 TabulatedAverageEnergy averageEnergy ) :
    ReactionProduct( std::move( product ),
                     std::move( multiplicity ),
                     std::nullopt,
                     std::nullopt,
                     std::move( averageEnergy ),
                     std::nullopt,
                     0,
                     false ) {}
