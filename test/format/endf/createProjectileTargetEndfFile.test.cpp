// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createProjectileTargetEndfFile.hpp"

// other includes
#include <cstdio>
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

std::string chunkForGroundState();
std::string chunkForMetastableState();
std::string readContentFromFile( const std::string& );

SCENARIO( "createAtomicRelaxationEndfFile" ) {

  GIVEN( "projectile-target data - incident neutrons for a ground state target" ) {

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

      CHECK( chunkForGroundState() == readContentFromFile( filename ) );

      std::remove( filename.c_str() );
    } // THEN
  } // GIVEN

  GIVEN( "projectile-target data - incident neutrons for a metastable target" ) {

    std::string description =
        " 93-Np-236M LANL      EVAL-JAN17 T. Kawano, P.Talou               \n"
        " NDS 148, 1 (2018)    DIST-AUG24 REV1-NOV19            20240830   \n"
        "---- ENDF/B-VIII.1    MATERIAL 9344         REVISION 1            \n"
        "----- INCIDENT-NEUTRON DATA                                       \n"
        "------ ENDF-6                                                     \n"
        "                                                                  \n"
        "******************************************************************\n"
        " Np-236m Evaluation                                               \n"
        "                                              T. Kawano, P. Talou \n"
        "                                                        Jan. 2012 \n"
        "******************************************************************\n"
        " Evaluation based on:                                             \n"
        "    ENDF/B-VII.1 (JENDL-4.0) Np236 ground state data              \n"
        "    CoH3 calculation to the ground and 60keV levels               \n"
        "                                                                  \n"
        " The coupled-channels calculation in JENDL-4.0 assumes            \n"
        " the following level scheme, where all the excited levels         \n"
        " except for 60keV meta state are postulated.                      \n"
        "                                                                  \n"
        "    -------------------                                           \n"
        "    No.  Ex(MeV)   J PI                                           \n"
        "    -------------------                                           \n"
        "     0  0.00000   6  -  *                                         \n"
        "     1  0.05600   7  -  *                                         \n"
        "     2  0.06000   1  +                                            \n"
        "     3  0.07600   2  +                                            \n"
        "     4  0.10000   3  +                                            \n"
        "     5  0.12000   8  -  *                                         \n"
        "     6  0.13200   4  +                                            \n"
        "                                                                  \n"
        " First we followed the same g.s. calculation as JENDL to try to   \n"
        " reproduce all the g.s. cross sections. Then the same parameters  \n"
        " are employed to calculate cross sections on the excited state,   \n"
        " with the coupling of 1+, 2+, 3+, and 4+ states.                  \n"
        "                                                                  \n"
        " MF1 MT452, 455, 456                                              \n"
        "    same as ground state                                          \n"
        "                                                                  \n"
        " MF2                                                              \n"
        "    the same resonance parameters for the ground state,           \n"
        "    but spins were changed.                                       \n"
        "                                                                  \n"
        " MF3                                                              \n"
        "    The following cross sections were evaluated by applying       \n"
        "    a scaling factor of F to the ground state cross sections,     \n"
        "    where F = CoH(meta) / CoH(ground).                            \n"
        "                                                                  \n"
        "    MT  16 (n,2n)                                                 \n"
        "    MT  17 (n,3n)                                                 \n"
        "    MT  18 fission                                                \n"
        "    MT  37 (n,4n)                                                 \n"
        "                                                                  \n"
        "    These sections below were replaced by the CoH excited state   \n"
        "    calculations.                                                 \n"
        "                                                                  \n"
        "    MT   1 total                                                  \n"
        "    MT   2 elastic = total - sum of partials                      \n"
        "    MT  51 - 56 discrete level inelastic scattering               \n"
        "    MT  91 continuum inelastic scattering                         \n"
        "    MT 102 radiative capture                                      \n"
        "                                                                  \n"
        " MF4                                                              \n"
        "    MT   2, 51 - 56, new CoH calculations                         \n"
        "                                                                  \n"
        " MF5                                                              \n"
        "    same as g.s.                                                  \n"
        "                                                                  \n"
        " MF6                                                              \n"
        "    MT  51 - 56                                                   \n"
        "    the angular distributions for the disrete levels removed,     \n"
        "    and given in new evaluations in MF4                           \n"
        "                                                                  \n"
        "    MT  16, 17, 37, 91, 102                                       \n"
        "    same as g.s.                                                  \n"
        "                                                                  \n"
        " MF12 MT18                                                        \n"
        "    same as g.s.                                                  \n"
        "                                                                  \n"
        " MF14 MT18                                                        \n"
        "    same as g.s.                                                  \n"
        "                                                                  \n"
        " MF15 MT18                                                        \n"
        "    same as g.s.                                                  \n"
        "                                                                  \n"
        "******************************************************************\n"
        "                                                                  \n"
        " ***************** Program LINEAR (VERSION 2017-1) ***************\n"
        " For All Data Greater than 1.0000E-10 barns in Absolute Value     \n"
        " Data Linearized to Within an Accuracy of .100000000 per-cent     \n"
        " ***************** Program FIXUP (Version 2017-1) ****************\n"
        " Corrected ZA/AWR in All Sections-----------------------------Yes \n"
        " Corrected Thresholds-----------------------------------------No  \n"
        " Extended Cross Sections to 20 MeV----------------------------No  \n"
        " Allow Cross Section Deletion---------------------------------No  \n"
        " Allow Cross Section Reconstruction---------------------------Yes \n"
        " Make All Cross Sections Non-Negative-------------------------Yes \n"
        " Delete Energies Not in Ascending Order-----------------------Yes \n"
        " Deleted Duplicate Points-------------------------------------Yes \n"
        " Check for Ascending MAT/MF/MT Order--------------------------Yes \n"
        " Check for Legal MF/MT Numbers--------------------------------Yes \n"
        " Allow Creation of Missing Sections---------------------------No  \n"
        " Allow Insertion of Energy Points-----------------------------No  \n"
        " Uniform Energy Grid for ALL MT-------------------------------No  \n"
        " Delete Section if Cross Section =0 at All Energies-----------Yes \n";

    std::vector< Reaction > reactions = {

      Reaction( id::ReactionID( "n,Np236_e2->total" ),
                { id::ReactionID( "n,Np236_e2->n,Np236_e2" ), id::ReactionID( "n,Np236_e2->2n,Np235[all]" ),
                  id::ReactionID( "n,Np236_e2->3n,Np234[all]" ), id::ReactionID( "n,Np236_e2->fission" ),
                  id::ReactionID( "n,Np236_e2->4n,Np233[all]" ), id::ReactionID( "n,Np236_e2->n,Np236" ),
                  id::ReactionID( "n,Np236_e2->n,Np236_e1" ), id::ReactionID( "n,Np236_e2->n,Np236_e3" ),
                  id::ReactionID( "n,Np236_e2->n,Np236_e4" ), id::ReactionID( "n,Np236_e2->n,Np236_e5" ),
                  id::ReactionID( "n,Np236_e2->n,Np236_e6" ), id::ReactionID( "n,Np236_e2->n,Np236[continuum]" ),
                  id::ReactionID( "n,Np236_e2->g,Np237[all]" ) },
                TabulatedCrossSection( { 1.000000e-5, 2.530000e-2, 2.150000e+1, 2.150000e+1, 23.3673337,
                                         24.8735163, 27.3167621, 3.000000e+1, 31.9780774, 33.8155969,
                                         37.2889621, 40.1261713, 42.3948687, 46.0406716, 5.000000e+1,
                                         54.3878654, 57.9296655, 63.6794833, 7.000000e+1, 76.5285581,
                                         81.8215398, 90.4552596, 1.000000e+2, 109.050774, 117.639701,
                                         125.708147, 133.220711, 147.464103, 159.137392, 168.494868,
                                         183.572802, 2.000000e+2, 221.336385, 238.819577, 252.832418,
                                         275.408289, 3.000000e+2, 319.780774, 338.155969, 372.889621,
                                         401.261713, 423.948687, 460.406716, 5.000000e+2, 543.878654,
                                         579.296655, 636.794833, 7.000000e+2, 765.285581, 818.215398,
                                         904.552596, 1.000000e+3, 1090.50774, 1176.39701, 1257.08147,
                                         1332.20711, 1474.64103, 1591.37392, 1684.94868, 1835.72802,
                                         2.000000e+3, 2213.36385, 2388.19576, 2528.32418, 2754.08289,
                                         3.000000e+3, 3197.80774, 3575.87035, 3888.47065, 4140.72721,
                                         4550.12485, 5.000000e+3, 5438.78654, 5792.96655, 6367.94833,
                                         7.000000e+3, 7652.85581, 8182.15398, 9045.52596, 1.000000e+4,
                                         10905.0774, 11763.9701, 12690.5097, 13432.9975, 14218.9262,
                                         14838.4044, 15484.8713, 15988.1385, 1.606836e+4, 17598.2223,
                                         17881.9119, 2.000000e+4, 22133.6385, 25768.3751, 3.000000e+4,
                                         34086.5811, 38729.8335, 4.017089e+4, 41283.5204, 5.000000e+4,
                                         59160.7979, 6.025634e+4, 7.000000e+4, 7.230761e+4, 83666.0027,
                                         1.000000e+5, 109544.512, 1.200000e+5, 129614.814, 1.400000e+5,
                                         1.700000e+5, 184390.890, 2.000000e+5, 211474.253, 223606.798,
                                         229931.650, 2.500000e+5, 273861.279, 3.000000e+5, 322370.980,
                                         340237.324, 346410.162, 368910.463, 4.000000e+5, 422948.506,
                                         441019.836, 469584.836, 5.000000e+5, 523317.570, 541516.633,
                                         547722.558, 570008.755, 6.000000e+5, 623573.927, 660682.791,
                                         7.000000e+5, 723762.416, 760927.023, 8.000000e+5, 823906.858,
                                         861113.334, 9.000000e+5, 948683.299, 1.000000e+6, 1048808.85,
                                         1.100000e+6, 1148912.53, 1.200000e+6, 1248999.60, 1.300000e+6,
                                         1349073.76, 1.400000e+6, 1449137.68, 1.500000e+6, 1549193.34,
                                         1.600000e+6, 1649242.25, 1.700000e+6, 1749285.57, 1.800000e+6,
                                         1849324.21, 1.900000e+6, 1949358.87, 2.000000e+6, 2071116.16,
                                         2126107.91, 2168307.83, 2233183.38, 2.300000e+6, 2348447.63,
                                         2385451.90, 2442054.42, 2.500000e+6, 2548566.38, 2585609.32,
                                         2642185.68, 2.700000e+6, 2772063.27, 2827370.15, 2869573.25,
                                         2.934062e+6, 3.000000e+6, 3058367.04, 3110368.97, 3156595.47,
                                         3197606.88, 3240370.35, 3270663.12, 3326548.60, 3369088.48,
                                         3433920.46, 3.500000e+6, 3558910.27, 3611269.57, 3657715.48,
                                         3698845.40, 3771938.77, 3827705.13, 3870070.30, 3934498.85,
                                         4.000000e+6, 4059327.19, 4111959.85, 4158572.93, 4241420.89,
                                         4304638.22, 4352668.80, 4425721.37, 4.500000e+6, 4559657.28,
                                         4612505.82, 4706468.94, 4778195.33, 4832706.57, 4915641.66,
                                         5.000000e+6, 5120568.45, 5212898.94, 5354525.58, 5.500000e+6,
                                         5.700940e+6, 5744562.65, 6.000000e+6, 6.500000e+6, 7.000000e+6,
                                         7.500000e+6, 8.000000e+6, 8.500000e+6, 9.000000e+6, 9.500000e+6,
                                         1.000000e+7, 10246950.8, 1.050000e+7, 10747092.7, 1.100000e+7,
                                         1.150000e+7, 1.200000e+7, 1.250000e+7, 1.271390e+7, 1.300000e+7,
                                         1.350000e+7, 1.400000e+7, 1.450000e+7, 1.500000e+7, 1.550000e+7,
                                         1.600000e+7, 1.650000e+7, 1.700000e+7, 1.750000e+7, 1.800000e+7,
                                         1.850000e+7, 1.880420e+7, 1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 0.000000e+0, 0.000000e+0, 97.9899276, 94.5374298,
                                         92.0126815, 88.3215918, 84.7359275, 82.5158479, 80.6155335,
                                         77.3789548, 75.0206824, 73.2879982, 70.7425315, 68.2558885,
                                         65.9713902, 64.3011478, 61.8598178, 59.4887034, 57.4477179,
                                         55.9578597, 53.7834832, 51.6749654, 50.0541369, 48.6787814,
                                         47.5061174, 46.5022305, 44.7918211, 43.5447548, 42.6278697,
                                         41.2795901, 39.9605512, 38.5994042, 37.6093123, 36.8827779,
                                         35.8168370, 34.7771291, 34.0795421, 33.4820702, 32.4636516,
                                         31.7209086, 3.117480e+1, 30.3718734, 29.5867160, 28.8701614,
                                         28.3456008, 27.5777765, 26.8307043, 26.1926795, 25.7260017,
                                         25.0433827, 24.3795830, 23.8802060, 23.4549648, 23.0912375,
                                         22.7789666, 22.2449035, 21.8538064, 21.5652806, 21.1394132,
                                         20.7208463, 20.3038349, 19.9982426, 19.7727033, 19.4396960,
                                         1.911232e+1, 18.9035928, 18.5453305, 18.2818013, 18.0866662,
                                         17.7973904, 17.5114376, 17.2973478, 17.1381502, 16.9010662,
                                         16.6653980, 16.4772821, 16.3364356, 16.1250399, 15.9128120,
                                         15.7867888, 15.6799903, 15.5657557, 15.4840025, 15.3982591,
                                         15.3359648, 15.2713846, 15.2251681, 15.2178518, 15.0330669,
                                         15.0011618, 14.7643522, 14.6371457, 14.4346428, 14.2156772,
                                         14.0810821, 13.9290671, 13.8848884, 13.8482212, 13.5626367,
                                         13.3502313, 13.3249488, 1.309361e+1, 13.0523672, 12.8439550,
                                         12.5458298, 12.3906369, 12.2270795, 12.0849935, 11.9321604,
                                         11.5236302, 11.3429892, 11.1477604, 11.0149946, 10.8749826,
                                         10.8043129, 10.5807403, 10.3397310, 10.0766499, 9.88060050,
                                         9.72448472, 9.67069846, 9.48332632, 9.22523749, 9.06900211,
                                         8.94627293, 8.75274389, 8.54721663, 8.42015636, 8.32119283,
                                         8.28751526, 8.16973746, 8.01160655, 7.91307405, 7.75837783,
                                         7.59494189, 7.51951813, 7.40184541, 7.27846306, 7.22288722,
                                         7.13660515, 7.04666923, 6.96848467, 6.88639927, 6.83736639,
                                         6.78618970, 6.76146217, 6.73582925, 6.73097418, 6.72607591,
                                         6.73703554, 6.74853606, 6.77163351, 6.79564856, 6.82762762,
                                         6.86074715, 6.89880211, 6.93810804, 6.97990297, 7.02297980,
                                         7.06663014, 7.11153885, 7.15556491, 7.20079013, 7.26034965,
                                         7.30647264, 7.34190259, 7.39642510, 7.45264113, 7.48718882,
                                         7.51359974, 7.55403437, 7.59546944, 7.62396416, 7.64571671,
                                         7.67896867, 7.71298119, 7.74337694, 7.76673836, 7.78458244,
                                         7.81187608, 7.83981357, 7.84963767, 7.85841141, 7.86622587,
                                         7.87316977, 7.88042407, 7.88601235, 7.89634035, 7.90421179,
                                         7.916223e+0, 7.92848228, 7.92399335, 7.92001528, 7.91649494,
                                         7.91338368, 7.90786769, 7.90366963, 7.90048589, 7.89565246,
                                         7.89074807, 7.87501374, 7.86106081, 7.84870798, 7.82676178,
                                         7.81002287, 7.79730897, 7.77797743, 7.75832799, 7.73454942,
                                         7.71348725, 7.67604472, 7.64746735, 7.62575114, 7.59271487,
                                         7.55911558, 7.50157342, 7.45751051, 7.38992572, 7.320509e+0,
                                         7.21911740, 7.19722056, 7.06900383, 6.82545895, 6.60271182,
                                         6.40680352, 6.23938625, 6.09983883, 5.98669149, 5.89828680,
                                         5.83291191, 5.81106341, 5.78867655, 5.77620356, 5.76343810,
                                         5.75483168, 5.76038688, 5.77763020, 5.78889913, 5.80415603,
                                         5.83768079, 5.87608346, 5.91743801, 5.96004117, 6.00242979,
                                         6.04339070, 6.08195264, 6.11737084, 6.14909654, 6.17674102,
                                         6.20003570, 6.21145886, 6.21881057, 6.23295175, 6.24239181 } ) ),
      Reaction( id::ReactionID( "n,Np236_e2->n,Np236_e2" ),
                TabulatedCrossSection( { 1.00000e-5, .025300000, 21.5000000, 21.5000000, 30.0000000,
                                         50.0000000, 70.0000000, 100.000000, 200.000000, 300.000000,
                                         500.000000, 700.000000, 1000.00000, 2000.00000, 3000.00000,
                                         5000.00000, 7000.00000, 10000.0000, 16068.3600, 20000.0000,
                                         30000.0000, 40170.8900, 50000.0000, 60256.3400, 70000.0000,
                                         72307.6100, 100000.000, 120000.000, 140000.000, 170000.000,
                                         200000.000, 250000.000, 300000.000, 400000.000, 500000.000,
                                         600000.000, 700000.000, 800000.000, 900000.000, 1000000.00,
                                         1100000.00, 1200000.00, 1300000.00, 1400000.00, 1500000.00,
                                         1600000.00, 1700000.00, 1800000.00, 1900000.00, 2000000.00,
                                         2300000.00, 2500000.00, 2700000.00, 3000000.00, 3500000.00,
                                         4000000.00, 4500000.00, 5000000.00, 5500000.00, 5700940.00,
                                         6000000.00, 6500000.00, 7000000.00, 7500000.00, 8000000.00,
                                         8500000.00, 9000000.00, 9500000.00, 10000000.0, 10500000.0,
                                         11000000.0, 11500000.0, 12000000.0, 12500000.0, 12713900.0,
                                         13000000.0, 13500000.0, 14000000.0, 14500000.0, 15000000.0,
                                         15500000.0, 16000000.0, 16500000.0, 17000000.0, 17500000.0,
                                         18000000.0, 18500000.0, 18804200.0, 19000000.0, 19500000.0,
                                         20000000.0 },
                                       { 0.0       , 0.0       , 0.0       , 21.7398100, 20.2005200,
                                         18.2842500, 17.2628400, 16.3501000, 14.9739100, 14.3582200,
                                         13.7323700, 13.3925300, 13.0818900, 12.5867500, 12.3424900,
                                         12.0591400, 11.8767600, 11.6772600, 11.4905100, 11.2387200,
                                         10.9145300, 10.6697300, 10.4063900, 10.1895600, 9.97708900,
                                         9.93660500, 9.42794000, 9.18338300, 8.89306500, 8.44759200,
                                         7.95721800, 7.41984000, 6.80589600, 5.99705000, 5.22101300,
                                         4.70465100, 4.25383900, 3.94537900, 3.69395500, 3.49621500,
                                         3.35988100, 3.26615300, 3.20784500, 3.18129900, 3.17944400,
                                         3.19896700, 3.23546900, 3.28425600, 3.34363700, 3.40904700,
                                         3.62904800, 3.76992600, 3.89663900, 4.04973200, 4.18044100,
                                         4.18624400, 4.10633900, 3.95752100, 3.77261400, 3.70457700,
                                         3.58384000, 3.44521500, 3.21841700, 3.02326600, 2.83711100,
                                         2.69665300, 2.58289300, 2.51195400, 2.46144400, 2.43771700,
                                         2.43161100, 2.44289500, 2.46570100, 2.50459900, 2.52632800,
                                         2.55554500, 2.60977600, 2.66803900, 2.72519900, 2.78271300,
                                         2.83767300, 2.88545400, 2.93477500, 2.98043800, 3.02185100,
                                         3.06005400, 3.09325100, 3.11063900, 3.12183000, 3.14631400,
                                         3.16616600 } ),
                {}, 0., 0. ),
      Reaction( id::ReactionID( "n,Np236_e2->n,Np236[all]" ),
                { id::ReactionID( "n,Np236_e2->n,Np236" ),
                  id::ReactionID( "n,Np236_e2->n,Np236_e1" ),
                  id::ReactionID( "n,Np236_e2->n,Np236_e3" ),
                  id::ReactionID( "n,Np236_e2->n,Np236_e4" ),
                  id::ReactionID( "n,Np236_e2->n,Np236_e5" ),
                  id::ReactionID( "n,Np236_e2->n,Np236_e6" ),
                  id::ReactionID( "n,Np236_e2->n,Np236[continuum]" )  },
                TabulatedCrossSection( { 1.000000e-5, 2.530000e-2, 2.150000e+1, 2.150000e+1, 3.000000e+1,
                                         5.000000e+1, 7.000000e+1, 1.000000e+2, 2.000000e+2, 3.000000e+2,
                                         5.000000e+2, 7.000000e+2, 1.000000e+3, 2.000000e+3, 3.000000e+3,
                                         5.000000e+3, 7.000000e+3, 1.000000e+4, 1.606836e+4, 2.000000e+4,
                                         3.000000e+4, 4.017089e+4, 5.000000e+4, 6.025634e+4, 7.000000e+4,
                                         7.230761e+4, 1.000000e+5, 1.200000e+5, 1.400000e+5, 1.700000e+5,
                                         2.000000e+5, 2.500000e+5, 3.000000e+5, 4.000000e+5, 5.000000e+5,
                                         6.000000e+5, 7.000000e+5, 8.000000e+5, 9.000000e+5, 1.000000e+6,
                                         1.100000e+6, 1.200000e+6, 1.300000e+6, 1.400000e+6, 1.500000e+6,
                                         1.600000e+6, 1.700000e+6, 1.800000e+6, 1.900000e+6, 2.000000e+6,
                                         2.300000e+6, 2.500000e+6, 2.700000e+6, 3.000000e+6, 3.500000e+6,
                                         4.000000e+6, 4.500000e+6, 5.000000e+6, 5.500000e+6, 6.000000e+6,
                                         6.500000e+6, 7.000000e+6, 7.500000e+6, 8.000000e+6, 8.500000e+6,
                                         9.000000e+6, 9.500000e+6, 1.000000e+7, 1.050000e+7, 1.100000e+7,
                                         1.150000e+7, 1.200000e+7, 1.250000e+7, 1.300000e+7, 1.350000e+7,
                                         1.400000e+7, 1.450000e+7, 1.500000e+7, 1.550000e+7, 1.600000e+7,
                                         1.650000e+7, 1.700000e+7, 1.750000e+7, 1.800000e+7, 1.850000e+7,
                                         1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 0.000000e+0, 0.000000e+0, 2.587731e-6, 2.549935e-6,
                                         2.480724e-6, 2.426770e-6, 2.361572e-6, 2.209501e-6, 2.104713e-6,
                                         1.957481e-6, 1.853097e-6, 1.738628e-6, 1.519935e-6, 1.404649e-6,
                                         1.289746e-6, 1.241938e-6, 1.225257e-6, 9.593472e-7, 1.448101e-2,
                                         2.481576e-2, 3.305070e-2, 4.518423e-2, 6.268358e-2, 7.930936e-2,
                                         8.378925e-2, 1.472003e-1, 0.18464664, 0.25206382, 0.30145446,
                                         0.39468681, 0.51232716, 6.204205e-1, 0.80544419, 0.95118768,
                                         1.06516606, 1.15637153, 1.23263614, 1.29987124, 1.36206973,
                                         1.42158383, 1.47948563, 1.53591066, 1.59044406, 1.64223422,
                                         1.69012340, 1.73296667, 1.77027019, 1.80212786, 1.82902471,
                                         1.88747974, 1.91221157, 1.93128090, 1.95444028, 1.98992205,
                                         2.01996889, 2.03191586, 2.02763820, 2.01710117, 1.88877130,
                                         1.54767617, 1.25583887, 1.03559312, 0.89153021, 0.80003410,
                                         0.73736511, 0.69080675, 0.65453089, 0.62507661, 0.60030420,
                                         0.57841252, 0.55815121, 0.53861321, 0.51926311, 0.50094144,
                                         0.48322608, 0.46572836, 0.44973789, 0.43461089, 0.42509723,
                                         0.41164229, 0.39910538, 0.38688155, 0.37543443, 0.36472112,
                                         0.35435082, 0.34442736, 3.350783e-1 } ) ),
      Reaction( id::ReactionID( "n,Np236_e2->2n,Np235[all]" ),
                TabulatedCrossSection( { 5.700940e+6, 6.000000e+6, 6.500000e+6, 7.000000e+6, 7.500000e+6,
                                         8.000000e+6, 8.500000e+6, 9.000000e+6, 9.500000e+6, 1.000000e+7,
                                         1.050000e+7, 1.100000e+7, 1.150000e+7, 1.200000e+7, 1.250000e+7,
                                         1.300000e+7, 1.350000e+7, 1.400000e+7, 1.450000e+7, 1.500000e+7,
                                         1.550000e+7, 1.600000e+7, 1.650000e+7, 1.700000e+7, 1.750000e+7,
                                         1.800000e+7, 1.850000e+7, 1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 2.026253e-2, 1.087389e-1, 1.946756e-1, 2.596363e-1,
                                         3.046834e-1, 3.304883e-1, 3.442355e-1, 3.495967e-1, 3.540409e-1,
                                         3.591597e-1, 3.637072e-1, 3.700345e-1, 3.732710e-1, 3.638931e-1,
                                         3.374588e-1, 3.053616e-1, 2.690662e-1, 2.346856e-1, 2.063118e-1,
                                         1.863148e-1, 1.691293e-1, 1.556952e-1, 1.451486e-1, 1.387251e-1,
                                         1.317189e-1, 1.260265e-1, 1.210358e-1, 1.168384e-1, 1.108491e-1 } ),
                {}, -5.676680e+6, -5.676680e+6 ),
      Reaction( id::ReactionID( "n,Np236_e2->3n,Np234[all]" ),
                TabulatedCrossSection( { 1.271390e+7, 1.350000e+7, 1.400000e+7, 1.450000e+7, 1.500000e+7,
                                         1.550000e+7, 1.600000e+7, 1.650000e+7, 1.700000e+7, 1.750000e+7,
                                         1.800000e+7, 1.850000e+7, 1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 8.429257e-5, 8.379144e-4, 4.393801e-3, 1.004855e-2,
                                         1.623820e-2, 2.582424e-2, 3.433012e-2, 4.483658e-2, 5.302409e-2,
                                         6.039802e-2, 6.690118e-2, 7.254851e-2, 7.628671e-2, 8.022689e-2 } ),
                {}, -1.265980e+7, -1.265980e+7 ),
      Reaction( id::ReactionID( "n,Np236_e2->fission" ),
                TabulatedCrossSection( { 1.000000e-5, 2.530000e-2, 2.150000e+1, 2.150000e+1, 23.3673337,
                                         24.8735163, 27.3167621, 3.000000e+1, 31.9780774, 33.8155969,
                                         37.2889621, 40.1261713, 42.3948687, 46.0406716, 5.000000e+1,
                                         54.3878654, 57.9296655, 63.6794833, 7.000000e+1, 76.5285581,
                                         81.8215398, 90.4552596, 1.000000e+2, 109.050774, 117.639701,
                                         125.708147, 133.220711, 147.464103, 159.137392, 168.494868,
                                         183.572802, 2.000000e+2, 221.336385, 238.819577, 252.832418,
                                         275.408289, 3.000000e+2, 319.780774, 338.155969, 372.889621,
                                         401.261713, 423.948687, 460.406716, 5.000000e+2, 543.878654,
                                         579.296655, 636.794833, 7.000000e+2, 765.285581, 818.215398,
                                         904.552596, 1.000000e+3, 1090.50774, 1176.39701, 1257.08147,
                                         1332.20711, 1474.64103, 1591.37392, 1684.94868, 1835.72802,
                                         2.000000e+3, 2213.36385, 2388.19576, 2528.32418, 2754.08289,
                                         3.000000e+3, 3197.80774, 3575.87035, 3888.47065, 4140.72721,
                                         4550.12485, 5.000000e+3, 5438.78654, 5792.96655, 6367.94833,
                                         7.000000e+3, 7652.85581, 8182.15398, 9045.52596, 1.000000e+4,
                                         10905.0774, 12690.5097, 14218.9262, 15484.8713, 17598.2223,
                                         2.000000e+4, 22133.6385, 25768.3751, 3.000000e+4, 38729.8335,
                                         5.000000e+4, 7.000000e+4, 1.000000e+5, 109544.512, 1.200000e+5,
                                         1.400000e+5, 1.700000e+5, 2.000000e+5, 223606.798, 2.500000e+5,
                                         3.000000e+5, 346410.162, 4.000000e+5, 5.000000e+5, 547722.558,
                                         6.000000e+5, 7.000000e+5, 8.000000e+5, 9.000000e+5, 1.000000e+6,
                                         1.100000e+6, 1.200000e+6, 1.300000e+6, 1.400000e+6, 1.500000e+6,
                                         1.600000e+6, 1.700000e+6, 1.800000e+6, 1.900000e+6, 2.000000e+6,
                                         2.300000e+6, 2.500000e+6, 2.700000e+6, 3.000000e+6, 3240370.35,
                                         3.500000e+6, 4.000000e+6, 4.500000e+6, 5.000000e+6, 5.500000e+6,
                                         6.000000e+6, 6.500000e+6, 7.000000e+6, 7.500000e+6, 8.000000e+6,
                                         8.500000e+6, 9.000000e+6, 9.500000e+6, 1.000000e+7, 1.050000e+7,
                                         1.100000e+7, 1.150000e+7, 1.200000e+7, 1.250000e+7, 1.300000e+7,
                                         1.350000e+7, 1.400000e+7, 1.450000e+7, 1.500000e+7, 1.550000e+7,
                                         1.600000e+7, 1.650000e+7, 1.700000e+7, 1.750000e+7, 1.800000e+7,
                                         1.850000e+7, 1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 0.000000e+0, 0.000000e+0, 7.055598e+1, 67.6744903,
                                         65.5908663, 62.5850969, 5.971707e+1, 57.8383502, 56.2430191,
                                         53.5563416, 51.6258970, 50.2238663, 48.1918878, 4.624212e+1,
                                         44.3357773, 42.9577741, 40.9706576, 3.907546e+1, 37.3708807,
                                         36.1414237, 34.3726602, 3.269046e+1, 31.3061307, 30.1430164,
                                         29.1607952, 28.3276425, 26.9264939, 25.9213037, 25.1921141,
                                         24.1366101, 2.312533e+1, 21.9875688, 21.1711361, 20.5787684,
                                         19.7211486, 1.889927e+1, 18.3111781, 17.8116289, 16.9699868,
                                         16.3649583, 15.9253854, 15.2880652, 1.467625e+1, 14.0823250,
                                         13.6527082, 13.0327324, 1.244091e+1, 11.9132465, 11.5322384,
                                         10.9834516, 1.046078e+1, 10.0403906, 9.68643192, 9.38696935,
                                         9.132544e+0, 8.70378046, 8.39547058, 8.17142655, 7.84652095,
                                         7.534534e+0, 7.19712982, 6.95402969, 6.77710859, 6.52013068,
                                         6.272897e+0, 6.10588879, 5.82425223, 5.62158314, 5.474223e+0,
                                         5.26039380, 5.054917e+0, 4.89410923, 4.77686954, 4.60625486,
                                         4.441734e+0, 4.30817456, 4.21064716, 4.06848003, 3.931113e+0,
                                         3.84118412, 3.68873045, 3.57837431, 3.49777929, 3.38027751,
                                         3.266723e+0, 3.21141677, 3.13020810, 3.051053e+0, 2.97665954,
                                         2.904080e+0, 2.841287e+0, 2.788270e+0, 2.73524327, 2.683225e+0,
                                         2.622368e+0, 2.614940e+0, 2.647628e+0, 2.58015936, 2.514410e+0,
                                         2.528816e+0, 2.42350677, 2.322583e+0, 2.291684e+0, 2.23087267,
                                         2.171675e+0, 2.125047e+0, 2.049066e+0, 2.008141e+0, 1.988853e+0,
                                         1.969956e+0, 1.959189e+0, 1.954529e+0, 1.951783e+0, 1.951406e+0,
                                         1.951268e+0, 1.951234e+0, 1.951774e+0, 1.950686e+0, 1.949073e+0,
                                         1.925940e+0, 1.905030e+0, 1.878294e+0, 1.830670e+0, 1.79251488,
                                         1.755155e+0, 1.682749e+0, 1.618952e+0, 1.573188e+0, 1.530191e+0,
                                         1.575584e+0, 1.723289e+0, 1.933237e+0, 2.087771e+0, 2.205540e+0,
                                         2.272154e+0, 2.321689e+0, 2.345422e+0, 2.362413e+0, 2.366277e+0,
                                         2.367403e+0, 2.363104e+0, 2.362900e+0, 2.370179e+0, 2.391527e+0,
                                         2.421198e+0, 2.454605e+0, 2.487131e+0, 2.510938e+0, 2.527309e+0,
                                         2.537610e+0, 2.545242e+0, 2.547582e+0, 2.548362e+0, 2.548890e+0,
                                         2.548897e+0, 2.548813e+0, 2.548859e+0, 2.549846e+0 } ),
                {}, 1.902335e+8, 1.902335e+8 ),
      Reaction( id::ReactionID( "n,Np236_e2->4n,Np233[all]" ),
                TabulatedCrossSection( { 1.880420e+7, 1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 4.974121e-8, 5.265795e-6 } ),
                {}, -1.872420e+7, -1.872420e+7 ),
      Reaction( id::ReactionID( "n,Np236_e2->n,Np236" ),
                TabulatedCrossSection( { 1.000000e-5, 2.530000e-2, 2.150000e+1, 1.000000e+3, 2.000000e+3,
                                         3.000000e+3, 5.000000e+3, 7.000000e+3, 1.000000e+4, 2.000000e+4,
                                         3.000000e+4, 5.000000e+4, 7.000000e+4, 1.000000e+5, 1.200000e+5,
                                         1.400000e+5, 1.700000e+5, 2.000000e+5, 2.500000e+5, 3.000000e+5,
                                         4.000000e+5, 5.000000e+5, 6.000000e+5, 7.000000e+5, 8.000000e+5,
                                         9.000000e+5, 1.000000e+6, 1.100000e+6, 1.200000e+6, 1.300000e+6,
                                         1.400000e+6, 1.500000e+6, 1.600000e+6, 1.700000e+6, 1.800000e+6,
                                         1.900000e+6, 2.000000e+6, 2.300000e+6, 2.500000e+6, 2.700000e+6,
                                         3.000000e+6, 3.500000e+6, 4.000000e+6, 4.500000e+6, 5.000000e+6,
                                         5.500000e+6, 6.000000e+6, 6.500000e+6, 7.000000e+6, 7.500000e+6,
                                         8.000000e+6, 8.500000e+6, 9.000000e+6, 9.500000e+6, 1.000000e+7,
                                         2.000000e+7 },
                                       { 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 1.513516e-9,
                                         2.323049e-9, 4.399249e-9, 7.187316e-9, 1.296579e-8, 5.126479e-8,
                                         1.420591e-7, 5.722159e-7, 1.592060e-6, 5.034973e-6, 9.351665e-6,
                                         1.553400e-5, 3.046515e-5, 5.189078e-5, 1.075757e-4, 1.903713e-4,
                                         4.388548e-4, 7.812344e-4, 1.181727e-3, 1.596032e-3, 1.977755e-3,
                                         2.284032e-3, 2.482655e-3, 2.559387e-3, 2.521175e-3, 2.392016e-3,
                                         2.203261e-3, 1.984445e-3, 1.758145e-3, 1.539122e-3, 1.335568e-3,
                                         1.151266e-3, 9.873130e-4, 6.089414e-4, 4.354544e-4, 3.085975e-4,
                                         1.811297e-4, 7.139688e-5, 2.706403e-5, 1.010284e-5, 3.791730e-6,
                                         1.454822e-6, 5.742739e-7, 2.326189e-7, 9.611811e-8, 4.033081e-8,
                                         1.716987e-8, 7.421556e-9, 3.261343e-9, 1.458493e-9, 0.000000e+0,
                                         0.000000e+0 } ),
                {}, 60000, 60000 ),
      Reaction( id::ReactionID( "n,Np236_e2->n,Np236_e1" ),
                TabulatedCrossSection( { 1.000000e-5, 2.530000e-2, 2.150000e+1, 2.150000e+1, 3.000000e+1,
                                         5.000000e+1, 7.000000e+1, 1.000000e+2, 2.000000e+2, 3.000000e+2,
                                         5.000000e+2, 7.000000e+2, 1.000000e+3, 2.000000e+3, 3.000000e+3,
                                         5.000000e+3, 7.000000e+3, 1.000000e+4, 2.000000e+4, 3.000000e+4,
                                         5.000000e+4, 7.000000e+4, 1.000000e+5, 1.200000e+5, 1.400000e+5,
                                         1.700000e+5, 2.000000e+5, 2.500000e+5, 3.000000e+5, 4.000000e+5,
                                         5.000000e+5, 6.000000e+5, 7.000000e+5, 8.000000e+5, 9.000000e+5,
                                         1.000000e+6, 1.100000e+6, 1.200000e+6, 1.300000e+6, 1.400000e+6,
                                         1.500000e+6, 1.600000e+6, 1.700000e+6, 1.800000e+6, 1.900000e+6,
                                         2.000000e+6, 2.300000e+6, 2.500000e+6, 2.700000e+6, 3.000000e+6,
                                         3.500000e+6, 4.000000e+6, 4.500000e+6, 5.000000e+6, 5.500000e+6,
                                         6.000000e+6, 6.500000e+6, 7.000000e+6, 7.500000e+6, 8.000000e+6,
                                         8.500000e+6, 9.000000e+6, 9.500000e+6, 1.000000e+7, 1.050000e+7,
                                         1.100000e+7, 1.150000e+7, 1.200000e+7, 1.250000e+7, 1.300000e+7,
                                         1.350000e+7, 1.400000e+7, 1.450000e+7, 1.500000e+7, 1.550000e+7,
                                         1.600000e+7, 1.650000e+7, 1.700000e+7, 1.750000e+7, 1.800000e+7,
                                         1.850000e+7, 1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 0.000000e+0, 0.000000e+0, 2.587731e-6, 2.549935e-6,
                                         2.480724e-6, 2.426770e-6, 2.361572e-6, 2.209501e-6, 2.104713e-6,
                                         1.957481e-6, 1.853097e-6, 1.738628e-6, 1.518421e-6, 1.402326e-6,
                                         1.285347e-6, 1.234751e-6, 1.212291e-6, 7.358018e-7, 1.011310e-6,
                                         1.082214e-6, 1.263088e-6, 1.955018e-6, 3.251930e-6, 3.876030e-6,
                                         7.604331e-6, 1.063382e-5, 2.130681e-5, 3.820323e-5, 9.384491e-5,
                                         1.787576e-4, 2.877780e-4, 4.119965e-4, 5.400758e-4, 6.594636e-4,
                                         7.578340e-4, 8.255217e-4, 8.579973e-4, 8.568518e-4, 8.284926e-4,
                                         7.812329e-4, 7.229768e-4, 6.597685e-4, 5.956979e-4, 5.333246e-4,
                                         4.741779e-4, 3.177520e-4, 2.306955e-4, 1.703237e-4, 1.053692e-4,
                                         4.455283e-5, 1.784385e-5, 6.976617e-6, 2.728921e-6, 1.087352e-6,
                                         4.441723e-7, 1.854230e-7, 1.258806e-5, 1.187647e-5, 1.115898e-5,
                                         1.044346e-5, 9.741442e-6, 9.078692e-6, 8.476114e-6, 7.930065e-6,
                                         7.439322e-6, 6.992008e-6, 6.580296e-6, 6.195725e-6, 5.825808e-6,
                                         5.489852e-6, 5.169949e-6, 4.864317e-6, 4.581303e-6, 4.314730e-6,
                                         4.144282e-6, 3.999054e-6, 3.864111e-6, 3.640901e-6, 3.434123e-6,
                                         3.241585e-6, 3.054138e-6, 2.874436e-6, 2.703236e-6 } ),
                {}, 60000, 4000 ),
      Reaction( id::ReactionID( "n,Np236_e2->n,Np236_e3" ),
                TabulatedCrossSection( { 1.606836e+4, 2.000000e+4, 3.000000e+4, 5.000000e+4, 7.000000e+4,
                                         1.000000e+5, 1.200000e+5, 1.400000e+5, 1.700000e+5, 2.000000e+5,
                                         2.500000e+5, 3.000000e+5, 4.000000e+5, 5.000000e+5, 6.000000e+5,
                                         7.000000e+5, 8.000000e+5, 9.000000e+5, 1.000000e+6, 1.100000e+6,
                                         1.200000e+6, 1.300000e+6, 1.400000e+6, 1.500000e+6, 1.600000e+6,
                                         1.700000e+6, 1.800000e+6, 1.900000e+6, 2.000000e+6, 2.300000e+6,
                                         2.500000e+6, 2.700000e+6, 3.000000e+6, 3.500000e+6, 4.000000e+6,
                                         4.500000e+6, 5.000000e+6, 5.500000e+6, 6.000000e+6, 6.500000e+6,
                                         7.000000e+6, 7.500000e+6, 8.000000e+6, 8.500000e+6, 9.000000e+6,
                                         9.500000e+6, 1.000000e+7, 1.050000e+7, 1.100000e+7, 1.150000e+7,
                                         1.200000e+7, 1.250000e+7, 1.300000e+7, 1.350000e+7, 1.400000e+7,
                                         1.450000e+7, 1.500000e+7, 1.550000e+7, 1.600000e+7, 1.650000e+7,
                                         1.700000e+7, 1.750000e+7, 1.800000e+7, 1.850000e+7, 1.900000e+7,
                                         1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 1.448022e-2, 2.481461e-2, 4.100726e-2, 5.758993e-2,
                                         8.208030e-2, 9.681656e-2, 1.084745e-1, 1.251586e-1, 1.356666e-1,
                                         1.477920e-1, 1.536260e-1, 1.548794e-1, 1.506680e-1, 1.459513e-1,
                                         1.426162e-1, 1.412092e-1, 1.417090e-1, 1.438577e-1, 1.473173e-1,
                                         1.517543e-1, 1.568800e-1, 1.624569e-1, 1.682864e-1, 1.741914e-1,
                                         1.800046e-1, 1.855664e-1, 1.907348e-1, 1.953944e-1, 2.056757e-1,
                                         2.093660e-1, 2.108549e-1, 2.098423e-1, 2.024049e-1, 1.910515e-1,
                                         1.784336e-1, 1.664447e-1, 1.562359e-1, 1.481502e-1, 1.418670e-1,
                                         1.368251e-1, 1.325099e-1, 1.286157e-1, 1.249593e-1, 1.214611e-1,
                                         1.181131e-1, 1.149333e-1, 1.119263e-1, 1.090703e-1, 1.063260e-1,
                                         1.036530e-1, 1.010219e-1, 9.841923e-2, 9.584573e-2, 9.331173e-2,
                                         9.083197e-2, 8.842148e-2, 8.609317e-2, 8.385729e-2, 8.172171e-2,
                                         7.969290e-2, 7.777647e-2, 7.597760e-2, 7.430037e-2, 7.274722e-2,
                                         7.131811e-2, 7.001007e-2 } ),
                {}, 60000, -16000 ),
      Reaction( id::ReactionID( "n,Np236_e2->n,Np236_e4" ),
                TabulatedCrossSection( { 4.017089e+4, 5.000000e+4, 7.000000e+4, 1.000000e+5, 1.200000e+5,
                                         1.400000e+5, 1.700000e+5, 2.000000e+5, 2.500000e+5, 3.000000e+5,
                                         4.000000e+5, 5.000000e+5, 6.000000e+5, 7.000000e+5, 8.000000e+5,
                                         9.000000e+5, 1.000000e+6, 1.100000e+6, 1.200000e+6, 1.300000e+6,
                                         1.400000e+6, 1.500000e+6, 1.600000e+6, 1.700000e+6, 1.800000e+6,
                                         1.900000e+6, 2.000000e+6, 2.300000e+6, 2.500000e+6, 2.700000e+6,
                                         3.000000e+6, 3.500000e+6, 4.000000e+6, 4.500000e+6, 5.000000e+6,
                                         5.500000e+6, 6.000000e+6, 6.500000e+6, 7.000000e+6, 7.500000e+6,
                                         8.000000e+6, 8.500000e+6, 9.000000e+6, 9.500000e+6, 1.000000e+7,
                                         1.050000e+7, 1.100000e+7, 1.150000e+7, 1.200000e+7, 1.250000e+7,
                                         1.300000e+7, 1.350000e+7, 1.400000e+7, 1.450000e+7, 1.500000e+7,
                                         1.550000e+7, 1.600000e+7, 1.650000e+7, 1.700000e+7, 1.750000e+7,
                                         1.800000e+7, 1.850000e+7, 1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 4.175315e-3, 2.171542e-2, 5.546136e-2, 7.836751e-2,
                                         9.894146e-2, 1.276736e-1, 1.496271e-1, 1.776263e-1, 1.963280e-1,
                                         2.172149e-1, 2.275769e-1, 2.342172e-1, 2.398609e-1, 2.455160e-1,
                                         2.514989e-1, 2.578451e-1, 2.644518e-1, 2.711283e-1, 2.776242e-1,
                                         2.836610e-1, 2.889728e-1, 2.933425e-1, 2.966238e-1, 2.987468e-1,
                                         2.997136e-1, 2.995831e-1, 2.936970e-1, 2.864956e-1, 2.778351e-1,
                                         2.637252e-1, 2.408637e-1, 2.210160e-1, 2.043431e-1, 1.905325e-1,
                                         1.793813e-1, 1.705917e-1, 1.636199e-1, 1.577648e-1, 1.523184e-1,
                                         1.468409e-1, 1.411910e-1, 1.354669e-1, 1.298601e-1, 1.245341e-1,
                                         1.195714e-1, 1.149763e-1, 1.107048e-1, 1.066973e-1, 1.029025e-1,
                                         9.928838e-2, 9.584361e-2, 9.257072e-2, 8.947835e-2, 8.657409e-2,
                                         8.386031e-2, 8.133297e-2, 7.898217e-2, 7.679435e-2, 7.475438e-2,
                                         7.284781e-2, 7.106197e-2, 6.938670e-2, 6.781433e-2, 6.633917e-2 } ),
                {}, 60000, -40000 ),
      Reaction( id::ReactionID( "n,Np236_e2->n,Np236_e5" ),
                TabulatedCrossSection( { 6.025634e+4, 7.000000e+4, 1.000000e+5, 1.200000e+5, 1.400000e+5,
                                         1.700000e+5, 2.000000e+5, 2.500000e+5, 3.000000e+5, 4.000000e+5,
                                         5.000000e+5, 6.000000e+5, 7.000000e+5, 8.000000e+5, 9.000000e+5,
                                         1.000000e+6, 1.100000e+6, 1.200000e+6, 1.300000e+6, 1.400000e+6,
                                         1.500000e+6, 1.600000e+6, 1.700000e+6, 1.800000e+6, 1.900000e+6,
                                         2.000000e+6, 2.300000e+6, 2.500000e+6, 2.700000e+6, 3.000000e+6,
                                         3.500000e+6, 4.000000e+6, 4.500000e+6, 5.000000e+6, 5.500000e+6,
                                         6.000000e+6, 6.500000e+6, 7.000000e+6, 7.500000e+6, 8.000000e+6,
                                         8.500000e+6, 9.000000e+6, 9.500000e+6, 1.000000e+7, 1.050000e+7,
                                         1.100000e+7, 1.150000e+7, 1.200000e+7, 1.250000e+7, 1.300000e+7,
                                         1.350000e+7, 1.400000e+7, 1.450000e+7, 1.500000e+7, 1.550000e+7,
                                         1.600000e+7, 1.650000e+7, 1.700000e+7, 1.750000e+7, 1.800000e+7,
                                         1.850000e+7, 1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 1.151130e-6, 1.342533e-6, 2.097958e-6, 2.042249e-6,
                                         3.656784e-6, 3.462665e-6, 4.493576e-6, 5.414932e-6, 7.145418e-6,
                                         9.473791e-6, 1.358989e-5, 2.092356e-5, 3.270152e-5, 4.974025e-5,
                                         7.192362e-5, 9.792710e-5, 1.252737e-4, 1.509070e-4, 1.721519e-4,
                                         1.872354e-4, 1.956833e-4, 1.978818e-4, 1.947995e-4, 1.876212e-4,
                                         1.775265e-4, 1.343763e-4, 9.951640e-5, 7.764732e-5, 5.152904e-5,
                                         2.393819e-5, 1.031608e-5, 4.282140e-6, 1.763235e-6, 7.349803e-7,
                                         3.123652e-7, 1.349438e-7, 1.253935e-5, 1.185367e-5, 1.115285e-5,
                                         1.044649e-5, 9.748161e-6, 9.085662e-6, 8.481620e-6, 7.933666e-6,
                                         7.441369e-6, 6.993169e-6, 6.581203e-6, 6.196794e-6, 5.827203e-6,
                                         5.491545e-6, 5.171798e-6, 4.866144e-6, 4.582949e-6, 4.316083e-6,
                                         4.145308e-6, 3.999745e-6, 3.864501e-6, 3.641052e-6, 3.434124e-6,
                                         3.241525e-6, 3.054093e-6, 2.874465e-6, 2.703376e-6 } ),
                {}, 60000, -60000 ),
      Reaction( id::ReactionID( "n,Np236_e2->n,Np236_e6" ),
                TabulatedCrossSection( { 7.230761e+4, 1.000000e+5, 1.200000e+5, 1.400000e+5, 1.700000e+5,
                                         2.000000e+5, 2.500000e+5, 3.000000e+5, 4.000000e+5, 5.000000e+5,
                                         6.000000e+5, 7.000000e+5, 8.000000e+5, 9.000000e+5, 1.000000e+6,
                                         1.100000e+6, 1.200000e+6, 1.300000e+6, 1.400000e+6, 1.500000e+6,
                                         1.600000e+6, 1.700000e+6, 1.800000e+6, 1.900000e+6, 2.000000e+6,
                                         2.300000e+6, 2.500000e+6, 2.700000e+6, 3.000000e+6, 3.500000e+6,
                                         4.000000e+6, 4.500000e+6, 5.000000e+6, 5.500000e+6, 6.000000e+6,
                                         6.500000e+6, 7.000000e+6, 7.500000e+6, 8.000000e+6, 8.500000e+6,
                                         9.000000e+6, 9.500000e+6, 1.000000e+7, 1.050000e+7, 1.100000e+7,
                                         1.150000e+7, 1.200000e+7, 1.250000e+7, 1.300000e+7, 1.350000e+7,
                                         1.400000e+7, 1.450000e+7, 1.500000e+7, 1.550000e+7, 1.600000e+7,
                                         1.650000e+7, 1.700000e+7, 1.750000e+7, 1.800000e+7, 1.850000e+7,
                                         1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 3.511408e-3, 7.054285e-3, 1.040024e-2, 1.511499e-2,
                                         1.832365e-2, 2.218008e-2, 2.448301e-2, 2.722814e-2, 3.020181e-2,
                                         3.440367e-2, 3.975878e-2, 4.584081e-2, 5.215780e-2, 5.830582e-2,
                                         6.399569e-2, 6.905668e-2, 7.341369e-2, 7.705725e-2, 8.001811e-2,
                                         8.235269e-2, 8.411750e-2, 8.538292e-2, 8.621725e-2, 8.668819e-2,
                                         8.653697e-2, 8.563730e-2, 8.442833e-2, 8.228075e-2, 7.803756e-2,
                                         7.305817e-2, 6.776180e-2, 6.270272e-2, 5.821569e-2, 5.431107e-2,
                                         5.079072e-2, 4.745985e-2, 4.419795e-2, 4.104298e-2, 3.808290e-2,
                                         3.540102e-2, 3.303388e-2, 3.096563e-2, 2.914645e-2, 2.751672e-2,
                                         2.602474e-2, 2.463525e-2, 2.332972e-2, 2.210195e-2, 2.095212e-2,
                                         1.988149e-2, 1.888921e-2, 1.797106e-2, 1.711988e-2, 1.632698e-2,
                                         1.558351e-2, 1.488200e-2, 1.421712e-2, 1.358625e-2, 1.298890e-2,
                                         1.242619e-2, 1.189997e-2, 1.141205e-2 } ),
                {}, 60000, -72000 ),
      Reaction( id::ReactionID( "n,Np236_e2->n,Np236[continuum]" ),
                TabulatedCrossSection( { 7.230761e+4, 1.000000e+5, 1.200000e+5, 1.400000e+5, 1.700000e+5,
                                         2.000000e+5, 2.500000e+5, 3.000000e+5, 4.000000e+5, 5.000000e+5,
                                         6.000000e+5, 7.000000e+5, 8.000000e+5, 9.000000e+5, 1.000000e+6,
                                         1.100000e+6, 1.200000e+6, 1.300000e+6, 1.400000e+6, 1.500000e+6,
                                         1.600000e+6, 1.700000e+6, 1.800000e+6, 1.900000e+6, 2.000000e+6,
                                         2.300000e+6, 2.500000e+6, 2.700000e+6, 3.000000e+6, 3.500000e+6,
                                         4.000000e+6, 4.500000e+6, 5.000000e+6, 5.500000e+6, 6.000000e+6,
                                         6.500000e+6, 7.000000e+6, 7.500000e+6, 8.000000e+6, 8.500000e+6,
                                         9.000000e+6, 9.500000e+6, 1.000000e+7, 1.050000e+7, 1.100000e+7,
                                         1.150000e+7, 1.200000e+7, 1.250000e+7, 1.300000e+7, 1.350000e+7,
                                         1.400000e+7, 1.450000e+7, 1.500000e+7, 1.550000e+7, 1.600000e+7,
                                         1.650000e+7, 1.700000e+7, 1.750000e+7, 1.800000e+7, 1.850000e+7,
                                         1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 6.138899e-3, 2.393584e-3, 3.422617e-2, 3.346554e-2,
                                         9.100347e-2, 1.645954e-1, 2.457495e-1, 4.055819e-1, 5.417715e-1,
                                         6.491108e-1, 7.321067e-1, 7.975196e-1, 8.515123e-1, 8.987487e-1,
                                         9.423362e-1, 9.840419e-1, 1.024593e+0, 1.064065e+0, 1.102004e+0,
                                         1.137560e+0, 1.169824e+0, 1.198448e+0, 1.223590e+0, 1.245720e+0,
                                         1.300509e+0, 1.329947e+0, 1.357606e+0, 1.398254e+0, 1.468476e+0,
                                         1.534788e+0, 1.581356e+0, 1.607950e+0, 1.623265e+0, 1.515717e+0,
                                         1.191398e+0, 9.137639e-1, 7.065431e-1, 5.750083e-1, 4.957800e-1,
                                         4.450166e-1, 4.097815e-1, 3.840809e-1, 3.644166e-1, 3.487260e-1,
                                         3.353430e-1, 3.231525e-1, 3.113467e-1, 2.994419e-1, 2.882890e-1,
                                         2.774518e-1, 2.665191e-1, 2.567621e-1, 2.475289e-1, 2.435717e-1,
                                         2.353469e-1, 2.277284e-1, 2.201263e-1, 2.130159e-1, 2.063634e-1,
                                         1.997846e-1, 1.933892e-1, 1.873116e-1 } ),
                {}, 60000, -72000 ),
      Reaction( id::ReactionID( "n,Np236_e2->g,Np237[all]" ),
                TabulatedCrossSection( { 1.000000e-5, 2.530000e-2, 2.150000e+1, 2.150000e+1, 23.3673337,
                                         24.8735163, 27.3167621, 3.000000e+1, 31.9780774, 33.8155969,
                                         37.2889621, 40.1261713, 42.3948687, 46.0406716, 5.000000e+1,
                                         54.3878654, 57.9296655, 63.6794833, 7.000000e+1, 76.5285581,
                                         81.8215398, 90.4552596, 1.000000e+2, 109.050774, 117.639701,
                                         125.708147, 133.220711, 147.464103, 159.137392, 168.494868,
                                         183.572802, 2.000000e+2, 221.336385, 238.819577, 252.832418,
                                         275.408289, 3.000000e+2, 319.780774, 338.155969, 372.889621,
                                         401.261713, 423.948687, 460.406716, 5.000000e+2, 543.878654,
                                         579.296655, 636.794833, 7.000000e+2, 765.285581, 818.215398,
                                         904.552596, 1.000000e+3, 1090.50774, 1176.39701, 1257.08147,
                                         1332.20711, 1474.64103, 1591.37392, 1684.94868, 1835.72802,
                                         2.000000e+3, 2213.36385, 2388.19576, 2528.32418, 2754.08289,
                                         3.000000e+3, 3197.80774, 3575.87035, 3888.47065, 4140.72721,
                                         4550.12485, 5.000000e+3, 5438.78654, 5792.96655, 6367.94833,
                                         7.000000e+3, 7652.85581, 8182.15398, 9045.52596, 1.000000e+4,
                                         10905.0774, 11763.9701, 13432.9975, 14838.4044, 15988.1385,
                                         17881.9119, 2.000000e+4, 22133.6385, 25768.3751, 3.000000e+4,
                                         34086.5811, 41283.5204, 5.000000e+4, 59160.7979, 7.000000e+4,
                                         83666.0027, 1.000000e+5, 109544.512, 1.200000e+5, 129614.814,
                                         1.400000e+5, 1.700000e+5, 184390.890, 2.000000e+5, 211474.253,
                                         229931.650, 2.500000e+5, 273861.279, 3.000000e+5, 322370.980,
                                         340237.324, 368910.463, 4.000000e+5, 422948.506, 441019.836,
                                         469584.836, 5.000000e+5, 523317.570, 541516.633, 570008.755,
                                         6.000000e+5, 623573.927, 660682.791, 7.000000e+5, 723762.416,
                                         760927.023, 8.000000e+5, 823906.858, 861113.334, 9.000000e+5,
                                         948683.299, 1.000000e+6, 1048808.85, 1.100000e+6, 1148912.53,
                                         1.200000e+6, 1248999.60, 1.300000e+6, 1349073.76, 1.400000e+6,
                                         1449137.68, 1.500000e+6, 1549193.34, 1.600000e+6, 1649242.25,
                                         1.700000e+6, 1749285.57, 1.800000e+6, 1849324.21, 1.900000e+6,
                                         1949358.87, 2.000000e+6, 2071116.16, 2126107.91, 2168307.83,
                                         2233183.38, 2.300000e+6, 2348447.63, 2385451.90, 2442054.42,
                                         2.500000e+6, 2548566.38, 2585609.32, 2642185.68, 2.700000e+6,
                                         2772063.27, 2827370.15, 2869573.25, 2.934062e+6, 3.000000e+6,
                                         3058367.04, 3110368.97, 3156595.47, 3197606.88, 3270663.12,
                                         3326548.60, 3369088.48, 3433920.46, 3.500000e+6, 3558910.27,
                                         3611269.57, 3657715.48, 3698845.40, 3771938.77, 3827705.13,
                                         3870070.30, 3934498.85, 4.000000e+6, 4059327.19, 4111959.85,
                                         4158572.93, 4241420.89, 4304638.22, 4352668.80, 4425721.37,
                                         4.500000e+6, 4559657.28, 4612505.82, 4706468.94, 4778195.33,
                                         4832706.57, 4915641.66, 5.000000e+6, 5120568.45, 5212898.94,
                                         5354525.58, 5.500000e+6, 5744562.65, 6.000000e+6, 6.500000e+6,
                                         7.000000e+6, 7.500000e+6, 8.000000e+6, 8.500000e+6, 9.000000e+6,
                                         9.500000e+6, 1.000000e+7, 10246950.8, 1.050000e+7, 10747092.7,
                                         1.100000e+7, 1.150000e+7, 1.200000e+7, 1.250000e+7, 1.300000e+7,
                                         1.350000e+7, 1.400000e+7, 1.450000e+7, 1.500000e+7, 1.550000e+7,
                                         1.600000e+7, 1.650000e+7, 1.700000e+7, 1.750000e+7, 1.800000e+7,
                                         1.850000e+7, 1.900000e+7, 1.950000e+7, 2.000000e+7 },
                                       { 0.000000e+0, 0.000000e+0, 0.000000e+0, 5.694135e+0, 5.46128784,
                                         5.29292265, 5.05005687, 4.818335e+0, 4.66650168, 4.53757751,
                                         4.32047166, 4.16448679, 4.05120514, 3.88703414, 3.729516e+0,
                                         3.57545087, 3.46409322, 3.30352580, 3.150401e+0, 3.01262399,
                                         2.91326003, 2.77032506, 2.634403e+0, 2.52245974, 2.42841844,
                                         2.34901283, 2.28166575, 2.16842116, 2.08719173, 2.02827285,
                                         1.94299833, 1.861309e+0, 1.76928918, 1.70327229, 1.65538122,
                                         1.58605755, 1.519637e+0, 1.47204087, 1.43161875, 1.36353258,
                                         1.31460150, 1.279059e+0, 1.22753889, 1.178094e+0, 1.13002309,
                                         1.09526157, 1.04511396, 9.972624e-1, 0.95450222, 0.92363964,
                                         0.87920672, 8.369113e-1, 0.80273769, 0.77398243, 0.74966781,
                                         0.72901994, 0.69424516, 0.66925705, 0.65110799, 0.62480303,
                                         5.995608e-1, 0.57206987, 0.55228209, 0.53789174, 0.51700619,
                                         4.969316e-1, 0.48323701, 0.46017334, 0.44360088, 4.315644e-1,
                                         0.41411926, 3.973793e-1, 0.38411024, 0.37445002, 0.36041332,
                                         3.469028e-1, 0.33576119, 0.32764045, 0.31582612, 3.044378e-1,
                                         0.29619667, 0.28916888, 0.27726911, 0.26866677, 0.26239061,
                                         0.25325020, 2.444282e-1, 0.23949330, 0.23227713, 2.252784e-1,
                                         0.22055813, 0.21366252, 2.069825e-1, 0.20137766, 1.959246e-1,
                                         0.18905149, 1.824195e-1, 0.17909185, 1.758249e-1, 0.17015276,
                                         1.646636e-1, 1.596437e-1, 0.15382978, 1.482276e-1, 0.14457895,
                                         0.13927369, 1.341631e-1, 0.12768379, 1.215174e-1, 0.11578512,
                                         0.11166407, 0.10575588, 1.001603e-1, 9.565873e-2, 9.241582e-2,
                                         8.775643e-2, 8.333195e-2, 7.981061e-2, 7.726759e-2, 7.360420e-2,
                                         7.011449e-2, 6.734742e-2, 6.340022e-2, 5.968436e-2, 5.749075e-2,
                                         5.435058e-2, 5.138192e-2, 4.962374e-2, 4.709862e-2, 4.470199e-2,
                                         4.189354e-2, 3.926154e-2, 3.694698e-2, 3.476887e-2, 3.283125e-2,
                                         3.100162e-2, 2.935258e-2, 2.779125e-2, 2.636398e-2, 2.501000e-2,
                                         2.375572e-2, 2.256434e-2, 2.144898e-2, 2.038875e-2, 1.938905e-2,
                                         1.843837e-2, 1.753696e-2, 1.667961e-2, 1.586385e-2, 1.508799e-2,
                                         1.434859e-2, 1.364542e-2, 1.267963e-2, 1.200042e-2, 1.151499e-2,
                                         1.082343e-2, 1.017339e-2, 9.669261e-3, 9.307628e-3, 8.790378e-3,
                                         8.301874e-3, 7.888345e-3, 7.591772e-3, 7.167689e-3, 6.767295e-3,
                                         6.265108e-3, 5.913079e-3, 5.662100e-3, 5.305463e-3, 4.971289e-3,
                                         4.660145e-3, 4.403912e-3, 4.191291e-3, 4.013686e-3, 3.720795e-3,
                                         3.515240e-3, 3.368561e-3, 3.159938e-3, 2.964235e-3, 2.782364e-3,
                                         2.632405e-3, 2.507835e-3, 2.403682e-3, 2.231715e-3, 2.110862e-3,
                                         2.024537e-3, 1.901624e-3, 1.786173e-3, 1.685156e-3, 1.601465e-3,
                                         1.531651e-3, 1.416720e-3, 1.336218e-3, 1.278858e-3, 1.197401e-3,
                                         1.121133e-3, 1.069416e-3, 1.026125e-3, 9.545397e-4, 9.041474e-4,
                                         8.681068e-4, 8.167216e-4, 7.683780e-4, 7.231527e-4, 6.909894e-4,
                                         6.454065e-4, 6.028307e-4, 5.737115e-4, 5.459988e-4, 5.398734e-4,
                                         5.433449e-4, 5.370965e-4, 5.216398e-4, 5.094324e-4, 5.088756e-4,
                                         5.073582e-4, 4.831257e-4, 4.643169e-4, 4.462404e-4, 4.291424e-4,
                                         4.126995e-4, 3.856595e-4, 3.636676e-4, 3.458836e-4, 3.314392e-4,
                                         3.194605e-4, 3.092590e-4, 3.002494e-4, 2.919285e-4, 2.838942e-4,
                                         2.759344e-4, 2.680302e-4, 2.602781e-4, 2.527993e-4, 2.456680e-4,
                                         2.388920e-4, 2.324316e-4, 2.262330e-4, 2.202558e-4 } ),
                {}, 6.637350e+6, 6.637350e+6 )
    };

    ProjectileTarget transport( id::ParticleID::neutron(), id::ParticleID( 93236, 2 ),
                                InteractionType::Nuclear,
                                std::move( reactions ) );
    transport.documentation().awr( 234.0190 );
    transport.documentation().library( 0 );
    transport.documentation().version( std::make_pair( 8, 1 ) );
    transport.documentation().description( std::move( description ) );

    THEN( "it can be converted to an ENDF material" ) {

      std::string filename = "apiehjcvuhrtoiahmxuherotalcnhoeureitcnisunhflk.endf";
      format::endf::createProjectileTargetEndfFile( transport, 9344, filename );
      format::endf::createProjectileTargetEndfFile( transport, 9344, "test.endf" );

      CHECK( chunkForMetastableState() == readContentFromFile( filename ) );

      std::remove( filename.c_str() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunkForGroundState() {

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

std::string chunkForMetastableState() {

  return
    "n+Np236_e2 data                                                      0 0  0     \n"
    " 9.323600+4 2.340190+2          1          1          0          09344 1451     \n"
    " 6.000000+4 1.000000+0          2          1          0          69344 1451     \n"
    " 1.000000+0 2.000000+7          1          0         10          89344 1451     \n"
    " 0.000000+0 0.000000+0          0          0        104         169344 1451     \n"
    " 93-Np-236M LANL      EVAL-JAN17 T. Kawano, P.Talou               9344 1451     \n"
    " NDS 148, 1 (2018)    DIST-AUG24 REV1-NOV19            20240830   9344 1451     \n"
    "---- ENDF/B-VIII.1    MATERIAL 9344         REVISION 1            9344 1451     \n"
    "----- INCIDENT-NEUTRON DATA                                       9344 1451     \n"
    "------ ENDF-6                                                     9344 1451     \n"
    "                                                                  9344 1451     \n"
    "******************************************************************9344 1451     \n"
    " Np-236m Evaluation                                               9344 1451     \n"
    "                                              T. Kawano, P. Talou 9344 1451     \n"
    "                                                        Jan. 2012 9344 1451     \n"
    "******************************************************************9344 1451     \n"
    " Evaluation based on:                                             9344 1451     \n"
    "    ENDF/B-VII.1 (JENDL-4.0) Np236 ground state data              9344 1451     \n"
    "    CoH3 calculation to the ground and 60keV levels               9344 1451     \n"
    "                                                                  9344 1451     \n"
    " The coupled-channels calculation in JENDL-4.0 assumes            9344 1451     \n"
    " the following level scheme, where all the excited levels         9344 1451     \n"
    " except for 60keV meta state are postulated.                      9344 1451     \n"
    "                                                                  9344 1451     \n"
    "    -------------------                                           9344 1451     \n"
    "    No.  Ex(MeV)   J PI                                           9344 1451     \n"
    "    -------------------                                           9344 1451     \n"
    "     0  0.00000   6  -  *                                         9344 1451     \n"
    "     1  0.05600   7  -  *                                         9344 1451     \n"
    "     2  0.06000   1  +                                            9344 1451     \n"
    "     3  0.07600   2  +                                            9344 1451     \n"
    "     4  0.10000   3  +                                            9344 1451     \n"
    "     5  0.12000   8  -  *                                         9344 1451     \n"
    "     6  0.13200   4  +                                            9344 1451     \n"
    "                                                                  9344 1451     \n"
    " First we followed the same g.s. calculation as JENDL to try to   9344 1451     \n"
    " reproduce all the g.s. cross sections. Then the same parameters  9344 1451     \n"
    " are employed to calculate cross sections on the excited state,   9344 1451     \n"
    " with the coupling of 1+, 2+, 3+, and 4+ states.                  9344 1451     \n"
    "                                                                  9344 1451     \n"
    " MF1 MT452, 455, 456                                              9344 1451     \n"
    "    same as ground state                                          9344 1451     \n"
    "                                                                  9344 1451     \n"
    " MF2                                                              9344 1451     \n"
    "    the same resonance parameters for the ground state,           9344 1451     \n"
    "    but spins were changed.                                       9344 1451     \n"
    "                                                                  9344 1451     \n"
    " MF3                                                              9344 1451     \n"
    "    The following cross sections were evaluated by applying       9344 1451     \n"
    "    a scaling factor of F to the ground state cross sections,     9344 1451     \n"
    "    where F = CoH(meta) / CoH(ground).                            9344 1451     \n"
    "                                                                  9344 1451     \n"
    "    MT  16 (n,2n)                                                 9344 1451     \n"
    "    MT  17 (n,3n)                                                 9344 1451     \n"
    "    MT  18 fission                                                9344 1451     \n"
    "    MT  37 (n,4n)                                                 9344 1451     \n"
    "                                                                  9344 1451     \n"
    "    These sections below were replaced by the CoH excited state   9344 1451     \n"
    "    calculations.                                                 9344 1451     \n"
    "                                                                  9344 1451     \n"
    "    MT   1 total                                                  9344 1451     \n"
    "    MT   2 elastic = total - sum of partials                      9344 1451     \n"
    "    MT  51 - 56 discrete level inelastic scattering               9344 1451     \n"
    "    MT  91 continuum inelastic scattering                         9344 1451     \n"
    "    MT 102 radiative capture                                      9344 1451     \n"
    "                                                                  9344 1451     \n"
    " MF4                                                              9344 1451     \n"
    "    MT   2, 51 - 56, new CoH calculations                         9344 1451     \n"
    "                                                                  9344 1451     \n"
    " MF5                                                              9344 1451     \n"
    "    same as g.s.                                                  9344 1451     \n"
    "                                                                  9344 1451     \n"
    " MF6                                                              9344 1451     \n"
    "    MT  51 - 56                                                   9344 1451     \n"
    "    the angular distributions for the disrete levels removed,     9344 1451     \n"
    "    and given in new evaluations in MF4                           9344 1451     \n"
    "                                                                  9344 1451     \n"
    "    MT  16, 17, 37, 91, 102                                       9344 1451     \n"
    "    same as g.s.                                                  9344 1451     \n"
    "                                                                  9344 1451     \n"
    " MF12 MT18                                                        9344 1451     \n"
    "    same as g.s.                                                  9344 1451     \n"
    "                                                                  9344 1451     \n"
    " MF14 MT18                                                        9344 1451     \n"
    "    same as g.s.                                                  9344 1451     \n"
    "                                                                  9344 1451     \n"
    " MF15 MT18                                                        9344 1451     \n"
    "    same as g.s.                                                  9344 1451     \n"
    "                                                                  9344 1451     \n"
    "******************************************************************9344 1451     \n"
    "                                                                  9344 1451     \n"
    " ***************** Program LINEAR (VERSION 2017-1) ***************9344 1451     \n"
    " For All Data Greater than 1.0000E-10 barns in Absolute Value     9344 1451     \n"
    " Data Linearized to Within an Accuracy of .100000000 per-cent     9344 1451     \n"
    " ***************** Program FIXUP (Version 2017-1) ****************9344 1451     \n"
    " Corrected ZA/AWR in All Sections-----------------------------Yes 9344 1451     \n"
    " Corrected Thresholds-----------------------------------------No  9344 1451     \n"
    " Extended Cross Sections to 20 MeV----------------------------No  9344 1451     \n"
    " Allow Cross Section Deletion---------------------------------No  9344 1451     \n"
    " Allow Cross Section Reconstruction---------------------------Yes 9344 1451     \n"
    " Make All Cross Sections Non-Negative-------------------------Yes 9344 1451     \n"
    " Delete Energies Not in Ascending Order-----------------------Yes 9344 1451     \n"
    " Deleted Duplicate Points-------------------------------------Yes 9344 1451     \n"
    " Check for Ascending MAT/MF/MT Order--------------------------Yes 9344 1451     \n"
    " Check for Legal MF/MT Numbers--------------------------------Yes 9344 1451     \n"
    " Allow Creation of Missing Sections---------------------------No  9344 1451     \n"
    " Allow Insertion of Energy Points-----------------------------No  9344 1451     \n"
    " Uniform Energy Grid for ALL MT-------------------------------No  9344 1451     \n"
    " Delete Section if Cross Section =0 at All Energies-----------Yes 9344 1451     \n"
    "                                1        451        124          09344 1451     \n"
    "                                3          1         88          09344 1451     \n"
    "                                3          2         34          09344 1451     \n"
    "                                3          4         33          09344 1451     \n"
    "                                3         16         13          09344 1451     \n"
    "                                3         17          8          09344 1451     \n"
    "                                3         18         56          09344 1451     \n"
    "                                3         37          4          09344 1451     \n"
    "                                3         51         22          09344 1451     \n"
    "                                3         52         31          09344 1451     \n"
    "                                3         53         26          09344 1451     \n"
    "                                3         54         25          09344 1451     \n"
    "                                3         55         25          09344 1451     \n"
    "                                3         56         24          09344 1451     \n"
    "                                3         91         24          09344 1451     \n"
    "                                3        102         83          09344 1451     \n"
    "                                                                  9344 1  0     \n"
    "                                                                  9344 0  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3  1     \n"
    " 0.000000+0 0.000000+0          0          0          1        2559344 3  1     \n"
    "        255          2                                            9344 3  1     \n"
    " 1.000000-5 0.000000+0 2.530000-2 0.000000+0 2.150000+1 0.000000+09344 3  1     \n"
    " 2.150000+1 97.9899276 23.3673337 94.5374298 24.8735163 92.01268159344 3  1     \n"
    " 27.3167621 88.3215918 3.000000+1 84.7359275 31.9780774 82.51584799344 3  1     \n"
    " 33.8155969 80.6155335 37.2889621 77.3789548 40.1261713 75.02068249344 3  1     \n"
    " 42.3948687 73.2879982 46.0406716 70.7425315 5.000000+1 68.25588859344 3  1     \n"
    " 54.3878654 65.9713902 57.9296655 64.3011478 63.6794833 61.85981789344 3  1     \n"
    " 7.000000+1 59.4887034 76.5285581 57.4477179 81.8215398 55.95785979344 3  1     \n"
    " 90.4552596 53.7834832 1.000000+2 51.6749654 109.050774 50.05413699344 3  1     \n"
    " 117.639701 48.6787814 125.708147 47.5061174 133.220711 46.50223059344 3  1     \n"
    " 147.464103 44.7918211 159.137392 43.5447548 168.494868 42.62786979344 3  1     \n"
    " 183.572802 41.2795901 2.000000+2 39.9605512 221.336385 38.59940429344 3  1     \n"
    " 238.819577 37.6093123 252.832418 36.8827779 275.408289 35.81683709344 3  1     \n"
    " 3.000000+2 34.7771291 319.780774 34.0795421 338.155969 33.48207029344 3  1     \n"
    " 372.889621 32.4636516 401.261713 31.7209086 423.948687 3.117480+19344 3  1     \n"
    " 460.406716 30.3718734 5.000000+2 29.5867160 543.878654 28.87016149344 3  1     \n"
    " 579.296655 28.3456008 636.794833 27.5777765 7.000000+2 26.83070439344 3  1     \n"
    " 765.285581 26.1926795 818.215398 25.7260017 904.552596 25.04338279344 3  1     \n"
    " 1.000000+3 24.3795830 1090.50774 23.8802060 1176.39701 23.45496489344 3  1     \n"
    " 1257.08147 23.0912375 1332.20711 22.7789666 1474.64103 22.24490359344 3  1     \n"
    " 1591.37392 21.8538064 1684.94868 21.5652806 1835.72802 21.13941329344 3  1     \n"
    " 2.000000+3 20.7208463 2213.36385 20.3038349 2388.19576 19.99824269344 3  1     \n"
    " 2528.32418 19.7727033 2754.08289 19.4396960 3.000000+3 1.911232+19344 3  1     \n"
    " 3197.80774 18.9035928 3575.87035 18.5453305 3888.47065 18.28180139344 3  1     \n"
    " 4140.72721 18.0866662 4550.12485 17.7973904 5.000000+3 17.51143769344 3  1     \n"
    " 5438.78654 17.2973478 5792.96655 17.1381502 6367.94833 16.90106629344 3  1     \n"
    " 7.000000+3 16.6653980 7652.85581 16.4772821 8182.15398 16.33643569344 3  1     \n"
    " 9045.52596 16.1250399 1.000000+4 15.9128120 10905.0774 15.78678889344 3  1     \n"
    " 11763.9701 15.6799903 12690.5097 15.5657557 13432.9975 15.48400259344 3  1     \n"
    " 14218.9262 15.3982591 14838.4044 15.3359648 15484.8713 15.27138469344 3  1     \n"
    " 15988.1385 15.2251681 1.606836+4 15.2178518 17598.2223 15.03306699344 3  1     \n"
    " 17881.9119 15.0011618 2.000000+4 14.7643522 22133.6385 14.63714579344 3  1     \n"
    " 25768.3751 14.4346428 3.000000+4 14.2156772 34086.5811 14.08108219344 3  1     \n"
    " 38729.8335 13.9290671 4.017089+4 13.8848884 41283.5204 13.84822129344 3  1     \n"
    " 5.000000+4 13.5626367 59160.7979 13.3502313 6.025634+4 13.32494889344 3  1     \n"
    " 7.000000+4 1.309361+1 7.230761+4 13.0523672 83666.0027 12.84395509344 3  1     \n"
    " 1.000000+5 12.5458298 109544.512 12.3906369 1.200000+5 12.22707959344 3  1     \n"
    " 129614.814 12.0849935 1.400000+5 11.9321604 1.700000+5 11.52363029344 3  1     \n"
    " 184390.890 11.3429892 2.000000+5 11.1477604 211474.253 11.01499469344 3  1     \n"
    " 223606.798 10.8749826 229931.650 10.8043129 2.500000+5 10.58074039344 3  1     \n"
    " 273861.279 10.3397310 3.000000+5 10.0766499 322370.980 9.880600509344 3  1     \n"
    " 340237.324 9.72448472 346410.162 9.67069846 368910.463 9.483326329344 3  1     \n"
    " 4.000000+5 9.22523749 422948.506 9.06900211 441019.836 8.946272939344 3  1     \n"
    " 469584.836 8.75274389 5.000000+5 8.54721663 523317.570 8.420156369344 3  1     \n"
    " 541516.633 8.32119283 547722.558 8.28751526 570008.755 8.169737469344 3  1     \n"
    " 6.000000+5 8.01160655 623573.927 7.91307405 660682.791 7.758377839344 3  1     \n"
    " 7.000000+5 7.59494189 723762.416 7.51951813 760927.023 7.401845419344 3  1     \n"
    " 8.000000+5 7.27846306 823906.858 7.22288722 861113.334 7.136605159344 3  1     \n"
    " 9.000000+5 7.04666923 948683.299 6.96848467 1.000000+6 6.886399279344 3  1     \n"
    " 1048808.85 6.83736639 1.100000+6 6.78618970 1148912.53 6.761462179344 3  1     \n"
    " 1.200000+6 6.73582925 1248999.60 6.73097418 1.300000+6 6.726075919344 3  1     \n"
    " 1349073.76 6.73703554 1.400000+6 6.74853606 1449137.68 6.771633519344 3  1     \n"
    " 1.500000+6 6.79564856 1549193.34 6.82762762 1.600000+6 6.860747159344 3  1     \n"
    " 1649242.25 6.89880211 1.700000+6 6.93810804 1749285.57 6.979902979344 3  1     \n"
    " 1.800000+6 7.02297980 1849324.21 7.06663014 1.900000+6 7.111538859344 3  1     \n"
    " 1949358.87 7.15556491 2.000000+6 7.20079013 2071116.16 7.260349659344 3  1     \n"
    " 2126107.91 7.30647264 2168307.83 7.34190259 2233183.38 7.396425109344 3  1     \n"
    " 2.300000+6 7.45264113 2348447.63 7.48718882 2385451.90 7.513599749344 3  1     \n"
    " 2442054.42 7.55403437 2.500000+6 7.59546944 2548566.38 7.623964169344 3  1     \n"
    " 2585609.32 7.64571671 2642185.68 7.67896867 2.700000+6 7.712981199344 3  1     \n"
    " 2772063.27 7.74337694 2827370.15 7.76673836 2869573.25 7.784582449344 3  1     \n"
    " 2.934062+6 7.81187608 3.000000+6 7.83981357 3058367.04 7.849637679344 3  1     \n"
    " 3110368.97 7.85841141 3156595.47 7.86622587 3197606.88 7.873169779344 3  1     \n"
    " 3240370.35 7.88042407 3270663.12 7.88601235 3326548.60 7.896340359344 3  1     \n"
    " 3369088.48 7.90421179 3433920.46 7.916223+0 3.500000+6 7.928482289344 3  1     \n"
    " 3558910.27 7.92399335 3611269.57 7.92001528 3657715.48 7.916494949344 3  1     \n"
    " 3698845.40 7.91338368 3771938.77 7.90786769 3827705.13 7.903669639344 3  1     \n"
    " 3870070.30 7.90048589 3934498.85 7.89565246 4.000000+6 7.890748079344 3  1     \n"
    " 4059327.19 7.87501374 4111959.85 7.86106081 4158572.93 7.848707989344 3  1     \n"
    " 4241420.89 7.82676178 4304638.22 7.81002287 4352668.80 7.797308979344 3  1     \n"
    " 4425721.37 7.77797743 4.500000+6 7.75832799 4559657.28 7.734549429344 3  1     \n"
    " 4612505.82 7.71348725 4706468.94 7.67604472 4778195.33 7.647467359344 3  1     \n"
    " 4832706.57 7.62575114 4915641.66 7.59271487 5.000000+6 7.559115589344 3  1     \n"
    " 5120568.45 7.50157342 5212898.94 7.45751051 5354525.58 7.389925729344 3  1     \n"
    " 5.500000+6 7.320509+0 5.700940+6 7.21911740 5744562.65 7.197220569344 3  1     \n"
    " 6.000000+6 7.06900383 6.500000+6 6.82545895 7.000000+6 6.602711829344 3  1     \n"
    " 7.500000+6 6.40680352 8.000000+6 6.23938625 8.500000+6 6.099838839344 3  1     \n"
    " 9.000000+6 5.98669149 9.500000+6 5.89828680 1.000000+7 5.832911919344 3  1     \n"
    " 10246950.8 5.81106341 1.050000+7 5.78867655 10747092.7 5.776203569344 3  1     \n"
    " 1.100000+7 5.76343810 1.150000+7 5.75483168 1.200000+7 5.760386889344 3  1     \n"
    " 1.250000+7 5.77763020 1.271390+7 5.78889913 1.300000+7 5.804156039344 3  1     \n"
    " 1.350000+7 5.83768079 1.400000+7 5.87608346 1.450000+7 5.917438019344 3  1     \n"
    " 1.500000+7 5.96004117 1.550000+7 6.00242979 1.600000+7 6.043390709344 3  1     \n"
    " 1.650000+7 6.08195264 1.700000+7 6.11737084 1.750000+7 6.149096549344 3  1     \n"
    " 1.800000+7 6.17674102 1.850000+7 6.20003570 1.880420+7 6.211458869344 3  1     \n"
    " 1.900000+7 6.21881057 1.950000+7 6.23295175 2.000000+7 6.242391819344 3  1     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3  2     \n"
    " 0.000000+0 0.000000+0          0          0          1         919344 3  2     \n"
    "         91          2                                            9344 3  2     \n"
    " 1.000000-5 0.000000+0 2.530000-2 0.000000+0 2.150000+1 0.000000+09344 3  2     \n"
    " 2.150000+1 2.173981+1 3.000000+1 2.020052+1 5.000000+1 1.828425+19344 3  2     \n"
    " 7.000000+1 1.726284+1 1.000000+2 1.635010+1 2.000000+2 1.497391+19344 3  2     \n"
    " 3.000000+2 1.435822+1 5.000000+2 1.373237+1 7.000000+2 1.339253+19344 3  2     \n"
    " 1.000000+3 1.308189+1 2.000000+3 1.258675+1 3.000000+3 1.234249+19344 3  2     \n"
    " 5.000000+3 1.205914+1 7.000000+3 1.187676+1 1.000000+4 1.167726+19344 3  2     \n"
    " 1.606836+4 1.149051+1 2.000000+4 1.123872+1 3.000000+4 1.091453+19344 3  2     \n"
    " 4.017089+4 1.066973+1 5.000000+4 1.040639+1 6.025634+4 1.018956+19344 3  2     \n"
    " 7.000000+4 9.977089+0 7.230761+4 9.936605+0 1.000000+5 9.427940+09344 3  2     \n"
    " 1.200000+5 9.183383+0 1.400000+5 8.893065+0 1.700000+5 8.447592+09344 3  2     \n"
    " 2.000000+5 7.957218+0 2.500000+5 7.419840+0 3.000000+5 6.805896+09344 3  2     \n"
    " 4.000000+5 5.997050+0 5.000000+5 5.221013+0 6.000000+5 4.704651+09344 3  2     \n"
    " 7.000000+5 4.253839+0 8.000000+5 3.945379+0 9.000000+5 3.693955+09344 3  2     \n"
    " 1.000000+6 3.496215+0 1.100000+6 3.359881+0 1.200000+6 3.266153+09344 3  2     \n"
    " 1.300000+6 3.207845+0 1.400000+6 3.181299+0 1.500000+6 3.179444+09344 3  2     \n"
    " 1.600000+6 3.198967+0 1.700000+6 3.235469+0 1.800000+6 3.284256+09344 3  2     \n"
    " 1.900000+6 3.343637+0 2.000000+6 3.409047+0 2.300000+6 3.629048+09344 3  2     \n"
    " 2.500000+6 3.769926+0 2.700000+6 3.896639+0 3.000000+6 4.049732+09344 3  2     \n"
    " 3.500000+6 4.180441+0 4.000000+6 4.186244+0 4.500000+6 4.106339+09344 3  2     \n"
    " 5.000000+6 3.957521+0 5.500000+6 3.772614+0 5.700940+6 3.704577+09344 3  2     \n"
    " 6.000000+6 3.583840+0 6.500000+6 3.445215+0 7.000000+6 3.218417+09344 3  2     \n"
    " 7.500000+6 3.023266+0 8.000000+6 2.837111+0 8.500000+6 2.696653+09344 3  2     \n"
    " 9.000000+6 2.582893+0 9.500000+6 2.511954+0 1.000000+7 2.461444+09344 3  2     \n"
    " 1.050000+7 2.437717+0 1.100000+7 2.431611+0 1.150000+7 2.442895+09344 3  2     \n"
    " 1.200000+7 2.465701+0 1.250000+7 2.504599+0 1.271390+7 2.526328+09344 3  2     \n"
    " 1.300000+7 2.555545+0 1.350000+7 2.609776+0 1.400000+7 2.668039+09344 3  2     \n"
    " 1.450000+7 2.725199+0 1.500000+7 2.782713+0 1.550000+7 2.837673+09344 3  2     \n"
    " 1.600000+7 2.885454+0 1.650000+7 2.934775+0 1.700000+7 2.980438+09344 3  2     \n"
    " 1.750000+7 3.021851+0 1.800000+7 3.060054+0 1.850000+7 3.093251+09344 3  2     \n"
    " 1.880420+7 3.110639+0 1.900000+7 3.121830+0 1.950000+7 3.146314+09344 3  2     \n"
    " 2.000000+7 3.166166+0                                            9344 3  2     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3  4     \n"
    " 6.000000+4 6.000000+4          0          0          1         889344 3  4     \n"
    "         88          2                                            9344 3  4     \n"
    " 1.000000-5 0.000000+0 2.530000-2 0.000000+0 2.150000+1 0.000000+09344 3  4     \n"
    " 2.150000+1 2.587731-6 3.000000+1 2.549935-6 5.000000+1 2.480724-69344 3  4     \n"
    " 7.000000+1 2.426770-6 1.000000+2 2.361572-6 2.000000+2 2.209501-69344 3  4     \n"
    " 3.000000+2 2.104713-6 5.000000+2 1.957481-6 7.000000+2 1.853097-69344 3  4     \n"
    " 1.000000+3 1.738628-6 2.000000+3 1.519935-6 3.000000+3 1.404649-69344 3  4     \n"
    " 5.000000+3 1.289746-6 7.000000+3 1.241938-6 1.000000+4 1.225257-69344 3  4     \n"
    " 1.606836+4 9.593472-7 2.000000+4 1.448101-2 3.000000+4 2.481576-29344 3  4     \n"
    " 4.017089+4 3.305070-2 5.000000+4 4.518423-2 6.025634+4 6.268358-29344 3  4     \n"
    " 7.000000+4 7.930936-2 7.230761+4 8.378925-2 1.000000+5 1.472003-19344 3  4     \n"
    " 1.200000+5 0.18464664 1.400000+5 0.25206382 1.700000+5 0.301454469344 3  4     \n"
    " 2.000000+5 0.39468681 2.500000+5 0.51232716 3.000000+5 6.204205-19344 3  4     \n"
    " 4.000000+5 0.80544419 5.000000+5 0.95118768 6.000000+5 1.065166069344 3  4     \n"
    " 7.000000+5 1.15637153 8.000000+5 1.23263614 9.000000+5 1.299871249344 3  4     \n"
    " 1.000000+6 1.36206973 1.100000+6 1.42158383 1.200000+6 1.479485639344 3  4     \n"
    " 1.300000+6 1.53591066 1.400000+6 1.59044406 1.500000+6 1.642234229344 3  4     \n"
    " 1.600000+6 1.69012340 1.700000+6 1.73296667 1.800000+6 1.770270199344 3  4     \n"
    " 1.900000+6 1.80212786 2.000000+6 1.82902471 2.300000+6 1.887479749344 3  4     \n"
    " 2.500000+6 1.91221157 2.700000+6 1.93128090 3.000000+6 1.954440289344 3  4     \n"
    " 3.500000+6 1.98992205 4.000000+6 2.01996889 4.500000+6 2.031915869344 3  4     \n"
    " 5.000000+6 2.02763820 5.500000+6 2.01710117 6.000000+6 1.888771309344 3  4     \n"
    " 6.500000+6 1.54767617 7.000000+6 1.25583887 7.500000+6 1.035593129344 3  4     \n"
    " 8.000000+6 0.89153021 8.500000+6 0.80003410 9.000000+6 0.737365119344 3  4     \n"
    " 9.500000+6 0.69080675 1.000000+7 0.65453089 1.050000+7 0.625076619344 3  4     \n"
    " 1.100000+7 0.60030420 1.150000+7 0.57841252 1.200000+7 0.558151219344 3  4     \n"
    " 1.250000+7 0.53861321 1.300000+7 0.51926311 1.350000+7 0.500941449344 3  4     \n"
    " 1.400000+7 0.48322608 1.450000+7 0.46572836 1.500000+7 0.449737899344 3  4     \n"
    " 1.550000+7 0.43461089 1.600000+7 0.42509723 1.650000+7 0.411642299344 3  4     \n"
    " 1.700000+7 0.39910538 1.750000+7 0.38688155 1.800000+7 0.375434439344 3  4     \n"
    " 1.850000+7 0.36472112 1.900000+7 0.35435082 1.950000+7 0.344427369344 3  4     \n"
    " 2.000000+7 3.350783-1                                            9344 3  4     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3 16     \n"
    "-5.676680+6-5.676680+6          0          0          1         309344 3 16     \n"
    "         30          2                                            9344 3 16     \n"
    " 5.700940+6 0.000000+0 6.000000+6 2.026253-2 6.500000+6 1.087389-19344 3 16     \n"
    " 7.000000+6 1.946756-1 7.500000+6 2.596363-1 8.000000+6 3.046834-19344 3 16     \n"
    " 8.500000+6 3.304883-1 9.000000+6 3.442355-1 9.500000+6 3.495967-19344 3 16     \n"
    " 1.000000+7 3.540409-1 1.050000+7 3.591597-1 1.100000+7 3.637072-19344 3 16     \n"
    " 1.150000+7 3.700345-1 1.200000+7 3.732710-1 1.250000+7 3.638931-19344 3 16     \n"
    " 1.300000+7 3.374588-1 1.350000+7 3.053616-1 1.400000+7 2.690662-19344 3 16     \n"
    " 1.450000+7 2.346856-1 1.500000+7 2.063118-1 1.550000+7 1.863148-19344 3 16     \n"
    " 1.600000+7 1.691293-1 1.650000+7 1.556952-1 1.700000+7 1.451486-19344 3 16     \n"
    " 1.750000+7 1.387251-1 1.800000+7 1.317189-1 1.850000+7 1.260265-19344 3 16     \n"
    " 1.900000+7 1.210358-1 1.950000+7 1.168384-1 2.000000+7 1.108491-19344 3 16     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3 17     \n"
    "-1.265980+7-1.265980+7          0          0          1         159344 3 17     \n"
    "         15          2                                            9344 3 17     \n"
    " 1.271390+7 0.000000+0 1.350000+7 8.429257-5 1.400000+7 8.379144-49344 3 17     \n"
    " 1.450000+7 4.393801-3 1.500000+7 1.004855-2 1.550000+7 1.623820-29344 3 17     \n"
    " 1.600000+7 2.582424-2 1.650000+7 3.433012-2 1.700000+7 4.483658-29344 3 17     \n"
    " 1.750000+7 5.302409-2 1.800000+7 6.039802-2 1.850000+7 6.690118-29344 3 17     \n"
    " 1.900000+7 7.254851-2 1.950000+7 7.628671-2 2.000000+7 8.022689-29344 3 17     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3 18     \n"
    " 1.902335+8 1.902335+8          0          0          1        1599344 3 18     \n"
    "        159          2                                            9344 3 18     \n"
    " 1.000000-5 0.000000+0 2.530000-2 0.000000+0 2.150000+1 0.000000+09344 3 18     \n"
    " 2.150000+1 7.055598+1 23.3673337 67.6744903 24.8735163 65.59086639344 3 18     \n"
    " 27.3167621 62.5850969 3.000000+1 5.971707+1 31.9780774 57.83835029344 3 18     \n"
    " 33.8155969 56.2430191 37.2889621 53.5563416 40.1261713 51.62589709344 3 18     \n"
    " 42.3948687 50.2238663 46.0406716 48.1918878 5.000000+1 4.624212+19344 3 18     \n"
    " 54.3878654 44.3357773 57.9296655 42.9577741 63.6794833 40.97065769344 3 18     \n"
    " 7.000000+1 3.907546+1 76.5285581 37.3708807 81.8215398 36.14142379344 3 18     \n"
    " 90.4552596 34.3726602 1.000000+2 3.269046+1 109.050774 31.30613079344 3 18     \n"
    " 117.639701 30.1430164 125.708147 29.1607952 133.220711 28.32764259344 3 18     \n"
    " 147.464103 26.9264939 159.137392 25.9213037 168.494868 25.19211419344 3 18     \n"
    " 183.572802 24.1366101 2.000000+2 2.312533+1 221.336385 21.98756889344 3 18     \n"
    " 238.819577 21.1711361 252.832418 20.5787684 275.408289 19.72114869344 3 18     \n"
    " 3.000000+2 1.889927+1 319.780774 18.3111781 338.155969 17.81162899344 3 18     \n"
    " 372.889621 16.9699868 401.261713 16.3649583 423.948687 15.92538549344 3 18     \n"
    " 460.406716 15.2880652 5.000000+2 1.467625+1 543.878654 14.08232509344 3 18     \n"
    " 579.296655 13.6527082 636.794833 13.0327324 7.000000+2 1.244091+19344 3 18     \n"
    " 765.285581 11.9132465 818.215398 11.5322384 904.552596 10.98345169344 3 18     \n"
    " 1.000000+3 1.046078+1 1090.50774 10.0403906 1176.39701 9.686431929344 3 18     \n"
    " 1257.08147 9.38696935 1332.20711 9.132544+0 1474.64103 8.703780469344 3 18     \n"
    " 1591.37392 8.39547058 1684.94868 8.17142655 1835.72802 7.846520959344 3 18     \n"
    " 2.000000+3 7.534534+0 2213.36385 7.19712982 2388.19576 6.954029699344 3 18     \n"
    " 2528.32418 6.77710859 2754.08289 6.52013068 3.000000+3 6.272897+09344 3 18     \n"
    " 3197.80774 6.10588879 3575.87035 5.82425223 3888.47065 5.621583149344 3 18     \n"
    " 4140.72721 5.474223+0 4550.12485 5.26039380 5.000000+3 5.054917+09344 3 18     \n"
    " 5438.78654 4.89410923 5792.96655 4.77686954 6367.94833 4.606254869344 3 18     \n"
    " 7.000000+3 4.441734+0 7652.85581 4.30817456 8182.15398 4.210647169344 3 18     \n"
    " 9045.52596 4.06848003 1.000000+4 3.931113+0 10905.0774 3.841184129344 3 18     \n"
    " 12690.5097 3.68873045 14218.9262 3.57837431 15484.8713 3.497779299344 3 18     \n"
    " 17598.2223 3.38027751 2.000000+4 3.266723+0 22133.6385 3.211416779344 3 18     \n"
    " 25768.3751 3.13020810 3.000000+4 3.051053+0 38729.8335 2.976659549344 3 18     \n"
    " 5.000000+4 2.904080+0 7.000000+4 2.841287+0 1.000000+5 2.788270+09344 3 18     \n"
    " 109544.512 2.73524327 1.200000+5 2.683225+0 1.400000+5 2.622368+09344 3 18     \n"
    " 1.700000+5 2.614940+0 2.000000+5 2.647628+0 223606.798 2.580159369344 3 18     \n"
    " 2.500000+5 2.514410+0 3.000000+5 2.528816+0 346410.162 2.423506779344 3 18     \n"
    " 4.000000+5 2.322583+0 5.000000+5 2.291684+0 547722.558 2.230872679344 3 18     \n"
    " 6.000000+5 2.171675+0 7.000000+5 2.125047+0 8.000000+5 2.049066+09344 3 18     \n"
    " 9.000000+5 2.008141+0 1.000000+6 1.988853+0 1.100000+6 1.969956+09344 3 18     \n"
    " 1.200000+6 1.959189+0 1.300000+6 1.954529+0 1.400000+6 1.951783+09344 3 18     \n"
    " 1.500000+6 1.951406+0 1.600000+6 1.951268+0 1.700000+6 1.951234+09344 3 18     \n"
    " 1.800000+6 1.951774+0 1.900000+6 1.950686+0 2.000000+6 1.949073+09344 3 18     \n"
    " 2.300000+6 1.925940+0 2.500000+6 1.905030+0 2.700000+6 1.878294+09344 3 18     \n"
    " 3.000000+6 1.830670+0 3240370.35 1.79251488 3.500000+6 1.755155+09344 3 18     \n"
    " 4.000000+6 1.682749+0 4.500000+6 1.618952+0 5.000000+6 1.573188+09344 3 18     \n"
    " 5.500000+6 1.530191+0 6.000000+6 1.575584+0 6.500000+6 1.723289+09344 3 18     \n"
    " 7.000000+6 1.933237+0 7.500000+6 2.087771+0 8.000000+6 2.205540+09344 3 18     \n"
    " 8.500000+6 2.272154+0 9.000000+6 2.321689+0 9.500000+6 2.345422+09344 3 18     \n"
    " 1.000000+7 2.362413+0 1.050000+7 2.366277+0 1.100000+7 2.367403+09344 3 18     \n"
    " 1.150000+7 2.363104+0 1.200000+7 2.362900+0 1.250000+7 2.370179+09344 3 18     \n"
    " 1.300000+7 2.391527+0 1.350000+7 2.421198+0 1.400000+7 2.454605+09344 3 18     \n"
    " 1.450000+7 2.487131+0 1.500000+7 2.510938+0 1.550000+7 2.527309+09344 3 18     \n"
    " 1.600000+7 2.537610+0 1.650000+7 2.545242+0 1.700000+7 2.547582+09344 3 18     \n"
    " 1.750000+7 2.548362+0 1.800000+7 2.548890+0 1.850000+7 2.548897+09344 3 18     \n"
    " 1.900000+7 2.548813+0 1.950000+7 2.548859+0 2.000000+7 2.549846+09344 3 18     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3 37     \n"
    "-1.872420+7-1.872420+7          0          0          1          39344 3 37     \n"
    "          3          2                                            9344 3 37     \n"
    " 1.880420+7 0.000000+0 1.950000+7 4.974121-8 2.000000+7 5.265795-69344 3 37     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3 51     \n"
    " 6.000000+4 6.000000+4          0          0          1         569344 3 51     \n"
    "         56          2                                            9344 3 51     \n"
    " 1.000000-5 0.000000+0 2.530000-2 0.000000+0 2.150000+1 0.000000+09344 3 51     \n"
    " 1.000000+3 0.000000+0 2.000000+3 1.513516-9 3.000000+3 2.323049-99344 3 51     \n"
    " 5.000000+3 4.399249-9 7.000000+3 7.187316-9 1.000000+4 1.296579-89344 3 51     \n"
    " 2.000000+4 5.126479-8 3.000000+4 1.420591-7 5.000000+4 5.722159-79344 3 51     \n"
    " 7.000000+4 1.592060-6 1.000000+5 5.034973-6 1.200000+5 9.351665-69344 3 51     \n"
    " 1.400000+5 1.553400-5 1.700000+5 3.046515-5 2.000000+5 5.189078-59344 3 51     \n"
    " 2.500000+5 1.075757-4 3.000000+5 1.903713-4 4.000000+5 4.388548-49344 3 51     \n"
    " 5.000000+5 7.812344-4 6.000000+5 1.181727-3 7.000000+5 1.596032-39344 3 51     \n"
    " 8.000000+5 1.977755-3 9.000000+5 2.284032-3 1.000000+6 2.482655-39344 3 51     \n"
    " 1.100000+6 2.559387-3 1.200000+6 2.521175-3 1.300000+6 2.392016-39344 3 51     \n"
    " 1.400000+6 2.203261-3 1.500000+6 1.984445-3 1.600000+6 1.758145-39344 3 51     \n"
    " 1.700000+6 1.539122-3 1.800000+6 1.335568-3 1.900000+6 1.151266-39344 3 51     \n"
    " 2.000000+6 9.873130-4 2.300000+6 6.089414-4 2.500000+6 4.354544-49344 3 51     \n"
    " 2.700000+6 3.085975-4 3.000000+6 1.811297-4 3.500000+6 7.139688-59344 3 51     \n"
    " 4.000000+6 2.706403-5 4.500000+6 1.010284-5 5.000000+6 3.791730-69344 3 51     \n"
    " 5.500000+6 1.454822-6 6.000000+6 5.742739-7 6.500000+6 2.326189-79344 3 51     \n"
    " 7.000000+6 9.611811-8 7.500000+6 4.033081-8 8.000000+6 1.716987-89344 3 51     \n"
    " 8.500000+6 7.421556-9 9.000000+6 3.261343-9 9.500000+6 1.458493-99344 3 51     \n"
    " 1.000000+7 0.000000+0 2.000000+7 0.000000+0                      9344 3 51     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3 52     \n"
    " 6.000000+4 4.000000+3          0          0          1         849344 3 52     \n"
    "         84          2                                            9344 3 52     \n"
    " 1.000000-5 0.000000+0 2.530000-2 0.000000+0 2.150000+1 0.000000+09344 3 52     \n"
    " 2.150000+1 2.587731-6 3.000000+1 2.549935-6 5.000000+1 2.480724-69344 3 52     \n"
    " 7.000000+1 2.426770-6 1.000000+2 2.361572-6 2.000000+2 2.209501-69344 3 52     \n"
    " 3.000000+2 2.104713-6 5.000000+2 1.957481-6 7.000000+2 1.853097-69344 3 52     \n"
    " 1.000000+3 1.738628-6 2.000000+3 1.518421-6 3.000000+3 1.402326-69344 3 52     \n"
    " 5.000000+3 1.285347-6 7.000000+3 1.234751-6 1.000000+4 1.212291-69344 3 52     \n"
    " 2.000000+4 7.358018-7 3.000000+4 1.011310-6 5.000000+4 1.082214-69344 3 52     \n"
    " 7.000000+4 1.263088-6 1.000000+5 1.955018-6 1.200000+5 3.251930-69344 3 52     \n"
    " 1.400000+5 3.876030-6 1.700000+5 7.604331-6 2.000000+5 1.063382-59344 3 52     \n"
    " 2.500000+5 2.130681-5 3.000000+5 3.820323-5 4.000000+5 9.384491-59344 3 52     \n"
    " 5.000000+5 1.787576-4 6.000000+5 2.877780-4 7.000000+5 4.119965-49344 3 52     \n"
    " 8.000000+5 5.400758-4 9.000000+5 6.594636-4 1.000000+6 7.578340-49344 3 52     \n"
    " 1.100000+6 8.255217-4 1.200000+6 8.579973-4 1.300000+6 8.568518-49344 3 52     \n"
    " 1.400000+6 8.284926-4 1.500000+6 7.812329-4 1.600000+6 7.229768-49344 3 52     \n"
    " 1.700000+6 6.597685-4 1.800000+6 5.956979-4 1.900000+6 5.333246-49344 3 52     \n"
    " 2.000000+6 4.741779-4 2.300000+6 3.177520-4 2.500000+6 2.306955-49344 3 52     \n"
    " 2.700000+6 1.703237-4 3.000000+6 1.053692-4 3.500000+6 4.455283-59344 3 52     \n"
    " 4.000000+6 1.784385-5 4.500000+6 6.976617-6 5.000000+6 2.728921-69344 3 52     \n"
    " 5.500000+6 1.087352-6 6.000000+6 4.441723-7 6.500000+6 1.854230-79344 3 52     \n"
    " 7.000000+6 1.258806-5 7.500000+6 1.187647-5 8.000000+6 1.115898-59344 3 52     \n"
    " 8.500000+6 1.044346-5 9.000000+6 9.741442-6 9.500000+6 9.078692-69344 3 52     \n"
    " 1.000000+7 8.476114-6 1.050000+7 7.930065-6 1.100000+7 7.439322-69344 3 52     \n"
    " 1.150000+7 6.992008-6 1.200000+7 6.580296-6 1.250000+7 6.195725-69344 3 52     \n"
    " 1.300000+7 5.825808-6 1.350000+7 5.489852-6 1.400000+7 5.169949-69344 3 52     \n"
    " 1.450000+7 4.864317-6 1.500000+7 4.581303-6 1.550000+7 4.314730-69344 3 52     \n"
    " 1.600000+7 4.144282-6 1.650000+7 3.999054-6 1.700000+7 3.864111-69344 3 52     \n"
    " 1.750000+7 3.640901-6 1.800000+7 3.434123-6 1.850000+7 3.241585-69344 3 52     \n"
    " 1.900000+7 3.054138-6 1.950000+7 2.874436-6 2.000000+7 2.703236-69344 3 52     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3 53     \n"
    " 6.000000+4-1.600000+4          0          0          1         679344 3 53     \n"
    "         67          2                                            9344 3 53     \n"
    " 1.606836+4 0.000000+0 2.000000+4 1.448022-2 3.000000+4 2.481461-29344 3 53     \n"
    " 5.000000+4 4.100726-2 7.000000+4 5.758993-2 1.000000+5 8.208030-29344 3 53     \n"
    " 1.200000+5 9.681656-2 1.400000+5 1.084745-1 1.700000+5 1.251586-19344 3 53     \n"
    " 2.000000+5 1.356666-1 2.500000+5 1.477920-1 3.000000+5 1.536260-19344 3 53     \n"
    " 4.000000+5 1.548794-1 5.000000+5 1.506680-1 6.000000+5 1.459513-19344 3 53     \n"
    " 7.000000+5 1.426162-1 8.000000+5 1.412092-1 9.000000+5 1.417090-19344 3 53     \n"
    " 1.000000+6 1.438577-1 1.100000+6 1.473173-1 1.200000+6 1.517543-19344 3 53     \n"
    " 1.300000+6 1.568800-1 1.400000+6 1.624569-1 1.500000+6 1.682864-19344 3 53     \n"
    " 1.600000+6 1.741914-1 1.700000+6 1.800046-1 1.800000+6 1.855664-19344 3 53     \n"
    " 1.900000+6 1.907348-1 2.000000+6 1.953944-1 2.300000+6 2.056757-19344 3 53     \n"
    " 2.500000+6 2.093660-1 2.700000+6 2.108549-1 3.000000+6 2.098423-19344 3 53     \n"
    " 3.500000+6 2.024049-1 4.000000+6 1.910515-1 4.500000+6 1.784336-19344 3 53     \n"
    " 5.000000+6 1.664447-1 5.500000+6 1.562359-1 6.000000+6 1.481502-19344 3 53     \n"
    " 6.500000+6 1.418670-1 7.000000+6 1.368251-1 7.500000+6 1.325099-19344 3 53     \n"
    " 8.000000+6 1.286157-1 8.500000+6 1.249593-1 9.000000+6 1.214611-19344 3 53     \n"
    " 9.500000+6 1.181131-1 1.000000+7 1.149333-1 1.050000+7 1.119263-19344 3 53     \n"
    " 1.100000+7 1.090703-1 1.150000+7 1.063260-1 1.200000+7 1.036530-19344 3 53     \n"
    " 1.250000+7 1.010219-1 1.300000+7 9.841923-2 1.350000+7 9.584573-29344 3 53     \n"
    " 1.400000+7 9.331173-2 1.450000+7 9.083197-2 1.500000+7 8.842148-29344 3 53     \n"
    " 1.550000+7 8.609317-2 1.600000+7 8.385729-2 1.650000+7 8.172171-29344 3 53     \n"
    " 1.700000+7 7.969290-2 1.750000+7 7.777647-2 1.800000+7 7.597760-29344 3 53     \n"
    " 1.850000+7 7.430037-2 1.900000+7 7.274722-2 1.950000+7 7.131811-29344 3 53     \n"
    " 2.000000+7 7.001007-2                                            9344 3 53     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3 54     \n"
    " 6.000000+4-4.000000+4          0          0          1         659344 3 54     \n"
    "         65          2                                            9344 3 54     \n"
    " 4.017089+4 0.000000+0 5.000000+4 4.175315-3 7.000000+4 2.171542-29344 3 54     \n"
    " 1.000000+5 5.546136-2 1.200000+5 7.836751-2 1.400000+5 9.894146-29344 3 54     \n"
    " 1.700000+5 1.276736-1 2.000000+5 1.496271-1 2.500000+5 1.776263-19344 3 54     \n"
    " 3.000000+5 1.963280-1 4.000000+5 2.172149-1 5.000000+5 2.275769-19344 3 54     \n"
    " 6.000000+5 2.342172-1 7.000000+5 2.398609-1 8.000000+5 2.455160-19344 3 54     \n"
    " 9.000000+5 2.514989-1 1.000000+6 2.578451-1 1.100000+6 2.644518-19344 3 54     \n"
    " 1.200000+6 2.711283-1 1.300000+6 2.776242-1 1.400000+6 2.836610-19344 3 54     \n"
    " 1.500000+6 2.889728-1 1.600000+6 2.933425-1 1.700000+6 2.966238-19344 3 54     \n"
    " 1.800000+6 2.987468-1 1.900000+6 2.997136-1 2.000000+6 2.995831-19344 3 54     \n"
    " 2.300000+6 2.936970-1 2.500000+6 2.864956-1 2.700000+6 2.778351-19344 3 54     \n"
    " 3.000000+6 2.637252-1 3.500000+6 2.408637-1 4.000000+6 2.210160-19344 3 54     \n"
    " 4.500000+6 2.043431-1 5.000000+6 1.905325-1 5.500000+6 1.793813-19344 3 54     \n"
    " 6.000000+6 1.705917-1 6.500000+6 1.636199-1 7.000000+6 1.577648-19344 3 54     \n"
    " 7.500000+6 1.523184-1 8.000000+6 1.468409-1 8.500000+6 1.411910-19344 3 54     \n"
    " 9.000000+6 1.354669-1 9.500000+6 1.298601-1 1.000000+7 1.245341-19344 3 54     \n"
    " 1.050000+7 1.195714-1 1.100000+7 1.149763-1 1.150000+7 1.107048-19344 3 54     \n"
    " 1.200000+7 1.066973-1 1.250000+7 1.029025-1 1.300000+7 9.928838-29344 3 54     \n"
    " 1.350000+7 9.584361-2 1.400000+7 9.257072-2 1.450000+7 8.947835-29344 3 54     \n"
    " 1.500000+7 8.657409-2 1.550000+7 8.386031-2 1.600000+7 8.133297-29344 3 54     \n"
    " 1.650000+7 7.898217-2 1.700000+7 7.679435-2 1.750000+7 7.475438-29344 3 54     \n"
    " 1.800000+7 7.284781-2 1.850000+7 7.106197-2 1.900000+7 6.938670-29344 3 54     \n"
    " 1.950000+7 6.781433-2 2.000000+7 6.633917-2                      9344 3 54     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3 55     \n"
    " 6.000000+4-6.000000+4          0          0          1         649344 3 55     \n"
    "         64          2                                            9344 3 55     \n"
    " 6.025634+4 0.000000+0 7.000000+4 1.151130-6 1.000000+5 1.342533-69344 3 55     \n"
    " 1.200000+5 2.097958-6 1.400000+5 2.042249-6 1.700000+5 3.656784-69344 3 55     \n"
    " 2.000000+5 3.462665-6 2.500000+5 4.493576-6 3.000000+5 5.414932-69344 3 55     \n"
    " 4.000000+5 7.145418-6 5.000000+5 9.473791-6 6.000000+5 1.358989-59344 3 55     \n"
    " 7.000000+5 2.092356-5 8.000000+5 3.270152-5 9.000000+5 4.974025-59344 3 55     \n"
    " 1.000000+6 7.192362-5 1.100000+6 9.792710-5 1.200000+6 1.252737-49344 3 55     \n"
    " 1.300000+6 1.509070-4 1.400000+6 1.721519-4 1.500000+6 1.872354-49344 3 55     \n"
    " 1.600000+6 1.956833-4 1.700000+6 1.978818-4 1.800000+6 1.947995-49344 3 55     \n"
    " 1.900000+6 1.876212-4 2.000000+6 1.775265-4 2.300000+6 1.343763-49344 3 55     \n"
    " 2.500000+6 9.951640-5 2.700000+6 7.764732-5 3.000000+6 5.152904-59344 3 55     \n"
    " 3.500000+6 2.393819-5 4.000000+6 1.031608-5 4.500000+6 4.282140-69344 3 55     \n"
    " 5.000000+6 1.763235-6 5.500000+6 7.349803-7 6.000000+6 3.123652-79344 3 55     \n"
    " 6.500000+6 1.349438-7 7.000000+6 1.253935-5 7.500000+6 1.185367-59344 3 55     \n"
    " 8.000000+6 1.115285-5 8.500000+6 1.044649-5 9.000000+6 9.748161-69344 3 55     \n"
    " 9.500000+6 9.085662-6 1.000000+7 8.481620-6 1.050000+7 7.933666-69344 3 55     \n"
    " 1.100000+7 7.441369-6 1.150000+7 6.993169-6 1.200000+7 6.581203-69344 3 55     \n"
    " 1.250000+7 6.196794-6 1.300000+7 5.827203-6 1.350000+7 5.491545-69344 3 55     \n"
    " 1.400000+7 5.171798-6 1.450000+7 4.866144-6 1.500000+7 4.582949-69344 3 55     \n"
    " 1.550000+7 4.316083-6 1.600000+7 4.145308-6 1.650000+7 3.999745-69344 3 55     \n"
    " 1.700000+7 3.864501-6 1.750000+7 3.641052-6 1.800000+7 3.434124-69344 3 55     \n"
    " 1.850000+7 3.241525-6 1.900000+7 3.054093-6 1.950000+7 2.874465-69344 3 55     \n"
    " 2.000000+7 2.703376-6                                            9344 3 55     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3 56     \n"
    " 6.000000+4-7.200000+4          0          0          1         639344 3 56     \n"
    "         63          2                                            9344 3 56     \n"
    " 7.230761+4 0.000000+0 1.000000+5 3.511408-3 1.200000+5 7.054285-39344 3 56     \n"
    " 1.400000+5 1.040024-2 1.700000+5 1.511499-2 2.000000+5 1.832365-29344 3 56     \n"
    " 2.500000+5 2.218008-2 3.000000+5 2.448301-2 4.000000+5 2.722814-29344 3 56     \n"
    " 5.000000+5 3.020181-2 6.000000+5 3.440367-2 7.000000+5 3.975878-29344 3 56     \n"
    " 8.000000+5 4.584081-2 9.000000+5 5.215780-2 1.000000+6 5.830582-29344 3 56     \n"
    " 1.100000+6 6.399569-2 1.200000+6 6.905668-2 1.300000+6 7.341369-29344 3 56     \n"
    " 1.400000+6 7.705725-2 1.500000+6 8.001811-2 1.600000+6 8.235269-29344 3 56     \n"
    " 1.700000+6 8.411750-2 1.800000+6 8.538292-2 1.900000+6 8.621725-29344 3 56     \n"
    " 2.000000+6 8.668819-2 2.300000+6 8.653697-2 2.500000+6 8.563730-29344 3 56     \n"
    " 2.700000+6 8.442833-2 3.000000+6 8.228075-2 3.500000+6 7.803756-29344 3 56     \n"
    " 4.000000+6 7.305817-2 4.500000+6 6.776180-2 5.000000+6 6.270272-29344 3 56     \n"
    " 5.500000+6 5.821569-2 6.000000+6 5.431107-2 6.500000+6 5.079072-29344 3 56     \n"
    " 7.000000+6 4.745985-2 7.500000+6 4.419795-2 8.000000+6 4.104298-29344 3 56     \n"
    " 8.500000+6 3.808290-2 9.000000+6 3.540102-2 9.500000+6 3.303388-29344 3 56     \n"
    " 1.000000+7 3.096563-2 1.050000+7 2.914645-2 1.100000+7 2.751672-29344 3 56     \n"
    " 1.150000+7 2.602474-2 1.200000+7 2.463525-2 1.250000+7 2.332972-29344 3 56     \n"
    " 1.300000+7 2.210195-2 1.350000+7 2.095212-2 1.400000+7 1.988149-29344 3 56     \n"
    " 1.450000+7 1.888921-2 1.500000+7 1.797106-2 1.550000+7 1.711988-29344 3 56     \n"
    " 1.600000+7 1.632698-2 1.650000+7 1.558351-2 1.700000+7 1.488200-29344 3 56     \n"
    " 1.750000+7 1.421712-2 1.800000+7 1.358625-2 1.850000+7 1.298890-29344 3 56     \n"
    " 1.900000+7 1.242619-2 1.950000+7 1.189997-2 2.000000+7 1.141205-29344 3 56     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3 91     \n"
    " 6.000000+4-7.200000+4          0          0          1         639344 3 91     \n"
    "         63          2                                            9344 3 91     \n"
    " 7.230761+4 0.000000+0 1.000000+5 6.138899-3 1.200000+5 2.393584-39344 3 91     \n"
    " 1.400000+5 3.422617-2 1.700000+5 3.346554-2 2.000000+5 9.100347-29344 3 91     \n"
    " 2.500000+5 1.645954-1 3.000000+5 2.457495-1 4.000000+5 4.055819-19344 3 91     \n"
    " 5.000000+5 5.417715-1 6.000000+5 6.491108-1 7.000000+5 7.321067-19344 3 91     \n"
    " 8.000000+5 7.975196-1 9.000000+5 8.515123-1 1.000000+6 8.987487-19344 3 91     \n"
    " 1.100000+6 9.423362-1 1.200000+6 9.840419-1 1.300000+6 1.024593+09344 3 91     \n"
    " 1.400000+6 1.064065+0 1.500000+6 1.102004+0 1.600000+6 1.137560+09344 3 91     \n"
    " 1.700000+6 1.169824+0 1.800000+6 1.198448+0 1.900000+6 1.223590+09344 3 91     \n"
    " 2.000000+6 1.245720+0 2.300000+6 1.300509+0 2.500000+6 1.329947+09344 3 91     \n"
    " 2.700000+6 1.357606+0 3.000000+6 1.398254+0 3.500000+6 1.468476+09344 3 91     \n"
    " 4.000000+6 1.534788+0 4.500000+6 1.581356+0 5.000000+6 1.607950+09344 3 91     \n"
    " 5.500000+6 1.623265+0 6.000000+6 1.515717+0 6.500000+6 1.191398+09344 3 91     \n"
    " 7.000000+6 9.137639-1 7.500000+6 7.065431-1 8.000000+6 5.750083-19344 3 91     \n"
    " 8.500000+6 4.957800-1 9.000000+6 4.450166-1 9.500000+6 4.097815-19344 3 91     \n"
    " 1.000000+7 3.840809-1 1.050000+7 3.644166-1 1.100000+7 3.487260-19344 3 91     \n"
    " 1.150000+7 3.353430-1 1.200000+7 3.231525-1 1.250000+7 3.113467-19344 3 91     \n"
    " 1.300000+7 2.994419-1 1.350000+7 2.882890-1 1.400000+7 2.774518-19344 3 91     \n"
    " 1.450000+7 2.665191-1 1.500000+7 2.567621-1 1.550000+7 2.475289-19344 3 91     \n"
    " 1.600000+7 2.435717-1 1.650000+7 2.353469-1 1.700000+7 2.277284-19344 3 91     \n"
    " 1.750000+7 2.201263-1 1.800000+7 2.130159-1 1.850000+7 2.063634-19344 3 91     \n"
    " 1.900000+7 1.997846-1 1.950000+7 1.933892-1 2.000000+7 1.873116-19344 3 91     \n"
    "                                                                  9344 3  0     \n"
    " 9.323600+4 2.340190+2          0          0          0          09344 3102     \n"
    " 6.637350+6 6.637350+6          0          0          1        2399344 3102     \n"
    "        239          2                                            9344 3102     \n"
    " 1.000000-5 0.000000+0 2.530000-2 0.000000+0 2.150000+1 0.000000+09344 3102     \n"
    " 2.150000+1 5.694135+0 23.3673337 5.46128784 24.8735163 5.292922659344 3102     \n"
    " 27.3167621 5.05005687 3.000000+1 4.818335+0 31.9780774 4.666501689344 3102     \n"
    " 33.8155969 4.53757751 37.2889621 4.32047166 40.1261713 4.164486799344 3102     \n"
    " 42.3948687 4.05120514 46.0406716 3.88703414 5.000000+1 3.729516+09344 3102     \n"
    " 54.3878654 3.57545087 57.9296655 3.46409322 63.6794833 3.303525809344 3102     \n"
    " 7.000000+1 3.150401+0 76.5285581 3.01262399 81.8215398 2.913260039344 3102     \n"
    " 90.4552596 2.77032506 1.000000+2 2.634403+0 109.050774 2.522459749344 3102     \n"
    " 117.639701 2.42841844 125.708147 2.34901283 133.220711 2.281665759344 3102     \n"
    " 147.464103 2.16842116 159.137392 2.08719173 168.494868 2.028272859344 3102     \n"
    " 183.572802 1.94299833 2.000000+2 1.861309+0 221.336385 1.769289189344 3102     \n"
    " 238.819577 1.70327229 252.832418 1.65538122 275.408289 1.586057559344 3102     \n"
    " 3.000000+2 1.519637+0 319.780774 1.47204087 338.155969 1.431618759344 3102     \n"
    " 372.889621 1.36353258 401.261713 1.31460150 423.948687 1.279059+09344 3102     \n"
    " 460.406716 1.22753889 5.000000+2 1.178094+0 543.878654 1.130023099344 3102     \n"
    " 579.296655 1.09526157 636.794833 1.04511396 7.000000+2 9.972624-19344 3102     \n"
    " 765.285581 0.95450222 818.215398 0.92363964 904.552596 0.879206729344 3102     \n"
    " 1.000000+3 8.369113-1 1090.50774 0.80273769 1176.39701 0.773982439344 3102     \n"
    " 1257.08147 0.74966781 1332.20711 0.72901994 1474.64103 0.694245169344 3102     \n"
    " 1591.37392 0.66925705 1684.94868 0.65110799 1835.72802 0.624803039344 3102     \n"
    " 2.000000+3 5.995608-1 2213.36385 0.57206987 2388.19576 0.552282099344 3102     \n"
    " 2528.32418 0.53789174 2754.08289 0.51700619 3.000000+3 4.969316-19344 3102     \n"
    " 3197.80774 0.48323701 3575.87035 0.46017334 3888.47065 0.443600889344 3102     \n"
    " 4140.72721 4.315644-1 4550.12485 0.41411926 5.000000+3 3.973793-19344 3102     \n"
    " 5438.78654 0.38411024 5792.96655 0.37445002 6367.94833 0.360413329344 3102     \n"
    " 7.000000+3 3.469028-1 7652.85581 0.33576119 8182.15398 0.327640459344 3102     \n"
    " 9045.52596 0.31582612 1.000000+4 3.044378-1 10905.0774 0.296196679344 3102     \n"
    " 11763.9701 0.28916888 13432.9975 0.27726911 14838.4044 0.268666779344 3102     \n"
    " 15988.1385 0.26239061 17881.9119 0.25325020 2.000000+4 2.444282-19344 3102     \n"
    " 22133.6385 0.23949330 25768.3751 0.23227713 3.000000+4 2.252784-19344 3102     \n"
    " 34086.5811 0.22055813 41283.5204 0.21366252 5.000000+4 2.069825-19344 3102     \n"
    " 59160.7979 0.20137766 7.000000+4 1.959246-1 83666.0027 0.189051499344 3102     \n"
    " 1.000000+5 1.824195-1 109544.512 0.17909185 1.200000+5 1.758249-19344 3102     \n"
    " 129614.814 0.17015276 1.400000+5 1.646636-1 1.700000+5 1.596437-19344 3102     \n"
    " 184390.890 0.15382978 2.000000+5 1.482276-1 211474.253 0.144578959344 3102     \n"
    " 229931.650 0.13927369 2.500000+5 1.341631-1 273861.279 0.127683799344 3102     \n"
    " 3.000000+5 1.215174-1 322370.980 0.11578512 340237.324 0.111664079344 3102     \n"
    " 368910.463 0.10575588 4.000000+5 1.001603-1 422948.506 9.565873-29344 3102     \n"
    " 441019.836 9.241582-2 469584.836 8.775643-2 5.000000+5 8.333195-29344 3102     \n"
    " 523317.570 7.981061-2 541516.633 7.726759-2 570008.755 7.360420-29344 3102     \n"
    " 6.000000+5 7.011449-2 623573.927 6.734742-2 660682.791 6.340022-29344 3102     \n"
    " 7.000000+5 5.968436-2 723762.416 5.749075-2 760927.023 5.435058-29344 3102     \n"
    " 8.000000+5 5.138192-2 823906.858 4.962374-2 861113.334 4.709862-29344 3102     \n"
    " 9.000000+5 4.470199-2 948683.299 4.189354-2 1.000000+6 3.926154-29344 3102     \n"
    " 1048808.85 3.694698-2 1.100000+6 3.476887-2 1148912.53 3.283125-29344 3102     \n"
    " 1.200000+6 3.100162-2 1248999.60 2.935258-2 1.300000+6 2.779125-29344 3102     \n"
    " 1349073.76 2.636398-2 1.400000+6 2.501000-2 1449137.68 2.375572-29344 3102     \n"
    " 1.500000+6 2.256434-2 1549193.34 2.144898-2 1.600000+6 2.038875-29344 3102     \n"
    " 1649242.25 1.938905-2 1.700000+6 1.843837-2 1749285.57 1.753696-29344 3102     \n"
    " 1.800000+6 1.667961-2 1849324.21 1.586385-2 1.900000+6 1.508799-29344 3102     \n"
    " 1949358.87 1.434859-2 2.000000+6 1.364542-2 2071116.16 1.267963-29344 3102     \n"
    " 2126107.91 1.200042-2 2168307.83 1.151499-2 2233183.38 1.082343-29344 3102     \n"
    " 2.300000+6 1.017339-2 2348447.63 9.669261-3 2385451.90 9.307628-39344 3102     \n"
    " 2442054.42 8.790378-3 2.500000+6 8.301874-3 2548566.38 7.888345-39344 3102     \n"
    " 2585609.32 7.591772-3 2642185.68 7.167689-3 2.700000+6 6.767295-39344 3102     \n"
    " 2772063.27 6.265108-3 2827370.15 5.913079-3 2869573.25 5.662100-39344 3102     \n"
    " 2.934062+6 5.305463-3 3.000000+6 4.971289-3 3058367.04 4.660145-39344 3102     \n"
    " 3110368.97 4.403912-3 3156595.47 4.191291-3 3197606.88 4.013686-39344 3102     \n"
    " 3270663.12 3.720795-3 3326548.60 3.515240-3 3369088.48 3.368561-39344 3102     \n"
    " 3433920.46 3.159938-3 3.500000+6 2.964235-3 3558910.27 2.782364-39344 3102     \n"
    " 3611269.57 2.632405-3 3657715.48 2.507835-3 3698845.40 2.403682-39344 3102     \n"
    " 3771938.77 2.231715-3 3827705.13 2.110862-3 3870070.30 2.024537-39344 3102     \n"
    " 3934498.85 1.901624-3 4.000000+6 1.786173-3 4059327.19 1.685156-39344 3102     \n"
    " 4111959.85 1.601465-3 4158572.93 1.531651-3 4241420.89 1.416720-39344 3102     \n"
    " 4304638.22 1.336218-3 4352668.80 1.278858-3 4425721.37 1.197401-39344 3102     \n"
    " 4.500000+6 1.121133-3 4559657.28 1.069416-3 4612505.82 1.026125-39344 3102     \n"
    " 4706468.94 9.545397-4 4778195.33 9.041474-4 4832706.57 8.681068-49344 3102     \n"
    " 4915641.66 8.167216-4 5.000000+6 7.683780-4 5120568.45 7.231527-49344 3102     \n"
    " 5212898.94 6.909894-4 5354525.58 6.454065-4 5.500000+6 6.028307-49344 3102     \n"
    " 5744562.65 5.737115-4 6.000000+6 5.459988-4 6.500000+6 5.398734-49344 3102     \n"
    " 7.000000+6 5.433449-4 7.500000+6 5.370965-4 8.000000+6 5.216398-49344 3102     \n"
    " 8.500000+6 5.094324-4 9.000000+6 5.088756-4 9.500000+6 5.073582-49344 3102     \n"
    " 1.000000+7 4.831257-4 10246950.8 4.643169-4 1.050000+7 4.462404-49344 3102     \n"
    " 10747092.7 4.291424-4 1.100000+7 4.126995-4 1.150000+7 3.856595-49344 3102     \n"
    " 1.200000+7 3.636676-4 1.250000+7 3.458836-4 1.300000+7 3.314392-49344 3102     \n"
    " 1.350000+7 3.194605-4 1.400000+7 3.092590-4 1.450000+7 3.002494-49344 3102     \n"
    " 1.500000+7 2.919285-4 1.550000+7 2.838942-4 1.600000+7 2.759344-49344 3102     \n"
    " 1.650000+7 2.680302-4 1.700000+7 2.602781-4 1.750000+7 2.527993-49344 3102     \n"
    " 1.800000+7 2.456680-4 1.850000+7 2.388920-4 1.900000+7 2.324316-49344 3102     \n"
    " 1.950000+7 2.262330-4 2.000000+7 2.202558-4                      9344 3102     \n"
    "                                                                  9344 3  0     \n"
    "                                                                  9344 0  0     \n"
    "                                                                     0 0  0     \n";
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