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
   * @brief Construct ResonanceTable from InterpolatedTable objects
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
    unifyEnergyGrids( this->widths_, this->spacings_ );
    verifyTable( this->channels_, this->widths_, this->spacings_);
  }

                                           