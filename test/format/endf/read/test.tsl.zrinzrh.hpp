namespace tsl {

// test functions based on tsl-ZrinZrH.endf
namespace zrinzrh {

  void verifyDocumentation( const Documentation& documentation ) {

    std::string description =
      " Zr(ZrH)   LANL       EVAL-APR93 MacFarlane                       \n"
      " Ref. 3 (1994)        DIST-AUG24 REV1-NOV19            20240830   \n"
      "---- ENDF/B-VIII.1    MATERIAL   58         REVISION 1            \n"
      "----- THERMAL NEUTRON SCATTERING DATA                             \n"
      "------ ENDF-6                                                     \n"
      "                                                                  \n"
      " Temperatures = 296 400 500 600 700 800 1000 1200 deg k.          \n"
      "                                                                  \n"
      " History                                                          \n"
      " -------                                                          \n"
      " this evaluation was produced at los alamos in 1993 using         \n"
      " the same model as the ga evaluation of 1968 (ref 1).  the        \n"
      " leapr module of njoy was used for the calculation, and           \n"
      " the alpha and beta grids were extended slightly.  constants      \n"
      " that match the endf/b-vi values were used.                       \n"
      "                                                                  \n"
      " Theory                                                           \n"
      " ------                                                           \n"
      " the lattice dynamics of zrh were computed from a central         \n"
      " force model.  the slightly tetragonal lattice of zrh_2 was       \n"
      " approximated by a face-centered-cubic lattice.  four force       \n"
      " constants (mu, gamma, nu, and delta) were introduced describing  \n"
      " respectively the interaction of a zirconium atoms with its       \n"
      " nearest neighbors ( 8 h atoms) and its next nearest neighbors    \n"
      " (12 zr atoms), and the interaction of a hydrogen atom with       \n"
      " its next nearest neighbors (6 h atoms) and its third nearest     \n"
      " atoms (12 h atoms).  eigenvalues and eigenvectors of the         \n"
      " dynamical matrix were calculated, and a phonon frequency         \n"
      " spectrum was obtained by means of a root sampling technique.     \n"
      " weighted frequency spectra for hydrogen in zrh were then         \n"
      " obtained by appropriate use of the dynamical matrix              \n"
      " eigenvectors (ref. 2).                                           \n"
      "                                                                  \n"
      " the final values of the four force constants were obtained       \n"
      " by fitting both specific heat and neutron data.  the             \n"
      " position of an optical peak observed by neutron scattering       \n"
      " techniques to be centered roughly around 0.14 ev determines      \n"
      " the constant mu, while the overall width and shape of this       \n"
      " peak determine nu and delta respectively.  existing neutron      \n"
      " data are not sufficiently precise to confirm the structure       \n"
      " predicted in the optical peak by the central force model.        \n"
      " specific heat data were used to determine the force              \n"
      " constant gamma, which primarily determines the upper             \n"
      " limit on the phonon energies associated with acoustic modes.     \n"
      "                                                                  \n"
      " References                                                       \n"
      " ----------                                                       \n"
      " 1. j.u.koppel and d.h.houston, reference manual for endf thermal \n"
      "    neutron scattering data, general atomic report ga-8774        \n"
      "    revised and reissued as endf-269 by the national nuclear      \n"
      "    data center, july 1978.                                       \n"
      " 2. e.l.slaggie, \"central force lattice dynamical model for       \n"
      "    zirconium hydride\", ga-8132 (1967).                           \n"
      " 3. r.e.macfarlane, new thermal neutron scattering files for      \n"
      "    endf/b-vi release 2, los alamos national laboratory report    \n"
      "    LA-12639-MS (ENDF-356) March 1994.                            \n"
      "                                                                  \n";

    CHECK( 0 == documentation.library() );
    CHECK( std::make_pair( 8, 1 ) == documentation.version() );
    CHECK( description == documentation.description() );
  }

  void verifyCoherentElastic( const std::optional< njoy::dryad::thermal::CoherentElasticScattering >& elastic ) {

    CHECK( std::nullopt == elastic );
  }

  void verifyIncoherentElastic( const std::optional< njoy::dryad::thermal::IncoherentElasticScattering >& elastic ) {

    CHECK( std::nullopt != elastic );

    CHECK_THAT( 1e-5   , WithinRel( elastic->lowerEnergyLimit() ) );
    CHECK_THAT( 1.00022, WithinRel( elastic->upperEnergyLimit() ) );

    CHECK_THAT( 6.337872, WithinRel( elastic->boundCrossSection() ) );
    CHECK( 8 == elastic->debyeWallerIntegral().temperatures().size() );
    CHECK( 8 == elastic->debyeWallerIntegral().values().size() );
    CHECK_THAT(  296, WithinRel( elastic->debyeWallerIntegral().temperatures()[0] ) );
    CHECK_THAT(  400, WithinRel( elastic->debyeWallerIntegral().temperatures()[1] ) );
    CHECK_THAT( 1000, WithinRel( elastic->debyeWallerIntegral().temperatures()[6] ) );
    CHECK_THAT( 1200, WithinRel( elastic->debyeWallerIntegral().temperatures()[7] ) );
    CHECK_THAT( 2.013538, WithinRel( elastic->debyeWallerIntegral().values()[0] ) );
    CHECK_THAT( 2.677764, WithinRel( elastic->debyeWallerIntegral().values()[1] ) );
    CHECK_THAT( 6.583171, WithinRel( elastic->debyeWallerIntegral().values()[6] ) );
    CHECK_THAT( 7.891981, WithinRel( elastic->debyeWallerIntegral().values()[7] ) );
  }

  void verifyIncoherentInelastic( const std::optional< njoy::dryad::thermal::IncoherentInelasticScattering >& inelastic ) {

    CHECK( std::nullopt != inelastic );

    CHECK_THAT( 1e-5   , WithinRel( inelastic->lowerEnergyLimit() ) );
    CHECK_THAT( 1.00022, WithinRel( inelastic->upperEnergyLimit() ) );
    CHECK_THAT( 6.2 * ( 90.436 + 1. ) * ( 90.436 + 1. ) / 90.436 / 90.436,
                WithinRel( inelastic->boundCrossSection() ) );
    CHECK_THAT( 90.436, WithinRel( inelastic->atomicWeightRatio() ) );

    CHECK( 8 == inelastic->numberModeratorTemperatures() );
    CHECK( 8 == inelastic->moderatorTemperatures().size() );
    CHECK_THAT(  296, WithinRel( inelastic->moderatorTemperatures()[0] ) );
    CHECK_THAT(  400, WithinRel( inelastic->moderatorTemperatures()[1] ) );
    CHECK_THAT(  500, WithinRel( inelastic->moderatorTemperatures()[2] ) );
    CHECK_THAT(  600, WithinRel( inelastic->moderatorTemperatures()[3] ) );
    CHECK_THAT(  700, WithinRel( inelastic->moderatorTemperatures()[4] ) );
    CHECK_THAT(  800, WithinRel( inelastic->moderatorTemperatures()[5] ) );
    CHECK_THAT( 1000, WithinRel( inelastic->moderatorTemperatures()[6] ) );
    CHECK_THAT( 1200, WithinRel( inelastic->moderatorTemperatures()[7] ) );

    double min = std::numeric_limits< double >::min();

    auto sab = inelastic->scatteringKernel( 296 );
    CHECK_THAT( 296     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 317.4163, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    auto table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.         , WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 39.5344    , WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 5.569960e-3, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 1.791430   , WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 7.242787e-3, WithinRel( table( 5.569960e-3, 0. ) ) );
    CHECK_THAT( min        , WithinRel( table( 5.569960e-3, 39.5344 ) ) );
    CHECK_THAT( 1.434476e-1, WithinRel( table( 1.791430   , 0. ) ) );
    CHECK_THAT( min        , WithinRel( table( 1.791430   , 39.5344 ) ) );

    sab = inelastic->scatteringKernel( 400 );
    CHECK_THAT( 400     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 416.3325, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.         , WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 39.5344    , WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 5.569960e-3, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 1.791430   , WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 1.321421e-2, WithinRel( table( 5.569960e-3, 0. ) ) );
    CHECK_THAT( min        , WithinRel( table( 5.569960e-3, 39.5344 ) ) );
    CHECK_THAT( 1.835178e-1, WithinRel( table( 1.791430   , 0. ) ) );
    CHECK_THAT( min        , WithinRel( table( 1.791430   , 39.5344 ) ) );

    sab = inelastic->scatteringKernel( 500 );
    CHECK_THAT( 500     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 513.2826, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.         , WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 39.5344    , WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 5.569960e-3, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 1.791430   , WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 2.062500e-2, WithinRel( table( 5.569960e-3, 0. ) ) );
    CHECK_THAT( min        , WithinRel( table( 5.569960e-3, 39.5344 ) ) );
    CHECK_THAT( 2.170594e-1, WithinRel( table( 1.791430   , 0. ) ) );
    CHECK_THAT( 2.13881e-24, WithinRel( table( 1.791430   , 39.5344 ) , 1e-12) );

    sab = inelastic->scatteringKernel( 600 );
    CHECK_THAT( 600     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 611.1816, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.         , WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 39.5344    , WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 5.569960e-3, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 1.791430   , WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 2.966493e-2, WithinRel( table( 5.569960e-3, 0. ) ) );
    CHECK_THAT( min        , WithinRel( table( 5.569960e-3, 39.5344 ) ) );
    CHECK_THAT( 2.470634e-1, WithinRel( table( 1.791430   , 0. ) ) );
    CHECK_THAT( 8.11991e-23, WithinRel( table( 1.791430   , 39.5344 ) ) );

    sab = inelastic->scatteringKernel( 700 );
    CHECK_THAT( 700     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 709.6479, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.         , WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 39.5344    , WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 5.569960e-3, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 1.791430   , WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 4.032669e-2, WithinRel( table( 5.569960e-3, 0. ) ) );
    CHECK_THAT( min        , WithinRel( table( 5.569960e-3, 39.5344 ) ) );
    CHECK_THAT( 2.743558e-1, WithinRel( table( 1.791430   , 0. ) ) );
    CHECK_THAT( 1.50711e-21, WithinRel( table( 1.791430   , 39.5344 ) ) );

    sab = inelastic->scatteringKernel( 800 );
    CHECK_THAT( 800     , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 808.4802, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.         , WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 39.5344    , WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 5.569960e-3, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 1.791430   , WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 5.260275e-2, WithinRel( table( 5.569960e-3, 0. ) ) );
    CHECK_THAT( min        , WithinRel( table( 5.569960e-3, 39.5344 ) ) );
    CHECK_THAT( 2.995066e-1, WithinRel( table( 1.791430   , 0. ) ) );
    CHECK_THAT( 1.84277e-20, WithinRel( table( 1.791430   , 39.5344 ) ) );

    sab = inelastic->scatteringKernel( 1000 );
    CHECK_THAT( 1000    , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 1006.822, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.         , WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 39.5344    , WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 5.569960e-3, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 1.791430   , WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 8.196668e-2, WithinRel( table( 5.569960e-3, 0. ) ) );
    CHECK_THAT( min        , WithinRel( table( 5.569960e-3, 39.5344 ) ) );
    CHECK_THAT( 3.448984e-1, WithinRel( table( 1.791430   , 0. ) ) );
    CHECK_THAT( 1.23757e-18, WithinRel( table( 1.791430   , 39.5344 ) ) );

    sab = inelastic->scatteringKernel( 1200 );
    CHECK_THAT( 1200    , WithinRel( sab.moderatorTemperature() ) );
    CHECK_THAT( 1205.703, WithinRel( sab.effectiveTemperature() ) );
    CHECK( true == sab.isEnergyTransferSymmetric() );
    table = sab.tabulatedScatteringKernel();
    CHECK_THAT( 0.         , WithinRel( table.lowerEnergyTransferLimit() ) );
    CHECK_THAT( 39.5344    , WithinRel( table.upperEnergyTransferLimit() ) );
    CHECK_THAT( 5.569960e-3, WithinRel( table.lowerMomentumTransferLimit() ) );
    CHECK_THAT( 1.791430   , WithinRel( table.upperMomentumTransferLimit() ) );
    CHECK_THAT( 1.176925e-1, WithinRel( table( 5.569960e-3, 0. ) ) );
    CHECK_THAT( min        , WithinRel( table( 5.569960e-3, 39.5344 ) ) );
    CHECK_THAT( 3.853824e-1, WithinRel( table( 1.791430   , 0. ) ) );
    CHECK_THAT( 4.06882e-17, WithinRel( table( 1.791430   , 39.5344 ) ) );
  }

  void verifyZrInZrH( const ThermalScattering& tsl ) {

    verifyDocumentation( tsl.documentation() );

    CHECK( false == tsl.hasCoherentElasticScattering() );
    CHECK( true == tsl.hasIncoherentElasticScattering() );
    CHECK( true == tsl.hasElasticScattering() );
    CHECK( true == tsl.hasIncoherentInelasticScattering() );
    CHECK( true == tsl.hasInelasticScattering() );

    verifyCoherentElastic( tsl.coherentElasticScattering() );
    verifyIncoherentElastic( tsl.incoherentElasticScattering() );
    verifyIncoherentInelastic( tsl.incoherentInelasticScattering() );
  }

} // namespace zrinzrh
} // namespace tsl
