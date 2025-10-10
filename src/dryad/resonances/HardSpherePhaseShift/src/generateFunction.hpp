static scion::math::PolynomialSeriesRatio< double, double >
generateFunction( unsigned int l ) {

  switch ( l ) {

    case 0 : return { { 0 } };
    case 1 : return { { 0, 1 } };
    case 2 : return { { 0, 3 }, { 3, 0, -1 } };
    case 3 : return { { 0, 15, 0, -1 }, { 15, 0, -6 } };
    case 4 : return { { 0, 105, 0, -10 }, { 105, 0, -45, 0, 1 } };
    default : {

      Log::error( "Cannot handle wave functions with l above 4, got \'{}\', "
                  "contact dryad developers", l );
      throw std::exception();
    }
  }
}
