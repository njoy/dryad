// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createProjectileTargetEndfFile.hpp"

// other includes
#include <cstdio>

// convenience typedefs
using namespace njoy::dryad;

std::string chunk();
std::string readContentFromFile( const std::string& );

SCENARIO( "createAtomicRelaxationEndfFile" ) {

  GIVEN( "projectile-target data - incident neutrons" ) {

    std::string description =
      "  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                         \n"
      " NDS 148, 1 (2018)    DIST-FEB18                       20170124   \n"
      "----ENDF/B-VIII.0     MATERIAL  125                               \n"
      "-----INCIDENT NEUTRON DATA                                        \n"
      "------ENDF-6 FORMAT                                               \n"
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

    std::vector< Reaction > reactions = {

      Reaction( id::ReactionID( "n,H1->total" ),
                { id::ReactionID( "n,H1->n,H1" ), id::ReactionID( "n,H1->g,H2[all]" ) },
                TabulatedCrossSection( { 1.000000e-5, 2.000000e-5, 5.000000e-5, 1.000000e-4, 2.000000e-4,
                                         5.000000e-4, 1.000000e-3, 2.000000e-3, 5.000000e-3, 1.000000e-2,
                                         2.530000e-2, 1.000000e-1, 2.000000e-1, 5.000000e-1, 1.000000e+0,
                                         2.000000e+0, 5.000000e+0, 1.000000e+1, 2.000000e+1, 5.000000e+1,
                                         1.000000e+2, 2.000000e+2, 5.000000e+2, 1.000000e+3, 2.000000e+3,
                                         3.000000e+3, 4.000000e+3, 5.000000e+3, 6.000000e+3, 7.000000e+3,
                                         8.000000e+3, 9.000000e+3, 1.000000e+4, 1.200000e+4, 1.400000e+4,
                                         1.600000e+4, 1.800000e+4, 2.000000e+4, 2.200000e+4, 2.400000e+4,
                                         2.600000e+4, 2.800000e+4, 3.000000e+4, 3.500000e+4, 4.000000e+4,
                                         4.500000e+4, 5.000000e+4, 5.500000e+4, 6.000000e+4, 6.500000e+4,
                                         7.000000e+4, 7.500000e+4, 8.000000e+4, 8.500000e+4, 9.000000e+4,
                                         9.500000e+4, 1.000000e+5, 1.100000e+5, 1.200000e+5, 1.300000e+5,
                                         1.400000e+5, 1.500000e+5, 1.600000e+5, 1.700000e+5, 1.800000e+5,
                                         1.900000e+5, 2.000000e+5, 2.200000e+5, 2.400000e+5, 2.600000e+5,
                                         2.800000e+5, 3.000000e+5, 3.200000e+5, 3.400000e+5, 3.600000e+5,
                                         3.800000e+5, 4.000000e+5, 4.200000e+5, 4.400000e+5, 4.600000e+5,
                                         4.800000e+5, 5.000000e+5, 5.500000e+5, 6.000000e+5, 6.500000e+5,
                                         7.000000e+5, 7.500000e+5, 8.000000e+5, 8.500000e+5, 9.000000e+5,
                                         9.500000e+5, 1.000000e+6, 1.100000e+6, 1.200000e+6, 1.300000e+6,
                                         1.400000e+6, 1.500000e+6, 1.600000e+6, 1.700000e+6, 1.800000e+6,
                                         1.900000e+6, 2.000000e+6, 2.200000e+6, 2.400000e+6, 2.600000e+6,
                                         2.800000e+6, 3.000000e+6, 3.200000e+6, 3.400000e+6, 3.600000e+6,
                                         3.800000e+6, 4.000000e+6, 4.200000e+6, 4.400000e+6, 4.600000e+6,
                                         4.800000e+6, 5.000000e+6, 5.200000e+6, 5.400000e+6, 5.600000e+6,
                                         5.800000e+6, 6.000000e+6, 6.200000e+6, 6.400000e+6, 6.600000e+6,
                                         6.800000e+6, 7.000000e+6, 7.500000e+6, 8.000000e+6, 8.500000e+6,
                                         9.000000e+6, 9.500000e+6, 1.000000e+7, 1.050000e+7, 1.100000e+7,
                                         1.150000e+7, 1.200000e+7, 1.250000e+7, 1.300000e+7, 1.350000e+7,
                                         1.400000e+7, 1.450000e+7, 1.500000e+7, 1.550000e+7, 1.600000e+7,
                                         1.650000e+7, 1.700000e+7, 1.750000e+7, 1.800000e+7, 1.850000e+7,
                                         1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 3.716477e+1, 3.226505e+1, 2.791738e+1, 2.572616e+1, 2.417673e+1,
                                         2.280187e+1, 2.210895e+1, 2.161898e+1, 2.118421e+1, 2.096509e+1,
                                         2.076866e+1, 2.060335e+1, 2.055434e+1, 2.051083e+1, 2.048885e+1,
                                         2.047322e+1, 2.045906e+1, 2.045146e+1, 2.044521e+1, 2.043683e+1,
                                         2.042791e+1, 2.041293e+1, 2.037138e+1, 2.030414e+1, 2.017204e+1,
                                         2.004215e+1, 1.991424e+1, 1.978823e+1, 1.966405e+1, 1.954166e+1,
                                         1.942101e+1, 1.930207e+1, 1.918479e+1, 1.895510e+1, 1.873167e+1,
                                         1.851423e+1, 1.830255e+1, 1.809640e+1, 1.789556e+1, 1.769984e+1,
                                         1.750902e+1, 1.732294e+1, 1.714141e+1, 1.670645e+1, 1.629656e+1,
                                         1.590960e+1, 1.554371e+1, 1.519718e+1, 1.486851e+1, 1.455635e+1,
                                         1.425946e+1, 1.397675e+1, 1.370721e+1, 1.344993e+1, 1.320410e+1,
                                         1.296894e+1, 1.274378e+1, 1.232097e+1, 1.193120e+1, 1.157070e+1,
                                         1.123625e+1, 1.092508e+1, 1.063481e+1, 1.036336e+1, 1.010893e+1,
                                         9.869935e+0, 9.644989e+0, 9.232457e+0, 8.863064e+0, 8.530225e+0,
                                         8.228636e+0, 7.953971e+0, 7.702670e+0, 7.471777e+0, 7.258815e+0,
                                         7.061693e+0, 6.878637e+0, 6.708125e+0, 6.548852e+0, 6.399688e+0,
                                         6.259648e+0, 6.127875e+0, 5.829882e+0, 5.569515e+0, 5.339645e+0,
                                         5.134850e+0, 4.950937e+0, 4.784609e+0, 4.633238e+0, 4.494702e+0,
                                         4.367271e+0, 4.249519e+0, 4.038494e+0, 3.854211e+0, 3.691309e+0,
                                         3.545810e+0, 3.414699e+0, 3.295645e+0, 3.186817e+0, 3.086754e+0,
                                         2.994275e+0, 2.908414e+0, 2.753484e+0, 2.617003e+0, 2.495402e+0,
                                         2.386035e+0, 2.286895e+0, 2.196421e+0, 2.113381e+0, 2.036785e+0,
                                         1.965823e+0, 1.899828e+0, 1.838244e+0, 1.780601e+0, 1.726497e+0,
                                         1.675590e+0, 1.627582e+0, 1.582216e+0, 1.539263e+0, 1.498525e+0,
                                         1.459826e+0, 1.423007e+0, 1.387929e+0, 1.354466e+0, 1.322504e+0,
                                         1.291942e+0, 1.262686e+0, 1.194725e+0, 1.133290e+0, 1.077473e+0,
                                         1.026529e+0, 9.798437e-1, 9.369061e-1, 8.972839e-1, 8.606105e-1,
                                         8.265722e-1, 7.948987e-1, 7.653557e-1, 7.377393e-1, 7.118704e-1,
                                         6.875919e-1, 6.647646e-1, 6.432651e-1, 6.229834e-1, 6.038214e-1,
                                         5.856907e-1, 5.685123e-1, 5.522144e-1, 5.367326e-1, 5.220080e-1,
                                         5.079874e-1, 4.946221e-1, 4.818679e-1 },
                                       { 8, 152 }, { InterpolationType::LogLog, InterpolationType::LinearLinear } ) ),
      Reaction( id::ReactionID( "n,H1->n,H1" ),
                TabulatedCrossSection( { 1.000000e-5, 2.000000e-5, 5.000000e-5, 1.000000e-4, 2.000000e-4,
                                         5.000000e-4, 1.000000e-3, 2.000000e-3, 5.000000e-3, 1.000000e-2,
                                         2.530000e-2, 1.000000e-1, 2.000000e-1, 5.000000e-1, 1.000000e+0,
                                         2.000000e+0, 5.000000e+0, 1.000000e+1, 2.000000e+1, 5.000000e+1,
                                         1.000000e+2, 2.000000e+2, 5.000000e+2, 1.000000e+3, 2.000000e+3,
                                         3.000000e+3, 4.000000e+3, 5.000000e+3, 6.000000e+3, 7.000000e+3,
                                         8.000000e+3, 9.000000e+3, 1.000000e+4, 1.200000e+4, 1.400000e+4,
                                         1.600000e+4, 1.800000e+4, 2.000000e+4, 2.200000e+4, 2.400000e+4,
                                         2.600000e+4, 2.800000e+4, 3.000000e+4, 3.500000e+4, 4.000000e+4,
                                         4.500000e+4, 5.000000e+4, 5.500000e+4, 6.000000e+4, 6.500000e+4,
                                         7.000000e+4, 7.500000e+4, 8.000000e+4, 8.500000e+4, 9.000000e+4,
                                         9.500000e+4, 1.000000e+5, 1.100000e+5, 1.200000e+5, 1.300000e+5,
                                         1.400000e+5, 1.500000e+5, 1.600000e+5, 1.700000e+5, 1.800000e+5,
                                         1.900000e+5, 2.000000e+5, 2.200000e+5, 2.400000e+5, 2.600000e+5,
                                         2.800000e+5, 3.000000e+5, 3.200000e+5, 3.400000e+5, 3.600000e+5,
                                         3.800000e+5, 4.000000e+5, 4.200000e+5, 4.400000e+5, 4.600000e+5,
                                         4.800000e+5, 5.000000e+5, 5.500000e+5, 6.000000e+5, 6.500000e+5,
                                         7.000000e+5, 7.500000e+5, 8.000000e+5, 8.500000e+5, 9.000000e+5,
                                         9.500000e+5, 1.000000e+6, 1.100000e+6, 1.200000e+6, 1.300000e+6,
                                         1.400000e+6, 1.500000e+6, 1.600000e+6, 1.700000e+6, 1.800000e+6,
                                         1.900000e+6, 2.000000e+6, 2.200000e+6, 2.400000e+6, 2.600000e+6,
                                         2.800000e+6, 3.000000e+6, 3.200000e+6, 3.400000e+6, 3.600000e+6,
                                         3.800000e+6, 4.000000e+6, 4.200000e+6, 4.400000e+6, 4.600000e+6,
                                         4.800000e+6, 5.000000e+6, 5.200000e+6, 5.400000e+6, 5.600000e+6,
                                         5.800000e+6, 6.000000e+6, 6.200000e+6, 6.400000e+6, 6.600000e+6,
                                         6.800000e+6, 7.000000e+6, 7.500000e+6, 8.000000e+6, 8.500000e+6,
                                         9.000000e+6, 9.500000e+6, 1.000000e+7, 1.050000e+7, 1.100000e+7,
                                         1.150000e+7, 1.200000e+7, 1.250000e+7, 1.300000e+7, 1.350000e+7,
                                         1.400000e+7, 1.450000e+7, 1.500000e+7, 1.550000e+7, 1.600000e+7,
                                         1.650000e+7, 1.700000e+7, 1.750000e+7, 1.800000e+7, 1.850000e+7,
                                         1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 2.043608e+1, 2.043608e+1, 2.043608e+1, 2.043608e+1, 2.043608e+1,
                                         2.043608e+1, 2.043608e+1, 2.043608e+1, 2.043608e+1, 2.043608e+1,
                                         2.043608e+1, 2.043607e+1, 2.043605e+1, 2.043601e+1, 2.043595e+1,
                                         2.043581e+1, 2.043541e+1, 2.043473e+1, 2.043339e+1, 2.042935e+1,
                                         2.042263e+1, 2.040919e+1, 2.036903e+1, 2.030248e+1, 2.017087e+1,
                                         2.004120e+1, 1.991343e+1, 1.978750e+1, 1.966339e+1, 1.954105e+1,
                                         1.942045e+1, 1.930154e+1, 1.918430e+1, 1.895466e+1, 1.873126e+1,
                                         1.851386e+1, 1.830220e+1, 1.809607e+1, 1.789525e+1, 1.769954e+1,
                                         1.750874e+1, 1.732267e+1, 1.714116e+1, 1.670622e+1, 1.629635e+1,
                                         1.590941e+1, 1.554353e+1, 1.519701e+1, 1.486836e+1, 1.455620e+1,
                                         1.425932e+1, 1.397662e+1, 1.370708e+1, 1.344982e+1, 1.320398e+1,
                                         1.296883e+1, 1.274368e+1, 1.232087e+1, 1.193111e+1, 1.157061e+1,
                                         1.123617e+1, 1.092500e+1, 1.063473e+1, 1.036329e+1, 1.010886e+1,
                                         9.869873e+0, 9.644929e+0, 9.232401e+0, 8.863011e+0, 8.530176e+0,
                                         8.228589e+0, 7.953925e+0, 7.702627e+0, 7.471735e+0, 7.258774e+0,
                                         7.061654e+0, 6.878598e+0, 6.708087e+0, 6.548815e+0, 6.399651e+0,
                                         6.259612e+0, 6.127840e+0, 5.829847e+0, 5.569481e+0, 5.339611e+0,
                                         5.134817e+0, 4.950904e+0, 4.784576e+0, 4.633204e+0, 4.494668e+0,
                                         4.367238e+0, 4.249485e+0, 4.038460e+0, 3.854177e+0, 3.691274e+0,
                                         3.545775e+0, 3.414663e+0, 3.295609e+0, 3.186781e+0, 3.086717e+0,
                                         2.994238e+0, 2.908377e+0, 2.753447e+0, 2.616966e+0, 2.495365e+0,
                                         2.385998e+0, 2.286858e+0, 2.196384e+0, 2.113344e+0, 2.036748e+0,
                                         1.965786e+0, 1.899792e+0, 1.838208e+0, 1.780565e+0, 1.726461e+0,
                                         1.675555e+0, 1.627547e+0, 1.582180e+0, 1.539228e+0, 1.498490e+0,
                                         1.459791e+0, 1.422973e+0, 1.387895e+0, 1.354432e+0, 1.322471e+0,
                                         1.291908e+0, 1.262652e+0, 1.194691e+0, 1.133258e+0, 1.077440e+0,
                                         1.026496e+0, 9.798120e-1, 9.368747e-1, 8.972527e-1, 8.605796e-1,
                                         8.265415e-1, 7.948682e-1, 7.653255e-1, 7.377093e-1, 7.118406e-1,
                                         6.875623e-1, 6.647352e-1, 6.432359e-1, 6.229545e-1, 6.037926e-1,
                                         5.856622e-1, 5.684839e-1, 5.521863e-1, 5.367046e-1, 5.219803e-1,
                                         5.079599e-1, 4.945948e-1, 4.818408e-1 } ),
                {}, 0., 0. ),
      Reaction( id::ReactionID( "n,H1->g,H2[all]" ),
                TabulatedCrossSection( { 1.000000e-5, 2.000000e-5, 5.000000e-5, 1.000000e-4, 2.000000e-4,
                                         5.000000e-4, 1.000000e-3, 2.000000e-3, 5.000000e-3, 1.000000e-2,
                                         2.530000e-2, 1.000000e-1, 2.000000e-1, 5.000000e-1, 1.000000e+0,
                                         2.000000e+0, 5.000000e+0, 1.000000e+1, 2.000000e+1, 5.000000e+1,
                                         1.000000e+2, 2.000000e+2, 5.000000e+2, 1.000000e+3, 2.000000e+3,
                                         3.000000e+3, 4.000000e+3, 5.000000e+3, 6.000000e+3, 7.000000e+3,
                                         8.000000e+3, 9.000000e+3, 1.000000e+4, 1.200000e+4, 1.400000e+4,
                                         1.600000e+4, 1.800000e+4, 2.000000e+4, 2.200000e+4, 2.400000e+4,
                                         2.600000e+4, 2.800000e+4, 3.000000e+4, 3.500000e+4, 4.000000e+4,
                                         4.500000e+4, 5.000000e+4, 5.500000e+4, 6.000000e+4, 6.500000e+4,
                                         7.000000e+4, 7.500000e+4, 8.000000e+4, 8.500000e+4, 9.000000e+4,
                                         9.500000e+4, 1.000000e+5, 1.100000e+5, 1.200000e+5, 1.300000e+5,
                                         1.400000e+5, 1.500000e+5, 1.600000e+5, 1.700000e+5, 1.800000e+5,
                                         1.900000e+5, 2.000000e+5, 2.200000e+5, 2.400000e+5, 2.600000e+5,
                                         2.800000e+5, 3.000000e+5, 3.200000e+5, 3.400000e+5, 3.600000e+5,
                                         3.800000e+5, 4.000000e+5, 4.200000e+5, 4.400000e+5, 4.600000e+5,
                                         4.800000e+5, 5.000000e+5, 5.500000e+5, 6.000000e+5, 6.500000e+5,
                                         7.000000e+5, 7.500000e+5, 8.000000e+5, 8.500000e+5, 9.000000e+5,
                                         9.500000e+5, 1.000000e+6, 1.100000e+6, 1.200000e+6, 1.300000e+6,
                                         1.400000e+6, 1.500000e+6, 1.600000e+6, 1.700000e+6, 1.800000e+6,
                                         1.900000e+6, 2.000000e+6, 2.200000e+6, 2.400000e+6, 2.600000e+6,
                                         2.800000e+6, 3.000000e+6, 3.200000e+6, 3.400000e+6, 3.600000e+6,
                                         3.800000e+6, 4.000000e+6, 4.200000e+6, 4.400000e+6, 4.600000e+6,
                                         4.800000e+6, 5.000000e+6, 5.200000e+6, 5.400000e+6, 5.600000e+6,
                                         5.800000e+6, 6.000000e+6, 6.200000e+6, 6.400000e+6, 6.600000e+6,
                                         6.800000e+6, 7.000000e+6, 7.500000e+6, 8.000000e+6, 8.500000e+6,
                                         9.000000e+6, 9.500000e+6, 1.000000e+7, 1.050000e+7, 1.100000e+7,
                                         1.150000e+7, 1.200000e+7, 1.250000e+7, 1.300000e+7, 1.350000e+7,
                                         1.400000e+7, 1.450000e+7, 1.500000e+7, 1.550000e+7, 1.600000e+7,
                                         1.650000e+7, 1.700000e+7, 1.750000e+7, 1.800000e+7, 1.850000e+7,
                                         1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 1.672869e+1, 1.182897e+1, 7.481299e+0, 5.290077e+0, 3.740649e+0,
                                         2.365794e+0, 1.672869e+0, 1.182897e+0, 7.481298e-1, 5.290077e-1,
                                         3.325842e-1, 1.672868e-1, 1.182896e-1, 7.481273e-2, 5.290040e-2,
                                         3.740597e-2, 2.365712e-2, 1.672753e-2, 1.182733e-2, 7.478702e-3,
                                         5.286408e-3, 3.735465e-3, 2.357618e-3, 1.661353e-3, 1.166741e-3,
                                         9.462015e-4, 8.139461e-4, 7.231833e-4, 6.558304e-4, 6.032225e-4,
                                         5.606171e-4, 5.251699e-4, 4.950573e-4, 4.462792e-4, 4.081033e-4,
                                         3.771411e-4, 3.513565e-4, 3.294414e-4, 3.105111e-4, 2.939427e-4,
                                         2.792827e-4, 2.661920e-4, 2.544108e-4, 2.294576e-4, 2.093174e-4,
                                         1.926474e-4, 1.785801e-4, 1.665254e-4, 1.560654e-4, 1.468947e-4,
                                         1.387839e-4, 1.315567e-4, 1.250750e-4, 1.192289e-4, 1.139298e-4,
                                         1.091051e-4, 1.046948e-4, 9.692518e-5, 9.030618e-5, 8.460828e-5,
                                         7.965967e-5, 7.532893e-5, 7.151376e-5, 6.813319e-5, 6.512232e-5,
                                         6.242845e-5, 6.000834e-5, 5.585212e-5, 5.243121e-5, 4.958603e-5,
                                         4.719921e-5, 4.518250e-5, 4.346834e-5, 4.200417e-5, 4.074852e-5,
                                         3.966823e-5, 3.873653e-5, 3.793158e-5, 3.723536e-5, 3.663293e-5,
                                         3.611179e-5, 3.566139e-5, 3.478944e-5, 3.419936e-5, 3.381641e-5,
                                         3.358747e-5, 3.347392e-5, 3.344714e-5, 3.348555e-5, 3.357270e-5,
                                         3.369588e-5, 3.384519e-5, 3.419283e-5, 3.457117e-5, 3.495241e-5,
                                         3.531924e-5, 3.566120e-5, 3.597230e-5, 3.624960e-5, 3.649216e-5,
                                         3.670034e-5, 3.687541e-5, 3.713370e-5, 3.728419e-5, 3.734507e-5,
                                         3.733340e-5, 3.726422e-5, 3.715036e-5, 3.700247e-5, 3.682929e-5,
                                         3.663785e-5, 3.643380e-5, 3.622162e-5, 3.600482e-5, 3.578613e-5,
                                         3.556769e-5, 3.535109e-5, 3.513755e-5, 3.492796e-5, 3.472296e-5,
                                         3.452299e-5, 3.432833e-5, 3.413912e-5, 3.395544e-5, 3.377725e-5,
                                         3.360450e-5, 3.343707e-5, 3.304070e-5, 3.267375e-5, 3.233307e-5,
                                         3.201545e-5, 3.171787e-5, 3.143754e-5, 3.117192e-5, 3.091877e-5,
                                         3.067609e-5, 3.044214e-5, 3.021540e-5, 2.999455e-5, 2.977845e-5,
                                         2.956611e-5, 2.935670e-5, 2.914951e-5, 2.894393e-5, 2.873946e-5,
                                         2.853569e-5, 2.833227e-5, 2.812894e-5, 2.792548e-5, 2.772174e-5,
                                         2.751761e-5, 2.731301e-5, 2.710792e-5 },
                                       { 32, 152 },{ InterpolationType::LogLog, InterpolationType::LinearLinear }  ),
                {}, 2.224648e+6, 2.224648e+6 )
    };

    ProjectileTarget transport( id::ParticleID::neutron(), id::ParticleID( 1001 ),
                                InteractionType::Nuclear,
                                std::move( reactions ) );
    transport.documentation().awr( .9991673 );
    transport.documentation().library( 0 );
    transport.documentation().version( std::make_pair( 8, 0 ) );
    transport.documentation().description( std::move( description ) );

    THEN( "it can be converted to an ENDF material" ) {

      std::string filename = "kjlaksdhlwaekhfvbnlkrfdgjghldkjghladkjfgh.endf";
      format::endf::createProjectileTargetEndfFile( transport, 125, filename );

      CHECK( chunk() == readContentFromFile( filename ) );

      std::remove( filename.c_str() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    "n+H1 data                                                            0 0  0     \n"
    " 1.001000+3 9.991673-1         -1          0          0          0 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n"
    " 0.000000+0 2.000000+7          0          0         10          8 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0         87          4 125 1451     \n"
    "  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                          125 1451     \n"
    " NDS 148, 1 (2018)    DIST-FEB18                       20170124    125 1451     \n"
    "----ENDF/B-VIII.0     MATERIAL  125                                125 1451     \n"
    "-----INCIDENT NEUTRON DATA                                         125 1451     \n"
    "------ENDF-6 FORMAT                                                125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "The new R-matrix analysis of the N-N system on which the ENDF/B-   125 1451     \n"
    "VII evaluation for 1H is based differs from the previous one use   125 1451     \n"
    "for ENDF/B-VI in several respects. Firstly, the n-p capture        125 1451     \n"
    "reaction (MT=102), and its inverse, deuteron photo-                125 1451     \n"
    "disintegration, were a part of the analysis, rather than added     125 1451     \n"
    "later as before. The analysis used a new method for including      125 1451     \n"
    "photon channels in R-matrix theory [1], which gave a better        125 1451     \n"
    "description of the E1 transitions, in particular.  The data for    125 1451     \n"
    "these reactions are mostly integrated and differential cross       125 1451     \n"
    "sections, but some information about polarizations was also        125 1451     \n"
    "included.  The thermal capture cross section was taken to be       125 1451     \n"
    "332.0 mb, as was the recommendation from preliminary data          125 1451     \n"
    "testing. Good agreement was obtained with recent cross-section     125 1451     \n"
    "measurements [2,3] by astrophysical groups in the 20-550 keV       125 1451     \n"
    "range, as well as with earlier measurements that had been done     125 1451     \n"
    "mostly as photo-disintegration experiments at energies below 14    125 1451     \n"
    "MeV.                                                               125 1451     \n"
    "The new analysis includes several additional measurements of the   125 1451     \n"
    "total cross section (MT=1).  The evaluated cross section           125 1451     \n"
    "deviates at most by about -0.5% around 10 MeV from that of         125 1451     \n"
    "ENDF/B-VI.  The estimated uncertainty of the MT=1 cross section    125 1451     \n"
    "is given at 2 MeV steps in the following table:                    125 1451     \n"
    "           En             Uncert. (%)                              125 1451     \n"
    "            0                0.20                                  125 1451     \n"
    "            2                0.22                                  125 1451     \n"
    "            4                0.30                                  125 1451     \n"
    "            6                0.36                                  125 1451     \n"
    "            8                0.44                                  125 1451     \n"
    "           10                0.50                                  125 1451     \n"
    "           12                0.49                                  125 1451     \n"
    "           14                0.46                                  125 1451     \n"
    "           16                0.40                                  125 1451     \n"
    "           18                0.35                                  125 1451     \n"
    "           20                0.30                                  125 1451     \n"
    "                                                                   125 1451     \n"
    "For n-p scattering (MT=2), new information was included about the  125 1451     \n"
    "low-energy cross sections (MF=3) and about the angular             125 1451     \n"
    "distributions (MF=4).  A new measurement of the angular            125 1451     \n"
    "distribution at 10 MeV [4], plus corrections to earlier data at    125 1451     \n"
    "14 MeV, moved the back-angle asymmetry in the 10-14 MeV range to   125 1451     \n"
    "values that lie between those obtained for ENDF/B-V and ENDF/B-    125 1451     \n"
    "VI.  The addition of the latest value of the thermal coherent      125 1451     \n"
    "scattering length [5] had the interesting effect of reducing the   125 1451     \n"
    "\"zero-energy\" scattering cross section somewhat to agree           125 1451     \n"
    "perfectly with an earlier measurement by Houk [6], and disagree    125 1451     \n"
    "with the later, more precise, value of Dilg [7].  The              125 1451     \n"
    "covariances for MT=2 will be added later, but the uncertainties    125 1451     \n"
    "on the integrated cross section should be similar to those         125 1451     \n"
    "listed above for the total cross section.                          125 1451     \n"
    "                                                                   125 1451     \n"
    "REFERENCES                                                         125 1451     \n"
    "                                                                   125 1451     \n"
    "[1] G. M. Hale and A. S. Johnson, Proc. 17th Int. IUPAP Conf. on   125 1451     \n"
    "    Few-Body Problems in Physics, 5-10 June 2003, Durham NC, W.    125 1451     \n"
    "    Gloeckle and W. Tornow,  eds., Elsevier B.V., pp. S120-S122    125 1451     \n"
    "   (2004).                                                         125 1451     \n"
    "[2] T. S. Suzuki et al., Astrophys. Lett. 449, L59 (1995).         125 1451     \n"
    "[3] Y. Nagai et al., Phys. Rev. C 56, 3173 (1997).                 125 1451     \n"
    "[4] N. Boukharouba et al., Phys. Rev. C 65, 014004 (2002).         125 1451     \n"
    "[5] K. Schoen et al., Phys. Rev. C 67, 044005 (2003).              125 1451     \n"
    "[6] T. L. Houk, Phys. Rev. C 3, 1886 (1971).                       125 1451     \n"
    "[7] W. Dilg, Phys. Rev. C 11, 103 (1975).                          125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                                                   125 1451     \n"
    "Covariances were adopted from COMMARA-2.0 library in July 2011.    125 1451     \n"
    "These covariances were obtained at LANL by full scale R-matrix     125 1451     \n"
    "analysis of more than 5000 experimental data (chi-square/degree    125 1451     \n"
    "of freedom of 0.83). [1] The major channel in this case is elastic 125 1451     \n"
    "scattering, often labeled also as ''n-p'' scattering. Elastic      125 1451     \n"
    "scattering serves as neutron cross section standard from 1 keV to  125 1451     \n"
    "20 MeV, with cross sections well determined. Uncertainties for     125 1451     \n"
    "elastic scattering rise from values well below 1%, reach maximum   125 1451     \n"
    "at about 8 MeV, then gradually decrease with increasing energy.    125 1451     \n"
    "In addition to elastic scattering, covariances are supplied for    125 1451     \n"
    "radiative capture.                                                 125 1451     \n"
    "                                                                   125 1451     \n"
    "REFERENCES                                                         125 1451     \n"
    "[1] G. M. Hale, \"Covariances from light-element R-matrix           125 1451     \n"
    "analyses,\" Nuclear Data Sheets, 109, 2812 (2008).                  125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                1        451         95          0 125 1451     \n"
    "                                3          1         54          0 125 1451     \n"
    "                                3          2         54          0 125 1451     \n"
    "                                3        102         54          0 125 1451     \n"
    "                                                                   125 1  0     \n"
    "                                                                   125 0  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1     \n"
    " 0.000000+0 0.000000+0          0          0          2        153 125 3  1     \n"
    "          9          5        153          2                       125 3  1     \n"
    " 1.000000-5 3.716477+1 2.000000-5 3.226505+1 5.000000-5 2.791738+1 125 3  1     \n"
    " 1.000000-4 2.572616+1 2.000000-4 2.417673+1 5.000000-4 2.280187+1 125 3  1     \n"
    " 1.000000-3 2.210895+1 2.000000-3 2.161898+1 5.000000-3 2.118421+1 125 3  1     \n"
    " 1.000000-2 2.096509+1 2.530000-2 2.076866+1 1.000000-1 2.060335+1 125 3  1     \n"
    " 2.000000-1 2.055434+1 5.000000-1 2.051083+1 1.000000+0 2.048885+1 125 3  1     \n"
    " 2.000000+0 2.047322+1 5.000000+0 2.045906+1 1.000000+1 2.045146+1 125 3  1     \n"
    " 2.000000+1 2.044521+1 5.000000+1 2.043683+1 1.000000+2 2.042791+1 125 3  1     \n"
    " 2.000000+2 2.041293+1 5.000000+2 2.037138+1 1.000000+3 2.030414+1 125 3  1     \n"
    " 2.000000+3 2.017204+1 3.000000+3 2.004215+1 4.000000+3 1.991424+1 125 3  1     \n"
    " 5.000000+3 1.978823+1 6.000000+3 1.966405+1 7.000000+3 1.954166+1 125 3  1     \n"
    " 8.000000+3 1.942101+1 9.000000+3 1.930207+1 1.000000+4 1.918479+1 125 3  1     \n"
    " 1.200000+4 1.895510+1 1.400000+4 1.873167+1 1.600000+4 1.851423+1 125 3  1     \n"
    " 1.800000+4 1.830255+1 2.000000+4 1.809640+1 2.200000+4 1.789556+1 125 3  1     \n"
    " 2.400000+4 1.769984+1 2.600000+4 1.750902+1 2.800000+4 1.732294+1 125 3  1     \n"
    " 3.000000+4 1.714141+1 3.500000+4 1.670645+1 4.000000+4 1.629656+1 125 3  1     \n"
    " 4.500000+4 1.590960+1 5.000000+4 1.554371+1 5.500000+4 1.519718+1 125 3  1     \n"
    " 6.000000+4 1.486851+1 6.500000+4 1.455635+1 7.000000+4 1.425946+1 125 3  1     \n"
    " 7.500000+4 1.397675+1 8.000000+4 1.370721+1 8.500000+4 1.344993+1 125 3  1     \n"
    " 9.000000+4 1.320410+1 9.500000+4 1.296894+1 1.000000+5 1.274378+1 125 3  1     \n"
    " 1.100000+5 1.232097+1 1.200000+5 1.193120+1 1.300000+5 1.157070+1 125 3  1     \n"
    " 1.400000+5 1.123625+1 1.500000+5 1.092508+1 1.600000+5 1.063481+1 125 3  1     \n"
    " 1.700000+5 1.036336+1 1.800000+5 1.010893+1 1.900000+5 9.869935+0 125 3  1     \n"
    " 2.000000+5 9.644989+0 2.200000+5 9.232457+0 2.400000+5 8.863064+0 125 3  1     \n"
    " 2.600000+5 8.530225+0 2.800000+5 8.228636+0 3.000000+5 7.953971+0 125 3  1     \n"
    " 3.200000+5 7.702670+0 3.400000+5 7.471777+0 3.600000+5 7.258815+0 125 3  1     \n"
    " 3.800000+5 7.061693+0 4.000000+5 6.878637+0 4.200000+5 6.708125+0 125 3  1     \n"
    " 4.400000+5 6.548852+0 4.600000+5 6.399688+0 4.800000+5 6.259648+0 125 3  1     \n"
    " 5.000000+5 6.127875+0 5.500000+5 5.829882+0 6.000000+5 5.569515+0 125 3  1     \n"
    " 6.500000+5 5.339645+0 7.000000+5 5.134850+0 7.500000+5 4.950937+0 125 3  1     \n"
    " 8.000000+5 4.784609+0 8.500000+5 4.633238+0 9.000000+5 4.494702+0 125 3  1     \n"
    " 9.500000+5 4.367271+0 1.000000+6 4.249519+0 1.100000+6 4.038494+0 125 3  1     \n"
    " 1.200000+6 3.854211+0 1.300000+6 3.691309+0 1.400000+6 3.545810+0 125 3  1     \n"
    " 1.500000+6 3.414699+0 1.600000+6 3.295645+0 1.700000+6 3.186817+0 125 3  1     \n"
    " 1.800000+6 3.086754+0 1.900000+6 2.994275+0 2.000000+6 2.908414+0 125 3  1     \n"
    " 2.200000+6 2.753484+0 2.400000+6 2.617003+0 2.600000+6 2.495402+0 125 3  1     \n"
    " 2.800000+6 2.386035+0 3.000000+6 2.286895+0 3.200000+6 2.196421+0 125 3  1     \n"
    " 3.400000+6 2.113381+0 3.600000+6 2.036785+0 3.800000+6 1.965823+0 125 3  1     \n"
    " 4.000000+6 1.899828+0 4.200000+6 1.838244+0 4.400000+6 1.780601+0 125 3  1     \n"
    " 4.600000+6 1.726497+0 4.800000+6 1.675590+0 5.000000+6 1.627582+0 125 3  1     \n"
    " 5.200000+6 1.582216+0 5.400000+6 1.539263+0 5.600000+6 1.498525+0 125 3  1     \n"
    " 5.800000+6 1.459826+0 6.000000+6 1.423007+0 6.200000+6 1.387929+0 125 3  1     \n"
    " 6.400000+6 1.354466+0 6.600000+6 1.322504+0 6.800000+6 1.291942+0 125 3  1     \n"
    " 7.000000+6 1.262686+0 7.500000+6 1.194725+0 8.000000+6 1.133290+0 125 3  1     \n"
    " 8.500000+6 1.077473+0 9.000000+6 1.026529+0 9.500000+6 9.798437-1 125 3  1     \n"
    " 1.000000+7 9.369061-1 1.050000+7 8.972839-1 1.100000+7 8.606105-1 125 3  1     \n"
    " 1.150000+7 8.265722-1 1.200000+7 7.948987-1 1.250000+7 7.653557-1 125 3  1     \n"
    " 1.300000+7 7.377393-1 1.350000+7 7.118704-1 1.400000+7 6.875919-1 125 3  1     \n"
    " 1.450000+7 6.647646-1 1.500000+7 6.432651-1 1.550000+7 6.229834-1 125 3  1     \n"
    " 1.600000+7 6.038214-1 1.650000+7 5.856907-1 1.700000+7 5.685123-1 125 3  1     \n"
    " 1.750000+7 5.522144-1 1.800000+7 5.367326-1 1.850000+7 5.220080-1 125 3  1     \n"
    " 1.900000+7 5.079874-1 1.950000+7 4.946221-1 2.000000+7 4.818679-1 125 3  1     \n"
    "                                                                   125 3  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  2     \n"
    " 0.000000+0 0.000000+0          0          0          1        153 125 3  2     \n"
    "        153          2                                             125 3  2     \n"
    " 1.000000-5 2.043608+1 2.000000-5 2.043608+1 5.000000-5 2.043608+1 125 3  2     \n"
    " 1.000000-4 2.043608+1 2.000000-4 2.043608+1 5.000000-4 2.043608+1 125 3  2     \n"
    " 1.000000-3 2.043608+1 2.000000-3 2.043608+1 5.000000-3 2.043608+1 125 3  2     \n"
    " 1.000000-2 2.043608+1 2.530000-2 2.043608+1 1.000000-1 2.043607+1 125 3  2     \n"
    " 2.000000-1 2.043605+1 5.000000-1 2.043601+1 1.000000+0 2.043595+1 125 3  2     \n"
    " 2.000000+0 2.043581+1 5.000000+0 2.043541+1 1.000000+1 2.043473+1 125 3  2     \n"
    " 2.000000+1 2.043339+1 5.000000+1 2.042935+1 1.000000+2 2.042263+1 125 3  2     \n"
    " 2.000000+2 2.040919+1 5.000000+2 2.036903+1 1.000000+3 2.030248+1 125 3  2     \n"
    " 2.000000+3 2.017087+1 3.000000+3 2.004120+1 4.000000+3 1.991343+1 125 3  2     \n"
    " 5.000000+3 1.978750+1 6.000000+3 1.966339+1 7.000000+3 1.954105+1 125 3  2     \n"
    " 8.000000+3 1.942045+1 9.000000+3 1.930154+1 1.000000+4 1.918430+1 125 3  2     \n"
    " 1.200000+4 1.895466+1 1.400000+4 1.873126+1 1.600000+4 1.851386+1 125 3  2     \n"
    " 1.800000+4 1.830220+1 2.000000+4 1.809607+1 2.200000+4 1.789525+1 125 3  2     \n"
    " 2.400000+4 1.769954+1 2.600000+4 1.750874+1 2.800000+4 1.732267+1 125 3  2     \n"
    " 3.000000+4 1.714116+1 3.500000+4 1.670622+1 4.000000+4 1.629635+1 125 3  2     \n"
    " 4.500000+4 1.590941+1 5.000000+4 1.554353+1 5.500000+4 1.519701+1 125 3  2     \n"
    " 6.000000+4 1.486836+1 6.500000+4 1.455620+1 7.000000+4 1.425932+1 125 3  2     \n"
    " 7.500000+4 1.397662+1 8.000000+4 1.370708+1 8.500000+4 1.344982+1 125 3  2     \n"
    " 9.000000+4 1.320398+1 9.500000+4 1.296883+1 1.000000+5 1.274368+1 125 3  2     \n"
    " 1.100000+5 1.232087+1 1.200000+5 1.193111+1 1.300000+5 1.157061+1 125 3  2     \n"
    " 1.400000+5 1.123617+1 1.500000+5 1.092500+1 1.600000+5 1.063473+1 125 3  2     \n"
    " 1.700000+5 1.036329+1 1.800000+5 1.010886+1 1.900000+5 9.869873+0 125 3  2     \n"
    " 2.000000+5 9.644929+0 2.200000+5 9.232401+0 2.400000+5 8.863011+0 125 3  2     \n"
    " 2.600000+5 8.530176+0 2.800000+5 8.228589+0 3.000000+5 7.953925+0 125 3  2     \n"
    " 3.200000+5 7.702627+0 3.400000+5 7.471735+0 3.600000+5 7.258774+0 125 3  2     \n"
    " 3.800000+5 7.061654+0 4.000000+5 6.878598+0 4.200000+5 6.708087+0 125 3  2     \n"
    " 4.400000+5 6.548815+0 4.600000+5 6.399651+0 4.800000+5 6.259612+0 125 3  2     \n"
    " 5.000000+5 6.127840+0 5.500000+5 5.829847+0 6.000000+5 5.569481+0 125 3  2     \n"
    " 6.500000+5 5.339611+0 7.000000+5 5.134817+0 7.500000+5 4.950904+0 125 3  2     \n"
    " 8.000000+5 4.784576+0 8.500000+5 4.633204+0 9.000000+5 4.494668+0 125 3  2     \n"
    " 9.500000+5 4.367238+0 1.000000+6 4.249485+0 1.100000+6 4.038460+0 125 3  2     \n"
    " 1.200000+6 3.854177+0 1.300000+6 3.691274+0 1.400000+6 3.545775+0 125 3  2     \n"
    " 1.500000+6 3.414663+0 1.600000+6 3.295609+0 1.700000+6 3.186781+0 125 3  2     \n"
    " 1.800000+6 3.086717+0 1.900000+6 2.994238+0 2.000000+6 2.908377+0 125 3  2     \n"
    " 2.200000+6 2.753447+0 2.400000+6 2.616966+0 2.600000+6 2.495365+0 125 3  2     \n"
    " 2.800000+6 2.385998+0 3.000000+6 2.286858+0 3.200000+6 2.196384+0 125 3  2     \n"
    " 3.400000+6 2.113344+0 3.600000+6 2.036748+0 3.800000+6 1.965786+0 125 3  2     \n"
    " 4.000000+6 1.899792+0 4.200000+6 1.838208+0 4.400000+6 1.780565+0 125 3  2     \n"
    " 4.600000+6 1.726461+0 4.800000+6 1.675555+0 5.000000+6 1.627547+0 125 3  2     \n"
    " 5.200000+6 1.582180+0 5.400000+6 1.539228+0 5.600000+6 1.498490+0 125 3  2     \n"
    " 5.800000+6 1.459791+0 6.000000+6 1.422973+0 6.200000+6 1.387895+0 125 3  2     \n"
    " 6.400000+6 1.354432+0 6.600000+6 1.322471+0 6.800000+6 1.291908+0 125 3  2     \n"
    " 7.000000+6 1.262652+0 7.500000+6 1.194691+0 8.000000+6 1.133258+0 125 3  2     \n"
    " 8.500000+6 1.077440+0 9.000000+6 1.026496+0 9.500000+6 9.798120-1 125 3  2     \n"
    " 1.000000+7 9.368747-1 1.050000+7 8.972527-1 1.100000+7 8.605796-1 125 3  2     \n"
    " 1.150000+7 8.265415-1 1.200000+7 7.948682-1 1.250000+7 7.653255-1 125 3  2     \n"
    " 1.300000+7 7.377093-1 1.350000+7 7.118406-1 1.400000+7 6.875623-1 125 3  2     \n"
    " 1.450000+7 6.647352-1 1.500000+7 6.432359-1 1.550000+7 6.229545-1 125 3  2     \n"
    " 1.600000+7 6.037926-1 1.650000+7 5.856622-1 1.700000+7 5.684839-1 125 3  2     \n"
    " 1.750000+7 5.521863-1 1.800000+7 5.367046-1 1.850000+7 5.219803-1 125 3  2     \n"
    " 1.900000+7 5.079599-1 1.950000+7 4.945948-1 2.000000+7 4.818408-1 125 3  2     \n"
    "                                                                   125 3  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3102     \n"
    " 2.224648+6 2.224648+6          0          0          2        153 125 3102     \n"
    "         33          5        153          2                       125 3102     \n"
    " 1.000000-5 1.672869+1 2.000000-5 1.182897+1 5.000000-5 7.481299+0 125 3102     \n"
    " 1.000000-4 5.290077+0 2.000000-4 3.740649+0 5.000000-4 2.365794+0 125 3102     \n"
    " 1.000000-3 1.672869+0 2.000000-3 1.182897+0 5.000000-3 7.481298-1 125 3102     \n"
    " 1.000000-2 5.290077-1 2.530000-2 3.325842-1 1.000000-1 1.672868-1 125 3102     \n"
    " 2.000000-1 1.182896-1 5.000000-1 7.481273-2 1.000000+0 5.290040-2 125 3102     \n"
    " 2.000000+0 3.740597-2 5.000000+0 2.365712-2 1.000000+1 1.672753-2 125 3102     \n"
    " 2.000000+1 1.182733-2 5.000000+1 7.478702-3 1.000000+2 5.286408-3 125 3102     \n"
    " 2.000000+2 3.735465-3 5.000000+2 2.357618-3 1.000000+3 1.661353-3 125 3102     \n"
    " 2.000000+3 1.166741-3 3.000000+3 9.462015-4 4.000000+3 8.139461-4 125 3102     \n"
    " 5.000000+3 7.231833-4 6.000000+3 6.558304-4 7.000000+3 6.032225-4 125 3102     \n"
    " 8.000000+3 5.606171-4 9.000000+3 5.251699-4 1.000000+4 4.950573-4 125 3102     \n"
    " 1.200000+4 4.462792-4 1.400000+4 4.081033-4 1.600000+4 3.771411-4 125 3102     \n"
    " 1.800000+4 3.513565-4 2.000000+4 3.294414-4 2.200000+4 3.105111-4 125 3102     \n"
    " 2.400000+4 2.939427-4 2.600000+4 2.792827-4 2.800000+4 2.661920-4 125 3102     \n"
    " 3.000000+4 2.544108-4 3.500000+4 2.294576-4 4.000000+4 2.093174-4 125 3102     \n"
    " 4.500000+4 1.926474-4 5.000000+4 1.785801-4 5.500000+4 1.665254-4 125 3102     \n"
    " 6.000000+4 1.560654-4 6.500000+4 1.468947-4 7.000000+4 1.387839-4 125 3102     \n"
    " 7.500000+4 1.315567-4 8.000000+4 1.250750-4 8.500000+4 1.192289-4 125 3102     \n"
    " 9.000000+4 1.139298-4 9.500000+4 1.091051-4 1.000000+5 1.046948-4 125 3102     \n"
    " 1.100000+5 9.692518-5 1.200000+5 9.030618-5 1.300000+5 8.460828-5 125 3102     \n"
    " 1.400000+5 7.965967-5 1.500000+5 7.532893-5 1.600000+5 7.151376-5 125 3102     \n"
    " 1.700000+5 6.813319-5 1.800000+5 6.512232-5 1.900000+5 6.242845-5 125 3102     \n"
    " 2.000000+5 6.000834-5 2.200000+5 5.585212-5 2.400000+5 5.243121-5 125 3102     \n"
    " 2.600000+5 4.958603-5 2.800000+5 4.719921-5 3.000000+5 4.518250-5 125 3102     \n"
    " 3.200000+5 4.346834-5 3.400000+5 4.200417-5 3.600000+5 4.074852-5 125 3102     \n"
    " 3.800000+5 3.966823-5 4.000000+5 3.873653-5 4.200000+5 3.793158-5 125 3102     \n"
    " 4.400000+5 3.723536-5 4.600000+5 3.663293-5 4.800000+5 3.611179-5 125 3102     \n"
    " 5.000000+5 3.566139-5 5.500000+5 3.478944-5 6.000000+5 3.419936-5 125 3102     \n"
    " 6.500000+5 3.381641-5 7.000000+5 3.358747-5 7.500000+5 3.347392-5 125 3102     \n"
    " 8.000000+5 3.344714-5 8.500000+5 3.348555-5 9.000000+5 3.357270-5 125 3102     \n"
    " 9.500000+5 3.369588-5 1.000000+6 3.384519-5 1.100000+6 3.419283-5 125 3102     \n"
    " 1.200000+6 3.457117-5 1.300000+6 3.495241-5 1.400000+6 3.531924-5 125 3102     \n"
    " 1.500000+6 3.566120-5 1.600000+6 3.597230-5 1.700000+6 3.624960-5 125 3102     \n"
    " 1.800000+6 3.649216-5 1.900000+6 3.670034-5 2.000000+6 3.687541-5 125 3102     \n"
    " 2.200000+6 3.713370-5 2.400000+6 3.728419-5 2.600000+6 3.734507-5 125 3102     \n"
    " 2.800000+6 3.733340-5 3.000000+6 3.726422-5 3.200000+6 3.715036-5 125 3102     \n"
    " 3.400000+6 3.700247-5 3.600000+6 3.682929-5 3.800000+6 3.663785-5 125 3102     \n"
    " 4.000000+6 3.643380-5 4.200000+6 3.622162-5 4.400000+6 3.600482-5 125 3102     \n"
    " 4.600000+6 3.578613-5 4.800000+6 3.556769-5 5.000000+6 3.535109-5 125 3102     \n"
    " 5.200000+6 3.513755-5 5.400000+6 3.492796-5 5.600000+6 3.472296-5 125 3102     \n"
    " 5.800000+6 3.452299-5 6.000000+6 3.432833-5 6.200000+6 3.413912-5 125 3102     \n"
    " 6.400000+6 3.395544-5 6.600000+6 3.377725-5 6.800000+6 3.360450-5 125 3102     \n"
    " 7.000000+6 3.343707-5 7.500000+6 3.304070-5 8.000000+6 3.267375-5 125 3102     \n"
    " 8.500000+6 3.233307-5 9.000000+6 3.201545-5 9.500000+6 3.171787-5 125 3102     \n"
    " 1.000000+7 3.143754-5 1.050000+7 3.117192-5 1.100000+7 3.091877-5 125 3102     \n"
    " 1.150000+7 3.067609-5 1.200000+7 3.044214-5 1.250000+7 3.021540-5 125 3102     \n"
    " 1.300000+7 2.999455-5 1.350000+7 2.977845-5 1.400000+7 2.956611-5 125 3102     \n"
    " 1.450000+7 2.935670-5 1.500000+7 2.914951-5 1.550000+7 2.894393-5 125 3102     \n"
    " 1.600000+7 2.873946-5 1.650000+7 2.853569-5 1.700000+7 2.833227-5 125 3102     \n"
    " 1.750000+7 2.812894-5 1.800000+7 2.792548-5 1.850000+7 2.772174-5 125 3102     \n"
    " 1.900000+7 2.751761-5 1.950000+7 2.731301-5 2.000000+7 2.710792-5 125 3102     \n"
    "                                                                   125 3  0     \n"
    "                                                                   125 0  0     \n"
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