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

  void verifyCoherentElastic( const std::optional< njoy::dryad::thermal::CoherentElasticScattering >& elastic ) {

    CHECK( std::nullopt != elastic );

    CHECK_THAT( 1e-5    , WithinRel( elastic->lowerEnergyLimit() ) );
    CHECK_THAT( 5.000001, WithinRel( elastic->upperEnergyLimit() ) );

    CHECK( 11 == elastic->numberModeratorTemperatures() );
    CHECK_THAT(   77, WithinRel( elastic->braggEdges()[0].temperature() ) );
    CHECK_THAT(  100, WithinRel( elastic->braggEdges()[1].temperature() ) );
    CHECK_THAT( 1000, WithinRel( elastic->braggEdges()[9].temperature() ) );
    CHECK_THAT( 1200, WithinRel( elastic->braggEdges()[10].temperature() ) );
    CHECK( 2306 == elastic->braggEdges()[0].numberBraggEdges() );
    CHECK( 2306 == elastic->braggEdges()[1].numberBraggEdges() );
    CHECK( 2306 == elastic->braggEdges()[9].numberBraggEdges() );
    CHECK( 2306 == elastic->braggEdges()[10].numberBraggEdges() );
    CHECK( 2306 == elastic->braggEdges()[0].energies().size() );
    CHECK( 2306 == elastic->braggEdges()[1].energies().size() );
    CHECK( 2306 == elastic->braggEdges()[9].energies().size() );
    CHECK( 2306 == elastic->braggEdges()[10].energies().size() );
    CHECK( 2306 == elastic->braggEdges()[0].values().size() );
    CHECK( 2306 == elastic->braggEdges()[1].values().size() );
    CHECK( 2306 == elastic->braggEdges()[9].values().size() );
    CHECK( 2306 == elastic->braggEdges()[10].values().size() );

    CHECK_THAT( 5.219736e-3, WithinRel( elastic->braggEdges()[0].energies().front() ) );
    CHECK_THAT( 5.219736e-3, WithinRel( elastic->braggEdges()[1].energies().front() ) );
    CHECK_THAT( 5.219736e-3, WithinRel( elastic->braggEdges()[9].energies().front() ) );
    CHECK_THAT( 5.219736e-3, WithinRel( elastic->braggEdges()[10].energies().front() ) );
    CHECK_THAT( 5., WithinRel( elastic->braggEdges()[0].energies().back() ) );
    CHECK_THAT( 5., WithinRel( elastic->braggEdges()[1].energies().back() ) );
    CHECK_THAT( 5., WithinRel( elastic->braggEdges()[9].energies().back() ) );
    CHECK_THAT( 5., WithinRel( elastic->braggEdges()[10].energies().back() ) );

    CHECK_THAT( 8.703783e-3, WithinRel( elastic->braggEdges()[0].values().front() ) );
    CHECK_THAT( 8.699222e-3, WithinRel( elastic->braggEdges()[1].values().front() ) );
    CHECK_THAT( 7.851222e-3, WithinRel( elastic->braggEdges()[9].values().front() ) );
    CHECK_THAT( 7.640495e-3, WithinRel( elastic->braggEdges()[10].values().front() ) );
    CHECK_THAT( 9.484639e-1, WithinRel( elastic->braggEdges()[0].values().back() ) );
    CHECK_THAT( 9.363035e-1, WithinRel( elastic->braggEdges()[1].values().back() ) );
    CHECK_THAT( 2.579243e-1, WithinRel( elastic->braggEdges()[9].values().back() ) );
    CHECK_THAT( 2.142492e-1, WithinRel( elastic->braggEdges()[10].values().back() ) );
  }

  void verifyIncoherentElastic( const std::optional< njoy::dryad::thermal::IncoherentElasticScattering >& elastic ) {

    CHECK( std::nullopt == elastic );
  }

  void verifyIncoherentInelastic( const std::optional< njoy::dryad::thermal::IncoherentInelasticScattering >& inelastic ) {

    CHECK( std::nullopt != inelastic );

    CHECK_THAT( 1e-5    , WithinRel( inelastic->lowerEnergyLimit() ) );
    CHECK_THAT( 5.000001, WithinRel( inelastic->upperEnergyLimit() ) );
    CHECK_THAT( 6.153875 * ( 8.93478 + 1. ) * ( 8.93478 + 1. ) / 8.93478 / 8.93478,
                WithinRel( inelastic->boundCrossSection() ) );
    CHECK_THAT( 8.93478, WithinRel( inelastic->atomicWeightRatio() ) );

    CHECK( 11 == inelastic->numberModeratorTemperatures() );
    CHECK( 11 == inelastic->moderatorTemperatures().size() );
    CHECK_THAT(   77  , WithinRel( inelastic->moderatorTemperatures()[0] ) );
    CHECK_THAT(  100  , WithinRel( inelastic->moderatorTemperatures()[1] ) );
    CHECK_THAT(  293.6, WithinRel( inelastic->moderatorTemperatures()[2] ) );
    CHECK_THAT(  296  , WithinRel( inelastic->moderatorTemperatures()[3] ) );
    CHECK_THAT(  400  , WithinRel( inelastic->moderatorTemperatures()[4] ) );
    CHECK_THAT(  500  , WithinRel( inelastic->moderatorTemperatures()[5] ) );
    CHECK_THAT(  600  , WithinRel( inelastic->moderatorTemperatures()[6] ) );
    CHECK_THAT(  700  , WithinRel( inelastic->moderatorTemperatures()[7] ) );
    CHECK_THAT(  800  , WithinRel( inelastic->moderatorTemperatures()[8] ) );
    CHECK_THAT( 1000  , WithinRel( inelastic->moderatorTemperatures()[9] ) );
    CHECK_THAT( 1200  , WithinRel( inelastic->moderatorTemperatures()[10] ) );

    double min = std::numeric_limits< double >::min();

    double factor;

    auto sab = inelastic->scatteringKernel( 77 );
    factor = 293.6 / 77.;
    CHECK_THAT( 77     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 359.9847, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    auto table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 1.976285e+2 * factor, WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 3.052968e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 8.847604e+1 * factor, WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 5.088369e-6         , WithinRel( table.functions().front().values().front() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().front() ) );
    CHECK_THAT( 4.38591e-18         , WithinRel( table.functions().front().values().back() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().back() ) );

    sab = inelastic->scatteringKernel( 100 );
    factor = 293.6 / 100.;
    CHECK_THAT( 100     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 361.0462, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 1.976285e+2 * factor, WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 3.052968e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 8.847604e+1 * factor, WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 8.582564e-6         , WithinRel( table.functions().front().values().front() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().front() ) );
    CHECK_THAT( 2.51995e-17         , WithinRel( table.functions().front().values().back() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().back() ) );

    sab = inelastic->scatteringKernel( 293.6 );
    factor = 1.;
    CHECK_THAT( 293.6     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 431.8891, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 1.976285e+2 * factor, WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 3.052968e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 8.847604e+1 * factor, WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 7.406648e-5         , WithinRel( table.functions().front().values().front() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().front() ) );
    CHECK_THAT( 9.87669e-11         , WithinRel( table.functions().front().values().back() ) );
    CHECK_THAT( 3.75431e-53         , WithinRel( table.functions().back().values().back() ) );

    sab = inelastic->scatteringKernel( 296 );
    factor = 293.6 / 296.;
    CHECK_THAT( 296     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 433.3832, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 1.976285e+2 * factor, WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 3.052968e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 8.847604e+1 * factor, WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 7.528346e-5         , WithinRel( table.functions().front().values().front() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().front() ) );
    CHECK_THAT( 1.12254e-10         , WithinRel( table.functions().front().values().back() ) );
    CHECK_THAT( 8.77718e-53         , WithinRel( table.functions().back().values().back() ) );

    sab = inelastic->scatteringKernel( 400 );
    factor = 293.6 / 400.;
    CHECK_THAT( 400     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 506.3941, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 1.976285e+2 * factor, WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 3.052968e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 8.847604e+1 * factor, WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 1.375632e-4         , WithinRel( table.functions().front().values().front() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().front() ) );
    CHECK_THAT( 9.519112e-9         , WithinRel( table.functions().front().values().back() ) );
    CHECK_THAT( 8.15850e-41         , WithinRel( table.functions().back().values().back() ) );

    sab = inelastic->scatteringKernel( 500 );
    factor = 293.6 / 500.;
    CHECK_THAT( 500     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 586.9482, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 1.976285e+2 * factor, WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 3.052968e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 8.847604e+1 * factor, WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 2.150554e-4         , WithinRel( table.functions().front().values().front() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().front() ) );
    CHECK_THAT( 1.631322e-7         , WithinRel( table.functions().front().values().back() ) );
    CHECK_THAT( 1.02258e-33         , WithinRel( table.functions().back().values().back() ) );

    sab = inelastic->scatteringKernel( 600 );
    factor = 293.6 / 600.;
    CHECK_THAT( 600     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 673.3314, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 1.976285e+2 * factor, WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 3.052968e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 8.847604e+1 * factor, WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 3.098288e-4         , WithinRel( table.functions().front().values().front() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().front() ) );
    CHECK_THAT( 1.223546e-6         , WithinRel( table.functions().front().values().back() ) );
    CHECK_THAT( 8.06577e-29         , WithinRel( table.functions().back().values().back() ) );

    sab = inelastic->scatteringKernel( 700 );
    factor = 293.6 / 700.;
    CHECK_THAT( 700     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 763.3215, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 1.976285e+2 * factor, WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 3.052968e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 8.847604e+1 * factor, WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 4.219018e-4         , WithinRel( table.functions().front().values().front() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().front() ) );
    CHECK_THAT( 5.464150e-6         , WithinRel( table.functions().front().values().back() ) );
    CHECK_THAT( 3.18758e-25         , WithinRel( table.functions().back().values().back() ) );

    sab = inelastic->scatteringKernel( 800 );
    factor = 293.6 / 800.;
    CHECK_THAT( 800     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 855.6762, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 1.976285e+2 * factor, WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 3.052968e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 8.847604e+1 * factor, WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 5.512926e-4         , WithinRel( table.functions().front().values().front() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().front() ) );
    CHECK_THAT( 1.731523e-5         , WithinRel( table.functions().front().values().back() ) );
    CHECK_THAT( 1.82885e-22         , WithinRel( table.functions().back().values().back() ) );

    sab = inelastic->scatteringKernel( 1000 );
    factor = 293.6 / 1000.;
    CHECK_THAT( 1000    , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 1044.799, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 1.976285e+2 * factor, WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 3.052968e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 8.847604e+1 * factor, WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 8.621017e-4         , WithinRel( table.functions().front().values().front() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().front() ) );
    CHECK_THAT( 9.113315e-5         , WithinRel( table.functions().front().values().back() ) );
    CHECK_THAT( 1.65963e-18         , WithinRel( table.functions().back().values().back() ) );

    sab = inelastic->scatteringKernel( 1200 );
    factor = 293.6 / 1200.;
    CHECK_THAT( 1200    , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 1237.451, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.          * factor, WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 1.976285e+2 * factor, WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 3.052968e-3 * factor, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 8.847604e+1 * factor, WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 1.242403e-3         , WithinRel( table.functions().front().values().front() ) );
    CHECK_THAT( min                 , WithinRel( table.functions().back().values().front() ) );
    CHECK_THAT( 2.848294e-4         , WithinRel( table.functions().front().values().back() ) );
    CHECK_THAT( 8.38858e-16         , WithinRel( table.functions().back().values().back() ) );
  }

  void verifyBeMetal( const ThermalScattering& tsl ) {

    verifyDocumentation( tsl.documentation() );

    CHECK( true == tsl.hasCoherentElasticScattering() );
    CHECK( false == tsl.hasIncoherentElasticScattering() );
    CHECK( true == tsl.hasElasticScattering() );
    CHECK( true == tsl.hasIncoherentInelasticScattering() );
    CHECK( true == tsl.hasInelasticScattering() );

    verifyCoherentElastic( tsl.coherentElasticScattering() );
    verifyIncoherentElastic( tsl.incoherentElasticScattering() );
    verifyIncoherentInelastic( tsl.incoherentInelasticScattering() );
  }

} // namespace bemetal
} // namespace tsl
