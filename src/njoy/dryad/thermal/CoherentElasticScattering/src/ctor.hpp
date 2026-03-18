/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CoherentElasticScattering() = default;

CoherentElasticScattering( const CoherentElasticScattering& ) = default;
CoherentElasticScattering( CoherentElasticScattering&& ) = default;

CoherentElasticScattering& operator=( const CoherentElasticScattering& ) = default;
CoherentElasticScattering& operator=( CoherentElasticScattering&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param braggEdges   the Bragg edge data
 */
CoherentElasticScattering( std::vector< BraggEdgeData > braggEdges ) :
    edges_( std::move( braggEdges ) ) {

  this->sortAndExtractTemperatures();
}
