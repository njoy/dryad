void updateWaveFunctions() {

  this->penetrability_ = selectPenetrabilityFunction(
                          this->identifier().quantumNumbers().orbitalAngularMomentum(),
                          this->outgoingParticlePair() );
  this->shift_factor_ = selectShiftFactorFunction(
                          this->identifier().quantumNumbers().orbitalAngularMomentum(),
                          this->outgoingParticlePair() );
  this->phase_shift_ = selectPhaseShiftFunction(
                          this->identifier().quantumNumbers().orbitalAngularMomentum(),
                          this->outgoingParticlePair() );
  this->phase_shift_difference_ = selectPhaseShiftDifferenceFunction(
                          this->identifier().quantumNumbers().orbitalAngularMomentum(),
                          this->outgoingParticlePair() );
}
