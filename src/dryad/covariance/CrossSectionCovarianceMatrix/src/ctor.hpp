private:

CrossSectionCovarianceMatrix( Parent&& base ) :
  Parent( std::move( base ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CrossSectionCovarianceMatrix() = default;

CrossSectionCovarianceMatrix( const CrossSectionCovarianceMatrix& ) = default;
CrossSectionCovarianceMatrix( CrossSectionCovarianceMatrix&& ) = default;

CrossSectionCovarianceMatrix& operator=( const CrossSectionCovarianceMatrix& ) = default;
CrossSectionCovarianceMatrix& operator=( CrossSectionCovarianceMatrix&& ) = default;

/**
 *  @brief Constructor for an on-diagonal cross section covariance matrix
 *
 *  @param[in] metadata      the row and column metadata
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag (default is true)
 *  @param[in] scaling       the variance scaling information (default is none)
 */
CrossSectionCovarianceMatrix( CrossSectionMetadata metadata,
                              Matrix< double > covariances,
                              bool relative = true,
                              std::optional< VarianceScaling > scaling = std::nullopt ) :
  CovarianceBlock( std::move( metadata ), std::move( covariances ), relative ),
  scaling_( std::move( scaling ) ) {}

/**
 *  @brief Constructor for an off-diagonal cross section covariance matrix
 *
 *  @param[in] rowMetadata       the row metadata
 *  @param[in] columnMetadata    the column metadata
 *  @param[in] covariances       the covariance matrix
 *  @param[in] relative          the relative covariance flag (default is true)
 */
CrossSectionCovarianceMatrix( CrossSectionMetadata rowMetadata,
                              CrossSectionMetadata columnMetadata,
                              Matrix< double > covariances,
                              bool relative = true ) :
  CovarianceBlock( std::move( rowMetadata ), std::move( columnMetadata ),
                   std::move( covariances ), relative ),
  scaling_( std::nullopt ) {}

/**
 *  @brief Constructor for an on-diagonal cross section covariance matrix
 *
 *  @param[in] reaction      the reaction identifier
 *  @param[in] energies      the energy boundaries
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag (default is true)
 *  @param[in] scaling       the variance scaling information (default is none)
 */
CrossSectionCovarianceMatrix( id::ParticleID projectile,
                              id::ParticleID target,
                              id::ReactionID reaction,
                              std::vector< double > energies,
                              Matrix< double > covariances,
                              bool relative = true,
                              std::optional< VarianceScaling > scaling = std::nullopt ) :
    CrossSectionCovarianceMatrix( CrossSectionMetadata( std::move( projectile ),
                                                        std::move( target ),
                                                        std::move( reaction ),
                                                        std::move( energies ) ),
                                  std::move( covariances ), relative, std::move( scaling ) ) {}

/**
 *  @brief Constructor for an off-diagonal cross section covariance matrix
 *
 *  @param[in] rowReaction         the row reaction identifier
 *  @param[in] rowEnergies         the row energy boundaries
 *  @param[in] columnReaction      the column reaction identifier
 *  @param[in] columnEnergies      the column energy boundaries
 *  @param[in] covariances         the covariance matrix
 *  @param[in] relative            the relative covariance flag (default is true)
 */
CrossSectionCovarianceMatrix( id::ReactionID rowReaction,
                              std::vector< double > rowEnergies,
                              id::ReactionID columnReaction,
                              std::vector< double > columnEnergies,
                              Matrix< double > covariances,
                              bool relative = true ) :
  CrossSectionCovarianceMatrix( CrossSectionMetadata( std::move( rowReaction ),
                                                      std::move( rowEnergies ) ),
                                CrossSectionMetadata( std::move( columnReaction ),
                                                      std::move( columnEnergies ) ),
                                std::move( covariances ), relative ) {}
