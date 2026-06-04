static void insertData( int z ) {

  // set the absolute datapath if we haven't already
  if ( ! Levels::ripl3_levels_datapath_.has_value() ) {

    std::string config = configuration().get( "ripl3_levels" );
    std::filesystem::path path( config );
    if ( ! path.is_absolute() ) {

      path = std::filesystem::path( std::getenv( "NJOY_DATAPATH" ) );
      path /= config;
    }
    Levels::ripl3_levels_datapath_ = path.string();
  }

  // open the ripl-3 file
  std::filesystem::path path( ripl3_levels_datapath_.value() );
  std::string file = z < 10 ? "z00" : z < 100 ? "z0" : "z";
  file += std::to_string( z ) + ".dat";
  path /= file;

  std::ifstream in( path.c_str(),
                    std::ios::in | std::ios::binary | std::ios::ate );
  if ( not in ) {

    Log::error( "Could not open file \'{}\'", path.string() );
    throw std::exception();
  }

  const auto file_size = in.tellg();
  in.seekg( 0, std::ios::beg );
  file.clear();
  file.resize( file_size / sizeof( char ) );
  in.read( &( file[ 0 ] ), file_size );


  // fortran statements
  using namespace njoy::tools::disco;
  using Identification = Record< Character< 5 >, Integer< 5 >, Integer< 5 >, Integer< 5 >,
                                 Integer< 5 >, Integer< 5 >, Integer< 5 >, Real< 12 >, Real< 12 > >;
  using Level = Record< Integer< 3 >, Column< 1 >, Real< 10 >, Column< 1 >, Real< 5 >,
                        Integer< 3 >, Column< 1 >, Real< 10 >, Integer< 3 > >;
  using Gamma = Record< Column< 39 >, Integer< 4 >, Column< 1 >, Real< 10 >,
                        Column< 1 >, Real< 10 >, Column< 1 >, Real< 10 >,
                        Column< 1 >, Real< 10 > >;

  // parse the file and get the data we need
  auto begin = file.begin();
  auto end = file.end();
  while ( begin != end ) {

    std::string symb;
    int a, z, Nol, Nog, Nmax, Nc;
    double Sn, Sp;
    Identification::read( begin, end, symb, a, z, Nol, Nog, Nmax, Nc, Sn, Sp );

    int za = z * 1000 + a;
    Sn *= constants::mega;
    Sp *= constants::mega;

    if ( Nol < 0 ) {

      Log::error( "Number of levels for isotope {} in ripl-3 levels file is less than zero", symb );
      throw std::exception();
    }

    std::size_t number_levels = static_cast< std::size_t >( Nol );
    for ( std::size_t i = 0; i < number_levels; ++i ) {

      int N1, p, Ng;
      double Elv, s, Thalf;
      Level::read( begin, end, N1, Elv, s, p, Thalf, Ng );

      id::ParticleID particle = id::ParticleID::nuclide( za, N1 - 1 );
      Elv *= constants::mega;

      if ( Ng < 0 ) {

        Log::error( "Number of gammas for isotope {} and level index {} in ripl-3 levels file is less than zero", symb, N1 );
        throw std::exception();
      }

      std::size_t number_gammas = static_cast< std::size_t >( Ng );
      for ( std::size_t j = 0; j < number_gammas; ++j ) {

        int Nf;
        double Eg, Pg, Pe, ICC;
        Gamma::read( begin, end, Nf, Eg, Pg, Pe, ICC );
      }

      std::cout << "adding nuclide " << particle.symbol() << std::endl;
      Levels::levels_[ particle ] = { particle, Elv,
                                      s < 0 ? std::nullopt : std::make_optional( s ),
                                      p == 0 ? std::nullopt : std::make_optional( p ),
                                      Thalf < 0 ? std::nullopt : std::make_optional( Thalf ) };
    }
  }
}
