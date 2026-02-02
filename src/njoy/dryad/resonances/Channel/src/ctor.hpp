/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
Channel() = default;

Channel( const Channel& ) = default;
Channel( Channel&& ) = default;

Channel& operator=( const Channel& ) = default;
Channel& operator=( Channel&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] identifier      the channel identifier
 *  @param[in] incident        the current incident particle pair
 *  @param[in] outgoing        the outgoing particle pair
 *  @param[in] qValue          the Q value associated with the transition from
 *                             the incident to the outgoing particle pair
 *  @param[in] boundary        the boundary condition
 *  @param[in] radii           the channel radii for the calculation of the
 *                             wave functions
 *  @param[in] kinematics      the kinematics type applied to the channel
 *  @param[in] penetrability   the penetrability of the channel
 *  @param[in] shiftFactor     the shift factor of the channel
 *  @param[in] phaseshift      the phase shift of the channel
 *  @param[in] difference      the phase shift differenceof the channel
 */
Channel( id::ChannelID identifier,
         ParticlePair incident,
         std::optional< ParticlePair > outgoing,
         double qValue,
         std::optional< double > boundary,
         ChannelRadii radii,
         Kinematics kinematics,
         std::optional< Background > background,
         Penetrability penetrability,
         ShiftFactor shiftFactor,
         PhaseShift phaseShift,
         PhaseShiftDifference difference ) :
    id_( std::move( identifier ) ),
    incident_pair_( std::move( incident ) ),
    outgoing_pair_( std::move( outgoing ) ),
    q_( qValue ),
    boundary_condition_( std::move( boundary ) ),
    background_( std::move( background ) ),
    radii_( std::move( radii ) ),
    wave_number_( selectWaveNumber( kinematics ) ),
    penetrability_( std::move( penetrability ) ),
    shift_factor_( std::move( shiftFactor ) ),
    phase_shift_( std::move( phaseShift ) ),
    phase_shift_difference_( std::move( difference ) ),
    spin_factor_( calculateSpinFactor( identifier.quantumNumbers(), outgoing ) ) {}

/**
 *  @brief Constructor without wave functions
 *
 *  @param[in] identifier   the channel identifier
 *  @param[in] incident     the current incident particle pair
 *  @param[in] outgoing     the outgoing particle pair
 *  @param[in] qValue       the Q value associated with the transition from
 *                          the incident to the outgoing particle pair
 *  @param[in] boundary     the boundary condition
 *  @param[in] radii        the channel radii for the calculation of the
 *                          wave functions
 *  @param[in] kinematics   the kinematics type applied to the channel (default is
 *                          non-relativistic)
 */
Channel( id::ChannelID identifier,
         ParticlePair incident,
         std::optional< ParticlePair > outgoing,
         double qValue,
         std::optional< double > boundary,
         ChannelRadii radii,
         Kinematics kinematics = Kinematics::NonRelativistic,
         std::optional< Background > background = std::nullopt ) :
    Channel( std::move( identifier ), std::move( incident ),
             std::move( outgoing ), qValue,
             std::move( boundary ), std::move( radii ),
             std::move( kinematics ),
             std::move( background ),
             selectPenetrabilityFunction( identifier.quantumNumbers().orbitalAngularMomentum(),
                                          outgoing ),
             selectShiftFactorFunction( identifier.quantumNumbers().orbitalAngularMomentum(),
                                        outgoing ),
             selectPhaseShiftFunction( identifier.quantumNumbers().orbitalAngularMomentum(),
                                       outgoing ),
             selectPhaseShiftDifferenceFunction( identifier.quantumNumbers().orbitalAngularMomentum(),
                                                 outgoing ) ) {}
