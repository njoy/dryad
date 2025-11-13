static
matrix::Matrix< std::complex< double > >
makeGMatrix( const ResonanceTable& table ) {

  matrix::Matrix< std::complex< double > > matrix( table.numberChannels(),
                                                   table.numberEnergies() );

  for ( unsigned int c = 0; c < table.numberChannels(); ++c ) {

    for ( unsigned int lambda = 0; lambda < table.numberEnergies(); ++lambda ) {

      matrix( c, lambda ) = table.reducedWidthAmplitudes()[c][lambda];
    }
  }

  return matrix;
}
