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

    CHECK( std::nullopt == documentation.library() );
    CHECK( std::nullopt == documentation.version() );
    CHECK( std::nullopt == documentation.description() );
  }

  void verifyIncoherentElastic( const std::optional< njoy::dryad::thermal::IncoherentElasticScattering >& incoherent ) {

    CHECK( std::nullopt != incoherent );

    CHECK_THAT( 6.337872, WithinRel( incoherent->boundCrossSection() ) );
    CHECK( 8 == incoherent->debyeWallerIntegral().temperatures().size() );
    CHECK( 8 == incoherent->debyeWallerIntegral().values().size() );
    CHECK_THAT(  296, WithinRel( incoherent->debyeWallerIntegral().temperatures()[0] ) );
    CHECK_THAT(  400, WithinRel( incoherent->debyeWallerIntegral().temperatures()[1] ) );
    CHECK_THAT( 1000, WithinRel( incoherent->debyeWallerIntegral().temperatures()[6] ) );
    CHECK_THAT( 1200, WithinRel( incoherent->debyeWallerIntegral().temperatures()[7] ) );
    CHECK_THAT( 2.013538, WithinRel( incoherent->debyeWallerIntegral().values()[0] ) );
    CHECK_THAT( 2.677764, WithinRel( incoherent->debyeWallerIntegral().values()[1] ) );
    CHECK_THAT( 6.583171, WithinRel( incoherent->debyeWallerIntegral().values()[6] ) );
    CHECK_THAT( 7.891981, WithinRel( incoherent->debyeWallerIntegral().values()[7] ) );
  }

  void verifyZrInZrH( const ThermalScattering& tsl ) {

    verifyDocumentation( tsl.documentation() );

    CHECK( false == tsl.hasCoherentElasticScattering() );
    CHECK( true == tsl.hasIncoherentElasticScattering() );
    CHECK( true == tsl.hasElasticScattering() );
    CHECK( false == tsl.hasInelasticScattering() );

    verifyIncoherentElastic( tsl.incoherentElasticScattering() );
  }

} // namespace zrinzrh
} // namespace tsl
