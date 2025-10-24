static PolynomialSeriesRatio generateFunction( unsigned int l ) {

  switch ( l ) {

    case 0 : return { { 0, 1 } };
    case 1 : return { { 0, 0, 0, 1 }, { 1, 0, 1 } };
    case 2 : return { { 0, 0, 0, 0, 0, 1 }, { 9, 0, 3, 0, 1 } };
    case 3 : return { { 0, 0, 0, 0, 0, 0, 0, 1 }, { 225, 0, 45, 0, 6, 0, 1 } };
    case 4 : return { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, { 11025, 0, 1575, 0, 135, 0, 10, 0, 1 } };
    default : {

      Log::error( "Cannot handle wave functions with l above 4, got \'{}\', "
                  "contact dryad developers", l );
      throw std::exception();
    }
  }
}
