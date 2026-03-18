/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
BraggEdgeData() = default;

BraggEdgeData( const BraggEdgeData& ) = default;
BraggEdgeData( BraggEdgeData&& ) = default;

BraggEdgeData& operator=( const BraggEdgeData& ) = default;
BraggEdgeData& operator=( BraggEdgeData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param temperature   the temperature
 *  @param energies      the Bragg edge energies
 *  @param values        the structure factor values
 */
BraggEdgeData( double temperature,
               std::vector< double > energies,
               std::vector< double > values ) :
  temperature_( temperature ),
  energies_( std::move( energies ) ),
  structure_factors_( std::move( values ) ) {}
