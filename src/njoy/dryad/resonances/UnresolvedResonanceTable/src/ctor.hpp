private:

  /**
   * @brief Private constructor of UnresolvedResonanceTable
   * 
   * @param[in] channels     the channel identifiers (nc values)
   * @param[in] widths       TabulatedAverageWidths (nc arrays)
   * @param[in] spacings     TabulatedLevelSpacing
   */
  UnresolvedResonanceTable( std::vector< id::ChannelID > channels,
                            std::vector< TabulatedAverageWidths > widths,
                            TabulatedLevelSpacing spacings ) :
    channels_( std::move( channels ) ),
    widths_( std::move( widths ) ),
    spacings_( std::move( spacings ) ) {
      processTable( this->channels_, this->widths_ );
    }

public:

  /**
   * @brief Default constructor (for pybind11 purposes only)
   */
  UnresolvedResonanceTable() = default;

  UnresolvedResonanceTable( const UnresolvedResonanceTable& ) = default;
  UnresolvedResonanceTable( UnresolvedResonanceTable&& ) = default;

  UnresolvedResonanceTable& operator=( const UnresolvedResonanceTable& ) = default;
  UnresolvedResonanceTable& operator=( UnresolvedResonanceTable&& ) = default;

  /**
   * @brief Construct level spacing and average widths tables from a common energy grid
   *
   * @param[in] channels        the channel identifiers (nc values)
   * @param[in] energies        the shared energy grid (ne values)
   * @param[in] spacingValues   level spacings on the energy grid (ne values)
   * @param[in] widthValues     average widths on the energy grid (nc x ne values)
   * @param[in] dofs            optional degrees of freedom per channel
   */
  UnresolvedResonanceTable( std::vector< id::ChannelID > channels,
                            std::vector< double > energies,
                            std::vector< double > spacingValues,
                            std::vector< std::vector< double > > widthValues,
                            const std::vector< std::optional< int > >& dofs = {} ) :
    UnresolvedResonanceTable( 
                             ( verifyTable( channels, energies, spacingValues, widthValues ), channels),
                             buildWidths( channels, energies, widthValues, dofs ),
                             TabulatedLevelSpacing( energies, spacingValues ) ) {}

                                           