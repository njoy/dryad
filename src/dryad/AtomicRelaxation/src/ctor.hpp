/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
AtomicRelaxation() = default;

AtomicRelaxation( const AtomicRelaxation& ) = default;
AtomicRelaxation( AtomicRelaxation&& ) = default;

AtomicRelaxation& operator=( const AtomicRelaxation& ) = default;
AtomicRelaxation& operator=( AtomicRelaxation&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param element      the element identifier
 *  @param subshells    the electron subshell configuration data
 */
AtomicRelaxation( id::ElementID element,
                  std::vector< atomic::ElectronSubshellConfiguration > subshells ) :
    element_id_( std::move( element ) ), subshells_( std::move( subshells ) ) {}
