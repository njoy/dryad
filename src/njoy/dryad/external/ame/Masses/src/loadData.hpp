static void loadData() {

  std::string config = configuration().get( "ame2020" );
  filesystem::path path( config );
  if ( ! path.is_absolute() ) {

    path = filesystem::path( std::getenv( "NJOY_DATAPATH" ) );
    path /= config;
  }

  std::ifstream in( path.c_str(),
                    std::ios::in | std::ios::binary | std::ios::ate );
  if ( not in ) {

    Log::error( "Could not open file \'{}\'", path.string() );
    throw std::exception();
  }

  const auto file_size = in.tellg();
  in.seekg( 0, std::ios::beg );
  std::string file;
  file.resize( file_size / sizeof( char ) );
  in.read( &( file[ 0 ] ), file_size );

//  // fortran statements
//  using namespace njoy::tools::disco;
//  using Identification = Record< Character< 5 >, Integer< 5 >, Integer< 5 >, Integer< 5 >,
//                                 Integer< 5 >, Integer< 5 >, Integer< 5 >, Real< 12 >, Real< 12 > >;
//  using Level = Record< Integer< 3 >, Column< 1 >, Real< 10 >, Column< 1 >, Real< 5 >,
//                        Integer< 3 >, Column< 1 >, Real< 10 >, Integer< 3 > >;
//  using Gamma = Record< Column< 39 >, Integer< 4 >, Column< 1 >, Real< 10 >,
//                        Column< 1 >, Real< 10 >, Column< 1 >, Real< 10 >,
//                        Column< 1 >, Real< 10 > >;
//
//  // parse the file and get the data we need
//  auto begin = file.begin();
//  auto end = file.end();
//  while ( begin != end ) {
//
//    std::string symb;
//    int a, z, Nol, Nog, Nmax, Nc;
//    double Sn, Sp;
//    Identification::read( begin, end, symb, a, z, Nol, Nog, Nmax, Nc, Sn, Sp );
//
//    int za = z * 1000 + a;
//    Sn *= constants::mega;
//    Sp *= constants::mega;
//
//    if ( Nol < 0 ) {
//
//      Log::error( "Number of levels for isotope {} in ripl-3 levels file is less than zero", symb );
//      throw std::exception();
//    }
//
//    std::size_t number_levels = static_cast< std::size_t >( Nol );
//    for ( std::size_t i = 0; i < number_levels; ++i ) {
//
//      int N1, p, Ng;
//      double Elv, s, Thalf;
//      Level::read( begin, end, N1, Elv, s, p, Thalf, Ng );
//
//      id::ParticleID particle = id::ParticleID::nuclide( za, N1 - 1 );
//      Elv *= constants::mega;
//
//      if ( Ng < 0 ) {
//
//        Log::error( "Number of gammas for isotope {} and level index {} in ripl-3 levels file is less than zero", symb, N1 );
//        throw std::exception();
//      }
//
//      std::size_t number_gammas = static_cast< std::size_t >( Ng );
//      for ( std::size_t j = 0; j < number_gammas; ++j ) {
//
//        int Nf;
//        double Eg, Pg, Pe, ICC;
//        Gamma::read( begin, end, Nf, Eg, Pg, Pe, ICC );
//      }
//
//      Levels::levels_[ particle ] = { particle, Elv,
//                                      s < 0 ? std::nullopt : std::make_optional( s ),
//                                      p == 0 ? std::nullopt : std::make_optional( p ),
//                                      Thalf < 0 ? std::nullopt : std::make_optional( Thalf ) };
//    }
//  }
}
