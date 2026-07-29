// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createDocumentation.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const Documentation& );

SCENARIO( "createDocumentation" ) {

  GIVEN( "GNDS data" ) {

    pugi::xml_document document;
    document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node documentation = document.child( "reactionSuite" ).child( "styles" )
                                           .child( "evaluated" ).child( "documentation" );

    WHEN( "a single GNDS documentation node is given" ) {

      THEN( "a Documentation can be created" ) {

        Documentation chunk = gnds::read::createDocumentation( documentation, "eval" );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const Documentation& chunk ) {

  std::string description =
    "  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                         \n"
    " NDS 148, 1 (2018)    DIST-AUG24 REV1-NOV23            20240830   \n"
    "---- ENDF/B-VIII.1    MATERIAL  125         REVISION 1            \n"
    "----- INCIDENT-NEUTRON DATA                                       \n"
    "------ ENDF-6                                                     \n"
    "                                                                  \n"
    " **************************************************************** \n"
    "The new R-matrix analysis of the N-N system on which the ENDF/B-  \n"
    "VII evaluation for 1H is based differs from the previous one use  \n"
    "for ENDF/B-VI in several respects. Firstly, the n-p capture       \n"
    "reaction (MT=102), and its inverse, deuteron photo-               \n"
    "disintegration, were a part of the analysis, rather than added    \n"
    "later as before. The analysis used a new method for including     \n"
    "photon channels in R-matrix theory [1], which gave a better       \n"
    "description of the E1 transitions, in particular.  The data for   \n"
    "these reactions are mostly integrated and differential cross      \n"
    "sections, but some information about polarizations was also       \n"
    "included.  The thermal capture cross section was taken to be      \n"
    "332.0 mb, as was the recommendation from preliminary data         \n"
    "testing. Good agreement was obtained with recent cross-section    \n"
    "measurements [2,3] by astrophysical groups in the 20-550 keV      \n"
    "range, as well as with earlier measurements that had been done    \n"
    "mostly as photo-disintegration experiments at energies below 14   \n"
    "MeV.                                                              \n"
    "The new analysis includes several additional measurements of the  \n"
    "total cross section (MT=1).  The evaluated cross section          \n"
    "deviates at most by about -0.5% around 10 MeV from that of        \n"
    "ENDF/B-VI.  The estimated uncertainty of the MT=1 cross section   \n"
    "is given at 2 MeV steps in the following table:                   \n"
    "           En             Uncert. (%)                             \n"
    "            0                0.20                                 \n"
    "            2                0.22                                 \n"
    "            4                0.30                                 \n"
    "            6                0.36                                 \n"
    "            8                0.44                                 \n"
    "           10                0.50                                 \n"
    "           12                0.49                                 \n"
    "           14                0.46                                 \n"
    "           16                0.40                                 \n"
    "           18                0.35                                 \n"
    "           20                0.30                                 \n"
    "                                                                  \n"
    "For n-p scattering (MT=2), new information was included about the \n"
    "low-energy cross sections (MF=3) and about the angular            \n"
    "distributions (MF=4).  A new measurement of the angular           \n"
    "distribution at 10 MeV [4], plus corrections to earlier data at   \n"
    "14 MeV, moved the back-angle asymmetry in the 10-14 MeV range to  \n"
    "values that lie between those obtained for ENDF/B-V and ENDF/B-   \n"
    "VI.  The addition of the latest value of the thermal coherent     \n"
    "scattering length [5] had the interesting effect of reducing the  \n"
    "\"zero-energy\" scattering cross section somewhat to agree          \n"
    "perfectly with an earlier measurement by Houk [6], and disagree   \n"
    "with the later, more precise, value of Dilg [7].  The             \n"
    "covariances for MT=2 will be added later, but the uncertainties   \n"
    "on the integrated cross section should be similar to those        \n"
    "listed above for the total cross section.                         \n"
    "                                                                  \n"
    "REFERENCES                                                        \n"
    "                                                                  \n"
    "[1] G. M. Hale and A. S. Johnson, Proc. 17th Int. IUPAP Conf. on  \n"
    "    Few-Body Problems in Physics, 5-10 June 2003, Durham NC, W.   \n"
    "    Gloeckle and W. Tornow,  eds., Elsevier B.V., pp. S120-S122   \n"
    "   (2004).                                                        \n"
    "[2] T. S. Suzuki et al., Astrophys. Lett. 449, L59 (1995).        \n"
    "[3] Y. Nagai et al., Phys. Rev. C 56, 3173 (1997).                \n"
    "[4] N. Boukharouba et al., Phys. Rev. C 65, 014004 (2002).        \n"
    "[5] K. Schoen et al., Phys. Rev. C 67, 044005 (2003).             \n"
    "[6] T. L. Houk, Phys. Rev. C 3, 1886 (1971).                      \n"
    "[7] W. Dilg, Phys. Rev. C 11, 103 (1975).                         \n"
    " **************************************************************** \n"
    "                                                                  \n"
    "Covariances were adopted from COMMARA-2.0 library in July 2011.   \n"
    "These covariances were obtained at LANL by full scale R-matrix    \n"
    "analysis of more than 5000 experimental data (chi-square/degree   \n"
    "of freedom of 0.83). [1] The major channel in this case is elastic\n"
    "scattering, often labeled also as ''n-p'' scattering. Elastic     \n"
    "scattering serves as neutron cross section standard from 1 keV to \n"
    "20 MeV, with cross sections well determined. Uncertainties for    \n"
    "elastic scattering rise from values well below 1%, reach maximum  \n"
    "at about 8 MeV, then gradually decrease with increasing energy.   \n"
    "In addition to elastic scattering, covariances are supplied for   \n"
    "radiative capture.                                                \n"
    "                                                                  \n"
    "REFERENCES                                                        \n"
    "[1] G. M. Hale, \"Covariances from light-element R-matrix          \n"
    "analyses,\" Nuclear Data Sheets, 109, 2812 (2008).                 \n"
    " **************************************************************** \n";

  CHECK( std::nullopt == chunk.library() );
  CHECK( std::nullopt == chunk.version() );
  CHECK( description == chunk.description().value() );
}
