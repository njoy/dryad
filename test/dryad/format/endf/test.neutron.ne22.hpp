namespace neutron {

// test functions based on n-010_Ne_022.endf
namespace ne22 {

  void verifyDocumentation( const Documentation& documentation ) {

    std::string description =
      " 10-Ne- 22  NRG       EVAL-DEC15 A.J. Koning and D. Rochman       \n"
      " TENDL-2015           DIST-FEB18 REV1-                            \n"
      "----ENDF/B-VIII.0     Material 1031         REVISION 1            \n"
      "-----Incident neutron  data                                       \n"
      "------ENDF-6 Format                                               \n"
      "                                                                  \n"
      "TENDL-2015 (TALYS Evaluated Nuclear Data Library)                 \n"
      "                                                                  \n"
      "Ne022 neutron general purpose library                             \n"
      "                                                                  \n"
      "Author: A.J. Koning and D. Rochman, NRG - IAEA - PSI              \n"
      "                                                                  \n"
      "The TENDL team: A.J. Koning, D. Rochman, S.C. van der Marck,      \n"
      "                J. Ch. Sublet, M. Fleming, J. Kopecky, S. Pomp,   \n"
      "                H. Sjostrand, R. Forrest, E. Bauge,               \n"
      "                H. Henriksson, O. Cabellos, S. Goriely,           \n"
      "                J. Leppanen, H. Leeb, A. Plompen, R. Mills,       \n"
      "                S. Hilaire, P. Romain, B. Morillon, H. Duarte     \n"
      "                                                                  \n"
      "Ref.: A.J. Koning and D. Rochman,                                 \n"
      "      Modern nuclear data evaluation with the TALYS code system,  \n"
      "      Nucl. Data Sheets 113, 2841 (2012).                         \n"
      "                                                                  \n"
      "************** G E N E R A L   I N F O R M A T I O N *************\n"
      "                                                                  \n"
      "This evaluated data file is based on a software system built      \n"
      "around the nuclear model code TALYS [kon07], version 1.74. It is  \n"
      "part of a large collection of isotopic evaluations, all created by\n"
      "running the system with either adjusted or default input          \n"
      "parameters. This means that the data in the entire collection have\n"
      "been tested in detail for many isotopes against individual        \n"
      "experimental data, while for other isotopes it is only as good as \n"
      "the global quality of TALYS at the moment. The mutual quality of  \n"
      "all individual data files is however consistent: The same set of  \n"
      "nuclear models is used and, equally important, the same ENDF-6    \n"
      "formatting procedures for each isotope. The data file has been    \n"
      "created automatically using the ENDF-6 format generator TEFAL.    \n"
      "                                                                  \n"
      "The resulting data file provides a complete representation of     \n"
      "nuclear data needed for transport, activation, damage, heating,   \n"
      "radioactivity, and shielding applications over the incident       \n"
      "neutron energy range from 1.e-11 to 200. MeV.                     \n"
      "                                                                  \n"
      "All transport and activation data for neutrons, charged particles,\n"
      "photons and residual nuclides are filed. This includes cross      \n"
      "sections, angular distributions, double-differential spectra,     \n"
      "isomeric production, discrete and continuum photon production     \n"
      "cross sections, residual production cross sections and recoils.   \n"
      "This general purpose evaluation can thus be used as both          \n"
      "transport and activation library.                                 \n"
      "                                                                  \n"
      "A complete set of covariance data is included, which is stored    \n"
      "in MF31-40.                                                       \n"
      "                                                                  \n"
      "**** N U C L I D E    S P E C I F I C   I N F O R M A T I O N ****\n"
      "                                                                  \n"
      "                      Resonance Range                             \n"
      "                                                                  \n"
      "  --------------------------------------------------------------- \n"
      "  --------------------------------------------------------------- \n"
      "                                                                  \n"
      "  General methodology: The global approach considered in this     \n"
      "          work is presented in the following paper: Modern        \n"
      "          nuclear data evaluation with the TALYS code system,     \n"
      "          A.J. Koning and D. Rochman, Nuclear Data Sheets 113     \n"
      "          (2012) 2841.                                            \n"
      "                                                                  \n"
      "  MF2:  Resolved resonance range  (RRR)                           \n"
      "       The RRR was generated with TARES-1.31, compiled on         \n"
      "       12-10-2015 11:58:11 PM at Villingen  , Switzerland. The RRR\n"
      "       expands from 0 to 1.261834E+6 eV. A total of               \n"
      "       2 l-values are used and 21 resonances. The resonance       \n"
      "       formalism is multi-level Breit Wigner (MLBW).              \n"
      "       The ladder approach from the CALENDF code is used to       \n"
      "       generate statistical resonances in the unresolved          \n"
      "       resonance range. Therefore, the URR is translated into     \n"
      "       resolved resonance range. Explanations about the method    \n"
      "       can be found in the CALENDF manual: CEA-Report CEA-R-6277  \n"
      "       \"CALENDF-2010: User manual\" by J.C. Sublet, P. Ribon and   \n"
      "       M. Coste-Delcaux.                                          \n"
      "       The method of creating statistical resonances in the       \n"
      "       URR region is described in: \"From average parameters to    \n"
      "       statistical resolved resonances\", D. Rochman et al.,       \n"
      "       Annals of Nucl. Ene. 51 (2013) 60.                         \n"
      "       The s-wave average level spacing is 1.416e+06 eV and       \n"
      "       the s-wave neutron strength is 8.5e-05 1e-4.               \n"
      "                                                                  \n"
      "  MF32: Covariance file for resonance parameters                  \n"
      "        The compact format is used to represent the covariance    \n"
      "        information on the resonance parameters. Uncertainties    \n"
      "        come from compilations, EXFOR or existing libraries and   \n"
      "        correlations between parameters are obtained following    \n"
      "        the method presented in NIM/A 589 (2008) 85.              \n"
      "                                                                  \n"
      "                                                                  \n"
      "               Average parameters from INTER                      \n"
      "                                                                  \n"
      "     ****************************************************         \n"
      "     *   Thermal (n,g) xs =  4.549420E-02 b.            *         \n"
      "     *   RI      (n,g)    =  2.059370E-02 b.            *         \n"
      "     *   MACS 30 keV      =  8.915900E-05 b. (MF2 only) *         \n"
      "     *                                                  *         \n"
      "     *   Thermal (n,el) xs = 5.091130E+00 b.            *         \n"
      "     *   RI      (n,el)    = 6.491580E+01 b.            *         \n"
      "     ****************************************************         \n"
      "                                                                  \n"
      "                                                                  \n"
      "               Plots of different cross sections                  \n"
      "                                                                  \n"
      "                         Ne22(n,el)                               \n"
      " 100 ++--+--+---+--+---+--+---+---+--+---+--+---+--+--++          \n"
      "     +      +      +      +       +      (n,el) + A    +          \n"
      "     +                                                 +          \n"
      "     +                                        A        +          \n"
      "  10 ++                                       A       ++          \n"
      "     +                                        AAA      +          \n"
      "     +   AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA AAA      +          \n"
      "     +                                       AAAA      +          \n"
      "     |                                         AA      |          \n"
      "   1 ++                                        AA     ++          \n"
      "     +                                                 +          \n"
      "     +                                                 +          \n"
      "     +      +      +      +       +      +      +      +          \n"
      " 0.1 ++--+--+---+--+---+--+---+---+--+---+--+---+--+--++          \n"
      "   1e-06  0.0001  0.01    1      100   10000  1e+06  1e+08        \n"
      "                         Energy (eV)                              \n"
      "                           Ne22(n,g)                              \n"
      "     10 ++-+---+--+--+---+--+---+--+--+---+--+--+---+-++          \n"
      "        +  AAA +     +      +      +    AA(n,g) + A    +          \n"
      "      1 ++    AAAA                      AA A          ++          \n"
      "    0.1 ++        AAAA                  AA A          ++          \n"
      "        +             AAAAA             AA A           +          \n"
      "   0.01 ++                AAAA          AA A          ++          \n"
      "  0.001 ++                    AAAA      AA A          ++          \n"
      "        +                         AAAA  AA A           +          \n"
      " 0.0001 ++                           AAAAA A          ++          \n"
      "        +                              AAA A   A       +          \n"
      "  1e-05 ++                               AAA   AA     ++          \n"
      "  1e-06 ++                                AA   AAA    ++          \n"
      "        +      +     +      +      +      +AA AAAA     +          \n"
      "  1e-07 ++-+---+--+--+---+--+---+--+--+---+-AAA-A---+-++          \n"
      "      1e-06  0.0001 0.01    1     100   10000 1e+06  1e+08        \n"
      "                          Energy (eV)                             \n"
      "                                                                  \n"
      "                                                                  \n"
      "  --------------------------------------------------------------- \n"
      "  --------------------------------------------------------------- \n"
      "                                                                  \n"
      "               Adjusted TALYS input parameters                    \n"
      "                                                                  \n"
      "#                                                                 \n"
      "# General                                                         \n"
      "#                                                                 \n"
      "ldmodel 2                                                         \n"
      "#                                                                 \n"
      "# (n,tot), (n,el), (n,inl)                                        \n"
      "#                                                                 \n"
      "#                                                                 \n"
      "# (n,p), (n,2n), (n,np)                                           \n"
      "#                                                                 \n"
      "#                                                                 \n"
      "# (n,a)                                                           \n"
      "#                                                                 \n"
      "#                                                                 \n"
      "# (n,g)                                                           \n"
      "#                                                                 \n"
      "gamgamadjust 10  23 0.60                                          \n"
      "#                                                                 \n"
      "# Other: Isomers, (n,d), (n,t), (n,h) etc.                        \n"
      "#                                                                 \n"
      "                                                                  \n"
      "***************************** T A L Y S **************************\n"
      "                                                                  \n"
      "TALYS is a computer code system for the prediction and analysis   \n"
      "of nuclear reactions. TALYS simulates reactions that involve      \n"
      "neutrons, gamma-rays, protons, deuterons, tritons, helions and    \n"
      "alpha-particles, in the 1 keV - 200 MeV energy range. This is     \n"
      "achieved by implementing a suite of nuclear reaction models into  \n"
      "a single code system. This nuclear data file is based on a        \n"
      "theoretical analysis that utilizes the optical model, compound    \n"
      "nucleus statistical theory, fission, direct reactions and         \n"
      "pre-equilibrium processes, in combination with databases and      \n"
      "models for nuclear structure. The following output of TALYS is    \n"
      "stored in this data file:                                         \n"
      "                                                                  \n"
      "- Total, elastic and non-elastic cross sections                   \n"
      "- Inelastic cross sections to discrete states                     \n"
      "- Exclusive channel cross sections, e.g. (n,g), (n,2n), (n,np),.. \n"
      "- Inelastic scattering angular distributions to discrete states   \n"
      "- Exclusive channel energy spectra                                \n"
      "- Exclusive channel double-differential spectra                   \n"
      "- Exclusive gamma production for discrete states and continuum    \n"
      "- Elastic scattering angular distributions                        \n"
      "- Recoil data                                                     \n"
      "- Total particle cross sections, e.g. (n,xn), (n,xp),..           \n"
      "- Total particle energy spectra                                   \n"
      "- Total particle double-differential spectra                      \n"
      "- Isomeric and ground state cross sections                        \n"
      "- Residual production cross sections                              \n"
      "                                                                  \n"
      "For a description of the used nuclear models and their            \n"
      "parameterization we refer to [kon12]. If for this specific        \n"
      "nuclide we deviate from the global parameterization, it is made   \n"
      "explicit above under Nuclide Specific Information.                \n"
      "                                                                  \n"
      "***************** F I L E   I N F O R M A T I O N ****************\n"
      "                                                                  \n"
      "##### MF1: GENERAL INFORMATION                                    \n"
      "                                                                  \n"
      "- MT451    : Descriptive data and directory                       \n"
      "                                                                  \n"
      "This text and the full directory of used MF/MT sections.          \n"
      "                                                                  \n"
      "##### MF2: RESONANCE PARAMETERS                                   \n"
      "                                                                  \n"
      "- MT151    : Resonance parameters                                 \n"
      "                                                                  \n"
      "Details about the origin of the resonance parameters for this     \n"
      "nuclide are given above in this description. In general, both a   \n"
      "Resolved and an Unresolved Resonance Range are given.             \n"
      "                                                                  \n"
      "##### MF3: REACTION CROSS SECTIONS                                \n"
      "                                                                  \n"
      "All the data present in the following MT-sections have been       \n"
      "calculated with TALYS, possibly normalized to experimental data.  \n"
      "If the maximal cross section in an excitation function over the   \n"
      "whole energy range does not exceed 1.e-9 b, the MT-number is not  \n"
      "included. Cross sections lower than 1.e-20 b are assumed to have  \n"
      "no physical meaning and are set to zero. All MT numbers extend up \n"
      "to the highest incident energy.                                   \n"
      "The following reaction channels/MT numbers are generally included:\n"
      "                                                                  \n"
      "- MT1      : Total cross section                                  \n"
      "                                                                  \n"
      "Calculated with the optical model over the whole energy range,    \n"
      "or partly reproduced using experimental data.                     \n"
      "                                                                  \n"
      "- MT2      : Elastic scattering cross section                     \n"
      "                                                                  \n"
      "Obtained by subtracting the non-elastic cross section from the    \n"
      "total cross section.                                              \n"
      "                                                                  \n"
      "- MT3      : Non-elastic cross section                            \n"
      "                                                                  \n"
      "Calculated with the optical model over the whole energy range.    \n"
      "                                                                  \n"
      "- MT4      : Total inelastic cross section                        \n"
      "                                                                  \n"
      "Sum of MT=51-91.                                                  \n"
      "                                                                  \n"
      "- MT5      : (n,anything) cross section                           \n"
      "                                                                  \n"
      "MT5 contains the reactions which can not be stored in any other   \n"
      "MT-number. The information of MF3/MT5 can be combined with        \n"
      "MF6/MT5 to obtain residual production cross sections particle     \n"
      "production cross sections and (double-)differential cross         \n"
      "sections.                                                         \n"
      "                                                                  \n"
      "- MT16     : (n,2n) cross section                                 \n"
      "- MT17     : (n,3n) cross section                                 \n"
      "- MT22     : (n,na) cross section                                 \n"
      "- MT28     : (n,np) cross section                                 \n"
      "- MT51-90  : (n,n') cross section for 1st-40th excited state      \n"
      "- MT91     : (n,n') continuum cross section                       \n"
      "- MT102    : (n,gamma) cross section                              \n"
      "- MT103    : (n,p) cross section                                  \n"
      "- MT104    : (n,d) cross section                                  \n"
      "- MT105    : (n,t) cross section                                  \n"
      "- MT106    : (n,h) cross section                                  \n"
      "- MT107    : (n,a) cross section                                  \n"
      "- MT600-610: (n,p) cross section for 0th-10th excited state       \n"
      "- MT649    : (n,p) continuum cross section                        \n"
      "- MT650-655: (n,d) cross section for 0th-5th excited state        \n"
      "- MT699    : (n,d) continuum cross section                        \n"
      "- MT700-705: (n,t) cross section for 0th-5th excited state        \n"
      "- MT749    : (n,t) continuum cross section                        \n"
      "- MT750-755: (n,h) cross section for 0th-5th excited state        \n"
      "- MT799    : (n,h) continuum cross section                        \n"
      "- MT800-810: (n,a) cross section for 0th-10th excited state       \n"
      "- MT849    : (n,a) continuum cross section                        \n"
      "                                                                  \n"
      "##### MF4: ANGULAR DISTRIBUTIONS OF SECONDARY PARTICLES           \n"
      "                                                                  \n"
      "We use MF4 for the neutron scattering angular distribution for    \n"
      "discrete levels.                                                  \n"
      "                                                                  \n"
      "- MT2      : Elastic angular distribution                         \n"
      "                                                                  \n"
      "The flag LTT=3 is used to indicate a switch at some high energy,  \n"
      "generally 50 MeV, from a Legendre representation to a tabulated   \n"
      "representation. For incident energies below this energy, the      \n"
      "Legendre coefficients are given on a sufficiently precise energy  \n"
      "grid. They are a sum of calculated Legendre coefficients for      \n"
      "compound nucleus and shape-elastic scattering. For higher         \n"
      "incident energies, relative angular distributions are tabulated   \n"
      "on an angular grid.                                               \n"
      "                                                                  \n"
      "- MT51-70  : (n,n') angular distribution for 1st-20th state       \n"
      "- MT600-610: (n,p) angular distribution for 0th-10th state        \n"
      "- MT650-655: (n,d) angular distribution for 0th-5th state         \n"
      "- MT700-705: (n,t) angular distribution for 0th-5th state         \n"
      "- MT750-755: (n,h) angular distribution for 0th-5th state         \n"
      "- MT800-810: (n,a) angular distribution for 0th-10th state        \n"
      "                                                                  \n"
      "##### MF6: PRODUCT ENERGY-ANGLE DISTRIBUTIONS                     \n"
      "                                                                  \n"
      "In MF6 we store all secondary energy, angle, and energy-angle     \n"
      "distributions, as well as all residual and discrete + continuum   \n"
      "photon production cross sections for channels other than capture  \n"
      "(MT102) and reactions to discrete levels (MT51,etc.).             \n"
      "All data are generated with TALYS.                                \n"
      "                                                                  \n"
      "- MT5      : (n,anything) yields and energy-angle distributions   \n"
      "                                                                  \n"
      "MT5 contains, in this order,                                      \n"
      "For neutrons up to alpha particles and photons:                   \n"
      "- the production yields per particle for the whole energy range   \n"
      "- the secondary energy-angle distributions per particles which are\n"
      "  not represented by explicit MT numbers. On a secondary energy   \n"
      "  grid the relative emission spectra are given together with the  \n"
      "  parameters for the Kalbach systematics for angular              \n"
      "  distributions. Inelastic scattering cross sections for discrete \n"
      "  states have been broadened and added to the continuum spectra.  \n"
      "For each residual product:                                        \n"
      "- the production yields for the whole energy range.               \n"
      "- the recoil                                                      \n"
      "These distributions can be multiplied with MF3/MT5 to get         \n"
      "the production cross sections and (double-)differential cross     \n"
      "sections.                                                         \n"
      "                                                                  \n"
      "- MT16     : (n,2n) energy-angle distr. and photon production     \n"
      "                                                                  \n"
      "First, for each type of outgoing particle, the (trivial) integer  \n"
      "particle yields are given. Next, on a sufficiently dense incident \n"
      "energy grid the secondary energy-angle distributions are          \n"
      "specified by means of the relative emission spectra and the       \n"
      "parameters for the Kalbach systematics for angular distributions. \n"
      "Next, the photon yield is tabulated as a function of incident     \n"
      "energy. For each incident energy, the photon production is given  \n"
      "for all discrete gamma lines present in the final nucleus. A      \n"
      "continuum photon distribution is added to this. We assume         \n"
      "isotropy for all produced gamma rays.                             \n"
      "                                                                  \n"
      "For the following MT-numbers, the same procedure as for MT16 is   \n"
      "followed:                                                         \n"
      "                                                                  \n"
      "- MT17 : (n,3n) energy-angle distr. and photon production         \n"
      "- MT22 : (n,na) energy-angle distr. and photon production         \n"
      "- MT28 : (n,np) energy-angle distr. and photon production         \n"
      "- MT91 : (n,n') continuum energy-angle distr. and phot. prod.     \n"
      "- MT649: (n,p) continuum energy-angle distr. and photon prod.     \n"
      "- MT699: (n,d) continuum energy-angle distr. and photon prod.     \n"
      "- MT749: (n,t) continuum energy-angle distr. and photon prod.     \n"
      "- MT809: (n,h) continuum energy-angle distr. and photon prod.     \n"
      "- MT849: (n,a) continuum energy-angle distr. and photon prod.     \n"
      "                                                                  \n"
      "##### MF8: RADIOACTIVE DECAY DATA                                 \n"
      "                                                                  \n"
      "For reactions to isomers, MF8 designates where the information    \n"
      "for isomeric versus ground state production, or residual          \n"
      "production can be found, i.e. for each MT number it points to     \n"
      "either MF6, MF9 or MF10.                                          \n"
      "                                                                  \n"
      "##### MF9: MULTIPLICITIES FOR PRODUCTION OF RADIOACTIVE NUCLIDES  \n"
      "                                                                  \n"
      "MF9 is used for isomer production by non-threshold reactions.     \n"
      "Final states with a lifetime that exceeds 1 second are treated    \n"
      "as isomer.                                                        \n"
      "                                                                  \n"
      "##### MF10: CROSS SECTIONS FOR PRODUCTION OF RADIOACTIVE NUCLIDES \n"
      "                                                                  \n"
      "MF10 is used for isomer production by threshold reactions.        \n"
      "Final states with a lifetime that exceeds 1 second are treated    \n"
      "as isomer.                                                        \n"
      "                                                                  \n"
      "##### MF12: PHOTON PRODUCTION YIELD DATA                          \n"
      "                                                                  \n"
      "MF12 is used for the photon production for two types of reactions:\n"
      "- Reactions to discrete levels (MT51, etc.) For this transition   \n"
      "  probabilities are used (LO=2)                                   \n"
      "- Photons from neutron capture (MT102). Here multiplicities are   \n"
      "  given                                                           \n"
      "                                                                  \n"
      "##### MF14: PHOTON ANGULAR DISTRIBUTIONS                          \n"
      "                                                                  \n"
      "All photon production is considered as isotropic                  \n"
      "                                                                  \n"
      "##### MF15: PHOTON ENERGY SPECTRA                                 \n"
      "                                                                  \n"
      "For capture (MT102), the photon energy spectrum is given.         \n"
      "                                                                  \n"
      "##### MF32: COVARIANCES OF RESONANCE PARAMETERS                   \n"
      "                                                                  \n"
      "In MF32, we store the covariances of resonance parameters,        \n"
      "and more details are given above in this description.             \n"
      "                                                                  \n"
      "##### MF33: COVARIANCES OF NEUTRON CROSS SECTIONS                 \n"
      "                                                                  \n"
      "In MF33, we store the covariances of most, but not all, reaction  \n"
      "channels that are given in MF3. All covariances are generated     \n"
      "with the TASMAN code [kon12], which generates TALYS runs using    \n"
      "a Monte Carlo parameter method.                                   \n"
      "For each MT-number, the information consists of:                  \n"
      "1. Covariances for MTa, Ea and MTa, Ea (variances)                \n"
      "2. Covariances for MTa, Ea and MTa, Eb (correlations for the      \n"
      "   same reaction channel between different energies)              \n"
      "3. Covariances for MTa, Ea and MTb, Ea (correlations between      \n"
      "   different reaction channels for the same energy)               \n"
      "4. Covariances for MTa, Ea and MTb, Eb (correlations between      \n"
      "   different reaction channels for different energies)            \n"
      "Classes 1 and 2 are covered by NI-type subsubsections with        \n"
      "flag LB=5, followed by a LB=8 section which contains              \n"
      "the cross section variances multiplied by 1.e-3. Next, classes 3  \n"
      "and 4 are covered by flag LB=6 to account for the different       \n"
      "energy grids that two correlating MT-sections may have. Since     \n"
      "the total correlation matrix is fully symmetric, we only need to  \n"
      "include the correlation elements between different MT-numbers     \n"
      "once, and we do that in the subsection with the lowest of the     \n"
      "two MT-numbers. We include covariance information for all the     \n"
      "total cross sections, the lumped partial cross sections and the   \n"
      "individual inelastic cross sections per level (MT51,...). We do   \n"
      "not include covariances for MT600 and higher MT-numbers. For the  \n"
      "most important channels, we include cross-channel correlations.   \n"
      "                                                                  \n"
      "##### MF34: COVARIANCES OF ANGULAR DISTRIBUTIONS                  \n"
      "                                                                  \n"
      "In MF34, we store the covariances of the elastic scattering       \n"
      "angular distributions that are given in MF4/MT2. All covariances  \n"
      "are generated with the TASMAN code [kon12], which generates       \n"
      "TALYS runs using a Monte Carlo parameter method. The tables are   \n"
      "restricted to MT2 and contain covariances for the first 6         \n"
      "Legendre coefficients. Both intra- and inter-correlations of the  \n"
      "various Legendre coefficients are given. As in MF33, the LB5      \n"
      "representation is used.                                           \n"
      "                                                                  \n"
      "##### MF40: COVARIANCES OF ISOMER PRODUCTION                      \n"
      "                                                                  \n"
      "For covariances of ground state and isomeric cross sections, the  \n"
      "same procedures as for MF33 are used.                             \n"
      "                                                                  \n"
      "***** F I L E   C H E C K I N G   A N D   P R O C E S S I N G ****\n"
      "                                                                  \n"
      "This file has been checked and processed by                       \n"
      "- the BNL checking codes CHECKR-8.13, FIZCON-8.09 and PSYCHE-8.05 \n"
      "  [her08],                                                        \n"
      "- the preprocessing codes PREPRO-2015 [cul12] into a PENDF file,  \n"
      "- the processing code NJOY12.50 [mac10] into a PENDF file and an  \n"
      "  MCNP (ACE) library,                                             \n"
      "- MCNP for a standard calculation with the ACE library.           \n"
      "                                                                  \n"
      "*********************** R E F E R E N C E S **********************\n"
      "                                                                  \n"
      "[cul12] D.E. Cullen, PREPRO 2013 - 2013 ENDF-6 Pre-processing     \n"
      "        codes, Technical report IAEA-NDS-39 (Rev.14), IAEA (2010) \n"
      "[her08] M. Herman, ENDF Utility Codes Release 8.0, (2008)         \n"
      "[kon07] A.J. Koning, S. Hilaire and M.C. Duijvestijn, TALYS-1.0,  \n"
      "        Proceedings of the International Conference on Nuclear    \n"
      "        Data for Science and Technology - ND-2007,                \n"
      "        April 22-27, 2007, Nice, France                           \n"
      "[kon12] A.J. Koning and D. Rochman, Modern nuclear data           \n"
      "        evaluation with the TALYS code system, Nuclear Data       \n"
      "        Sheets 113, 2841 (2012)                                   \n"
      "[mac10] R.E. Macfarlane and A.C. Kahler, Methods for processing   \n"
      "        ENDF/B-VII with NJOY, Nuclear Data Sheets 111, 2739 (2010)\n"
      "                                                                  \n"
      "************************* C O N T E N T S ************************\n"
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

    CHECK( 0 == documentation.library() );
    CHECK( std::make_pair( 8, 0 ) == documentation.version() );
    CHECK( description == documentation.description() );
  }

  void verifyParticleDatabase( const ParticleDatabase& particles ) {

    using namespace njoy::constants;

    CHECK( 58 == particles.numberParticles() );

    CHECK( true == particles.hasParticle( id::ParticleID( "g" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "n" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "p" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "d" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "t" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "h" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "a" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "C13[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "C14[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "C15[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "N17[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "N18[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "O16[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "O17[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "O18[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "O19[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "O20[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "O21[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "F19[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "F20[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "F21[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "F22[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne20[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne21[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e1" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e2" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e3" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e4" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e5" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e6" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e7" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e8" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e9" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e10" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e11" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e12" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e13" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e14" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e15" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e16" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e17" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e18" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e19" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e20" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e21" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e22" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e23" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e24" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e25" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e26" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e27" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e28" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e29" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22_e30" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22[continuum]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne22[all]" ) ) );
    CHECK( true == particles.hasParticle( id::ParticleID( "Ne23[all]" ) ) );

    auto particle = particles.particle( id::ParticleID( "n" ) );
    CHECK( id::ParticleID::neutron() == particle.identifier() );
    CHECK_THAT( neutron_mass, WithinRel( particle.mass().value() ) );
    CHECK_THAT( 0.5, WithinRel( particle.spin().value() ) );
    CHECK( +1 == particle.parity().value() );
    CHECK( std::nullopt == particle.energy() );
    CHECK( std::nullopt == particle.nuclearMass() );
    CHECK( std::nullopt == particle.massUncertainty() );
    CHECK( std::nullopt == particle.nuclearMassUncertainty() );
    CHECK( std::nullopt == particle.energyUncertainty() );

    particle = particles.particle( id::ParticleID( "Ne22" ) );
    CHECK( id::ParticleID( "Ne22" ) == particle.identifier() );
    CHECK_THAT( 21.80247 * neutron_mass, WithinRel( particle.mass().value() ) );
    CHECK_THAT( 0.0, WithinRel( particle.spin().value() ) );
    CHECK( +1 == particle.parity().value() );
    CHECK_THAT( 0. , WithinRel( particle.energy().value() ) );
    CHECK( std::nullopt == particle.nuclearMass() );
    CHECK( std::nullopt == particle.massUncertainty() );
    CHECK( std::nullopt == particle.nuclearMassUncertainty() );
    CHECK( std::nullopt == particle.energyUncertainty() );
  }

  void verifyAngularDistributionCovariances( const covariance::AngularDistributionCovarianceData& angle ) {

    CHECK( false == angle.hasCovarianceMatrix( id::ReactionID( "n,Ne22->total" ) ) );
    CHECK( true == angle.hasCovarianceMatrix( id::ReactionID( "n,Ne22->n(0)" ) ) );

    CHECK( 1 == angle.numberReactions() );
    CHECK( 1 == angle.reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == angle.reactionIdentifiers()[0] );//

    CHECK( 1 == angle.numberCovarianceMatrices() );
    CHECK( 1 == angle.covariances().size() );

    using CovarianceMatrix = njoy::dryad::covariance::AngularDistributionCovarianceMatrix;
    auto variant = angle.covarianceMatrix( id::ReactionID( "n,Ne22->n(0)" ) );
    auto matrices = std::get< std::vector< CovarianceMatrix > >( variant );
    CHECK( 21 == matrices.size() );

    auto matrix = matrices[0];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 1 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  6.461320e-1 == matrix.covariances()( 0, 0) );
    CHECK(  7.195770e-2 == matrix.covariances()( 0, 8) );
    CHECK(  7.195770e-2 == matrix.covariances()( 8, 0) );
    CHECK(  1.402580e-2 == matrix.covariances()( 8, 8) );

    matrix = matrices[1];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 1 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 2 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK( -1.917260e-2 == matrix.covariances()( 0, 0) );
    CHECK(  2.804280e-2 == matrix.covariances()( 0, 8) );
    CHECK(  2.804280e-2 == matrix.covariances()( 8, 0) );
    CHECK(  8.603500e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[2];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 1 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 3 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  9.280390e-2 == matrix.covariances()( 0, 0) );
    CHECK(  4.003050e-2 == matrix.covariances()( 0, 8) );
    CHECK(  4.003050e-2 == matrix.covariances()( 8, 0) );
    CHECK(  5.173480e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[3];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 1 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 4 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  2.390450e-1 == matrix.covariances()( 0, 0) );
    CHECK( -3.115410e-2 == matrix.covariances()( 0, 8) );
    CHECK( -3.115410e-2 == matrix.covariances()( 8, 0) );
    CHECK( -1.294910e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[4];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 1 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 5 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  2.976840e-1 == matrix.covariances()( 0, 0) );
    CHECK(  1.016920e-2 == matrix.covariances()( 0, 8) );
    CHECK(  1.016920e-2 == matrix.covariances()( 8, 0) );
    CHECK(  1.380130e-2 == matrix.covariances()( 8, 8) );

    matrix = matrices[5];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 1 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 6 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  7.168980e-2 == matrix.covariances()( 0, 0) );
    CHECK( -1.229440e-1 == matrix.covariances()( 0, 8) );
    CHECK( -1.229440e-1 == matrix.covariances()( 8, 0) );
    CHECK( -4.624270e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[6];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 2 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  8.228060e-2 == matrix.covariances()( 0, 0) );
    CHECK(  1.831640e-2 == matrix.covariances()( 0, 8) );
    CHECK(  1.831640e-2 == matrix.covariances()( 8, 0) );
    CHECK(  6.716340e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[7];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 2 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 3 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  3.415830e-2 == matrix.covariances()( 0, 0) );
    CHECK( -2.681660e-3 == matrix.covariances()( 0, 8) );
    CHECK( -2.681660e-3 == matrix.covariances()( 8, 0) );
    CHECK(  2.627130e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[8];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 2 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 4 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK( -1.247560e-1 == matrix.covariances()( 0, 0) );
    CHECK(  1.026980e-2 == matrix.covariances()( 0, 8) );
    CHECK(  1.026980e-2 == matrix.covariances()( 8, 0) );
    CHECK(  1.418250e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[9];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 2 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 5 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK( -4.701100e-2 == matrix.covariances()( 0, 0) );
    CHECK(  4.330050e-2 == matrix.covariances()( 0, 8) );
    CHECK(  4.330050e-2 == matrix.covariances()( 8, 0) );
    CHECK(  1.334910e-2 == matrix.covariances()( 8, 8) );

    matrix = matrices[10];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 2 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 6 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  5.913020e-2 == matrix.covariances()( 0, 0) );
    CHECK(  4.700340e-2 == matrix.covariances()( 0, 8) );
    CHECK(  4.700340e-2 == matrix.covariances()( 8, 0) );
    CHECK(  5.403800e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[11];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 3 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  6.408760e-2 == matrix.covariances()( 0, 0) );
    CHECK(  9.136090e-3 == matrix.covariances()( 0, 8) );
    CHECK(  9.136090e-3 == matrix.covariances()( 8, 0) );
    CHECK(  4.462820e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[12];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 3 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 4 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK( -9.277740e-3 == matrix.covariances()( 0, 0) );
    CHECK(  3.179460e-3 == matrix.covariances()( 0, 8) );
    CHECK(  3.179460e-3 == matrix.covariances()( 8, 0) );
    CHECK( -9.136080e-4 == matrix.covariances()( 8, 8) );

    matrix = matrices[13];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 3 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 5 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  1.123890e-1 == matrix.covariances()( 0, 0) );
    CHECK(  2.973450e-2 == matrix.covariances()( 0, 8) );
    CHECK(  2.973450e-2 == matrix.covariances()( 8, 0) );
    CHECK(  3.524320e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[14];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 3 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 6 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  4.052250e-2 == matrix.covariances()( 0, 0) );
    CHECK(  7.925030e-3 == matrix.covariances()( 0, 8) );
    CHECK(  7.925030e-3 == matrix.covariances()( 8, 0) );
    CHECK( -6.764580e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[15];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 4 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  3.293190e-1 == matrix.covariances()( 0, 0) );
    CHECK( -1.920330e-2 == matrix.covariances()( 0, 8) );
    CHECK( -1.920330e-2 == matrix.covariances()( 8, 0) );
    CHECK(  4.164310e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[16];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 4 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 5 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  1.939020e-1 == matrix.covariances()( 0, 0) );
    CHECK( -5.247920e-2 == matrix.covariances()( 0, 8) );
    CHECK( -5.247920e-2 == matrix.covariances()( 8, 0) );
    CHECK(  7.030260e-3 == matrix.covariances()( 8, 8) );

    matrix = matrices[17];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 4 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 6 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK( -6.077330e-2 == matrix.covariances()( 0, 0) );
    CHECK( -1.028040e-1 == matrix.covariances()( 0, 8) );
    CHECK( -1.028040e-1 == matrix.covariances()( 8, 0) );
    CHECK(  1.366060e-2 == matrix.covariances()( 8, 8) );

    matrix = matrices[18];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 5 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  2.495290e-1 == matrix.covariances()( 0, 0) );
    CHECK(  2.131720e-2 == matrix.covariances()( 0, 8) );
    CHECK(  2.131720e-2 == matrix.covariances()( 8, 0) );
    CHECK(  3.725310e-2 == matrix.covariances()( 8, 8) );

    matrix = matrices[19];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 5 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( 1 == matrix.columnMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.columnMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.columnMetadata().moments().size() );
    CHECK( 6 == matrix.columnMetadata().moments()[0] );
    CHECK( 10 == matrix.columnMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.columnMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.columnMetadata().energies().back() ) );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  3.741020e-2 == matrix.covariances()( 0, 0) );
    CHECK( -6.477740e-2 == matrix.covariances()( 0, 8) );
    CHECK( -6.477740e-2 == matrix.covariances()( 8, 0) );
    CHECK(  2.388810e-2 == matrix.covariances()( 8, 8) );

    matrix = matrices[20];
    CHECK( ReferenceFrame::CentreOfMass == matrix.frame() );
    CHECK( 1 == matrix.rowMetadata().reactionIdentifiers().size() );
    CHECK( id::ReactionID( "n,Ne22->n(0)" ) == matrix.rowMetadata().reactionIdentifiers()[0] );
    CHECK( 1 == matrix.rowMetadata().moments().size() );
    CHECK( 6 == matrix.rowMetadata().moments()[0] );
    CHECK( 10 == matrix.rowMetadata().energies().size() );
    CHECK_THAT( 3.0e+5, WithinRel( matrix.rowMetadata().energies().front() ) );
    CHECK_THAT( 2.0e+8, WithinRel( matrix.rowMetadata().energies().back() ) );
    CHECK( matrix.columnMetadata() == matrix.rowMetadata() );
    CHECK( 9 == matrix.covariances().rows() );
    CHECK( 9 == matrix.covariances().cols() );
    CHECK(  6.676800e-2 == matrix.covariances()( 0, 0) );
    CHECK(  1.830770e-2 == matrix.covariances()( 0, 8) );
    CHECK(  1.830770e-2 == matrix.covariances()( 8, 0) );
    CHECK(  5.335100e-2 == matrix.covariances()( 8, 8) );
  }

  void verifyNe22( const ProjectileTarget& Ne22, bool /* normalise */ ) {

    neutron::ne22::verifyDocumentation( Ne22.documentation() );

    CHECK( id::ParticleID( "n" ) == Ne22.projectileIdentifier() );
    CHECK( id::ParticleID( "Ne22" ) == Ne22.targetIdentifier() );

    CHECK( InteractionType::Nuclear == Ne22.interactionType() );

    CHECK( std::nullopt != Ne22.particleData() );
    verifyParticleDatabase( Ne22.particleData().value() );

    CHECK( std::nullopt == Ne22.resonances() );

    CHECK( std::nullopt != Ne22.covarianceData() );

    CHECK( std::nullopt != Ne22.covarianceData()->crossSection() );

    CHECK( std::nullopt != Ne22.covarianceData()->angularDistribution() );
    verifyAngularDistributionCovariances( Ne22.covarianceData()->angularDistribution().value() );
  }
} // namespace ne22
} // namespace neutron
