private:

  /**
   * @brief Private constructor of UnresolvedResonanceTable
   * 
   */
  UnresolvedResonanceTable( std::vector< id::ChannelID > channels,
                            std::vector< TabulatedAverageWidths > widths,
                            TabulatedLevelSpacing spacings ) :
    channels_( std::move( channels ) ),
    widths_( std::move( widths ) ),
    spacings_( std::move( spacings ) ) {}

public:

  /**
   * @brief Default constructor (for pybind11 purposes only)
   */
  UnresolvedResonanceTable() = default;

  UnresolvedResonanceTable( const UnresolvedResonanceTable& ) = default;
  UnresolvedResonanceTable( UnresolvedResonanceTable&& ) = default;

  UnresolvedResonanceTable& operator=( const UnresolvedResonanceTable& ) = default;
  UnresolvedResonanceTable& operator=( UnresolvedResonanceTable&& ) = default;