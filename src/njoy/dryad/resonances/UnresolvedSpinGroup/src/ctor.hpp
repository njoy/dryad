/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
UnresolvedSpinGroup() = default;
 
UnresolvedSpinGroup( const UnresolvedSpinGroup& ) = default;
UnresolvedSpinGroup( UnresolvedSpinGroup&& ) = default;
 
UnresolvedSpinGroup& operator=( const UnresolvedSpinGroup& ) = default;
UnresolvedSpinGroup& operator=( UnresolvedSpinGroup&& ) = default;
 
/**
 *  @brief Constructor
 *
 *  If the channels are not sorted, they will get sorted through the order
 *  of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical
 *  sorting order).
 *
 *  @param[in] channels     the channels in the spin group
 *  @param[in] resonances   the unresolved resonance table of the spin group
 */
// TODO: a future overload may accept a calculator and/or sampler
//       configuration once those interfaces are decided on (mirroring
//       SpinGroup's ctor that takes a Formalism and BoundaryCondition and
//       calls selectCalculator). For now the spin group only stores the
//       channels and the average parameter table.
UnresolvedSpinGroup( std::vector< UnresolvedChannel > channels,
                     UnresolvedResonanceTable resonances ) :
                  channels_( std::move( channels ) ),
                  table_( std::move( resonances ) ) {
  this->processChannels();
  verifySpinGroup( this->channels(), this->resonanceTable() );
  }
