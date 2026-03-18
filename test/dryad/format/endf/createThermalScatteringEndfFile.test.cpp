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

std::string chunk();
std::string readContentFromFile( const std::string& );

SCENARIO( "createThermalScatteringEndfFile" ) {

  GIVEN( "Thermal scattering data" ) {

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
    tsl.documentation().awr( 90.436 );
    tsl.documentation().library( 0 );
    tsl.documentation().version( std::make_pair( 8, 1 ) );
    tsl.documentation().description( std::move( description ) );

    THEN( "it can be converted to an ENDF material" ) {

      std::string filename = "jadngjndvkajeakjselkfasjdbbfakjbflakwlrec.endf";
      format::endf::createThermalScatteringEndfFile( tsl, 158, 58, filename );

      CHECK( chunk() == readContentFromFile( filename ) );

      std::remove( filename.c_str() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    "Thermal scattering data                                              0 0  0     \n"
    " 1.580000+2 9.043600+1         -1          0          0          0  58 1451     \n"
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
    " 1.580000+2 9.043600+1          2          0          0          0  58 7  2     \n"
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