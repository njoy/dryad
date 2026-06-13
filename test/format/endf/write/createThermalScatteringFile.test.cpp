// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/createThermalScatteringEndfFile.hpp"

// other includes
#include <cstdio>

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

std::string chunkWithCoherentElasticAndInelastic();
std::string chunkWithIncoherentElasticAndInelastic();
std::string chunkWithMixedElasticAndInelastic();
std::string readContentFromFile( const std::string& );

SCENARIO( "createThermalScatteringEndfFile" ) {

  // Note: these tests are spliced together from existing files and fictitious
  //       data. none of these are realistic data.

  GIVEN( "Thermal scattering data - coherent elastic and inelastic" ) {

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

    CoherentElasticScattering
    coherent( { { 293.6, { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                         { 3.757353e-3, 1.386287e-2, 8.406348e-2, 8.406348e-2 } },
                {  400., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                         { 3.686081e-3, 1.346478e-2, 6.996602e-2, 6.996602e-2 } },
                {  500., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                         { 3.605680e-3, 1.305428e-2, 5.924634e-2, 5.924634e-2 } },
                {  600., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                         { 3.518734e-3, 1.263070e-2, 5.075797e-2, 5.075797e-2 } },
                {  700., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                         { 3.428755e-3, 1.220544e-2, 4.402291e-2, 4.402291e-2 } },
                {  800., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                         { 3.337757e-3, 1.178474e-2, 3.861519e-2, 3.861519e-2 } } } );

    ThermalScattering tsl( std::move( coherent ), std::nullopt );
    tsl.documentation().library( 0 );
    tsl.documentation().version( std::make_pair( 8, 1 ) );
    tsl.documentation().description( std::move( description ) );

    THEN( "it can be converted to an ENDF material" ) {

      std::string filename = "dshflkadsjhflahlfblsdakfbleauflkdnclsne.endf";
      format::endf::createThermalScatteringEndfFile( tsl, 126, 26, filename );

      CHECK( chunkWithCoherentElasticAndInelastic() == readContentFromFile( filename ) );

      std::remove( filename.c_str() );
    } // THEN
  } // GIVEN

  GIVEN( "Thermal scattering data - incoherent elastic and inelastic" ) {

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

    IncoherentElasticScattering
    incoherent( 6.337872,
                { { 296, 400, 500, 600, 700, 800, 1000, 1200 },
                  { 2.013538, 2.677764, 3.323456, 3.972601,
                    4.623738, 5.276127, 6.583171, 7.891981 } } );

    ThermalScattering tsl( std::nullopt, std::move( incoherent ) );
    tsl.documentation().library( 0 );
    tsl.documentation().version( std::make_pair( 8, 1 ) );
    tsl.documentation().description( std::move( description ) );

    THEN( "it can be converted to an ENDF material" ) {

      std::string filename = "jadngjndvkajeakjselkfasjdbbfakjbflakwlrec.endf";
      format::endf::createThermalScatteringEndfFile( tsl, 158, 58, filename );

      CHECK( chunkWithIncoherentElasticAndInelastic() == readContentFromFile( filename ) );

      std::remove( filename.c_str() );
    } // THEN
  } // GIVEN

  GIVEN( "Thermal scattering data - mixed elastic and inelastic" ) {

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

    CoherentElasticScattering
    coherent( { { 293.6, { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                         { 3.757353e-3, 1.386287e-2, 8.406348e-2, 8.406348e-2 } },
                {  400., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                         { 3.686081e-3, 1.346478e-2, 6.996602e-2, 6.996602e-2 } },
                {  500., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                         { 3.605680e-3, 1.305428e-2, 5.924634e-2, 5.924634e-2 } },
                {  600., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                         { 3.518734e-3, 1.263070e-2, 5.075797e-2, 5.075797e-2 } },
                {  700., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                         { 3.428755e-3, 1.220544e-2, 4.402291e-2, 4.402291e-2 } },
                {  800., { 3.706719e-3, 4.942291e-3, 5.572434e-1, 5. },
                         { 3.337757e-3, 1.178474e-2, 3.861519e-2, 3.861519e-2 } } } );

    IncoherentElasticScattering
    incoherent( 6.337872,
                { { 293.6, 400, 500, 600, 800 },
                  { 2.013538, 2.677764, 3.323456, 3.972601,
                    5.276127 } } );

    ThermalScattering tsl( std::move( coherent ), std::move( incoherent ) );
    tsl.documentation().library( 0 );
    tsl.documentation().version( std::make_pair( 8, 1 ) );
    tsl.documentation().description( std::move( description ) );

    THEN( "it can be converted to an ENDF material" ) {

      std::string filename = "ecueiohfcieruhfcalmxemhaioehfmoiehfxoa.endf";
      format::endf::createThermalScatteringEndfFile( tsl, 126, 26, filename );

      CHECK( chunkWithMixedElasticAndInelastic() == readContentFromFile( filename ) );

      std::remove( filename.c_str() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunkWithCoherentElasticAndInelastic() {

  return

    "Thermal scattering data                                              0 0  0     \n"
    " 1.260000+2 0.000000+0         -1          0          0          0  26 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6  26 1451     \n"
    " 1.000000+0 0.000000+0          1          0         12          8  26 1451     \n"
    " 0.000000+0 0.000000+0          0          0         63          2  26 1451     \n"
    " Be-Metal  LEIP LAB   EVAL-Nov21 J.P.W. Crozier, N.C. Fleming,      26 1451     \n"
    "                      DIST-AUG24 REV1-JUL24            20240830     26 1451     \n"
    "---- ENDF/B-VIII.1    MATERIAL   26         REVISION 1              26 1451     \n"
    "----- THERMAL NEUTRON SCATTERING DATA                               26 1451     \n"
    "------ ENDF-6                                                       26 1451     \n"
    "                                                                    26 1451     \n"
    " Temperatures = 77 100 293.6 296 400 500 600 700 800 1000 1200 K    26 1451     \n"
    "                                                                    26 1451     \n"
    "                                                                    26 1451     \n"
    " HISTORY                                                            26 1451     \n"
    " -------                                                            26 1451     \n"
    " 1. This library was produced by the Low Energy Interaction         26 1451     \n"
    "    Physics (LEIP) group at North Carolina State University, USA.   26 1451     \n"
    "    The thermal scattering law data for Beryllium Metal was         26 1451     \n"
    "    developed using ab initio lattice dynamics (AILD) [1, 2].       26 1451     \n"
    "    Eleven temperatures are available in this library and extend    26 1451     \n"
    "    into the cryogenic range. The Full Law Analysis Scattering      26 1451     \n"
    "    System Hub (FLASSH) system was used to produce File 7 MT = 2,   26 1451     \n"
    "    4 data for Beryllium [3]. The coherent elastic data were        26 1451     \n"
    "    prepared using the cubic approximation. MAT=26 and ZA=126 are   26 1451     \n"
    "    used for Beryllium Metal. Elemental AWR and free-atom cross     26 1451     \n"
    "    section were computed from MF=3, MT=2 at 1e-5 eV from the ENDF  26 1451     \n"
    "    /B-VIII.0 nuclide evaluation [4].                               26 1451     \n"
    "                                                                    26 1451     \n"
    "    |-----------------------------------------------------|         26 1451     \n"
    "    | ISOTOPE |   MASS [4]   | FREE ATOM [4] |ABUNDANCE(%)|         26 1451     \n"
    "    |         | (neut. wt.)  |       (b)     |  NIST [5]  |         26 1451     \n"
    "    |-----------------------------------------------------|         26 1451     \n"
    "    | Be-9    | 8.934780E+01 |  6.153875E+00 |     100    |         26 1451     \n"
    "    |-----------------------------------------------------|         26 1451     \n"
    "                                                                    26 1451     \n"
    "    |----------------------------------------|                      26 1451     \n"
    "    | LATTICE | a (Ang) [6]  | c (Ang) [6]   |                      26 1451     \n"
    "    | CONSTANT|              |               |                      26 1451     \n"
    "    |----------------------------------------|                      26 1451     \n"
    "    |         |  2.2856E+00  |   3.5842E+00  |                      26 1451     \n"
    "    |----------------------------------------|                      26 1451     \n"
    "                                                                    26 1451     \n"
    " REFERENCES                                                         26 1451     \n"
    " ----------                                                         26 1451     \n"
    " 1. A.I. Hawari, \"Modern Techniques in Inelastic Thermal Neutron    26 1451     \n"
    "    Scattering Analysis,\" Nucl. Data Sheets 118, 172 (2014).        26 1451     \n"
    "                                                                    26 1451     \n"
    " 2. J.L. Wormald, A.I. Hawari, \"Thermal Neutron Scattering Law      26 1451     \n"
    "    Calculations using Ab Initio Molecular Dynamics,\" EPJ Wed of    26 1451     \n"
    "    Conferences 146, 13002 (2017).                                  26 1451     \n"
    "                                                                    26 1451     \n"
    " 3. N.C. Fleming, et al., \"FLASSH 1.0: Thermal Scattering Law       26 1451     \n"
    "    Evaluation and Cross Section Generation for Reactor Physics     26 1451     \n"
    "    Applications,\" Nucl. Sci. and Eng. (2023).                      26 1451     \n"
    "                                                                    26 1451     \n"
    " 4. D.A. Brown, et al., \"ENDF/B-VIII.0: The 8th Major Release of    26 1451     \n"
    "    the Nuclear Reaction Data Library with CIELO-project Cross      26 1451     \n"
    "    Sections, New Standards and Thermal Scattering Data,\"           26 1451     \n"
    "    Nucl.Data Sheets, 148 (2018).                                   26 1451     \n"
    "                                                                    26 1451     \n"
    " 5. V.F. Sears, \"Neutron Scattering Lengths and Cross Sections,\"    26 1451     \n"
    "    Neutron News, Vol. 3, No.3, 1992.                               26 1451     \n"
    "                                                                    26 1451     \n"
    " 6. A. Taylor, B. Kagle, \"Crystallographic Data on Metal and Alloy  26 1451     \n"
    "    Structures\", Dover NY, 1963                                     26 1451     \n"
    "                                                                    26 1451     \n"
    " -----------------------------------------------------------------  26 1451     \n"
    "                                1        451         69          0  26 1451     \n"
    "                                7          2         15          0  26 1451     \n"
    "                                                                    26 1  0     \n"
    "                                                                    26 0  0     \n"
    " 1.260000+2 0.000000+0          1          0          0          0  26 7  2     \n"
    " 2.936000+2 0.000000+0          5          0          1          4  26 7  2     \n"
    "          4          1                                              26 7  2     \n"
    " 3.706719-3 3.757353-3 4.942291-3 1.386287-2 5.572434-1 8.406348-2  26 7  2     \n"
    " 5.000000+0 8.406348-2                                              26 7  2     \n"
    " 4.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.686081-3 1.346478-2 6.996602-2 6.996602-2                        26 7  2     \n"
    " 5.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.605680-3 1.305428-2 5.924634-2 5.924634-2                        26 7  2     \n"
    " 6.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.518734-3 1.263070-2 5.075797-2 5.075797-2                        26 7  2     \n"
    " 7.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.428755-3 1.220544-2 4.402291-2 4.402291-2                        26 7  2     \n"
    " 8.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.337757-3 1.178474-2 3.861519-2 3.861519-2                        26 7  2     \n"
    "                                                                    26 7  0     \n"
    "                                                                    26 0  0     \n"
    "                                                                     0 0  0     \n"
    "                                                                    -1 0  0     \n";
}

std::string chunkWithIncoherentElasticAndInelastic() {

  return
    "Thermal scattering data                                              0 0  0     \n"
    " 1.580000+2 0.000000+0         -1          0          0          0  58 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6  58 1451     \n"
    " 1.000000+0 0.000000+0          1          0         12          8  58 1451     \n"
    " 0.000000+0 0.000000+0          0          0         57          2  58 1451     \n"
    " Zr(ZrH)   LANL       EVAL-APR93 MacFarlane                         58 1451     \n"
    " Ref. 3 (1994)        DIST-AUG24 REV1-NOV19            20240830     58 1451     \n"
    "---- ENDF/B-VIII.1    MATERIAL   58         REVISION 1              58 1451     \n"
    "----- THERMAL NEUTRON SCATTERING DATA                               58 1451     \n"
    "------ ENDF-6                                                       58 1451     \n"
    "                                                                    58 1451     \n"
    " Temperatures = 296 400 500 600 700 800 1000 1200 deg k.            58 1451     \n"
    "                                                                    58 1451     \n"
    " History                                                            58 1451     \n"
    " -------                                                            58 1451     \n"
    " this evaluation was produced at los alamos in 1993 using           58 1451     \n"
    " the same model as the ga evaluation of 1968 (ref 1).  the          58 1451     \n"
    " leapr module of njoy was used for the calculation, and             58 1451     \n"
    " the alpha and beta grids were extended slightly.  constants        58 1451     \n"
    " that match the endf/b-vi values were used.                         58 1451     \n"
    "                                                                    58 1451     \n"
    " Theory                                                             58 1451     \n"
    " ------                                                             58 1451     \n"
    " the lattice dynamics of zrh were computed from a central           58 1451     \n"
    " force model.  the slightly tetragonal lattice of zrh_2 was         58 1451     \n"
    " approximated by a face-centered-cubic lattice.  four force         58 1451     \n"
    " constants (mu, gamma, nu, and delta) were introduced describing    58 1451     \n"
    " respectively the interaction of a zirconium atoms with its         58 1451     \n"
    " nearest neighbors ( 8 h atoms) and its next nearest neighbors      58 1451     \n"
    " (12 zr atoms), and the interaction of a hydrogen atom with         58 1451     \n"
    " its next nearest neighbors (6 h atoms) and its third nearest       58 1451     \n"
    " atoms (12 h atoms).  eigenvalues and eigenvectors of the           58 1451     \n"
    " dynamical matrix were calculated, and a phonon frequency           58 1451     \n"
    " spectrum was obtained by means of a root sampling technique.       58 1451     \n"
    " weighted frequency spectra for hydrogen in zrh were then           58 1451     \n"
    " obtained by appropriate use of the dynamical matrix                58 1451     \n"
    " eigenvectors (ref. 2).                                             58 1451     \n"
    "                                                                    58 1451     \n"
    " the final values of the four force constants were obtained         58 1451     \n"
    " by fitting both specific heat and neutron data.  the               58 1451     \n"
    " position of an optical peak observed by neutron scattering         58 1451     \n"
    " techniques to be centered roughly around 0.14 ev determines        58 1451     \n"
    " the constant mu, while the overall width and shape of this         58 1451     \n"
    " peak determine nu and delta respectively.  existing neutron        58 1451     \n"
    " data are not sufficiently precise to confirm the structure         58 1451     \n"
    " predicted in the optical peak by the central force model.          58 1451     \n"
    " specific heat data were used to determine the force                58 1451     \n"
    " constant gamma, which primarily determines the upper               58 1451     \n"
    " limit on the phonon energies associated with acoustic modes.       58 1451     \n"
    "                                                                    58 1451     \n"
    " References                                                         58 1451     \n"
    " ----------                                                         58 1451     \n"
    " 1. j.u.koppel and d.h.houston, reference manual for endf thermal   58 1451     \n"
    "    neutron scattering data, general atomic report ga-8774          58 1451     \n"
    "    revised and reissued as endf-269 by the national nuclear        58 1451     \n"
    "    data center, july 1978.                                         58 1451     \n"
    " 2. e.l.slaggie, \"central force lattice dynamical model for         58 1451     \n"
    "    zirconium hydride\", ga-8132 (1967).                             58 1451     \n"
    " 3. r.e.macfarlane, new thermal neutron scattering files for        58 1451     \n"
    "    endf/b-vi release 2, los alamos national laboratory report      58 1451     \n"
    "    LA-12639-MS (ENDF-356) March 1994.                              58 1451     \n"
    "                                                                    58 1451     \n"
    "                                1        451         63          0  58 1451     \n"
    "                                7          2          6          0  58 1451     \n"
    "                                                                    58 1  0     \n"
    "                                                                    58 0  0     \n"
    " 1.580000+2 0.000000+0          2          0          0          0  58 7  2     \n"
    " 6.337872+0 0.000000+0          0          0          1          8  58 7  2     \n"
    "          8          2                                              58 7  2     \n"
    " 2.960000+2 2.013538+0 4.000000+2 2.677764+0 5.000000+2 3.323456+0  58 7  2     \n"
    " 6.000000+2 3.972601+0 7.000000+2 4.623738+0 8.000000+2 5.276127+0  58 7  2     \n"
    " 1.000000+3 6.583171+0 1.200000+3 7.891981+0                        58 7  2     \n"
    "                                                                    58 7  0     \n"
    "                                                                    58 0  0     \n"
    "                                                                     0 0  0     \n"
    "                                                                    -1 0  0     \n";
}

std::string chunkWithMixedElasticAndInelastic() {

  return

    "Thermal scattering data                                              0 0  0     \n"
    " 1.260000+2 0.000000+0         -1          0          0          0  26 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6  26 1451     \n"
    " 1.000000+0 0.000000+0          1          0         12          8  26 1451     \n"
    " 0.000000+0 0.000000+0          0          0         63          2  26 1451     \n"
    " Be-Metal  LEIP LAB   EVAL-Nov21 J.P.W. Crozier, N.C. Fleming,      26 1451     \n"
    "                      DIST-AUG24 REV1-JUL24            20240830     26 1451     \n"
    "---- ENDF/B-VIII.1    MATERIAL   26         REVISION 1              26 1451     \n"
    "----- THERMAL NEUTRON SCATTERING DATA                               26 1451     \n"
    "------ ENDF-6                                                       26 1451     \n"
    "                                                                    26 1451     \n"
    " Temperatures = 77 100 293.6 296 400 500 600 700 800 1000 1200 K    26 1451     \n"
    "                                                                    26 1451     \n"
    "                                                                    26 1451     \n"
    " HISTORY                                                            26 1451     \n"
    " -------                                                            26 1451     \n"
    " 1. This library was produced by the Low Energy Interaction         26 1451     \n"
    "    Physics (LEIP) group at North Carolina State University, USA.   26 1451     \n"
    "    The thermal scattering law data for Beryllium Metal was         26 1451     \n"
    "    developed using ab initio lattice dynamics (AILD) [1, 2].       26 1451     \n"
    "    Eleven temperatures are available in this library and extend    26 1451     \n"
    "    into the cryogenic range. The Full Law Analysis Scattering      26 1451     \n"
    "    System Hub (FLASSH) system was used to produce File 7 MT = 2,   26 1451     \n"
    "    4 data for Beryllium [3]. The coherent elastic data were        26 1451     \n"
    "    prepared using the cubic approximation. MAT=26 and ZA=126 are   26 1451     \n"
    "    used for Beryllium Metal. Elemental AWR and free-atom cross     26 1451     \n"
    "    section were computed from MF=3, MT=2 at 1e-5 eV from the ENDF  26 1451     \n"
    "    /B-VIII.0 nuclide evaluation [4].                               26 1451     \n"
    "                                                                    26 1451     \n"
    "    |-----------------------------------------------------|         26 1451     \n"
    "    | ISOTOPE |   MASS [4]   | FREE ATOM [4] |ABUNDANCE(%)|         26 1451     \n"
    "    |         | (neut. wt.)  |       (b)     |  NIST [5]  |         26 1451     \n"
    "    |-----------------------------------------------------|         26 1451     \n"
    "    | Be-9    | 8.934780E+01 |  6.153875E+00 |     100    |         26 1451     \n"
    "    |-----------------------------------------------------|         26 1451     \n"
    "                                                                    26 1451     \n"
    "    |----------------------------------------|                      26 1451     \n"
    "    | LATTICE | a (Ang) [6]  | c (Ang) [6]   |                      26 1451     \n"
    "    | CONSTANT|              |               |                      26 1451     \n"
    "    |----------------------------------------|                      26 1451     \n"
    "    |         |  2.2856E+00  |   3.5842E+00  |                      26 1451     \n"
    "    |----------------------------------------|                      26 1451     \n"
    "                                                                    26 1451     \n"
    " REFERENCES                                                         26 1451     \n"
    " ----------                                                         26 1451     \n"
    " 1. A.I. Hawari, \"Modern Techniques in Inelastic Thermal Neutron    26 1451     \n"
    "    Scattering Analysis,\" Nucl. Data Sheets 118, 172 (2014).        26 1451     \n"
    "                                                                    26 1451     \n"
    " 2. J.L. Wormald, A.I. Hawari, \"Thermal Neutron Scattering Law      26 1451     \n"
    "    Calculations using Ab Initio Molecular Dynamics,\" EPJ Wed of    26 1451     \n"
    "    Conferences 146, 13002 (2017).                                  26 1451     \n"
    "                                                                    26 1451     \n"
    " 3. N.C. Fleming, et al., \"FLASSH 1.0: Thermal Scattering Law       26 1451     \n"
    "    Evaluation and Cross Section Generation for Reactor Physics     26 1451     \n"
    "    Applications,\" Nucl. Sci. and Eng. (2023).                      26 1451     \n"
    "                                                                    26 1451     \n"
    " 4. D.A. Brown, et al., \"ENDF/B-VIII.0: The 8th Major Release of    26 1451     \n"
    "    the Nuclear Reaction Data Library with CIELO-project Cross      26 1451     \n"
    "    Sections, New Standards and Thermal Scattering Data,\"           26 1451     \n"
    "    Nucl.Data Sheets, 148 (2018).                                   26 1451     \n"
    "                                                                    26 1451     \n"
    " 5. V.F. Sears, \"Neutron Scattering Lengths and Cross Sections,\"    26 1451     \n"
    "    Neutron News, Vol. 3, No.3, 1992.                               26 1451     \n"
    "                                                                    26 1451     \n"
    " 6. A. Taylor, B. Kagle, \"Crystallographic Data on Metal and Alloy  26 1451     \n"
    "    Structures\", Dover NY, 1963                                     26 1451     \n"
    "                                                                    26 1451     \n"
    " -----------------------------------------------------------------  26 1451     \n"
    "                                1        451         69          0  26 1451     \n"
    "                                7          2         19          0  26 1451     \n"
    "                                                                    26 1  0     \n"
    "                                                                    26 0  0     \n"
    " 1.260000+2 0.000000+0          3          0          0          0  26 7  2     \n"
    " 2.936000+2 0.000000+0          5          0          1          4  26 7  2     \n"
    "          4          1                                              26 7  2     \n"
    " 3.706719-3 3.757353-3 4.942291-3 1.386287-2 5.572434-1 8.406348-2  26 7  2     \n"
    " 5.000000+0 8.406348-2                                              26 7  2     \n"
    " 4.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.686081-3 1.346478-2 6.996602-2 6.996602-2                        26 7  2     \n"
    " 5.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.605680-3 1.305428-2 5.924634-2 5.924634-2                        26 7  2     \n"
    " 6.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.518734-3 1.263070-2 5.075797-2 5.075797-2                        26 7  2     \n"
    " 7.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.428755-3 1.220544-2 4.402291-2 4.402291-2                        26 7  2     \n"
    " 8.000000+2 0.000000+0          2          0          4          0  26 7  2     \n"
    " 3.337757-3 1.178474-2 3.861519-2 3.861519-2                        26 7  2     \n"
    " 6.337872+0 0.000000+0          0          0          1          5  26 7  2     \n"
    "          5          2                                              26 7  2     \n"
    " 2.936000+2 2.013538+0 4.000000+2 2.677764+0 5.000000+2 3.323456+0  26 7  2     \n"
    " 6.000000+2 3.972601+0 8.000000+2 5.276127+0                        26 7  2     \n"
    "                                                                    26 7  0     \n"
    "                                                                    26 0  0     \n"
    "                                                                     0 0  0     \n"
    "                                                                    -1 0  0     \n";
}

std::string readContentFromFile( const std::string& filename ) {

  std::string content;
  std::ifstream in( filename,
                    std::ios::in | std::ios::binary | std::ios::ate );
  if ( not in ) {

    std::string message = filename;
    message += " not found";
    throw std::runtime_error( message );
  }

  const auto file_size = in.tellg();
  in.seekg( 0, std::ios::beg );
  content.resize( file_size / sizeof( char ) );
  in.read( &( content[ 0 ] ), file_size );
  in.close();

  return content;
}