namespace neutron {

// test functions based on n-003_Li_007.endf
namespace li7 {

  void verifyDocumentation( const Documentation& documentation ) {

    std::string description =
      "  3-Li-  7 LANL       EVAL-AUG88 P.G.Young                        \n"
      " NDS 148, 1 (2018)    DIST-AUG24 REV1-JUL23            20240830   \n"
      "---- ENDF/B-VIII.1    MATERIAL  328         REVISION 1            \n"
      "----- INCIDENT-NEUTRON DATA                                       \n"
      "------ ENDF-6                                                     \n"
      " FILE INFORMATION                                                 \n"
      "                                                                  \n"
      " **************************************************************** \n"
      "                                                                  \n"
      " ENDF/B-VII Evaluation, June 2015, B. W. Sleaford (LLNL)          \n"
      "           R. F. Firestone (LBNL)                                 \n"
      "                                                                  \n"
      "The prompt gamma-ray spectrum for thermal radiative capture       \n"
      "(MF 12, MT 102) has been updated with new experimental data.[Fi]  \n"
      "                                                                  \n"
      " **************************************************************** \n"
      "                                                                  \n"
      " ENDF/B-VII  converted from ENDF/B-VI by NNDC OCT 2004            \n"
      "                                                                  \n"
      " **************************************************************** \n"
      "                                                                  \n"
      "               PRELIMINARY EVALUATION FOR ENDF/B-VI               \n"
      "                                                                  \n"
      " BASED ON AN UPDATE OF THE VARIANCE-COVARIANCE ANALYSIS PERFORMED \n"
      " FOR ENDF/B-V.2 (YO81). INCLUDES NEW (N,NT) DATA THROUGH 1/1/88   \n"
      " (LI83, MA83, SM84, MA86, TA84, GO85, CH85, SW85, QA86), AS WELL  \n"
      " AS NEW ELASTIC AND INELASTIC DATA (CH85, SH84, AL82, DR86,       \n"
      " SC87, DE87).  SIMILAR TECHNIQUES TO YO82 WERE USED EXCEPT        \n"
      " CROSS CORRELATIONS AMONG (N,NT) MEASUREMENTS WERE INCLUDED.      \n"
      " IN ADDITION, A SEPARATE COVARIANCE ANALYSIS WAS PERFORMED FOR    \n"
      " THE (N,N2) DISCRETE INELASTIC CROSS SECTION TO THE 4.63-MEV      \n"
      " STATE OF LI7.  PRIMARY REFERENCE IS YO88.                        \n"
      " THE THERMAL NEUTRON DATA WERE UPDATED USING THE MU81 COMPILATION.\n"
      "                                                                  \n"
      " *********** GENERAL DESCRIPTION *********************************\n"
      "                                                                  \n"
      "   INDEPENDENT V-C ANALYSIS FOR THE FOLLOWING FOUR REACTIONS      \n"
      " WAS PERFORMED USING THE GLUCS CODE SYSTEM (HE80).                \n"
      "     (1) TOTAL X/S (MT1)                                          \n"
      "     (2) ELASTIC + (N,NPRIME) X/S TO 1ST LEVEL (MT2+MT51)         \n"
      "     (3) (N,NT) X/S (SUM OF MT52 THRU MT82)                       \n"
      "     (4) (N,2N)+(N,2ND)+(N,3NP)+(N,D)  (MT16+MT24+MT25+MT104)     \n"
      " VARIANCES AND COVARIANCES FROM THE GLUCS ANALYSIS WERE THEN AD-  \n"
      " JUSTED WITH THE ALVIN CODE (HA75) UNDER THE CONSTRAINT THAT      \n"
      " REACTIONS (2)-(4) SUM TO REACTION (1). MOST CROSS SECTIONS       \n"
      " AND COVARIANCES IN MF=3 AND 33 ARE BASED ON THESE RESULTS.       \n"
      "   A SEPARATE GLUCS ANALYSIS WAS PERFORMED OF MT51 X/S DATA AND   \n"
      " THEN SUBTRACTED FROM REACTION (2) TO OBTAIN MT2. TO SEPARATE     \n"
      " COMPONENT MTS FROM REACTION (4), MT104 FROM ENDF/B-V.1 WAS       \n"
      " ADOPTED, AND AD HOC CURVES WERE DRAWN FOR MT16+MT24 AND MT25     \n"
      " USING THE MEAGER EXP DATA. MT16 AND MT24 WERE THEN SEPARATED     \n"
      " USING STATISTICAL THEORY CALCULATIONS.                           \n"
      "   COVARIANCE MATRICES WERE DEVELOPED FOR EACH EXPERIMENT. IN     \n"
      " MOST CASES STANDARD DEVIATIONS WERE AVAILABLE BUT IT WAS USUALLY \n"
      " NECESSARY TO MAKE GENERIC ASSUMPTIONS FOR THE ERROR CORRELATIONS \n"
      " ACCORDING TO THE TYPE OF MEASUREMENT. EXPERIMENTAL DATA INCLUDED \n"
      " IN THE ANALYSIS ARE REFERENCED BELOW.  CROSS CORRELATIONS        \n"
      " BETWEEN DIFFERENT TRITIUM-PROD.EXPERIMENTS DUE TO STANDARDS      \n"
      " AND TRITIUM HALF LIFE WERE INCLUDED IN V-C ANALYSIS.             \n"
      "                                                                  \n"
      " *********** MF=2 RESONANCE PARAMETERS ***************************\n"
      "                                                                  \n"
      " MT=151  SCATTERING RADIUS ONLY.                                  \n"
      "                                                                  \n"
      " *********** MF=3 SMOOTH NEUTRON CROSS SECTIONS ******************\n"
      "                                                                  \n"
      " MT=  1  TOTAL CROSS SECTION. ENDF/B-V.1 ADOPTED BELOW 0.1 MEV    \n"
      "         EXCEPT THE THERMAL DATA OF MU81 WAS USED AND THE ELAST.  \n"
      "         DATA OF AL82 WAS MATCHED.  V-C ANALYSIS ABOVE 0.1        \n"
      "         MEV BASED ON ME70, GO71, HA78, FO71, KA57, BR58, PE60,   \n"
      "         CO52, LA79, AND HI68. ERRORS DOUBLED NEAR 260-KEV        \n"
      "         RESONANCE FOR HI68, ME70 DATA.                           \n"
      " MT=  2  ELASTIC CROSS SECTION. V-C ANALYSIS USED DATA OF TH56,   \n"
      "         WI56, KN68, BA63A, HO68, LI80, CO67, WO62, RE66, AR64,   \n"
      "         HY68, LA61, KN81, KN79, HO79, LA64, CH85, SH84, AND      \n"
      "         DR86.  THE ERRORS IN THE V-C ANALYSIS WERE TRIPLED NEAR  \n"
      "         260-KEV RESONANCE FOR LA61, LA64 DATA. OPTICAL MODEL     \n"
      "         ANALYSIS OF HO79 DATA USED TO CALCULATE X/S ABOVE        \n"
      "         14 MEV FOR V-C ANALYSIS. THERMAL CROSS SECTION OF MU81   \n"
      "         USED, AND EVALUATION MATCHED TO AL82 DATA BELOW 0.1 MEV. \n"
      " MT=  4  (N,NPRIME)GAMMA + (N,NPRIME)ALPHA-T.  SUM OF MT=51-82.   \n"
      " MT= 16  (N,2N) CROSS SECTION.  V-C ANALYSIS OF MT16+MT24 USED    \n"
      "         DATA OF CH85, AS58, MC61, MA69. SEPARATION OF MT16 AND   \n"
      "         MT24 FOLLOWS THE RATIO OF THE ENDF/B-V.1 DATA.           \n"
      " MT= 24  (N,2N)ALPHA-D CROSS SECTION.  SEE COMMENT FOR MT16.      \n"
      " MT= 25  (N,3N)ALPHA-P CROSS SECTION.  SMOOTH CURVE DRAWN ABOVE 14\n"
      "         MEV SO AS TO APPROXIMATELY AGREE WITH MA69, KO71 DATA.   \n"
      " MT= 51  (N,NPRIME)GAMMA CROSS SECTION.  SEPARATE V-C ANALYSIS    \n"
      "         USED DATA OF PR72, OL80, SM76, DI74, MO78, FR55, KN81,   \n"
      "         BE60, BA53, CH61, KN68, GL63, HO68, BA63A. ERRORS        \n"
      "         DOUBLED ON FR55, BE60, AND TRIPLED ON CH61.              \n"
      " MT= 56  (N,NPRIME)ALPHA-T CROSS SECTION.  SEPARATE V-C ANALYSIS  \n"
      "         PERFORMED USING DATA OF CH85, DR87, SC87, DE87, RE66,    \n"
      "         AR64, HY68, WO62, CO67, BI77, HO79, BA79, BA63, LI80,    \n"
      "         HO68, RO62 AND YO65.                                     \n"
      " MT=52-82 (N,NPRIME)ALPHA-T CROSS SECTION.  EXCEPT FOR MT56,      \n"
      "         EXCITATION ENERGY BINS WERE CONSTRUCTED SUCH THAT CALCU- \n"
      "         LATED NEUTRON EMISSION SPECTRA AGREE WITH THE MEASURE-   \n"
      "         MENTS BY LI80 AT 5.96, 9.83, AND 14.1 MEV INCIDENT ENER- \n"
      "         GY. INTERPOLATION OF CROSS SECTIONS BETWEEN ENERGIES     \n"
      "         BASED ON LINEAR INTERPOLATION OF COMPUTED CM EMISSION    \n"
      "         SPECTRA, SUITABLY CONTRACTED OR EXPANDED TO CONSERVE     \n"
      "         ENERGY.  ABOVE 14.1 MEV, THE EXP EMISSION SHAPE WAS USED \n"
      "         TO INFER THE X/S, WITH THE SHAPES AGAIN SUITABLY EX-     \n"
      "         PANDED TO CONSERVE ENERGY.                               \n"
      "         AT ALL INCIDENT ENERGIES, THE SUM OF MT=52-82 WAS        \n"
      "         CONSTRAINED TO EQUAL THE (N,NT) CROSS SECTION FROM THE   \n"
      "         VARIANCE-COVARIANCE ANALYSIS.                            \n"
      " MT=102  (N,GAMMA) CROSS SECTION.  SHAPE FROM ENDF/B-V.1 EXCEPT   \n"
      "         DATA RAISED ABOVE 10 EV TO AGREE WITH EXP.DATA (IM59).   \n"
      "         THERMAL CROSS SECTION OF MU81 USED.                      \n"
      " MT=104  (N,D) CROSS SECTION.  ADOPTED FROM ENDF/B-V.1. DATA      \n"
      "         AGREE APPROXIMATELY WITH EXPS OF BA53, BA63B, LI73,      \n"
      "         AND DISAGREE WITH MI61.                                  \n"
      "                                                                  \n"
      " *********** MF=4 NEUTRON ANGULAR DISTRIBUTIONS ******************\n"
      "                                                                  \n"
      " MT=  2  LEGENDRE COEFFICIENTS OBTAINED BY DRAWING SMOOTH CURVE   \n"
      "         THROUGH FITTED COEFFICIENTS FROM MEASUREMENTS LISTED     \n"
      "         UNDER MF3/MT2. DATA OF LA61, KN68, KN79, KN81, HO79,     \n"
      "         EMPHASIZED. OPTICAL MODEL CALCULATIONS USED ABOVE 14 MEV.\n"
      " MT= 16  TABULATED DISTRIBUTION OBTAINED BY INTEGRATING THREE-    \n"
      "         BODY PHASE SPACE CALCULATION OVER SECONDARY ENERGY.      \n"
      " MT= 24  TABULATED DISTRIBUTION OBTAINED BY INTEGRATING FOUR-     \n"
      "         BODY PHASE SPACE CALCULATION OVER SECONDARY ENERGY.      \n"
      " MT= 25  TABULATED DISTRIBUTION OBTAINED BY INTEGRATING FIVE-     \n"
      "         BODY PHASE SPACE CALCULATION OVER SECONDARY ENERGY.      \n"
      " MT= 51  LEGENDRE COEFFICIENTS OBTAINED FROM R-MATRIX ANALYSIS    \n"
      "         OF KN81 BELOW 6 MEV, JOINED SMOOTHLY TO DWBA CALCULATION \n"
      "         ABOVE 8 MEV USING DWUCK CODE AND OPTICAL PARAMETERS FROM \n"
      "         MT=2 ANALYSIS. SOME USE ALSO MADE OF LI7(P,PPRIME) DATA. \n"
      " MT=52-71  LEGENDRE COEFFICIENTS OBTAINED FROM ANALYSIS OF LI80   \n"
      "         EXPERIMENT DESCRIBED IN MF3 ABOVE (EXCEPT MT56). COEF-   \n"
      "         FICIENTS FOR MT=56 OBTAINED BY DRAWING SMOOTH CURVES     \n"
      "         THROUGH FITTED VALUES FROM EXPERIMENTS LISTED ABOVE      \n"
      "         UNDER MF3/MT56, ESPECIALLY HO68 AND HO79.                \n"
      " MT=72,82  ISOTROPY ASSUMED.                                      \n"
      "                                                                  \n"
      " *********** MF=5 NEUTRON ENERGY DISTRIBUTIONS *******************\n"
      "                                                                  \n"
      " MT= 16  TABULATED DISTRIBUTION OBTAINED BY INTEGRATING THREE-    \n"
      "         BODY PHASE SPACE CALCULATION OVER SECONDARY ANGLE.       \n"
      " MT= 24  TABULATED DISTRIBUTION OBTAINED BY INTEGRATING FOUR-     \n"
      "         BODY PHASE SPACE CALCULATION OVER SECONDARY ANGLE.       \n"
      " MT= 25  TABULATED DISTRIBUTION OBTAINED BY INTEGRATING FIVE-     \n"
      "         BODY PHASE SPACE CALCULATION OVER SECONDARY ANGLE.       \n"
      "                                                                  \n"
      " *********** MF=12 PHOTON MULTIPLICITIES *************************\n"
      "                                                                  \n"
      " MT= 51  MULTIPLICITY IS 1.0 EVERYWHERE SINCE FIRST LEVEL IN      \n"
      "         LI7 IS ONLY KNOWN PHOTON EMITTER.                        \n"
      " MT=102  ADOPTED DIRECTLY FROM ENDF/B-V.1. DUE TO THE ABSENCE     \n"
      "         OF DATA, THE TRANSITIONS ARE SIMPLY REASONABLE GUESSES.  \n"
      "                                                                  \n"
      " *********** MF=14 PHOTON ANGULAR DISTRIBUTIONS ******************\n"
      "                                                                  \n"
      " MT= 51  ISOTROPY ASSUMED AT ALL ENERGIES.                        \n"
      " MT=102  ISOTROPY ASSUMED FOR ALL GAMMAS AT ALL ENERGIES.         \n"
      "                                                                  \n"
      " *********** MF=33 NEUTRON CROSS SECTION COVARIANCES *************\n"
      "                                                                  \n"
      " MT=  1  BELOW 100 KEV, DERIVED FROM MT2 + MT102.  ABOVE 100      \n"
      "         KEV, TAKEN DIRECTLY FROM GLUCS-ALVIN ANALYSIS.           \n"
      " MT=  2  BELOW 100 KEV, 5PC CORRELATED ERROR ASSUMED.  ABOVE 100  \n"
      "         KEV, DERIVED FROM MT1-MT4-MT851(MT16+MT24 LUMP), WHICH   \n"
      "         IS THE GLUCS-ALVIN ANALYSIS RESULT.                      \n"
      " MT=  4  FROM GLUCS-ALVIN ANALYSIS (MT51 MATRIX SUBTRACTED FROM   \n"
      "         REACTION 3 (ABOVE) COVARIANCE MATRIX.                    \n"
      " MT= 16  LUMP INDICATOR ONLY.                                     \n"
      " MT= 24  LUMP INDICATOR ONLY.                                     \n"
      " MT= 25  AD HOC ESTIMATE.                                         \n"
      " MT=51-82 LUMP INDICATORS ONLY.                                   \n"
      " MT=102  AD HOC ESTIMATE BASED ON EXPERIMENTAL SPREAD AND ERROR   \n"
      "         BELOW 1 MEV.                                             \n"
      " MT=104  AD HOC ESTIMATE BASED ON EXPERIMENTAL ERRORS.            \n"
      " MT=851  LUMP OF MT16 + MT24 ERRORS, AS DETERMINED IN GLUCS-ALVIN \n"
      "         ANALYSIS.                                                \n"
      " MT=852  SINGLE LUMP OF MT=51 ERROR.  DETERMINED IN INDEPENDENT   \n"
      "         GLUCS ANALYSIS OF MT51 EXPERIMENTAL DATA (SEE ABOVE).    \n"
      " MT=853  LUMP OF MT=52-55 ERRORS.  DETERMINED IN SIMULTANEOUS     \n"
      "         ANALYSIS USING ALVIN TO CONSTRAIN (ADJUST) THE PARTIAL   \n"
      "         REACTION COVARIANCES FOR MT=853-859 TO BE CONSISTENT     \n"
      "         WITH THE TOTAL (N,NT) COVARIANCE (REACTION 3 ABOVE) FROM \n"
      "         THE GLUCS-ALVIN ANALYSIS.  INPUT COVARIANCES PRIOR TO    \n"
      "         THE ADJUSTMENT WERE ESTIMATED FROM EXPERIMENTAL DATA     \n"
      "         DESCRIBED UNDER MF=3 ABOVE. COMBINED VARIANCES FOR       \n"
      "         MT852-859 CONSTRAINED TO EQUAL MT4 VARIANCES, I.E.,      \n"
      "         CONSISTENT WITH THOSE FROM THE (N,NT) V-C ANALYSIS.      \n"
      " MT=854  SINGLE LUMP OF MT=56 DETERMINED FROM SCATTER AND ERRORS  \n"
      "         OF EXPERIMENTAL DATA (SEE MF=3 DESCRIPTION).             \n"
      " MT=855  LUMP OF MT=57-61 DETERMINED AS DESCRIBED UNDER MT-853.   \n"
      " MT=856  LUMP OF MT=62-66 DETERMINED AS DESCRIBED UNDER MT-853.   \n"
      " MT=857  LUMP OF MT=67-71 DETERMINED AS DESCRIBED UNDER MT-853.   \n"
      " MT=858  LUMP OF MT=72-76 DETERMINED AS DESCRIBED UNDER MT-853.   \n"
      " MT=859  LUMP OF MT=77-82 DETERMINED AS DESCRIBED UNDER MT-853.   \n"
      " ***NOTE. THE PROCEDURE USED TO DETERMINE MT=852-859 HAS THE      \n"
      " ***RESULT THAT THESE MATRICES SUM ONLY APPROXIMATELY TO MT=4.    \n"
      " ***THEREFORE, IT IS RECOMMENDED THAT MT=852-859 BE USED ONLY FOR \n"
      " ***CALCULATING NEUTRON EMISSION SPECTRUM UNCERTAINTIES AND THAT  \n"
      " ***MT=1,2,4,25,102,104,851 BE USED FOR CALCULATING CROSS SECTION \n"
      " ***UNCERTAINTIES.                                                \n"
      "                                                                  \n"
      " *********** REFERENCES ******************************************\n"
      "                                                                  \n"
      "  AL82  V.ALFIMENKOV ET AL., JADERNAJA FIZIKA 35,542(1982).       \n"
      "  AR64  A.H.ARMSTRONG ET AL, NUCL.PHYS.52, 505(1964)              \n"
      "  AS58  V.J.ASHBY ET AL, UCRL-5239 (1958)                         \n"
      "  BA53  M.E.BATTAT, F.L.RIBE, PHYS.REV.89, 80(1953)               \n"
      "  BA63A R.BATCHELOR, J.H.TOWLE, NUCL.PHYS.47, 385(1963)           \n"
      "  BA63B J.F.BARRY, J.NUCL.ENER.A/B17, 273(1963)                   \n"
      "  BA79  M.BABA ET AL., CONF.NEUT.CROSS SECT.TECH., KNOXVILLE,1979 \n"
      "  BE60  J.BENVENISTE ET AL, UCRL-6074 (1960)                      \n"
      "  BI77  N.S.BIRJUKOV ET AL., A.E. 43, 176(1977).                  \n"
      "  BR58  A.BRATENAHL ET AL, PHYS.REV. 110,927 (1958)               \n"
      "  BR63  F.BROWN ET AL, J.NUCL.ENER.A/B17, 137(1963)               \n"
      "  CH61  D.M.CHITTENDEN, A-ARK-61, 1(1961)                         \n"
      "  CH85  S.CHIBA ET AL., J.NUC.SCI.& TECH. 22,771(1985).           \n"
      "  CO52  J.H.COON ET AL, PHYS.REV. 88,562 (1952)                   \n"
      "  CO67  J.A.COOKSON ET AL, NUCL.PHYS.A91, 273(1967)               \n"
      "  DE87  E.DEKEMPENEER ET AL., NSE 97,353(1987).                   \n"
      "  DI74  J.K.DICKENS ET AL, ORNL-TM-4538 (1974)                    \n"
      "  DR86  M.DROSG ET AL., RAD.EFFECTS 92,145(1986).                 \n"
      "  FI07  Data derived from the Evaluated Gamma-ray Activation File \n"
      "        (EGAF) as described in \"Database of Prompt Gamma Rays from\n"
      "        Slow Neutron Capture for Elemental Analysis\", R.B.        \n"
      "        Firestone, H.D. Choi, R.M. Lindstrom, G.L. Molnar, S.F.   \n"
      "        Mughabghab, R. Paviotti-Corcuera, Zs. Revay, V. Zerkin,   \n"
      "        and C.M. Zhou, IAEA Technical Report Series,              \n"
      "        STI/PUB/1263(2007)                                        \n"
      "  FO71  D.G.FOSTER,JR., D.W.GLASGOW, PHYS.REV. C3,576 (1971)      \n"
      "  FR55  J.M.FREEMAN ET AL, PHIL.MAG.46, 17(1955)                  \n"
      "  GL63  N.P.GLAZKOV, ATOMNAYA ENERGIYA 15, 416(1963)              \n"
      "  GO71  C.A.GOULDING ET AL, COO-3058-1 (1971)                     \n"
      "  GO85  E.GOLDBERG ET AL., NSE 91,173(1985).                      \n"
      "  HA75  D.R.HARRIS ET AL, LA-5987 (1975)                          \n"
      "  HE80  D.M.HETRICK, C.Y.FU, ORNL/TM-7341 (1980)                  \n"
      "  HI68  C.T.HIBDON, F.P.MOORING, CONF.NEUT.X/S.TECH,WASH(1968)P159\n"
      "  HA78  J.A.HARVEY ET AL, DOE/NDC-12/U (1978)P229                 \n"
      "  HO68  J.C.HOPKINS ET AL, NUCL.PHYS.107, 139(1968)               \n"
      "  HO79  H.H.HOGUE ET AL, NUCL.SCI.ENG.69, 22(1979)                \n"
      "  HY68  M.HYAKUTAKE ET AL, EANDC(J)-10 (1968)P22                  \n"
      "  IM59  W.IMHOF ET AL., PHYS.REV.114,1037(1959).                  \n"
      "  KA57  L.N.KATSAUROV ET AL, ATOM.ENER.SUPPL.5, 90(1957)          \n"
      "  KN68  H.-H.KNITTER, M.COPPOLA, CONF.NEUT.X/S.TECH,WASH(1968)P827\n"
      "  KN79  H.D.KNOX ET AL, NUCL.SCI.ENG.69, 223(1979)                \n"
      "  KN81  H.D.KNOX, R.O.LANE, NUCL.PHYS.A359, 131(1981)             \n"
      "  KO71  K.F.KORAL ET AL, NUCL.PHYS.A175, 156(1971)                \n"
      "  LA61  R.O.LANE ET AL, ANN.PHYSICS 12, 135(1961)                 \n"
      "  LA64  R.O.LANE ET AL, PHYS.REV.136, B1710(1964)                 \n"
      "  LA79  G.P.LAMAZE ET AL, BULL.AM.PHYS.SOC.24, 862(1979)          \n"
      "  LI73  R.H.LINDSAY ET AL, NUCL.PHYS.A199, 513(1973)              \n"
      "  LI80  P.W.LISOWSKI ET AL, LA-8342 (1980)                        \n"
      "  LI81  H.LISKIEN, A.PAULSEN, ANNALS NUCL.ENER.8, 423(1981)       \n"
      "  MA69  D.S.MATHER, L.F.PAIN, AWRE-O-47/69 (1969)                 \n"
      "  MA83  H.MAEKAWA ET AL., JAERI-M-83-196 (1983).                  \n"
      "  MA86  H.MAEKAWA ET AL., PERSONAL COMMUNICATION (1986).          \n"
      "  MC61  M.H.MCTAGGART, H.GOODFELLOW (AWRE), PERSONAL COMM.TO ,    \n"
      "             R.J.HOWERTON (1961)                                  \n"
      "  ME70  J.W.MEADOWS, J.F.WHALEN, NUCL.SCI.ENG. 41,351 (1970)      \n"
      "  MI61  M.MIKHAILINA ET AL, SOV.PROG.NEUT.PHYS. (1961)P185        \n"
      "  MO78  G.L.MORGAN, ORNL/TM-6247 (1978)                           \n"
      "  MU81  S.F.MUGHABGHAB ET AL., NEUTRON RES.PARAMETERS AND         \n"
      "             THERMAL CROSS SECT., ACADEMIC PRESS (1981) V1.       \n"
      "  OL80  D.K.OLSEN ET AL, NUCL.SCI.ENG.74, 219(1980)               \n"
      "  OS61  A.R.OSBORN, H.W.WILSON, AWRE-NR/C-1/61 (1961)             \n"
      "  PE60  J.M.PETERSON ET AL, PHYS.REV. 120,521 (1960)              \n"
      "  PR72  G.PRESSER, R.BASS, NUCL.PHYS.A182, 321(1972)              \n"
      "  QA86  S.M.QAIM, R.WOLFLE, NSE 96,52(1986).                      \n"
      "  RE66  V.REGIS ET AL, J.PHYSIQUE SUPPL.C1-84 (1966)              \n"
      "  RO62  L.ROSEN, L.STEWART, PHYS.REV.126, 1150(1962)              \n"
      "  SC87  D.SCHMIDT ET AL., NSE 96,159(1987).                       \n"
      "  SH84  G.SHEN ET AL.,NSE 86,184(1984).                           \n"
      "  SM76  D.L.SMITH, NUCL.SCI.ENG.61, 540(1976)                     \n"
      "  SM81  D.L.SMITH ET AL, NUCL.SCI.ENG.78, 359(1981)               \n"
      "  SM84  D.L.SMITH ET AL., ANL/NDM-87 (1984).                      \n"
      "  SW79  M.T.SWINHOE, C.A.UTTLEY, NBS SPEC.PUB.594, 246(1980)      \n"
      "  SW85  M.T.SWINHOE, C.A.UTTLEY, NSE 89,261(1985).                \n"
      "  TA84  A.TAKAHASHI ET AL., SYMP.FUSION TECH.,VARESE,ITALY (1984) \n"
      "             P.1325.                                              \n"
      "  TH56  R.G.THOMAS ET AL, PHYS.REV.101, 759(1956)                 \n"
      "  WI56  H.B.WILLARD ET AL, PHYS.REV.101, 765(1956)                \n"
      "  WO62  C.WONG ET AL, NUCL.PHYS.33, 680(1962)                     \n"
      "  WY58  M.E.WYMAN, M.M.THORPE, LA-2235 (1958)                     \n"
      "  YO65  A.YOSHIMURA ET AL (KYUSHU U.), PERSONAL COMM. NNDC (1965) \n"
      "  YO81  P.G.YOUNG, TRANS.AM.NUCL.SOC.39, 272(1981)                \n"
      "  YO88  P.G.YOUNG, INT.CONF.NUCL.DATA SCI.& TECH., MITO (1988).   \n"
      "                                                                  \n"
      " **************** Program DICTIN (VERSION 2012-1) ****************\n"
      " **************** Program DICTIN (VERSION 2015-2) ****************\n"
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
      " Delete Section if Cross Section =0 at All Energies-----------Yes \n"
      " **************** Program DICTIN (VERSION 2018-1) ****************\n";

    CHECK( 6.955732 == documentation.awr() );
    CHECK( 0 == documentation.library() );
    CHECK( std::make_pair( 8, 1 ) == documentation.version() );
    CHECK( description == documentation.description() );
  }

  void verifyTotalReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "1" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 38 == partials.size() );
    CHECK( id::ReactionID(   "2" ) == partials[0] );
    CHECK( id::ReactionID(  "16" ) == partials[1] );
    CHECK( id::ReactionID(  "24" ) == partials[2] );
    CHECK( id::ReactionID(  "25" ) == partials[3] );
    CHECK( id::ReactionID(  "51" ) == partials[4] );
    CHECK( id::ReactionID(  "52" ) == partials[5] );
    CHECK( id::ReactionID(  "53" ) == partials[6] );
    CHECK( id::ReactionID(  "54" ) == partials[7] );
    CHECK( id::ReactionID(  "55" ) == partials[8] );
    CHECK( id::ReactionID(  "56" ) == partials[9] );
    CHECK( id::ReactionID(  "57" ) == partials[10] );
    CHECK( id::ReactionID(  "58" ) == partials[11] );
    CHECK( id::ReactionID(  "59" ) == partials[12] );
    CHECK( id::ReactionID(  "60" ) == partials[13] );
    CHECK( id::ReactionID(  "61" ) == partials[14] );
    CHECK( id::ReactionID(  "62" ) == partials[15] );
    CHECK( id::ReactionID(  "63" ) == partials[16] );
    CHECK( id::ReactionID(  "64" ) == partials[17] );
    CHECK( id::ReactionID(  "65" ) == partials[18] );
    CHECK( id::ReactionID(  "66" ) == partials[19] );
    CHECK( id::ReactionID(  "67" ) == partials[20] );
    CHECK( id::ReactionID(  "68" ) == partials[21] );
    CHECK( id::ReactionID(  "69" ) == partials[22] );
    CHECK( id::ReactionID(  "70" ) == partials[23] );
    CHECK( id::ReactionID(  "71" ) == partials[24] );
    CHECK( id::ReactionID(  "72" ) == partials[25] );
    CHECK( id::ReactionID(  "73" ) == partials[26] );
    CHECK( id::ReactionID(  "74" ) == partials[27] );
    CHECK( id::ReactionID(  "75" ) == partials[28] );
    CHECK( id::ReactionID(  "76" ) == partials[29] );
    CHECK( id::ReactionID(  "77" ) == partials[30] );
    CHECK( id::ReactionID(  "78" ) == partials[31] );
    CHECK( id::ReactionID(  "79" ) == partials[32] );
    CHECK( id::ReactionID(  "80" ) == partials[33] );
    CHECK( id::ReactionID(  "81" ) == partials[34] );
    CHECK( id::ReactionID(  "82" ) == partials[35] );
    CHECK( id::ReactionID( "102" ) == partials[36] );
    CHECK( id::ReactionID( "104" ) == partials[37] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 537 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 537 == reaction.crossSection().energies().size() );
    CHECK( 537 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 536 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[536] ) );
    CHECK_THAT( 3.254     , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1.19328997, WithinRel( reaction.crossSection().values()[536] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyElasticReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "2" ) == reaction.identifier() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 0, WithinRel( reaction.massDifferenceQValue().value() ) );
    CHECK_THAT( 0, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 179 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 179 == reaction.crossSection().energies().size() );
    CHECK( 179 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 178 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[178] ) );
    CHECK_THAT( .97     , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .8637753, WithinRel( reaction.crossSection().values()[178] ) );

    CHECK( 1 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( true == neutron.isLinearised() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( true == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt != neutron.distributionData() );
    CHECK( true == std::holds_alternative< TwoBodyDistributionData >( neutron.distributionData().value() ) );
    auto data = std::get< TwoBodyDistributionData >( neutron.distributionData().value() );
    CHECK( DistributionDataType::TwoBody == data.type() );
    CHECK( true == std::holds_alternative< LegendreAngularDistributions >( data.angle() ) );
    auto angle = std::get< LegendreAngularDistributions >( data.angle() );
    CHECK( 75 == angle.numberPoints() );
    CHECK( 1 == angle.numberRegions() );
    CHECK( 75 == angle.grid().size() );
    CHECK( 75 == angle.distributions().size() );
    CHECK( 1 == angle.boundaries().size() );
    CHECK( 1 == angle.interpolants().size() );
    CHECK_THAT( 1e-5   , WithinRel( angle.grid()[0] ) );
    CHECK_THAT( 1e+4   , WithinRel( angle.grid()[1] ) );
    CHECK_THAT( 19e+6, WithinRel( angle.grid()[73] ) );
    CHECK_THAT( 20e+6, WithinRel( angle.grid()[74] ) );
    CHECK(  1 == angle.distributions()[0].pdf().coefficients().size() );
    CHECK(  1 == angle.distributions()[1].pdf().coefficients().size() );
    CHECK( 19 == angle.distributions()[73].pdf().coefficients().size() );
    CHECK( 19 == angle.distributions()[74].pdf().coefficients().size() );
    CHECK_THAT( 0.5         , WithinRel( angle.distributions()[0].pdf().coefficients()[0] ) );
    CHECK_THAT( 0.5         , WithinRel( angle.distributions()[1].pdf().coefficients()[0] ) );
    CHECK_THAT( 0.5         , WithinRel( angle.distributions()[73].pdf().coefficients()[0] ) );
    CHECK_THAT( 1.188585    , WithinRel( angle.distributions()[73].pdf().coefficients()[1] ) );
    CHECK_THAT( 1.829625e-07, WithinRel( angle.distributions()[73].pdf().coefficients()[17] ) );
    CHECK_THAT( 3.59381e-08 , WithinRel( angle.distributions()[73].pdf().coefficients()[18] ) );
    CHECK_THAT( 0.5         , WithinRel( angle.distributions()[74].pdf().coefficients()[0] ) );
    CHECK_THAT( 1.202805    , WithinRel( angle.distributions()[74].pdf().coefficients()[1] ) );
    CHECK_THAT( 3.224725e-07, WithinRel( angle.distributions()[74].pdf().coefficients()[17] ) );
    CHECK_THAT( 6.63336e-08 , WithinRel( angle.distributions()[74].pdf().coefficients()[18] ) );
    CHECK( 2 == angle.distributions()[0].cdf().coefficients().size() );
    CHECK( 2 == angle.distributions()[1].cdf().coefficients().size() );
    CHECK( 20 == angle.distributions()[73].cdf().coefficients().size() );
    CHECK( 20 == angle.distributions()[74].cdf().coefficients().size() );
    CHECK_THAT( 0.5       , WithinRel( angle.distributions()[0].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.5       , WithinRel( angle.distributions()[1].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.103805  , WithinRel( angle.distributions()[73].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.22273   , WithinRel( angle.distributions()[73].cdf().coefficients()[1] ) );
    CHECK_THAT( 5.2275e-09, WithinRel( angle.distributions()[73].cdf().coefficients()[18] ) );
    CHECK_THAT( 9.713e-10 , WithinRel( angle.distributions()[73].cdf().coefficients()[19] ) );
    CHECK_THAT( 0.099065  , WithinRel( angle.distributions()[74].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.21624   , WithinRel( angle.distributions()[74].cdf().coefficients()[1] ) );
    CHECK_THAT( 9.2135e-09, WithinRel( angle.distributions()[74].cdf().coefficients()[18] ) );
    CHECK_THAT( 1.7928e-09, WithinRel( angle.distributions()[74].cdf().coefficients()[19] ) );
    CHECK( 74 == angle.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );
  }

  void verifyCaptureReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "102" ) == reaction.identifier() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 2032800, WithinRel( reaction.massDifferenceQValue().value() ) );
    CHECK_THAT( 2032800, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 362 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 362 == reaction.crossSection().energies().size() );
    CHECK( 362 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 361 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1e-5       , WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1.090516E-5, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 16e+6      , WithinRel( reaction.crossSection().energies()[360] ) );
    CHECK_THAT( 20e+6      , WithinRel( reaction.crossSection().energies()[361] ) );
    CHECK_THAT( 2.284      , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 2.18715316 , WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 4.067041E-6, WithinRel( reaction.crossSection().values()[360] ) );
    CHECK_THAT( 4.E-6      , WithinRel( reaction.crossSection().values()[361] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction851( const Reaction& reaction ) {

    CHECK( id::ReactionID( "851" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 2 == partials.size() );
    CHECK( id::ReactionID( "16" ) == partials[0] );
    CHECK( id::ReactionID( "24" ) == partials[1] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 29 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 29 == reaction.crossSection().energies().size() );
    CHECK( 29 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 28 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 8.29288000e+06, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 8.5e+06       , WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.95e+7       , WithinRel( reaction.crossSection().energies()[27] ) );
    CHECK_THAT( 2e+7          , WithinRel( reaction.crossSection().energies()[28] ) );
    CHECK_THAT( 0.            , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 3.44833400e-04, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 7.20042300e-02, WithinRel( reaction.crossSection().values()[27] ) );
    CHECK_THAT( 7.52300000e-02, WithinRel( reaction.crossSection().values()[28] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction852( const Reaction& reaction ) {

    CHECK( id::ReactionID( "852" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 1 == partials.size() );
    CHECK( id::ReactionID( "51" ) == partials[0] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 134 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 134 == reaction.crossSection().energies().size() );
    CHECK( 134 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 133 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 5.46277000e+05, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 5.50000000e+05, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[132] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[133] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 5.90690000e-03, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 3.97335000e-02, WithinRel( reaction.crossSection().values()[132] ) );
    CHECK_THAT( 3.93590000e-02, WithinRel( reaction.crossSection().values()[133] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction853( const Reaction& reaction ) {

    CHECK( id::ReactionID( "853" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 4 == partials.size() );
    CHECK( id::ReactionID( "52" ) == partials[0] );
    CHECK( id::ReactionID( "53" ) == partials[1] );
    CHECK( id::ReactionID( "54" ) == partials[2] );
    CHECK( id::ReactionID( "55" ) == partials[3] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 95 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 95 == reaction.crossSection().energies().size() );
    CHECK( 95 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 94 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 3.14540000e+06, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 3.20000000e+06, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[93] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[94] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 9.67624500e-04, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 1.89748930e-03, WithinRel( reaction.crossSection().values()[93] ) );
    CHECK_THAT( 1.77996460e-03, WithinRel( reaction.crossSection().values()[94] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction854( const Reaction& reaction ) {

    CHECK( id::ReactionID( "854" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 1 == partials.size() );
    CHECK( id::ReactionID( "56" ) == partials[0] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 73 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 73 == reaction.crossSection().energies().size() );
    CHECK( 73 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 72 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 5295640.00, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 5300000.00, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 19730000.0, WithinRel( reaction.crossSection().energies()[71] ) );
    CHECK_THAT( 20000000.0, WithinRel( reaction.crossSection().energies()[72] ) );
    CHECK_THAT( 0.0       , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .003490122, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( .078823130, WithinRel( reaction.crossSection().values()[71] ) );
    CHECK_THAT( .078000000, WithinRel( reaction.crossSection().values()[72] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction855( const Reaction& reaction ) {

    CHECK( id::ReactionID( "855" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 5 == partials.size() );
    CHECK( id::ReactionID( "57" ) == partials[0] );
    CHECK( id::ReactionID( "58" ) == partials[1] );
    CHECK( id::ReactionID( "59" ) == partials[2] );
    CHECK( id::ReactionID( "60" ) == partials[3] );
    CHECK( id::ReactionID( "61" ) == partials[4] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 68 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 68 == reaction.crossSection().energies().size() );
    CHECK( 68 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 67 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 5.43290000e+06, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 5.50000000e+06, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[66] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[67] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 7.59054300e-03, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 9.16765500e-03, WithinRel( reaction.crossSection().values()[66] ) );
    CHECK_THAT( 8.56193900e-03, WithinRel( reaction.crossSection().values()[67] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction856( const Reaction& reaction ) {

    CHECK( id::ReactionID( "856" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 5 == partials.size() );
    CHECK( id::ReactionID( "62" ) == partials[0] );
    CHECK( id::ReactionID( "63" ) == partials[1] );
    CHECK( id::ReactionID( "64" ) == partials[2] );
    CHECK( id::ReactionID( "65" ) == partials[3] );
    CHECK( id::ReactionID( "66" ) == partials[4] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 48 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 48 == reaction.crossSection().energies().size() );
    CHECK( 48 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 47 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 8.29230000e+06, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 8.50000000e+06, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[46] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[47] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 8.22307000e-03, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 1.91613490e-02, WithinRel( reaction.crossSection().values()[46] ) );
    CHECK_THAT( 1.79659390e-02, WithinRel( reaction.crossSection().values()[47] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction857( const Reaction& reaction ) {

    CHECK( id::ReactionID( "857" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 5 == partials.size() );
    CHECK( id::ReactionID( "67" ) == partials[0] );
    CHECK( id::ReactionID( "68" ) == partials[1] );
    CHECK( id::ReactionID( "69" ) == partials[2] );
    CHECK( id::ReactionID( "70" ) == partials[3] );
    CHECK( id::ReactionID( "71" ) == partials[4] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 34 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 34 == reaction.crossSection().energies().size() );
    CHECK( 34 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 33 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1.11520000e+07, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1.15000000e+07, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[32] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[33] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1.02849900e-02, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 2.38844240e-02, WithinRel( reaction.crossSection().values()[32] ) );
    CHECK_THAT( 2.27516480e-02, WithinRel( reaction.crossSection().values()[33] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction858( const Reaction& reaction ) {

    CHECK( id::ReactionID( "858" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 5 == partials.size() );
    CHECK( id::ReactionID( "72" ) == partials[0] );
    CHECK( id::ReactionID( "73" ) == partials[1] );
    CHECK( id::ReactionID( "74" ) == partials[2] );
    CHECK( id::ReactionID( "75" ) == partials[3] );
    CHECK( id::ReactionID( "76" ) == partials[4] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 23 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 23 == reaction.crossSection().energies().size() );
    CHECK( 23 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 22 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1.40110000e+07, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1.45000000e+07, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[21] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[22] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1.20486300e-02, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 3.05346270e-02, WithinRel( reaction.crossSection().values()[21] ) );
    CHECK_THAT( 2.84387580e-02, WithinRel( reaction.crossSection().values()[22] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumpedReaction859( const Reaction& reaction ) {

    CHECK( id::ReactionID( "859" ) == reaction.identifier() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );
    CHECK( true == reaction.isLinearised() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 6 == partials.size() );
    CHECK( id::ReactionID( "77" ) == partials[0] );
    CHECK( id::ReactionID( "78" ) == partials[1] );
    CHECK( id::ReactionID( "79" ) == partials[2] );
    CHECK( id::ReactionID( "80" ) == partials[3] );
    CHECK( id::ReactionID( "81" ) == partials[4] );
    CHECK( id::ReactionID( "82" ) == partials[5] );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 13 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 13 == reaction.crossSection().energies().size() );
    CHECK( 13 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 12 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1.68710000e+07, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1.70000000e+07, WithinRel( reaction.crossSection().energies()[1] ) );
    CHECK_THAT( 1.97300000e+07, WithinRel( reaction.crossSection().energies()[11] ) );
    CHECK_THAT( 2.00000000e+07, WithinRel( reaction.crossSection().energies()[12] ) );
    CHECK_THAT( 0.00000000e+00, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1.78534600e-03, WithinRel( reaction.crossSection().values()[1] ) );
    CHECK_THAT( 3.55291340e-02, WithinRel( reaction.crossSection().values()[11] ) );
    CHECK_THAT( 3.76534200e-02, WithinRel( reaction.crossSection().values()[12] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

} // namespace h1
} // namespace neutron
