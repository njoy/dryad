/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
AtomicRelaxation() = default;

AtomicRelaxation( const AtomicRelaxation& ) = default;
AtomicRelaxation( AtomicRelaxation&& ) = default;

AtomicRelaxation& operator=( const AtomicRelaxation& ) = default;
AtomicRelaxation& operator=( AtomicRelaxation&& ) = default;

/**
 *  @brief Constructor with documentation
 *
 *  @param[in] element         the element identifier
 *  @param[in] subshells       the electron subshell configuration data
 *  @param[in] documentation   the documentation
 *  @param[in] normalise       option to indicate whether or not to normalise
 *                             all probability data (default: no normalisation)
 */
AtomicRelaxation( Documentation documentation,
                  id::ElementID element,
                  std::vector< atomic::ElectronSubshellConfiguration > subshells,
                  bool normalise = false ) :
    documentation_( std::move( documentation ) ),
    element_id_( std::move( element ) ),
    subshells_( std::move( subshells ) ) {

  this->sort();
  if ( normalise ) {

    this->normalise();
  }
}

/**
 *  @brief Constructor
 *
 *  @param[in] element      the element identifier
 *  @param[in] subshells    the electron subshell configuration data
 *  @param[in] normalise    option to indicate whether or not to normalise
 *                          all probability data (default: no normalisation)
 */
AtomicRelaxation( id::ElementID element,
                  std::vector< atomic::ElectronSubshellConfiguration > subshells,
                  bool normalise = false ) :
    AtomicRelaxation( {}, std::move( element ), std::move( subshells ),
                      normalise ) {}
