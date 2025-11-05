/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
SpinGroup() = default;

SpinGroup( const SpinGroup& ) = default;
SpinGroup( SpinGroup&& ) = default;

SpinGroup& operator=( const SpinGroup& ) = default;
SpinGroup& operator=( SpinGroup&& ) = default;

/**
 *  @brief Constructor
 *
 *  If the channels are not sorted, they will get sorted through the order
 *  of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical
 *  sorting order).
 *
 *  @param[in] channels     the channels in the spingroup
 *  @param[in] resonances   the resonance table of the spingroup
 *  @param[in] formalism    the r matrix formalism option to be applied
 *  @param[in] boundary     the boundary condition option to be applied
 */
SpinGroup( std::vector< Channel > channels,
           ResonanceTable resonances,
           const Formalism& formalism,
           const BoundaryCondition& boundary ) :
    channels_( std::move( channels ) ),
    table_( std::move( resonances ) ),
    formalism_( formalism ),
    boundary_condition_( boundary ) {

  this->processChannels();
  this->calculator_ = selectCalculator( this->formalism(), this->boundaryCondition(),
                                        this->channels() );
  verifySpinGroup( this->channels(), this->resonanceTable() );
}

private:

/**
 *  @brief Private intermediate constructor
 */
SpinGroup( std::tuple< std::vector< Channel >, ResonanceTable > data,
           const Formalism& formalism,
           const BoundaryCondition& boundary ) :
    SpinGroup( std::move( std::get< 0 >( data ) ),
               std::move( std::get< 1 >( data ) ),
               formalism, boundary ) {}

public:

/**
 *  @brief Constructor
 *
 *  If the channels are not sorted, they will get sorted through the order
 *  of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical
 *  sorting order).
 *
 *  @param[in] channels     the channel data in the spingroup
 *  @param[in] formalism    the r matrix formalism option to be applied
 *  @param[in] boundary     the boundary condition option to be applied
 */
SpinGroup( std::vector< ChannelData > channels,
           const Formalism& formalism,
           const BoundaryCondition& boundary ) :
    SpinGroup( createData( std::move( channels ) ), formalism, boundary ) {}
