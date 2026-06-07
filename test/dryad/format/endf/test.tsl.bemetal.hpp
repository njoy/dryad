namespace tsl {

// test functions based on tsl-Be-metal.endf
namespace bemetal {

  void verifyDocumentation( const Documentation& documentation ) {

    std::string description =
      " Be-Metal  LEIP LAB   EVAL-Nov21 J.P.W. Crozier, N.C. Fleming,    \n"
      "                      DIST-AUG24 REV1-JUL24            20240830   \n"
      "---- ENDF/B-VIII.1    MATERIAL   26         REVISION 1            \n"
      "----- THERMAL NEUTRON SCATTERING DATA                             \n"
      "------ ENDF-6                                                     \n"
      "                                                                  \n"
      " Temperatures = 77 100 293.6 296 400 500 600 700 800 1000 1200 K  \n"
      "                                                                  \n"
      "                                                                  \n"
      " HISTORY                                                          \n"
      " -------                                                          \n"
      " 1. This library was produced by the Low Energy Interaction       \n"
      "    Physics (LEIP) group at North Carolina State University, USA. \n"
      "    The thermal scattering law data for Beryllium Metal was       \n"
      "    developed using ab initio lattice dynamics (AILD) [1, 2].     \n"
      "    Eleven temperatures are available in this library and extend  \n"
      "    into the cryogenic range. The Full Law Analysis Scattering    \n"
      "    System Hub (FLASSH) system was used to produce File 7 MT = 2, \n"
      "    4 data for Beryllium [3]. The coherent elastic data were      \n"
      "    prepared using the cubic approximation. MAT=26 and ZA=126 are \n"
      "    used for Beryllium Metal. Elemental AWR and free-atom cross   \n"
      "    section were computed from MF=3, MT=2 at 1e-5 eV from the ENDF\n"
      "    /B-VIII.0 nuclide evaluation [4].                             \n"
      "                                                                  \n"
      "    |-----------------------------------------------------|       \n"
      "    | ISOTOPE |   MASS [4]   | FREE ATOM [4] |ABUNDANCE(%)|       \n"
      "    |         | (neut. wt.)  |       (b)     |  NIST [5]  |       \n"
      "    |-----------------------------------------------------|       \n"
      "    | Be-9    | 8.934780E+01 |  6.153875E+00 |     100    |       \n"
      "    |-----------------------------------------------------|       \n"
      "                                                                  \n"
      "    |----------------------------------------|                    \n"
      "    | LATTICE | a (Ang) [6]  | c (Ang) [6]   |                    \n"
      "    | CONSTANT|              |               |                    \n"
      "    |----------------------------------------|                    \n"
      "    |         |  2.2856E+00  |   3.5842E+00  |                    \n"
      "    |----------------------------------------|                    \n"
      "                                                                  \n"
      " REFERENCES                                                       \n"
      " ----------                                                       \n"
      " 1. A.I. Hawari, \"Modern Techniques in Inelastic Thermal Neutron  \n"
      "    Scattering Analysis,\" Nucl. Data Sheets 118, 172 (2014).      \n"
      "                                                                  \n"
      " 2. J.L. Wormald, A.I. Hawari, \"Thermal Neutron Scattering Law    \n"
      "    Calculations using Ab Initio Molecular Dynamics,\" EPJ Wed of  \n"
      "    Conferences 146, 13002 (2017).                                \n"
      "                                                                  \n"
      " 3. N.C. Fleming, et al., \"FLASSH 1.0: Thermal Scattering Law     \n"
      "    Evaluation and Cross Section Generation for Reactor Physics   \n"
      "    Applications,\" Nucl. Sci. and Eng. (2023).                    \n"
      "                                                                  \n"
      " 4. D.A. Brown, et al., \"ENDF/B-VIII.0: The 8th Major Release of  \n"
      "    the Nuclear Reaction Data Library with CIELO-project Cross    \n"
      "    Sections, New Standards and Thermal Scattering Data,\"         \n"
      "    Nucl.Data Sheets, 148 (2018).                                 \n"
      "                                                                  \n"
      " 5. V.F. Sears, \"Neutron Scattering Lengths and Cross Sections,\"  \n"
      "    Neutron News, Vol. 3, No.3, 1992.                             \n"
      "                                                                  \n"
      " 6. A. Taylor, B. Kagle, \"Crystallographic Data on Metal and Alloy\n"
      "    Structures\", Dover NY, 1963                                   \n"
      "                                                                  \n"
      " -----------------------------------------------------------------\n";

    CHECK( 0 == documentation.library() );
    CHECK( std::make_pair( 8, 1 ) == documentation.version() );
    CHECK( description == documentation.description() );
  }

  void verifyCoherentElastic( const std::optional< njoy::dryad::thermal::CoherentElasticScattering >& coherent ) {

    CHECK( std::nullopt != coherent );

    CHECK( 11 == coherent->numberModeratorTemperatures() );
    CHECK_THAT(   77, WithinRel( coherent->braggEdges()[0].temperature() ) );
    CHECK_THAT(  100, WithinRel( coherent->braggEdges()[1].temperature() ) );
    CHECK_THAT( 1000, WithinRel( coherent->braggEdges()[9].temperature() ) );
    CHECK_THAT( 1200, WithinRel( coherent->braggEdges()[10].temperature() ) );
    CHECK( 2306 == coherent->braggEdges()[0].numberBraggEdges() );
    CHECK( 2306 == coherent->braggEdges()[1].numberBraggEdges() );
    CHECK( 2306 == coherent->braggEdges()[9].numberBraggEdges() );
    CHECK( 2306 == coherent->braggEdges()[10].numberBraggEdges() );
    CHECK( 2306 == coherent->braggEdges()[0].energies().size() );
    CHECK( 2306 == coherent->braggEdges()[1].energies().size() );
    CHECK( 2306 == coherent->braggEdges()[9].energies().size() );
    CHECK( 2306 == coherent->braggEdges()[10].energies().size() );
    CHECK( 2306 == coherent->braggEdges()[0].values().size() );
    CHECK( 2306 == coherent->braggEdges()[1].values().size() );
    CHECK( 2306 == coherent->braggEdges()[9].values().size() );
    CHECK( 2306 == coherent->braggEdges()[10].values().size() );

    CHECK_THAT( 5.219736e-3, WithinRel( coherent->braggEdges()[0].energies().front() ) );
    CHECK_THAT( 5.219736e-3, WithinRel( coherent->braggEdges()[1].energies().front() ) );
    CHECK_THAT( 5.219736e-3, WithinRel( coherent->braggEdges()[9].energies().front() ) );
    CHECK_THAT( 5.219736e-3, WithinRel( coherent->braggEdges()[10].energies().front() ) );
    CHECK_THAT( 5., WithinRel( coherent->braggEdges()[0].energies().back() ) );
    CHECK_THAT( 5., WithinRel( coherent->braggEdges()[1].energies().back() ) );
    CHECK_THAT( 5., WithinRel( coherent->braggEdges()[9].energies().back() ) );
    CHECK_THAT( 5., WithinRel( coherent->braggEdges()[10].energies().back() ) );

    CHECK_THAT( 8.703783e-3, WithinRel( coherent->braggEdges()[0].values().front() ) );
    CHECK_THAT( 8.699222e-3, WithinRel( coherent->braggEdges()[1].values().front() ) );
    CHECK_THAT( 7.851222e-3, WithinRel( coherent->braggEdges()[9].values().front() ) );
    CHECK_THAT( 7.640495e-3, WithinRel( coherent->braggEdges()[10].values().front() ) );
    CHECK_THAT( 9.484639e-1, WithinRel( coherent->braggEdges()[0].values().back() ) );
    CHECK_THAT( 9.363035e-1, WithinRel( coherent->braggEdges()[1].values().back() ) );
    CHECK_THAT( 2.579243e-1, WithinRel( coherent->braggEdges()[9].values().back() ) );
    CHECK_THAT( 2.142492e-1, WithinRel( coherent->braggEdges()[10].values().back() ) );
  }

  void verifyBeMetal( const ThermalScattering& tsl ) {

    verifyDocumentation( tsl.documentation() );

    CHECK( true == tsl.hasCoherentElasticScattering() );
    CHECK( false == tsl.hasIncoherentElasticScattering() );
    CHECK( true == tsl.hasElasticScattering() );
    CHECK( false == tsl.hasInelasticScattering() );

    verifyCoherentElastic( tsl.coherentElasticScattering() );
  }

} // namespace bemetal
} // namespace tsl
