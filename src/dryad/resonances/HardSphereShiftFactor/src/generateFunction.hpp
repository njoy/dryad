static PolynomialSeriesRatio generateFunction( unsigned int l ) {

  switch ( l ) {

    case 0 : return { { 0 } };
    case 1 : return { { -1 }, { 1, 0, 1 } };
    case 2 : return { { -18, 0, -3 }, { 9, 0, 3, 0, 1 } };
    case 3 : return { { -675, 0, -90, 0, -6 }, { 225, 0, 45, 0, 6, 0, 1 } };
    case 4 : return { { -44100, 0, -4725, 0, -270, 0, -10 }, { 11025, 0, 1575, 0, 135, 0, 10, 0, 1 } };
    default : {

      Log::error( "Cannot handle wave functions with l above 4, got \'{}\', "
                  "contact dryad developers", l );
      throw std::exception();
    }
  }
}
