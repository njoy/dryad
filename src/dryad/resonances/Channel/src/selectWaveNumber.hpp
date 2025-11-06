static WaveNumber selectWaveNumber( const Kinematics& kinematics ) {

  if ( kinematics == Kinematics::NonRelativistic ) {

    return NonRelativisticWaveNumber();
  }
  else {

    return RelativisticWaveNumber();
  }
}
