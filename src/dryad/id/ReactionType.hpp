#ifndef NJOY_DRYAD_ID_REACTIONTYPE
#define NJOY_DRYAD_ID_REACTIONTYPE

// system includes
#include <cstdint>
#include <optional>
#include <string>
#include <numeric>
#include <map>
#include <unordered_map>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/InteractionType.hpp"
#include "dryad/id/ElectronSubshellID.hpp"
#include "dryad/id/LevelID.hpp"
#include "dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace id {

  /**
   *  @class
   *  @brief The reaction types, with associated symbol, aliases, particles, etc.
   *
   *  The ReactionType can be used to identify reaction types. For the moment, only
   *  registered types can be used. In the future, we will extend this so that users
   *  can create types other than the ones currently registered.
   *
   *  For more information on how to create instances of ReactionType, see the
   *  Jupyter notebook dryad-identifiers.ipynb under python/examples.
   */
  class ReactionType {

    /* helper class */
    #include "dryad/id/ReactionType/Entry.hpp"

    static inline std::vector< Entry > entries{

      // nuclear reaction types

      // special types: reactions without ejectiles, unknown number and/or types of ejectiles, or with
      // ejectiles that depend on the projectile
      Entry{          1,   1, InteractionType::Nuclear, { "total", "total[nuclear]" } },
      Entry{          3,   3, InteractionType::Nuclear, { "non-elastic" } },
      Entry{          5,   5, InteractionType::Nuclear, { "anything" } },
      Entry{         18,  18, InteractionType::Nuclear, { "fission(t)", "fission" } },
      Entry{         19,  19, InteractionType::Nuclear, { "fission[first]", "fission1" } },
      Entry{         20,  20, InteractionType::Nuclear, { "fission[second]", "fission2" } },
      Entry{         21,  21, InteractionType::Nuclear, { "fission[third]", "fission3" } },
      Entry{         38,  38, InteractionType::Nuclear, { "fission[fourth]", "fission4" } },
      Entry{         27,  27, InteractionType::Nuclear, { "absorption" } },
      Entry{        101, 101, InteractionType::Nuclear, { "disappearance" } },
      Entry{        851, 851, InteractionType::Nuclear, { "lumped1" } },
      Entry{        852, 852, InteractionType::Nuclear, { "lumped2" } },
      Entry{        853, 853, InteractionType::Nuclear, { "lumped3" } },
      Entry{        854, 854, InteractionType::Nuclear, { "lumped4" } },
      Entry{        855, 855, InteractionType::Nuclear, { "lumped5" } },
      Entry{        856, 856, InteractionType::Nuclear, { "lumped6" } },
      Entry{        857, 857, InteractionType::Nuclear, { "lumped7" } },
      Entry{        858, 858, InteractionType::Nuclear, { "lumped8" } },
      Entry{        859, 859, InteractionType::Nuclear, { "lumped9" } },
      Entry{        860, 860, InteractionType::Nuclear, { "lumped10" } },
      Entry{        861, 861, InteractionType::Nuclear, { "lumped11" } },
      Entry{        862, 862, InteractionType::Nuclear, { "lumped12" } },
      Entry{        863, 863, InteractionType::Nuclear, { "lumped13" } },
      Entry{        864, 864, InteractionType::Nuclear, { "lumped14" } },
      Entry{        865, 865, InteractionType::Nuclear, { "lumped15" } },
      Entry{        866, 866, InteractionType::Nuclear, { "lumped16" } },
      Entry{        867, 867, InteractionType::Nuclear, { "lumped17" } },
      Entry{        868, 868, InteractionType::Nuclear, { "lumped18" } },
      Entry{        869, 869, InteractionType::Nuclear, { "lumped19" } },
      Entry{        870, 870, InteractionType::Nuclear, { "lumped20" } },

      // normal reactions: reactions with ejectiles (not counting photons and residual)
      // all these must have a final excited state set for the residual
      Entry{       1000,      InteractionType::Nuclear, { "g(0)"  }                                     , {}, 0 },
      Entry{       1001,      InteractionType::Nuclear, { "g(1)"  }                                     , {}, 1 },
      Entry{       1002,      InteractionType::Nuclear, { "g(2)"  }                                     , {}, 2 },
      Entry{       1003,      InteractionType::Nuclear, { "g(3)"  }                                     , {}, 3 },
      Entry{       1004,      InteractionType::Nuclear, { "g(4)"  }                                     , {}, 4 },
      Entry{       1005,      InteractionType::Nuclear, { "g(5)"  }                                     , {}, 5 },
      Entry{       1006,      InteractionType::Nuclear, { "g(6)"  }                                     , {}, 6 },
      Entry{       1007,      InteractionType::Nuclear, { "g(7)"  }                                     , {}, 7 },
      Entry{       1008,      InteractionType::Nuclear, { "g(8)"  }                                     , {}, 8 },
      Entry{       1009,      InteractionType::Nuclear, { "g(9)"  }                                     , {}, 9 },
      Entry{       1010,      InteractionType::Nuclear, { "g(10)" }                                     , {}, 10 },
      Entry{       1011,      InteractionType::Nuclear, { "g(11)" }                                     , {}, 11 },
      Entry{       1012,      InteractionType::Nuclear, { "g(12)" }                                     , {}, 12 },
      Entry{       1013,      InteractionType::Nuclear, { "g(13)" }                                     , {}, 13 },
      Entry{       1014,      InteractionType::Nuclear, { "g(14)" }                                     , {}, 14 },
      Entry{       1015,      InteractionType::Nuclear, { "g(15)" }                                     , {}, 15 },
      Entry{       1016,      InteractionType::Nuclear, { "g(16)" }                                     , {}, 16 },
      Entry{       1017,      InteractionType::Nuclear, { "g(17)" }                                     , {}, 17 },
      Entry{       1018,      InteractionType::Nuclear, { "g(18)" }                                     , {}, 18 },
      Entry{       1019,      InteractionType::Nuclear, { "g(19)" }                                     , {}, 19 },
      Entry{       1020,      InteractionType::Nuclear, { "g(20)" }                                     , {}, 20 },
      Entry{       1021,      InteractionType::Nuclear, { "g(21)" }                                     , {}, 21 },
      Entry{       1022,      InteractionType::Nuclear, { "g(22)" }                                     , {}, 22 },
      Entry{       1023,      InteractionType::Nuclear, { "g(23)" }                                     , {}, 23 },
      Entry{       1024,      InteractionType::Nuclear, { "g(24)" }                                     , {}, 24 },
      Entry{       1025,      InteractionType::Nuclear, { "g(25)" }                                     , {}, 25 },
      Entry{       1026,      InteractionType::Nuclear, { "g(26)" }                                     , {}, 26 },
      Entry{       1027,      InteractionType::Nuclear, { "g(27)" }                                     , {}, 27 },
      Entry{       1028,      InteractionType::Nuclear, { "g(28)" }                                     , {}, 28 },
      Entry{       1029,      InteractionType::Nuclear, { "g(29)" }                                     , {}, 29 },
      Entry{       1030,      InteractionType::Nuclear, { "g(30)" }                                     , {}, 30 },
      Entry{       1031,      InteractionType::Nuclear, { "g(31)" }                                     , {}, 31 },
      Entry{       1032,      InteractionType::Nuclear, { "g(32)" }                                     , {}, 32 },
      Entry{       1033,      InteractionType::Nuclear, { "g(33)" }                                     , {}, 33 },
      Entry{       1034,      InteractionType::Nuclear, { "g(34)" }                                     , {}, 34 },
      Entry{       1035,      InteractionType::Nuclear, { "g(35)" }                                     , {}, 35 },
      Entry{       1036,      InteractionType::Nuclear, { "g(36)" }                                     , {}, 36 },
      Entry{       1037,      InteractionType::Nuclear, { "g(37)" }                                     , {}, 37 },
      Entry{       1038,      InteractionType::Nuclear, { "g(38)" }                                     , {}, 38 },
      Entry{       1039,      InteractionType::Nuclear, { "g(39)" }                                     , {}, 39 },
      Entry{       1040,      InteractionType::Nuclear, { "g(40)" }                                     , {}, 40 },
      Entry{       1041,      InteractionType::Nuclear, { "g(41)" }                                     , {}, 41 },
      Entry{       1042,      InteractionType::Nuclear, { "g(42)" }                                     , {}, 42 },
      Entry{       1043,      InteractionType::Nuclear, { "g(43)" }                                     , {}, 43 },
      Entry{       1044,      InteractionType::Nuclear, { "g(44)" }                                     , {}, 44 },
      Entry{       1045,      InteractionType::Nuclear, { "g(45)" }                                     , {}, 45 },
      Entry{       1046,      InteractionType::Nuclear, { "g(46)" }                                     , {}, 46 },
      Entry{       1047,      InteractionType::Nuclear, { "g(47)" }                                     , {}, 47 },
      Entry{       1048,      InteractionType::Nuclear, { "g(48)" }                                     , {}, 48 },
      Entry{       1049,      InteractionType::Nuclear, { "g(49)" }                                     , {}, 49 },
      Entry{       1050,      InteractionType::Nuclear, { "g(50)" }                                     , {}, 50 },
      Entry{       1051,      InteractionType::Nuclear, { "g(51)" }                                     , {}, 51 },
      Entry{       1052,      InteractionType::Nuclear, { "g(52)" }                                     , {}, 52 },
      Entry{       1053,      InteractionType::Nuclear, { "g(53)" }                                     , {}, 53 },
      Entry{       1054,      InteractionType::Nuclear, { "g(54)" }                                     , {}, 54 },
      Entry{       1055,      InteractionType::Nuclear, { "g(55)" }                                     , {}, 55 },
      Entry{       1056,      InteractionType::Nuclear, { "g(56)" }                                     , {}, 56 },
      Entry{       1057,      InteractionType::Nuclear, { "g(57)" }                                     , {}, 57 },
      Entry{       1058,      InteractionType::Nuclear, { "g(58)" }                                     , {}, 58 },
      Entry{       1059,      InteractionType::Nuclear, { "g(59)" }                                     , {}, 59 },
      Entry{       1060,      InteractionType::Nuclear, { "g(60)" }                                     , {}, 60 },
      Entry{       1061,      InteractionType::Nuclear, { "g(61)" }                                     , {}, 61 },
      Entry{       1062,      InteractionType::Nuclear, { "g(62)" }                                     , {}, 62 },
      Entry{       1063,      InteractionType::Nuclear, { "g(63)" }                                     , {}, 63 },
      Entry{       1064,      InteractionType::Nuclear, { "g(64)" }                                     , {}, 64 },
      Entry{       1065,      InteractionType::Nuclear, { "g(65)" }                                     , {}, 65 },
      Entry{       1066,      InteractionType::Nuclear, { "g(66)" }                                     , {}, 66 },
      Entry{       1067,      InteractionType::Nuclear, { "g(67)" }                                     , {}, 67 },
      Entry{       1068,      InteractionType::Nuclear, { "g(68)" }                                     , {}, 68 },
      Entry{       1069,      InteractionType::Nuclear, { "g(69)" }                                     , {}, 69 },
      Entry{       1070,      InteractionType::Nuclear, { "g(70)" }                                     , {}, 70 },
      Entry{       1071,      InteractionType::Nuclear, { "g(71)" }                                     , {}, 71 },
      Entry{       1072,      InteractionType::Nuclear, { "g(72)" }                                     , {}, 72 },
      Entry{       1073,      InteractionType::Nuclear, { "g(73)" }                                     , {}, 73 },
      Entry{       1074,      InteractionType::Nuclear, { "g(74)" }                                     , {}, 74 },
      Entry{       1075,      InteractionType::Nuclear, { "g(75)" }                                     , {}, 75 },
      Entry{       1076,      InteractionType::Nuclear, { "g(76)" }                                     , {}, 76 },
      Entry{       1077,      InteractionType::Nuclear, { "g(77)" }                                     , {}, 77 },
      Entry{       1078,      InteractionType::Nuclear, { "g(78)" }                                     , {}, 78 },
      Entry{       1079,      InteractionType::Nuclear, { "g(79)" }                                     , {}, 79 },
      Entry{       1080,      InteractionType::Nuclear, { "g(80)" }                                     , {}, 80 },
      Entry{       1081,      InteractionType::Nuclear, { "g(81)" }                                     , {}, 81 },
      Entry{       1082,      InteractionType::Nuclear, { "g(82)" }                                     , {}, 82 },
      Entry{       1083,      InteractionType::Nuclear, { "g(83)" }                                     , {}, 83 },
      Entry{       1084,      InteractionType::Nuclear, { "g(84)" }                                     , {}, 84 },
      Entry{       1085,      InteractionType::Nuclear, { "g(85)" }                                     , {}, 85 },
      Entry{       1086,      InteractionType::Nuclear, { "g(86)" }                                     , {}, 86 },
      Entry{       1087,      InteractionType::Nuclear, { "g(87)" }                                     , {}, 87 },
      Entry{       1088,      InteractionType::Nuclear, { "g(88)" }                                     , {}, 88 },
      Entry{       1089,      InteractionType::Nuclear, { "g(89)" }                                     , {}, 89 },
      Entry{       1090,      InteractionType::Nuclear, { "g(90)" }                                     , {}, 90 },
      Entry{       1091,      InteractionType::Nuclear, { "g(91)" }                                     , {}, 91 },
      Entry{       1092,      InteractionType::Nuclear, { "g(92)" }                                     , {}, 92 },
      Entry{       1093,      InteractionType::Nuclear, { "g(93)" }                                     , {}, 93 },
      Entry{       1094,      InteractionType::Nuclear, { "g(94)" }                                     , {}, 94 },
      Entry{       1095,      InteractionType::Nuclear, { "g(95)" }                                     , {}, 95 },
      Entry{       1096,      InteractionType::Nuclear, { "g(96)" }                                     , {}, 96 },
      Entry{       1097,      InteractionType::Nuclear, { "g(97)" }                                     , {}, 97 },
      Entry{       1098,      InteractionType::Nuclear, { "g(98)" }                                     , {}, 98 },
      Entry{       1099,      InteractionType::Nuclear, { "g(99)" }                                     , {}, 99 },
      Entry{       1150,      InteractionType::Nuclear, { "g(c)" }                                      , {}, LevelID::continuum },
      Entry{       1151, 102, InteractionType::Nuclear, { "g(t)", "capture", "g" }                      , {}, LevelID::all },

      Entry{      10000,  50, InteractionType::Nuclear, { "n(0)" }                                      , { { ParticleID::neutron(), 1 } }, 0 },
      Entry{      10001,  51, InteractionType::Nuclear, { "n(1)" }                                      , { { ParticleID::neutron(), 1 } }, 1 },
      Entry{      10002,  52, InteractionType::Nuclear, { "n(2)" }                                      , { { ParticleID::neutron(), 1 } }, 2 },
      Entry{      10003,  53, InteractionType::Nuclear, { "n(3)" }                                      , { { ParticleID::neutron(), 1 } }, 3 },
      Entry{      10004,  54, InteractionType::Nuclear, { "n(4)" }                                      , { { ParticleID::neutron(), 1 } }, 4 },
      Entry{      10005,  55, InteractionType::Nuclear, { "n(5)" }                                      , { { ParticleID::neutron(), 1 } }, 5 },
      Entry{      10006,  56, InteractionType::Nuclear, { "n(6)" }                                      , { { ParticleID::neutron(), 1 } }, 6 },
      Entry{      10007,  57, InteractionType::Nuclear, { "n(7)" }                                      , { { ParticleID::neutron(), 1 } }, 7 },
      Entry{      10008,  58, InteractionType::Nuclear, { "n(8)" }                                      , { { ParticleID::neutron(), 1 } }, 8 },
      Entry{      10009,  59, InteractionType::Nuclear, { "n(9)" }                                      , { { ParticleID::neutron(), 1 } }, 9 },
      Entry{      10010,  60, InteractionType::Nuclear, { "n(10)" }                                     , { { ParticleID::neutron(), 1 } }, 10 },
      Entry{      10011,  61, InteractionType::Nuclear, { "n(11)" }                                     , { { ParticleID::neutron(), 1 } }, 11 },
      Entry{      10012,  62, InteractionType::Nuclear, { "n(12)" }                                     , { { ParticleID::neutron(), 1 } }, 12 },
      Entry{      10013,  63, InteractionType::Nuclear, { "n(13)" }                                     , { { ParticleID::neutron(), 1 } }, 13 },
      Entry{      10014,  64, InteractionType::Nuclear, { "n(14)" }                                     , { { ParticleID::neutron(), 1 } }, 14 },
      Entry{      10015,  65, InteractionType::Nuclear, { "n(15)" }                                     , { { ParticleID::neutron(), 1 } }, 15 },
      Entry{      10016,  66, InteractionType::Nuclear, { "n(16)" }                                     , { { ParticleID::neutron(), 1 } }, 16 },
      Entry{      10017,  67, InteractionType::Nuclear, { "n(17)" }                                     , { { ParticleID::neutron(), 1 } }, 17 },
      Entry{      10018,  68, InteractionType::Nuclear, { "n(18)" }                                     , { { ParticleID::neutron(), 1 } }, 18 },
      Entry{      10019,  69, InteractionType::Nuclear, { "n(19)" }                                     , { { ParticleID::neutron(), 1 } }, 19 },
      Entry{      10020,  70, InteractionType::Nuclear, { "n(20)" }                                     , { { ParticleID::neutron(), 1 } }, 20 },
      Entry{      10021,  71, InteractionType::Nuclear, { "n(21)" }                                     , { { ParticleID::neutron(), 1 } }, 21 },
      Entry{      10022,  72, InteractionType::Nuclear, { "n(22)" }                                     , { { ParticleID::neutron(), 1 } }, 22 },
      Entry{      10023,  73, InteractionType::Nuclear, { "n(23)" }                                     , { { ParticleID::neutron(), 1 } }, 23 },
      Entry{      10024,  74, InteractionType::Nuclear, { "n(24)" }                                     , { { ParticleID::neutron(), 1 } }, 24 },
      Entry{      10025,  75, InteractionType::Nuclear, { "n(25)" }                                     , { { ParticleID::neutron(), 1 } }, 25 },
      Entry{      10026,  76, InteractionType::Nuclear, { "n(26)" }                                     , { { ParticleID::neutron(), 1 } }, 26 },
      Entry{      10027,  77, InteractionType::Nuclear, { "n(27)" }                                     , { { ParticleID::neutron(), 1 } }, 27 },
      Entry{      10028,  78, InteractionType::Nuclear, { "n(28)" }                                     , { { ParticleID::neutron(), 1 } }, 28 },
      Entry{      10029,  79, InteractionType::Nuclear, { "n(29)" }                                     , { { ParticleID::neutron(), 1 } }, 29 },
      Entry{      10030,  80, InteractionType::Nuclear, { "n(30)" }                                     , { { ParticleID::neutron(), 1 } }, 30 },
      Entry{      10031,  81, InteractionType::Nuclear, { "n(31)" }                                     , { { ParticleID::neutron(), 1 } }, 31 },
      Entry{      10032,  82, InteractionType::Nuclear, { "n(32)" }                                     , { { ParticleID::neutron(), 1 } }, 32 },
      Entry{      10033,  83, InteractionType::Nuclear, { "n(33)" }                                     , { { ParticleID::neutron(), 1 } }, 33 },
      Entry{      10034,  84, InteractionType::Nuclear, { "n(34)" }                                     , { { ParticleID::neutron(), 1 } }, 34 },
      Entry{      10035,  85, InteractionType::Nuclear, { "n(35)" }                                     , { { ParticleID::neutron(), 1 } }, 35 },
      Entry{      10036,  86, InteractionType::Nuclear, { "n(36)" }                                     , { { ParticleID::neutron(), 1 } }, 36 },
      Entry{      10037,  87, InteractionType::Nuclear, { "n(37)" }                                     , { { ParticleID::neutron(), 1 } }, 37 },
      Entry{      10038,  88, InteractionType::Nuclear, { "n(38)" }                                     , { { ParticleID::neutron(), 1 } }, 38 },
      Entry{      10039,  89, InteractionType::Nuclear, { "n(39)" }                                     , { { ParticleID::neutron(), 1 } }, 39 },
      Entry{      10040,  90, InteractionType::Nuclear, { "n(40)" }                                     , { { ParticleID::neutron(), 1 } }, 40 },
      Entry{      10041,      InteractionType::Nuclear, { "n(41)" }                                     , { { ParticleID::neutron(), 1 } }, 41 },
      Entry{      10042,      InteractionType::Nuclear, { "n(42)" }                                     , { { ParticleID::neutron(), 1 } }, 42 },
      Entry{      10043,      InteractionType::Nuclear, { "n(43)" }                                     , { { ParticleID::neutron(), 1 } }, 43 },
      Entry{      10044,      InteractionType::Nuclear, { "n(44)" }                                     , { { ParticleID::neutron(), 1 } }, 44 },
      Entry{      10045,      InteractionType::Nuclear, { "n(45)" }                                     , { { ParticleID::neutron(), 1 } }, 45 },
      Entry{      10046,      InteractionType::Nuclear, { "n(46)" }                                     , { { ParticleID::neutron(), 1 } }, 46 },
      Entry{      10047,      InteractionType::Nuclear, { "n(47)" }                                     , { { ParticleID::neutron(), 1 } }, 47 },
      Entry{      10048,      InteractionType::Nuclear, { "n(48)" }                                     , { { ParticleID::neutron(), 1 } }, 48 },
      Entry{      10049,      InteractionType::Nuclear, { "n(49)" }                                     , { { ParticleID::neutron(), 1 } }, 49 },
      Entry{      10050,      InteractionType::Nuclear, { "n(50)" }                                     , { { ParticleID::neutron(), 1 } }, 50 },
      Entry{      10051,      InteractionType::Nuclear, { "n(51)" }                                     , { { ParticleID::neutron(), 1 } }, 51 },
      Entry{      10052,      InteractionType::Nuclear, { "n(52)" }                                     , { { ParticleID::neutron(), 1 } }, 52 },
      Entry{      10053,      InteractionType::Nuclear, { "n(53)" }                                     , { { ParticleID::neutron(), 1 } }, 53 },
      Entry{      10054,      InteractionType::Nuclear, { "n(54)" }                                     , { { ParticleID::neutron(), 1 } }, 54 },
      Entry{      10055,      InteractionType::Nuclear, { "n(55)" }                                     , { { ParticleID::neutron(), 1 } }, 55 },
      Entry{      10056,      InteractionType::Nuclear, { "n(56)" }                                     , { { ParticleID::neutron(), 1 } }, 56 },
      Entry{      10057,      InteractionType::Nuclear, { "n(57)" }                                     , { { ParticleID::neutron(), 1 } }, 57 },
      Entry{      10058,      InteractionType::Nuclear, { "n(58)" }                                     , { { ParticleID::neutron(), 1 } }, 58 },
      Entry{      10059,      InteractionType::Nuclear, { "n(59)" }                                     , { { ParticleID::neutron(), 1 } }, 59 },
      Entry{      10060,      InteractionType::Nuclear, { "n(60)" }                                     , { { ParticleID::neutron(), 1 } }, 60 },
      Entry{      10061,      InteractionType::Nuclear, { "n(61)" }                                     , { { ParticleID::neutron(), 1 } }, 61 },
      Entry{      10062,      InteractionType::Nuclear, { "n(62)" }                                     , { { ParticleID::neutron(), 1 } }, 62 },
      Entry{      10063,      InteractionType::Nuclear, { "n(63)" }                                     , { { ParticleID::neutron(), 1 } }, 63 },
      Entry{      10064,      InteractionType::Nuclear, { "n(64)" }                                     , { { ParticleID::neutron(), 1 } }, 64 },
      Entry{      10065,      InteractionType::Nuclear, { "n(65)" }                                     , { { ParticleID::neutron(), 1 } }, 65 },
      Entry{      10066,      InteractionType::Nuclear, { "n(66)" }                                     , { { ParticleID::neutron(), 1 } }, 66 },
      Entry{      10067,      InteractionType::Nuclear, { "n(67)" }                                     , { { ParticleID::neutron(), 1 } }, 67 },
      Entry{      10068,      InteractionType::Nuclear, { "n(68)" }                                     , { { ParticleID::neutron(), 1 } }, 68 },
      Entry{      10069,      InteractionType::Nuclear, { "n(69)" }                                     , { { ParticleID::neutron(), 1 } }, 69 },
      Entry{      10070,      InteractionType::Nuclear, { "n(70)" }                                     , { { ParticleID::neutron(), 1 } }, 70 },
      Entry{      10071,      InteractionType::Nuclear, { "n(71)" }                                     , { { ParticleID::neutron(), 1 } }, 71 },
      Entry{      10072,      InteractionType::Nuclear, { "n(72)" }                                     , { { ParticleID::neutron(), 1 } }, 72 },
      Entry{      10073,      InteractionType::Nuclear, { "n(73)" }                                     , { { ParticleID::neutron(), 1 } }, 73 },
      Entry{      10074,      InteractionType::Nuclear, { "n(74)" }                                     , { { ParticleID::neutron(), 1 } }, 74 },
      Entry{      10075,      InteractionType::Nuclear, { "n(75)" }                                     , { { ParticleID::neutron(), 1 } }, 75 },
      Entry{      10076,      InteractionType::Nuclear, { "n(76)" }                                     , { { ParticleID::neutron(), 1 } }, 76 },
      Entry{      10077,      InteractionType::Nuclear, { "n(77)" }                                     , { { ParticleID::neutron(), 1 } }, 77 },
      Entry{      10078,      InteractionType::Nuclear, { "n(78)" }                                     , { { ParticleID::neutron(), 1 } }, 78 },
      Entry{      10079,      InteractionType::Nuclear, { "n(79)" }                                     , { { ParticleID::neutron(), 1 } }, 79 },
      Entry{      10080,      InteractionType::Nuclear, { "n(80)" }                                     , { { ParticleID::neutron(), 1 } }, 80 },
      Entry{      10081,      InteractionType::Nuclear, { "n(81)" }                                     , { { ParticleID::neutron(), 1 } }, 81 },
      Entry{      10082,      InteractionType::Nuclear, { "n(82)" }                                     , { { ParticleID::neutron(), 1 } }, 82 },
      Entry{      10083,      InteractionType::Nuclear, { "n(83)" }                                     , { { ParticleID::neutron(), 1 } }, 83 },
      Entry{      10084,      InteractionType::Nuclear, { "n(84)" }                                     , { { ParticleID::neutron(), 1 } }, 84 },
      Entry{      10085,      InteractionType::Nuclear, { "n(85)" }                                     , { { ParticleID::neutron(), 1 } }, 85 },
      Entry{      10086,      InteractionType::Nuclear, { "n(86)" }                                     , { { ParticleID::neutron(), 1 } }, 86 },
      Entry{      10087,      InteractionType::Nuclear, { "n(87)" }                                     , { { ParticleID::neutron(), 1 } }, 87 },
      Entry{      10088,      InteractionType::Nuclear, { "n(88)" }                                     , { { ParticleID::neutron(), 1 } }, 88 },
      Entry{      10089,      InteractionType::Nuclear, { "n(89)" }                                     , { { ParticleID::neutron(), 1 } }, 89 },
      Entry{      10090,      InteractionType::Nuclear, { "n(90)" }                                     , { { ParticleID::neutron(), 1 } }, 90 },
      Entry{      10091,      InteractionType::Nuclear, { "n(91)" }                                     , { { ParticleID::neutron(), 1 } }, 91 },
      Entry{      10092,      InteractionType::Nuclear, { "n(92)" }                                     , { { ParticleID::neutron(), 1 } }, 92 },
      Entry{      10093,      InteractionType::Nuclear, { "n(93)" }                                     , { { ParticleID::neutron(), 1 } }, 93 },
      Entry{      10094,      InteractionType::Nuclear, { "n(94)" }                                     , { { ParticleID::neutron(), 1 } }, 94 },
      Entry{      10095,      InteractionType::Nuclear, { "n(95)" }                                     , { { ParticleID::neutron(), 1 } }, 95 },
      Entry{      10096,      InteractionType::Nuclear, { "n(96)" }                                     , { { ParticleID::neutron(), 1 } }, 96 },
      Entry{      10097,      InteractionType::Nuclear, { "n(97)" }                                     , { { ParticleID::neutron(), 1 } }, 97 },
      Entry{      10098,      InteractionType::Nuclear, { "n(98)" }                                     , { { ParticleID::neutron(), 1 } }, 98 },
      Entry{      10099,      InteractionType::Nuclear, { "n(99)" }                                     , { { ParticleID::neutron(), 1 } }, 99 },
      Entry{      10150,  91, InteractionType::Nuclear, { "n(c)" }                                      , { { ParticleID::neutron(), 1 } }, LevelID::continuum },
      Entry{      10151,   4, InteractionType::Nuclear, { "n(t)", "n" }                                 , { { ParticleID::neutron(), 1 } }, LevelID::all },

      Entry{      20000, 875, InteractionType::Nuclear, { "2n(0)" }                                     , { { ParticleID::neutron(), 2 } }, 0 },
      Entry{      20001, 876, InteractionType::Nuclear, { "2n(1)" }                                     , { { ParticleID::neutron(), 2 } }, 1 },
      Entry{      20002, 877, InteractionType::Nuclear, { "2n(2)" }                                     , { { ParticleID::neutron(), 2 } }, 2 },
      Entry{      20003, 878, InteractionType::Nuclear, { "2n(3)" }                                     , { { ParticleID::neutron(), 2 } }, 3 },
      Entry{      20004, 879, InteractionType::Nuclear, { "2n(4)" }                                     , { { ParticleID::neutron(), 2 } }, 4 },
      Entry{      20005, 880, InteractionType::Nuclear, { "2n(5)" }                                     , { { ParticleID::neutron(), 2 } }, 5 },
      Entry{      20006, 881, InteractionType::Nuclear, { "2n(6)" }                                     , { { ParticleID::neutron(), 2 } }, 6 },
      Entry{      20007, 882, InteractionType::Nuclear, { "2n(7)" }                                     , { { ParticleID::neutron(), 2 } }, 7 },
      Entry{      20008, 883, InteractionType::Nuclear, { "2n(8)" }                                     , { { ParticleID::neutron(), 2 } }, 8 },
      Entry{      20009, 884, InteractionType::Nuclear, { "2n(9)" }                                     , { { ParticleID::neutron(), 2 } }, 9 },
      Entry{      20010, 885, InteractionType::Nuclear, { "2n(10)" }                                    , { { ParticleID::neutron(), 2 } }, 10 },
      Entry{      20011, 886, InteractionType::Nuclear, { "2n(11)" }                                    , { { ParticleID::neutron(), 2 } }, 11 },
      Entry{      20012, 887, InteractionType::Nuclear, { "2n(12)" }                                    , { { ParticleID::neutron(), 2 } }, 12 },
      Entry{      20013, 888, InteractionType::Nuclear, { "2n(13)" }                                    , { { ParticleID::neutron(), 2 } }, 13 },
      Entry{      20014, 889, InteractionType::Nuclear, { "2n(14)" }                                    , { { ParticleID::neutron(), 2 } }, 14 },
      Entry{      20015, 890, InteractionType::Nuclear, { "2n(15)" }                                    , { { ParticleID::neutron(), 2 } }, 15 },
      Entry{      20150, 891, InteractionType::Nuclear, { "2n(c)" }                                     , { { ParticleID::neutron(), 2 } }, LevelID::continuum },
      Entry{      20151,  16, InteractionType::Nuclear, { "2n(t)", "2n" }                               , { { ParticleID::neutron(), 2 } }, LevelID::all },
      Entry{      30151,  17, InteractionType::Nuclear, { "3n(t)", "3n" }                               , { { ParticleID::neutron(), 3 } }, LevelID::all },
      Entry{      40151,  37, InteractionType::Nuclear, { "4n(t)", "4n" }                               , { { ParticleID::neutron(), 4 } }, LevelID::all },
      Entry{      50151, 152, InteractionType::Nuclear, { "5n(t)", "5n" }                               , { { ParticleID::neutron(), 5 } }, LevelID::all },
      Entry{      60151, 153, InteractionType::Nuclear, { "6n(t)", "6n" }                               , { { ParticleID::neutron(), 6 } }, LevelID::all },
      Entry{      70151, 160, InteractionType::Nuclear, { "7n(t)", "7n" }                               , { { ParticleID::neutron(), 7 } }, LevelID::all },
      Entry{      80151, 161, InteractionType::Nuclear, { "8n(t)", "8n" }                               , { { ParticleID::neutron(), 8 } }, LevelID::all },

      Entry{     100000, 600, InteractionType::Nuclear, { "p(0)" }                                      , { { ParticleID::proton(), 1 } }, 0 },
      Entry{     100001, 601, InteractionType::Nuclear, { "p(1)" }                                      , { { ParticleID::proton(), 1 } }, 1 },
      Entry{     100002, 602, InteractionType::Nuclear, { "p(2)" }                                      , { { ParticleID::proton(), 1 } }, 2 },
      Entry{     100003, 603, InteractionType::Nuclear, { "p(3)" }                                      , { { ParticleID::proton(), 1 } }, 3 },
      Entry{     100004, 604, InteractionType::Nuclear, { "p(4)" }                                      , { { ParticleID::proton(), 1 } }, 4 },
      Entry{     100005, 605, InteractionType::Nuclear, { "p(5)" }                                      , { { ParticleID::proton(), 1 } }, 5 },
      Entry{     100006, 606, InteractionType::Nuclear, { "p(6)" }                                      , { { ParticleID::proton(), 1 } }, 6 },
      Entry{     100007, 607, InteractionType::Nuclear, { "p(7)" }                                      , { { ParticleID::proton(), 1 } }, 7 },
      Entry{     100008, 608, InteractionType::Nuclear, { "p(8)" }                                      , { { ParticleID::proton(), 1 } }, 8 },
      Entry{     100009, 609, InteractionType::Nuclear, { "p(9)" }                                      , { { ParticleID::proton(), 1 } }, 9 },
      Entry{     100010, 610, InteractionType::Nuclear, { "p(10)" }                                     , { { ParticleID::proton(), 1 } }, 10 },
      Entry{     100011, 611, InteractionType::Nuclear, { "p(11)" }                                     , { { ParticleID::proton(), 1 } }, 11 },
      Entry{     100012, 612, InteractionType::Nuclear, { "p(12)" }                                     , { { ParticleID::proton(), 1 } }, 12 },
      Entry{     100013, 613, InteractionType::Nuclear, { "p(13)" }                                     , { { ParticleID::proton(), 1 } }, 13 },
      Entry{     100014, 614, InteractionType::Nuclear, { "p(14)" }                                     , { { ParticleID::proton(), 1 } }, 14 },
      Entry{     100015, 615, InteractionType::Nuclear, { "p(15)" }                                     , { { ParticleID::proton(), 1 } }, 15 },
      Entry{     100016, 616, InteractionType::Nuclear, { "p(16)" }                                     , { { ParticleID::proton(), 1 } }, 16 },
      Entry{     100017, 617, InteractionType::Nuclear, { "p(17)" }                                     , { { ParticleID::proton(), 1 } }, 17 },
      Entry{     100018, 618, InteractionType::Nuclear, { "p(18)" }                                     , { { ParticleID::proton(), 1 } }, 18 },
      Entry{     100019, 619, InteractionType::Nuclear, { "p(19)" }                                     , { { ParticleID::proton(), 1 } }, 19 },
      Entry{     100020, 620, InteractionType::Nuclear, { "p(20)" }                                     , { { ParticleID::proton(), 1 } }, 20 },
      Entry{     100021, 621, InteractionType::Nuclear, { "p(21)" }                                     , { { ParticleID::proton(), 1 } }, 21 },
      Entry{     100022, 622, InteractionType::Nuclear, { "p(22)" }                                     , { { ParticleID::proton(), 1 } }, 22 },
      Entry{     100023, 623, InteractionType::Nuclear, { "p(23)" }                                     , { { ParticleID::proton(), 1 } }, 23 },
      Entry{     100024, 624, InteractionType::Nuclear, { "p(24)" }                                     , { { ParticleID::proton(), 1 } }, 24 },
      Entry{     100025, 625, InteractionType::Nuclear, { "p(25)" }                                     , { { ParticleID::proton(), 1 } }, 25 },
      Entry{     100026, 626, InteractionType::Nuclear, { "p(26)" }                                     , { { ParticleID::proton(), 1 } }, 26 },
      Entry{     100027, 627, InteractionType::Nuclear, { "p(27)" }                                     , { { ParticleID::proton(), 1 } }, 27 },
      Entry{     100028, 628, InteractionType::Nuclear, { "p(28)" }                                     , { { ParticleID::proton(), 1 } }, 28 },
      Entry{     100029, 629, InteractionType::Nuclear, { "p(29)" }                                     , { { ParticleID::proton(), 1 } }, 29 },
      Entry{     100030, 630, InteractionType::Nuclear, { "p(30)" }                                     , { { ParticleID::proton(), 1 } }, 30 },
      Entry{     100031, 631, InteractionType::Nuclear, { "p(31)" }                                     , { { ParticleID::proton(), 1 } }, 31 },
      Entry{     100032, 632, InteractionType::Nuclear, { "p(32)" }                                     , { { ParticleID::proton(), 1 } }, 32 },
      Entry{     100033, 633, InteractionType::Nuclear, { "p(33)" }                                     , { { ParticleID::proton(), 1 } }, 33 },
      Entry{     100034, 634, InteractionType::Nuclear, { "p(34)" }                                     , { { ParticleID::proton(), 1 } }, 34 },
      Entry{     100035, 635, InteractionType::Nuclear, { "p(35)" }                                     , { { ParticleID::proton(), 1 } }, 35 },
      Entry{     100036, 636, InteractionType::Nuclear, { "p(36)" }                                     , { { ParticleID::proton(), 1 } }, 36 },
      Entry{     100037, 637, InteractionType::Nuclear, { "p(37)" }                                     , { { ParticleID::proton(), 1 } }, 37 },
      Entry{     100038, 638, InteractionType::Nuclear, { "p(38)" }                                     , { { ParticleID::proton(), 1 } }, 38 },
      Entry{     100039, 639, InteractionType::Nuclear, { "p(39)" }                                     , { { ParticleID::proton(), 1 } }, 39 },
      Entry{     100040, 640, InteractionType::Nuclear, { "p(40)" }                                     , { { ParticleID::proton(), 1 } }, 40 },
      Entry{     100041, 641, InteractionType::Nuclear, { "p(41)" }                                     , { { ParticleID::proton(), 1 } }, 41 },
      Entry{     100042, 642, InteractionType::Nuclear, { "p(42)" }                                     , { { ParticleID::proton(), 1 } }, 42 },
      Entry{     100043, 643, InteractionType::Nuclear, { "p(43)" }                                     , { { ParticleID::proton(), 1 } }, 43 },
      Entry{     100044, 644, InteractionType::Nuclear, { "p(44)" }                                     , { { ParticleID::proton(), 1 } }, 44 },
      Entry{     100045, 645, InteractionType::Nuclear, { "p(45)" }                                     , { { ParticleID::proton(), 1 } }, 45 },
      Entry{     100046, 646, InteractionType::Nuclear, { "p(46)" }                                     , { { ParticleID::proton(), 1 } }, 46 },
      Entry{     100047, 647, InteractionType::Nuclear, { "p(47)" }                                     , { { ParticleID::proton(), 1 } }, 47 },
      Entry{     100048, 648, InteractionType::Nuclear, { "p(48)" }                                     , { { ParticleID::proton(), 1 } }, 48 },
      Entry{     100049,      InteractionType::Nuclear, { "p(49)" }                                     , { { ParticleID::proton(), 1 } }, 49 },
      Entry{     100050,      InteractionType::Nuclear, { "p(50)" }                                     , { { ParticleID::proton(), 1 } }, 50 },
      Entry{     100051,      InteractionType::Nuclear, { "p(51)" }                                     , { { ParticleID::proton(), 1 } }, 51 },
      Entry{     100052,      InteractionType::Nuclear, { "p(52)" }                                     , { { ParticleID::proton(), 1 } }, 52 },
      Entry{     100053,      InteractionType::Nuclear, { "p(53)" }                                     , { { ParticleID::proton(), 1 } }, 53 },
      Entry{     100054,      InteractionType::Nuclear, { "p(54)" }                                     , { { ParticleID::proton(), 1 } }, 54 },
      Entry{     100055,      InteractionType::Nuclear, { "p(55)" }                                     , { { ParticleID::proton(), 1 } }, 55 },
      Entry{     100056,      InteractionType::Nuclear, { "p(56)" }                                     , { { ParticleID::proton(), 1 } }, 56 },
      Entry{     100057,      InteractionType::Nuclear, { "p(57)" }                                     , { { ParticleID::proton(), 1 } }, 57 },
      Entry{     100058,      InteractionType::Nuclear, { "p(58)" }                                     , { { ParticleID::proton(), 1 } }, 58 },
      Entry{     100059,      InteractionType::Nuclear, { "p(59)" }                                     , { { ParticleID::proton(), 1 } }, 59 },
      Entry{     100060,      InteractionType::Nuclear, { "p(60)" }                                     , { { ParticleID::proton(), 1 } }, 60 },
      Entry{     100061,      InteractionType::Nuclear, { "p(61)" }                                     , { { ParticleID::proton(), 1 } }, 61 },
      Entry{     100062,      InteractionType::Nuclear, { "p(62)" }                                     , { { ParticleID::proton(), 1 } }, 62 },
      Entry{     100063,      InteractionType::Nuclear, { "p(63)" }                                     , { { ParticleID::proton(), 1 } }, 63 },
      Entry{     100064,      InteractionType::Nuclear, { "p(64)" }                                     , { { ParticleID::proton(), 1 } }, 64 },
      Entry{     100065,      InteractionType::Nuclear, { "p(65)" }                                     , { { ParticleID::proton(), 1 } }, 65 },
      Entry{     100066,      InteractionType::Nuclear, { "p(66)" }                                     , { { ParticleID::proton(), 1 } }, 66 },
      Entry{     100067,      InteractionType::Nuclear, { "p(67)" }                                     , { { ParticleID::proton(), 1 } }, 67 },
      Entry{     100068,      InteractionType::Nuclear, { "p(68)" }                                     , { { ParticleID::proton(), 1 } }, 68 },
      Entry{     100069,      InteractionType::Nuclear, { "p(69)" }                                     , { { ParticleID::proton(), 1 } }, 69 },
      Entry{     100070,      InteractionType::Nuclear, { "p(70)" }                                     , { { ParticleID::proton(), 1 } }, 70 },
      Entry{     100071,      InteractionType::Nuclear, { "p(71)" }                                     , { { ParticleID::proton(), 1 } }, 71 },
      Entry{     100072,      InteractionType::Nuclear, { "p(72)" }                                     , { { ParticleID::proton(), 1 } }, 72 },
      Entry{     100073,      InteractionType::Nuclear, { "p(73)" }                                     , { { ParticleID::proton(), 1 } }, 73 },
      Entry{     100074,      InteractionType::Nuclear, { "p(74)" }                                     , { { ParticleID::proton(), 1 } }, 74 },
      Entry{     100075,      InteractionType::Nuclear, { "p(75)" }                                     , { { ParticleID::proton(), 1 } }, 75 },
      Entry{     100076,      InteractionType::Nuclear, { "p(76)" }                                     , { { ParticleID::proton(), 1 } }, 76 },
      Entry{     100077,      InteractionType::Nuclear, { "p(77)" }                                     , { { ParticleID::proton(), 1 } }, 77 },
      Entry{     100078,      InteractionType::Nuclear, { "p(78)" }                                     , { { ParticleID::proton(), 1 } }, 78 },
      Entry{     100079,      InteractionType::Nuclear, { "p(79)" }                                     , { { ParticleID::proton(), 1 } }, 79 },
      Entry{     100080,      InteractionType::Nuclear, { "p(80)" }                                     , { { ParticleID::proton(), 1 } }, 80 },
      Entry{     100081,      InteractionType::Nuclear, { "p(81)" }                                     , { { ParticleID::proton(), 1 } }, 81 },
      Entry{     100082,      InteractionType::Nuclear, { "p(82)" }                                     , { { ParticleID::proton(), 1 } }, 82 },
      Entry{     100083,      InteractionType::Nuclear, { "p(83)" }                                     , { { ParticleID::proton(), 1 } }, 83 },
      Entry{     100084,      InteractionType::Nuclear, { "p(84)" }                                     , { { ParticleID::proton(), 1 } }, 84 },
      Entry{     100085,      InteractionType::Nuclear, { "p(85)" }                                     , { { ParticleID::proton(), 1 } }, 85 },
      Entry{     100086,      InteractionType::Nuclear, { "p(86)" }                                     , { { ParticleID::proton(), 1 } }, 86 },
      Entry{     100087,      InteractionType::Nuclear, { "p(87)" }                                     , { { ParticleID::proton(), 1 } }, 87 },
      Entry{     100088,      InteractionType::Nuclear, { "p(88)" }                                     , { { ParticleID::proton(), 1 } }, 88 },
      Entry{     100089,      InteractionType::Nuclear, { "p(89)" }                                     , { { ParticleID::proton(), 1 } }, 89 },
      Entry{     100090,      InteractionType::Nuclear, { "p(90)" }                                     , { { ParticleID::proton(), 1 } }, 90 },
      Entry{     100091,      InteractionType::Nuclear, { "p(91)" }                                     , { { ParticleID::proton(), 1 } }, 91 },
      Entry{     100092,      InteractionType::Nuclear, { "p(92)" }                                     , { { ParticleID::proton(), 1 } }, 92 },
      Entry{     100093,      InteractionType::Nuclear, { "p(93)" }                                     , { { ParticleID::proton(), 1 } }, 93 },
      Entry{     100094,      InteractionType::Nuclear, { "p(94)" }                                     , { { ParticleID::proton(), 1 } }, 94 },
      Entry{     100095,      InteractionType::Nuclear, { "p(95)" }                                     , { { ParticleID::proton(), 1 } }, 95 },
      Entry{     100096,      InteractionType::Nuclear, { "p(96)" }                                     , { { ParticleID::proton(), 1 } }, 96 },
      Entry{     100097,      InteractionType::Nuclear, { "p(97)" }                                     , { { ParticleID::proton(), 1 } }, 97 },
      Entry{     100098,      InteractionType::Nuclear, { "p(98)" }                                     , { { ParticleID::proton(), 1 } }, 98 },
      Entry{     100099,      InteractionType::Nuclear, { "p(99)" }                                     , { { ParticleID::proton(), 1 } }, 99 },
      Entry{     100150, 649, InteractionType::Nuclear, { "p(c)" }                                      , { { ParticleID::proton(), 1 } }, LevelID::continuum },
      Entry{     100151, 103, InteractionType::Nuclear, { "p(t)", "p" }                                 , { { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     110151,  28, InteractionType::Nuclear, { "np(t)", "np" , "n,p(t)", "n,p" }             , { { ParticleID::neutron(), 1 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     120151,  41, InteractionType::Nuclear, { "2np(t)", "2np", "2n,p(t)", "2n,p" }          , { { ParticleID::neutron(), 2 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     130151,  42, InteractionType::Nuclear, { "3np(t)", "3np", "3n,p(t)", "3n,p" }          , { { ParticleID::neutron(), 3 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     210151,  44, InteractionType::Nuclear, { "n2p(t)", "n2p", "n,2p(t)", "n,2p" }          , { { ParticleID::neutron(), 1 }, { ParticleID::proton(), 2 } }, LevelID::all },
      Entry{     140151, 156, InteractionType::Nuclear, { "4np(t)", "4np", "4n,p(t)", "4n,p" }          , { { ParticleID::neutron(), 4 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     150151, 162, InteractionType::Nuclear, { "5np(t)", "5np", "5n,p(t)", "5n,p" }          , { { ParticleID::neutron(), 5 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     160151, 163, InteractionType::Nuclear, { "6np(t)", "6np", "6n,p(t)", "6n,p" }          , { { ParticleID::neutron(), 6 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     170151, 164, InteractionType::Nuclear, { "7np(t)", "7np", "7n,p(t)", "7n,p" }          , { { ParticleID::neutron(), 7 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     200151, 111, InteractionType::Nuclear, { "2p(t)", "2p" }                               , { { ParticleID::proton(), 2 } }, LevelID::all },
      Entry{     220151, 190, InteractionType::Nuclear, { "2n2p(t)", "2n2p", "2n,2p(t)", "2n,2p" }      , { { ParticleID::neutron(), 2 }, { ParticleID::proton(), 2 } }, LevelID::all },
      Entry{     230151, 179, InteractionType::Nuclear, { "3n2p(t)", "3n2p", "3n,2p(t)", "3n,2p" }      , { { ParticleID::neutron(), 3 }, { ParticleID::proton(), 2 } }, LevelID::all },
      Entry{     240151, 194, InteractionType::Nuclear, { "4n2p(t)", "4n2p", "4n,2p(t)", "4n,2p" }      , { { ParticleID::neutron(), 4 }, { ParticleID::proton(), 2 } }, LevelID::all },
      Entry{     250151, 200, InteractionType::Nuclear, { "5n2p(t)", "5n2p", "5n,2p(t)", "5n,2p" }      , { { ParticleID::neutron(), 5 }, { ParticleID::proton(), 2 } }, LevelID::all },
      Entry{     300151, 197, InteractionType::Nuclear, { "3p(t)", "3p" }                               , { { ParticleID::proton(), 3 } }, LevelID::all },
      Entry{     310151, 198, InteractionType::Nuclear, { "n3p(t)", "n3p", "n,3p", "n,3p(t)" }          , { { ParticleID::neutron(), 1 }, { ParticleID::proton(), 3 } }, LevelID::all },

      Entry{    1000000, 650, InteractionType::Nuclear, { "d(0)" }                                      , { { ParticleID::deuteron(), 1 } }, 0 },
      Entry{    1000001, 651, InteractionType::Nuclear, { "d(1)" }                                      , { { ParticleID::deuteron(), 1 } }, 1 },
      Entry{    1000002, 652, InteractionType::Nuclear, { "d(2)" }                                      , { { ParticleID::deuteron(), 1 } }, 2 },
      Entry{    1000003, 653, InteractionType::Nuclear, { "d(3)" }                                      , { { ParticleID::deuteron(), 1 } }, 3 },
      Entry{    1000004, 654, InteractionType::Nuclear, { "d(4)" }                                      , { { ParticleID::deuteron(), 1 } }, 4 },
      Entry{    1000005, 655, InteractionType::Nuclear, { "d(5)" }                                      , { { ParticleID::deuteron(), 1 } }, 5 },
      Entry{    1000006, 656, InteractionType::Nuclear, { "d(6)" }                                      , { { ParticleID::deuteron(), 1 } }, 6 },
      Entry{    1000007, 657, InteractionType::Nuclear, { "d(7)" }                                      , { { ParticleID::deuteron(), 1 } }, 7 },
      Entry{    1000008, 658, InteractionType::Nuclear, { "d(8)" }                                      , { { ParticleID::deuteron(), 1 } }, 8 },
      Entry{    1000009, 659, InteractionType::Nuclear, { "d(9)" }                                      , { { ParticleID::deuteron(), 1 } }, 9 },
      Entry{    1000010, 660, InteractionType::Nuclear, { "d(10)" }                                     , { { ParticleID::deuteron(), 1 } }, 10 },
      Entry{    1000011, 661, InteractionType::Nuclear, { "d(11)" }                                     , { { ParticleID::deuteron(), 1 } }, 11 },
      Entry{    1000012, 662, InteractionType::Nuclear, { "d(12)" }                                     , { { ParticleID::deuteron(), 1 } }, 12 },
      Entry{    1000013, 663, InteractionType::Nuclear, { "d(13)" }                                     , { { ParticleID::deuteron(), 1 } }, 13 },
      Entry{    1000014, 664, InteractionType::Nuclear, { "d(14)" }                                     , { { ParticleID::deuteron(), 1 } }, 14 },
      Entry{    1000015, 665, InteractionType::Nuclear, { "d(15)" }                                     , { { ParticleID::deuteron(), 1 } }, 15 },
      Entry{    1000016, 666, InteractionType::Nuclear, { "d(16)" }                                     , { { ParticleID::deuteron(), 1 } }, 16 },
      Entry{    1000017, 667, InteractionType::Nuclear, { "d(17)" }                                     , { { ParticleID::deuteron(), 1 } }, 17 },
      Entry{    1000018, 668, InteractionType::Nuclear, { "d(18)" }                                     , { { ParticleID::deuteron(), 1 } }, 18 },
      Entry{    1000019, 669, InteractionType::Nuclear, { "d(19)" }                                     , { { ParticleID::deuteron(), 1 } }, 19 },
      Entry{    1000020, 670, InteractionType::Nuclear, { "d(20)" }                                     , { { ParticleID::deuteron(), 1 } }, 20 },
      Entry{    1000021, 671, InteractionType::Nuclear, { "d(21)" }                                     , { { ParticleID::deuteron(), 1 } }, 21 },
      Entry{    1000022, 672, InteractionType::Nuclear, { "d(22)" }                                     , { { ParticleID::deuteron(), 1 } }, 22 },
      Entry{    1000023, 673, InteractionType::Nuclear, { "d(23)" }                                     , { { ParticleID::deuteron(), 1 } }, 23 },
      Entry{    1000024, 674, InteractionType::Nuclear, { "d(24)" }                                     , { { ParticleID::deuteron(), 1 } }, 24 },
      Entry{    1000025, 675, InteractionType::Nuclear, { "d(25)" }                                     , { { ParticleID::deuteron(), 1 } }, 25 },
      Entry{    1000026, 676, InteractionType::Nuclear, { "d(26)" }                                     , { { ParticleID::deuteron(), 1 } }, 26 },
      Entry{    1000027, 677, InteractionType::Nuclear, { "d(27)" }                                     , { { ParticleID::deuteron(), 1 } }, 27 },
      Entry{    1000028, 678, InteractionType::Nuclear, { "d(28)" }                                     , { { ParticleID::deuteron(), 1 } }, 28 },
      Entry{    1000029, 679, InteractionType::Nuclear, { "d(29)" }                                     , { { ParticleID::deuteron(), 1 } }, 29 },
      Entry{    1000030, 680, InteractionType::Nuclear, { "d(30)" }                                     , { { ParticleID::deuteron(), 1 } }, 30 },
      Entry{    1000031, 681, InteractionType::Nuclear, { "d(31)" }                                     , { { ParticleID::deuteron(), 1 } }, 31 },
      Entry{    1000032, 682, InteractionType::Nuclear, { "d(32)" }                                     , { { ParticleID::deuteron(), 1 } }, 32 },
      Entry{    1000033, 683, InteractionType::Nuclear, { "d(33)" }                                     , { { ParticleID::deuteron(), 1 } }, 33 },
      Entry{    1000034, 684, InteractionType::Nuclear, { "d(34)" }                                     , { { ParticleID::deuteron(), 1 } }, 34 },
      Entry{    1000035, 685, InteractionType::Nuclear, { "d(35)" }                                     , { { ParticleID::deuteron(), 1 } }, 35 },
      Entry{    1000036, 686, InteractionType::Nuclear, { "d(36)" }                                     , { { ParticleID::deuteron(), 1 } }, 36 },
      Entry{    1000037, 687, InteractionType::Nuclear, { "d(37)" }                                     , { { ParticleID::deuteron(), 1 } }, 37 },
      Entry{    1000038, 688, InteractionType::Nuclear, { "d(38)" }                                     , { { ParticleID::deuteron(), 1 } }, 38 },
      Entry{    1000039, 689, InteractionType::Nuclear, { "d(39)" }                                     , { { ParticleID::deuteron(), 1 } }, 39 },
      Entry{    1000040, 690, InteractionType::Nuclear, { "d(40)" }                                     , { { ParticleID::deuteron(), 1 } }, 40 },
      Entry{    1000041, 691, InteractionType::Nuclear, { "d(41)" }                                     , { { ParticleID::deuteron(), 1 } }, 41 },
      Entry{    1000042, 692, InteractionType::Nuclear, { "d(42)" }                                     , { { ParticleID::deuteron(), 1 } }, 42 },
      Entry{    1000043, 693, InteractionType::Nuclear, { "d(43)" }                                     , { { ParticleID::deuteron(), 1 } }, 43 },
      Entry{    1000044, 694, InteractionType::Nuclear, { "d(44)" }                                     , { { ParticleID::deuteron(), 1 } }, 44 },
      Entry{    1000045, 695, InteractionType::Nuclear, { "d(45)" }                                     , { { ParticleID::deuteron(), 1 } }, 45 },
      Entry{    1000046, 696, InteractionType::Nuclear, { "d(46)" }                                     , { { ParticleID::deuteron(), 1 } }, 46 },
      Entry{    1000047, 697, InteractionType::Nuclear, { "d(47)" }                                     , { { ParticleID::deuteron(), 1 } }, 47 },
      Entry{    1000048, 698, InteractionType::Nuclear, { "d(48)" }                                     , { { ParticleID::deuteron(), 1 } }, 48 },
      Entry{    1000049,      InteractionType::Nuclear, { "d(49)" }                                     , { { ParticleID::deuteron(), 1 } }, 49 },
      Entry{    1000050,      InteractionType::Nuclear, { "d(50)" }                                     , { { ParticleID::deuteron(), 1 } }, 50 },
      Entry{    1000051,      InteractionType::Nuclear, { "d(51)" }                                     , { { ParticleID::deuteron(), 1 } }, 51 },
      Entry{    1000052,      InteractionType::Nuclear, { "d(52)" }                                     , { { ParticleID::deuteron(), 1 } }, 52 },
      Entry{    1000053,      InteractionType::Nuclear, { "d(53)" }                                     , { { ParticleID::deuteron(), 1 } }, 53 },
      Entry{    1000054,      InteractionType::Nuclear, { "d(54)" }                                     , { { ParticleID::deuteron(), 1 } }, 54 },
      Entry{    1000055,      InteractionType::Nuclear, { "d(55)" }                                     , { { ParticleID::deuteron(), 1 } }, 55 },
      Entry{    1000056,      InteractionType::Nuclear, { "d(56)" }                                     , { { ParticleID::deuteron(), 1 } }, 56 },
      Entry{    1000057,      InteractionType::Nuclear, { "d(57)" }                                     , { { ParticleID::deuteron(), 1 } }, 57 },
      Entry{    1000058,      InteractionType::Nuclear, { "d(58)" }                                     , { { ParticleID::deuteron(), 1 } }, 58 },
      Entry{    1000059,      InteractionType::Nuclear, { "d(59)" }                                     , { { ParticleID::deuteron(), 1 } }, 59 },
      Entry{    1000060,      InteractionType::Nuclear, { "d(60)" }                                     , { { ParticleID::deuteron(), 1 } }, 60 },
      Entry{    1000061,      InteractionType::Nuclear, { "d(61)" }                                     , { { ParticleID::deuteron(), 1 } }, 61 },
      Entry{    1000062,      InteractionType::Nuclear, { "d(62)" }                                     , { { ParticleID::deuteron(), 1 } }, 62 },
      Entry{    1000063,      InteractionType::Nuclear, { "d(63)" }                                     , { { ParticleID::deuteron(), 1 } }, 63 },
      Entry{    1000064,      InteractionType::Nuclear, { "d(64)" }                                     , { { ParticleID::deuteron(), 1 } }, 64 },
      Entry{    1000065,      InteractionType::Nuclear, { "d(65)" }                                     , { { ParticleID::deuteron(), 1 } }, 65 },
      Entry{    1000066,      InteractionType::Nuclear, { "d(66)" }                                     , { { ParticleID::deuteron(), 1 } }, 66 },
      Entry{    1000067,      InteractionType::Nuclear, { "d(67)" }                                     , { { ParticleID::deuteron(), 1 } }, 67 },
      Entry{    1000068,      InteractionType::Nuclear, { "d(68)" }                                     , { { ParticleID::deuteron(), 1 } }, 68 },
      Entry{    1000069,      InteractionType::Nuclear, { "d(69)" }                                     , { { ParticleID::deuteron(), 1 } }, 69 },
      Entry{    1000070,      InteractionType::Nuclear, { "d(70)" }                                     , { { ParticleID::deuteron(), 1 } }, 70 },
      Entry{    1000071,      InteractionType::Nuclear, { "d(71)" }                                     , { { ParticleID::deuteron(), 1 } }, 71 },
      Entry{    1000072,      InteractionType::Nuclear, { "d(72)" }                                     , { { ParticleID::deuteron(), 1 } }, 72 },
      Entry{    1000073,      InteractionType::Nuclear, { "d(73)" }                                     , { { ParticleID::deuteron(), 1 } }, 73 },
      Entry{    1000074,      InteractionType::Nuclear, { "d(74)" }                                     , { { ParticleID::deuteron(), 1 } }, 74 },
      Entry{    1000075,      InteractionType::Nuclear, { "d(75)" }                                     , { { ParticleID::deuteron(), 1 } }, 75 },
      Entry{    1000076,      InteractionType::Nuclear, { "d(76)" }                                     , { { ParticleID::deuteron(), 1 } }, 76 },
      Entry{    1000077,      InteractionType::Nuclear, { "d(77)" }                                     , { { ParticleID::deuteron(), 1 } }, 77 },
      Entry{    1000078,      InteractionType::Nuclear, { "d(78)" }                                     , { { ParticleID::deuteron(), 1 } }, 78 },
      Entry{    1000079,      InteractionType::Nuclear, { "d(79)" }                                     , { { ParticleID::deuteron(), 1 } }, 79 },
      Entry{    1000080,      InteractionType::Nuclear, { "d(80)" }                                     , { { ParticleID::deuteron(), 1 } }, 80 },
      Entry{    1000081,      InteractionType::Nuclear, { "d(81)" }                                     , { { ParticleID::deuteron(), 1 } }, 81 },
      Entry{    1000082,      InteractionType::Nuclear, { "d(82)" }                                     , { { ParticleID::deuteron(), 1 } }, 82 },
      Entry{    1000083,      InteractionType::Nuclear, { "d(83)" }                                     , { { ParticleID::deuteron(), 1 } }, 83 },
      Entry{    1000084,      InteractionType::Nuclear, { "d(84)" }                                     , { { ParticleID::deuteron(), 1 } }, 84 },
      Entry{    1000085,      InteractionType::Nuclear, { "d(85)" }                                     , { { ParticleID::deuteron(), 1 } }, 85 },
      Entry{    1000086,      InteractionType::Nuclear, { "d(86)" }                                     , { { ParticleID::deuteron(), 1 } }, 86 },
      Entry{    1000087,      InteractionType::Nuclear, { "d(87)" }                                     , { { ParticleID::deuteron(), 1 } }, 87 },
      Entry{    1000088,      InteractionType::Nuclear, { "d(88)" }                                     , { { ParticleID::deuteron(), 1 } }, 88 },
      Entry{    1000089,      InteractionType::Nuclear, { "d(89)" }                                     , { { ParticleID::deuteron(), 1 } }, 89 },
      Entry{    1000090,      InteractionType::Nuclear, { "d(90)" }                                     , { { ParticleID::deuteron(), 1 } }, 90 },
      Entry{    1000091,      InteractionType::Nuclear, { "d(91)" }                                     , { { ParticleID::deuteron(), 1 } }, 91 },
      Entry{    1000092,      InteractionType::Nuclear, { "d(92)" }                                     , { { ParticleID::deuteron(), 1 } }, 92 },
      Entry{    1000093,      InteractionType::Nuclear, { "d(93)" }                                     , { { ParticleID::deuteron(), 1 } }, 93 },
      Entry{    1000094,      InteractionType::Nuclear, { "d(94)" }                                     , { { ParticleID::deuteron(), 1 } }, 94 },
      Entry{    1000095,      InteractionType::Nuclear, { "d(95)" }                                     , { { ParticleID::deuteron(), 1 } }, 95 },
      Entry{    1000096,      InteractionType::Nuclear, { "d(96)" }                                     , { { ParticleID::deuteron(), 1 } }, 96 },
      Entry{    1000097,      InteractionType::Nuclear, { "d(97)" }                                     , { { ParticleID::deuteron(), 1 } }, 97 },
      Entry{    1000098,      InteractionType::Nuclear, { "d(98)" }                                     , { { ParticleID::deuteron(), 1 } }, 98 },
      Entry{    1000099,      InteractionType::Nuclear, { "d(99)" }                                     , { { ParticleID::deuteron(), 1 } }, 99 },
      Entry{    1000150, 699, InteractionType::Nuclear, { "d(c)" }                                      , { { ParticleID::deuteron(), 1 } }, LevelID::continuum },
      Entry{    1000151, 104, InteractionType::Nuclear, { "d(t)", "d" }                                 , { { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1010151,  32, InteractionType::Nuclear, { "nd(t)", "nd", "n,d(t)", "n,d" }              , { { ParticleID::neutron(), 1 }, { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1020151,  11, InteractionType::Nuclear, { "2nd(t)", "2nd", "2n,d(t)", "2n,d" }          , { { ParticleID::neutron(), 2 }, { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1030151, 157, InteractionType::Nuclear, { "3nd(t)", "3nd", "3n,d(t)", "3n,d" }          , { { ParticleID::neutron(), 3 }, { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1040151, 169, InteractionType::Nuclear, { "4nd(t)", "4nd", "4n,d(t)", "4n,d" }          , { { ParticleID::neutron(), 4 }, { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1050151, 170, InteractionType::Nuclear, { "5nd(t)", "5nd", "5n,d(t)", "5n,d" }          , { { ParticleID::neutron(), 5 }, { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1060151, 171, InteractionType::Nuclear, { "6nd(t)", "6nd", "6n,d(t)", "6n,d" }          , { { ParticleID::neutron(), 6 }, { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1100151, 115, InteractionType::Nuclear, { "pd(t)", "pd" , "p,d(t)" , "p,d" }            , { { ParticleID::proton(), 1 }, { ParticleID::deuteron(), 1 } }, LevelID::all },

      Entry{   10000000, 700, InteractionType::Nuclear, { "t(0)" }                                      , { { ParticleID::triton(), 1 } }, 0 },
      Entry{   10000001, 701, InteractionType::Nuclear, { "t(1)" }                                      , { { ParticleID::triton(), 1 } }, 1 },
      Entry{   10000002, 702, InteractionType::Nuclear, { "t(2)" }                                      , { { ParticleID::triton(), 1 } }, 2 },
      Entry{   10000003, 703, InteractionType::Nuclear, { "t(3)" }                                      , { { ParticleID::triton(), 1 } }, 3 },
      Entry{   10000004, 704, InteractionType::Nuclear, { "t(4)" }                                      , { { ParticleID::triton(), 1 } }, 4 },
      Entry{   10000005, 705, InteractionType::Nuclear, { "t(5)" }                                      , { { ParticleID::triton(), 1 } }, 5 },
      Entry{   10000006, 706, InteractionType::Nuclear, { "t(6)" }                                      , { { ParticleID::triton(), 1 } }, 6 },
      Entry{   10000007, 707, InteractionType::Nuclear, { "t(7)" }                                      , { { ParticleID::triton(), 1 } }, 7 },
      Entry{   10000008, 708, InteractionType::Nuclear, { "t(8)" }                                      , { { ParticleID::triton(), 1 } }, 8 },
      Entry{   10000009, 709, InteractionType::Nuclear, { "t(9)" }                                      , { { ParticleID::triton(), 1 } }, 9 },
      Entry{   10000010, 710, InteractionType::Nuclear, { "t(10)" }                                     , { { ParticleID::triton(), 1 } }, 10 },
      Entry{   10000011, 711, InteractionType::Nuclear, { "t(11)" }                                     , { { ParticleID::triton(), 1 } }, 11 },
      Entry{   10000012, 712, InteractionType::Nuclear, { "t(12)" }                                     , { { ParticleID::triton(), 1 } }, 12 },
      Entry{   10000013, 713, InteractionType::Nuclear, { "t(13)" }                                     , { { ParticleID::triton(), 1 } }, 13 },
      Entry{   10000014, 714, InteractionType::Nuclear, { "t(14)" }                                     , { { ParticleID::triton(), 1 } }, 14 },
      Entry{   10000015, 715, InteractionType::Nuclear, { "t(15)" }                                     , { { ParticleID::triton(), 1 } }, 15 },
      Entry{   10000016, 716, InteractionType::Nuclear, { "t(16)" }                                     , { { ParticleID::triton(), 1 } }, 16 },
      Entry{   10000017, 717, InteractionType::Nuclear, { "t(17)" }                                     , { { ParticleID::triton(), 1 } }, 17 },
      Entry{   10000018, 718, InteractionType::Nuclear, { "t(18)" }                                     , { { ParticleID::triton(), 1 } }, 18 },
      Entry{   10000019, 719, InteractionType::Nuclear, { "t(19)" }                                     , { { ParticleID::triton(), 1 } }, 19 },
      Entry{   10000020, 720, InteractionType::Nuclear, { "t(20)" }                                     , { { ParticleID::triton(), 1 } }, 20 },
      Entry{   10000021, 721, InteractionType::Nuclear, { "t(21)" }                                     , { { ParticleID::triton(), 1 } }, 21 },
      Entry{   10000022, 722, InteractionType::Nuclear, { "t(22)" }                                     , { { ParticleID::triton(), 1 } }, 22 },
      Entry{   10000023, 723, InteractionType::Nuclear, { "t(23)" }                                     , { { ParticleID::triton(), 1 } }, 23 },
      Entry{   10000024, 724, InteractionType::Nuclear, { "t(24)" }                                     , { { ParticleID::triton(), 1 } }, 24 },
      Entry{   10000025, 725, InteractionType::Nuclear, { "t(25)" }                                     , { { ParticleID::triton(), 1 } }, 25 },
      Entry{   10000026, 726, InteractionType::Nuclear, { "t(26)" }                                     , { { ParticleID::triton(), 1 } }, 26 },
      Entry{   10000027, 727, InteractionType::Nuclear, { "t(27)" }                                     , { { ParticleID::triton(), 1 } }, 27 },
      Entry{   10000028, 728, InteractionType::Nuclear, { "t(28)" }                                     , { { ParticleID::triton(), 1 } }, 28 },
      Entry{   10000029, 729, InteractionType::Nuclear, { "t(29)" }                                     , { { ParticleID::triton(), 1 } }, 29 },
      Entry{   10000030, 730, InteractionType::Nuclear, { "t(30)" }                                     , { { ParticleID::triton(), 1 } }, 30 },
      Entry{   10000031, 731, InteractionType::Nuclear, { "t(31)" }                                     , { { ParticleID::triton(), 1 } }, 31 },
      Entry{   10000032, 732, InteractionType::Nuclear, { "t(32)" }                                     , { { ParticleID::triton(), 1 } }, 32 },
      Entry{   10000033, 733, InteractionType::Nuclear, { "t(33)" }                                     , { { ParticleID::triton(), 1 } }, 33 },
      Entry{   10000034, 734, InteractionType::Nuclear, { "t(34)" }                                     , { { ParticleID::triton(), 1 } }, 34 },
      Entry{   10000035, 735, InteractionType::Nuclear, { "t(35)" }                                     , { { ParticleID::triton(), 1 } }, 35 },
      Entry{   10000036, 736, InteractionType::Nuclear, { "t(36)" }                                     , { { ParticleID::triton(), 1 } }, 36 },
      Entry{   10000037, 737, InteractionType::Nuclear, { "t(37)" }                                     , { { ParticleID::triton(), 1 } }, 37 },
      Entry{   10000038, 738, InteractionType::Nuclear, { "t(38)" }                                     , { { ParticleID::triton(), 1 } }, 38 },
      Entry{   10000039, 739, InteractionType::Nuclear, { "t(39)" }                                     , { { ParticleID::triton(), 1 } }, 39 },
      Entry{   10000040, 740, InteractionType::Nuclear, { "t(40)" }                                     , { { ParticleID::triton(), 1 } }, 40 },
      Entry{   10000041, 741, InteractionType::Nuclear, { "t(41)" }                                     , { { ParticleID::triton(), 1 } }, 41 },
      Entry{   10000042, 742, InteractionType::Nuclear, { "t(42)" }                                     , { { ParticleID::triton(), 1 } }, 42 },
      Entry{   10000043, 743, InteractionType::Nuclear, { "t(43)" }                                     , { { ParticleID::triton(), 1 } }, 43 },
      Entry{   10000044, 744, InteractionType::Nuclear, { "t(44)" }                                     , { { ParticleID::triton(), 1 } }, 44 },
      Entry{   10000045, 745, InteractionType::Nuclear, { "t(45)" }                                     , { { ParticleID::triton(), 1 } }, 45 },
      Entry{   10000046, 746, InteractionType::Nuclear, { "t(46)" }                                     , { { ParticleID::triton(), 1 } }, 46 },
      Entry{   10000047, 747, InteractionType::Nuclear, { "t(47)" }                                     , { { ParticleID::triton(), 1 } }, 47 },
      Entry{   10000048, 748, InteractionType::Nuclear, { "t(48)" }                                     , { { ParticleID::triton(), 1 } }, 48 },
      Entry{   10000049,      InteractionType::Nuclear, { "t(49)" }                                     , { { ParticleID::triton(), 1 } }, 49 },
      Entry{   10000050,      InteractionType::Nuclear, { "t(50)" }                                     , { { ParticleID::triton(), 1 } }, 50 },
      Entry{   10000051,      InteractionType::Nuclear, { "t(51)" }                                     , { { ParticleID::triton(), 1 } }, 51 },
      Entry{   10000052,      InteractionType::Nuclear, { "t(52)" }                                     , { { ParticleID::triton(), 1 } }, 52 },
      Entry{   10000053,      InteractionType::Nuclear, { "t(53)" }                                     , { { ParticleID::triton(), 1 } }, 53 },
      Entry{   10000054,      InteractionType::Nuclear, { "t(54)" }                                     , { { ParticleID::triton(), 1 } }, 54 },
      Entry{   10000055,      InteractionType::Nuclear, { "t(55)" }                                     , { { ParticleID::triton(), 1 } }, 55 },
      Entry{   10000056,      InteractionType::Nuclear, { "t(56)" }                                     , { { ParticleID::triton(), 1 } }, 56 },
      Entry{   10000057,      InteractionType::Nuclear, { "t(57)" }                                     , { { ParticleID::triton(), 1 } }, 57 },
      Entry{   10000058,      InteractionType::Nuclear, { "t(58)" }                                     , { { ParticleID::triton(), 1 } }, 58 },
      Entry{   10000059,      InteractionType::Nuclear, { "t(59)" }                                     , { { ParticleID::triton(), 1 } }, 59 },
      Entry{   10000060,      InteractionType::Nuclear, { "t(60)" }                                     , { { ParticleID::triton(), 1 } }, 60 },
      Entry{   10000061,      InteractionType::Nuclear, { "t(61)" }                                     , { { ParticleID::triton(), 1 } }, 61 },
      Entry{   10000062,      InteractionType::Nuclear, { "t(62)" }                                     , { { ParticleID::triton(), 1 } }, 62 },
      Entry{   10000063,      InteractionType::Nuclear, { "t(63)" }                                     , { { ParticleID::triton(), 1 } }, 63 },
      Entry{   10000064,      InteractionType::Nuclear, { "t(64)" }                                     , { { ParticleID::triton(), 1 } }, 64 },
      Entry{   10000065,      InteractionType::Nuclear, { "t(65)" }                                     , { { ParticleID::triton(), 1 } }, 65 },
      Entry{   10000066,      InteractionType::Nuclear, { "t(66)" }                                     , { { ParticleID::triton(), 1 } }, 66 },
      Entry{   10000067,      InteractionType::Nuclear, { "t(67)" }                                     , { { ParticleID::triton(), 1 } }, 67 },
      Entry{   10000068,      InteractionType::Nuclear, { "t(68)" }                                     , { { ParticleID::triton(), 1 } }, 68 },
      Entry{   10000069,      InteractionType::Nuclear, { "t(69)" }                                     , { { ParticleID::triton(), 1 } }, 69 },
      Entry{   10000070,      InteractionType::Nuclear, { "t(70)" }                                     , { { ParticleID::triton(), 1 } }, 70 },
      Entry{   10000071,      InteractionType::Nuclear, { "t(71)" }                                     , { { ParticleID::triton(), 1 } }, 71 },
      Entry{   10000072,      InteractionType::Nuclear, { "t(72)" }                                     , { { ParticleID::triton(), 1 } }, 72 },
      Entry{   10000073,      InteractionType::Nuclear, { "t(73)" }                                     , { { ParticleID::triton(), 1 } }, 73 },
      Entry{   10000074,      InteractionType::Nuclear, { "t(74)" }                                     , { { ParticleID::triton(), 1 } }, 74 },
      Entry{   10000075,      InteractionType::Nuclear, { "t(75)" }                                     , { { ParticleID::triton(), 1 } }, 75 },
      Entry{   10000076,      InteractionType::Nuclear, { "t(76)" }                                     , { { ParticleID::triton(), 1 } }, 76 },
      Entry{   10000077,      InteractionType::Nuclear, { "t(77)" }                                     , { { ParticleID::triton(), 1 } }, 77 },
      Entry{   10000078,      InteractionType::Nuclear, { "t(78)" }                                     , { { ParticleID::triton(), 1 } }, 78 },
      Entry{   10000079,      InteractionType::Nuclear, { "t(79)" }                                     , { { ParticleID::triton(), 1 } }, 79 },
      Entry{   10000080,      InteractionType::Nuclear, { "t(80)" }                                     , { { ParticleID::triton(), 1 } }, 80 },
      Entry{   10000081,      InteractionType::Nuclear, { "t(81)" }                                     , { { ParticleID::triton(), 1 } }, 81 },
      Entry{   10000082,      InteractionType::Nuclear, { "t(82)" }                                     , { { ParticleID::triton(), 1 } }, 82 },
      Entry{   10000083,      InteractionType::Nuclear, { "t(83)" }                                     , { { ParticleID::triton(), 1 } }, 83 },
      Entry{   10000084,      InteractionType::Nuclear, { "t(84)" }                                     , { { ParticleID::triton(), 1 } }, 84 },
      Entry{   10000085,      InteractionType::Nuclear, { "t(85)" }                                     , { { ParticleID::triton(), 1 } }, 85 },
      Entry{   10000086,      InteractionType::Nuclear, { "t(86)" }                                     , { { ParticleID::triton(), 1 } }, 86 },
      Entry{   10000087,      InteractionType::Nuclear, { "t(87)" }                                     , { { ParticleID::triton(), 1 } }, 87 },
      Entry{   10000088,      InteractionType::Nuclear, { "t(88)" }                                     , { { ParticleID::triton(), 1 } }, 88 },
      Entry{   10000089,      InteractionType::Nuclear, { "t(89)" }                                     , { { ParticleID::triton(), 1 } }, 89 },
      Entry{   10000090,      InteractionType::Nuclear, { "t(90)" }                                     , { { ParticleID::triton(), 1 } }, 90 },
      Entry{   10000091,      InteractionType::Nuclear, { "t(91)" }                                     , { { ParticleID::triton(), 1 } }, 91 },
      Entry{   10000092,      InteractionType::Nuclear, { "t(92)" }                                     , { { ParticleID::triton(), 1 } }, 92 },
      Entry{   10000093,      InteractionType::Nuclear, { "t(93)" }                                     , { { ParticleID::triton(), 1 } }, 93 },
      Entry{   10000094,      InteractionType::Nuclear, { "t(94)" }                                     , { { ParticleID::triton(), 1 } }, 94 },
      Entry{   10000095,      InteractionType::Nuclear, { "t(95)" }                                     , { { ParticleID::triton(), 1 } }, 95 },
      Entry{   10000096,      InteractionType::Nuclear, { "t(96)" }                                     , { { ParticleID::triton(), 1 } }, 96 },
      Entry{   10000097,      InteractionType::Nuclear, { "t(97)" }                                     , { { ParticleID::triton(), 1 } }, 97 },
      Entry{   10000098,      InteractionType::Nuclear, { "t(98)" }                                     , { { ParticleID::triton(), 1 } }, 98 },
      Entry{   10000099,      InteractionType::Nuclear, { "t(99)" }                                     , { { ParticleID::triton(), 1 } }, 99 },
      Entry{   10000150, 749, InteractionType::Nuclear, { "t(c)" }                                      , { { ParticleID::triton(), 1 } }, LevelID::continuum },
      Entry{   10000151, 105, InteractionType::Nuclear, { "t(t)", "t" }                                 , { { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10010151,  33, InteractionType::Nuclear, { "nt(t)", "nt" , "n,t(t)", "n,t" }             , { { ParticleID::neutron(), 1 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10020151, 154, InteractionType::Nuclear, { "2nt(t)", "2nt", "2n,t(t)", "2n,t" }          , { { ParticleID::neutron(), 2 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10030151, 172, InteractionType::Nuclear, { "3nt(t)", "3nt", "3n,t(t)", "3n,t" }          , { { ParticleID::neutron(), 3 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10040151, 173, InteractionType::Nuclear, { "4nt(t)", "4nt", "4n,t(t)", "4n,t" }          , { { ParticleID::neutron(), 4 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10050151, 174, InteractionType::Nuclear, { "5nt(t)", "5nt", "5n,t(t)", "5n,t" }          , { { ParticleID::neutron(), 5 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10060151, 175, InteractionType::Nuclear, { "6nt(t)", "6nt", "6n,t(t)", "6n,t" }          , { { ParticleID::neutron(), 6 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10100151, 116, InteractionType::Nuclear, { "pt(t)", "pt" , "p,t(t)", "p,t" }             , { { ParticleID::proton(), 1 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10110151, 184, InteractionType::Nuclear, { "npt(t)", "npt", "n,p,t(t)", "n,p,t" }        , { { ParticleID::neutron(), 1 }, { ParticleID::proton(), 1 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   11000151, 182, InteractionType::Nuclear, { "dt(t)", "dt" , "d,t(t)", "d,t"   }           , { { ParticleID::deuteron(), 1 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   11010151, 185, InteractionType::Nuclear, { "ndt(t)", "ndt", "n,d,t(t)", "n,d,t" }        , { { ParticleID::neutron(), 1 }, { ParticleID::deuteron(), 1 }, { ParticleID::triton(), 1 } }, LevelID::all },

      Entry{  100000000, 750, InteractionType::Nuclear, { "h(0)" }                                      , { { ParticleID::helion(), 1 } }, 0 },
      Entry{  100000001, 751, InteractionType::Nuclear, { "h(1)" }                                      , { { ParticleID::helion(), 1 } }, 1 },
      Entry{  100000002, 752, InteractionType::Nuclear, { "h(2)" }                                      , { { ParticleID::helion(), 1 } }, 2 },
      Entry{  100000003, 753, InteractionType::Nuclear, { "h(3)" }                                      , { { ParticleID::helion(), 1 } }, 3 },
      Entry{  100000004, 754, InteractionType::Nuclear, { "h(4)" }                                      , { { ParticleID::helion(), 1 } }, 4 },
      Entry{  100000005, 755, InteractionType::Nuclear, { "h(5)" }                                      , { { ParticleID::helion(), 1 } }, 5 },
      Entry{  100000006, 756, InteractionType::Nuclear, { "h(6)" }                                      , { { ParticleID::helion(), 1 } }, 6 },
      Entry{  100000007, 757, InteractionType::Nuclear, { "h(7)" }                                      , { { ParticleID::helion(), 1 } }, 7 },
      Entry{  100000008, 758, InteractionType::Nuclear, { "h(8)" }                                      , { { ParticleID::helion(), 1 } }, 8 },
      Entry{  100000009, 759, InteractionType::Nuclear, { "h(9)" }                                      , { { ParticleID::helion(), 1 } }, 9 },
      Entry{  100000010, 760, InteractionType::Nuclear, { "h(10)" }                                     , { { ParticleID::helion(), 1 } }, 10 },
      Entry{  100000011, 761, InteractionType::Nuclear, { "h(11)" }                                     , { { ParticleID::helion(), 1 } }, 11 },
      Entry{  100000012, 762, InteractionType::Nuclear, { "h(12)" }                                     , { { ParticleID::helion(), 1 } }, 12 },
      Entry{  100000013, 763, InteractionType::Nuclear, { "h(13)" }                                     , { { ParticleID::helion(), 1 } }, 13 },
      Entry{  100000014, 764, InteractionType::Nuclear, { "h(14)" }                                     , { { ParticleID::helion(), 1 } }, 14 },
      Entry{  100000015, 765, InteractionType::Nuclear, { "h(15)" }                                     , { { ParticleID::helion(), 1 } }, 15 },
      Entry{  100000016, 766, InteractionType::Nuclear, { "h(16)" }                                     , { { ParticleID::helion(), 1 } }, 16 },
      Entry{  100000017, 767, InteractionType::Nuclear, { "h(17)" }                                     , { { ParticleID::helion(), 1 } }, 17 },
      Entry{  100000018, 768, InteractionType::Nuclear, { "h(18)" }                                     , { { ParticleID::helion(), 1 } }, 18 },
      Entry{  100000019, 769, InteractionType::Nuclear, { "h(19)" }                                     , { { ParticleID::helion(), 1 } }, 19 },
      Entry{  100000020, 770, InteractionType::Nuclear, { "h(20)" }                                     , { { ParticleID::helion(), 1 } }, 20 },
      Entry{  100000021, 771, InteractionType::Nuclear, { "h(21)" }                                     , { { ParticleID::helion(), 1 } }, 21 },
      Entry{  100000022, 772, InteractionType::Nuclear, { "h(22)" }                                     , { { ParticleID::helion(), 1 } }, 22 },
      Entry{  100000023, 773, InteractionType::Nuclear, { "h(23)" }                                     , { { ParticleID::helion(), 1 } }, 23 },
      Entry{  100000024, 774, InteractionType::Nuclear, { "h(24)" }                                     , { { ParticleID::helion(), 1 } }, 24 },
      Entry{  100000025, 775, InteractionType::Nuclear, { "h(25)" }                                     , { { ParticleID::helion(), 1 } }, 25 },
      Entry{  100000026, 776, InteractionType::Nuclear, { "h(26)" }                                     , { { ParticleID::helion(), 1 } }, 26 },
      Entry{  100000027, 777, InteractionType::Nuclear, { "h(27)" }                                     , { { ParticleID::helion(), 1 } }, 27 },
      Entry{  100000028, 778, InteractionType::Nuclear, { "h(28)" }                                     , { { ParticleID::helion(), 1 } }, 28 },
      Entry{  100000029, 779, InteractionType::Nuclear, { "h(29)" }                                     , { { ParticleID::helion(), 1 } }, 29 },
      Entry{  100000030, 780, InteractionType::Nuclear, { "h(30)" }                                     , { { ParticleID::helion(), 1 } }, 30 },
      Entry{  100000031, 781, InteractionType::Nuclear, { "h(31)" }                                     , { { ParticleID::helion(), 1 } }, 31 },
      Entry{  100000032, 782, InteractionType::Nuclear, { "h(32)" }                                     , { { ParticleID::helion(), 1 } }, 32 },
      Entry{  100000033, 783, InteractionType::Nuclear, { "h(33)" }                                     , { { ParticleID::helion(), 1 } }, 33 },
      Entry{  100000034, 784, InteractionType::Nuclear, { "h(34)" }                                     , { { ParticleID::helion(), 1 } }, 34 },
      Entry{  100000035, 785, InteractionType::Nuclear, { "h(35)" }                                     , { { ParticleID::helion(), 1 } }, 35 },
      Entry{  100000036, 786, InteractionType::Nuclear, { "h(36)" }                                     , { { ParticleID::helion(), 1 } }, 36 },
      Entry{  100000037, 787, InteractionType::Nuclear, { "h(37)" }                                     , { { ParticleID::helion(), 1 } }, 37 },
      Entry{  100000038, 788, InteractionType::Nuclear, { "h(38)" }                                     , { { ParticleID::helion(), 1 } }, 38 },
      Entry{  100000039, 789, InteractionType::Nuclear, { "h(39)" }                                     , { { ParticleID::helion(), 1 } }, 39 },
      Entry{  100000040, 790, InteractionType::Nuclear, { "h(40)" }                                     , { { ParticleID::helion(), 1 } }, 40 },
      Entry{  100000041, 791, InteractionType::Nuclear, { "h(41)" }                                     , { { ParticleID::helion(), 1 } }, 41 },
      Entry{  100000042, 792, InteractionType::Nuclear, { "h(42)" }                                     , { { ParticleID::helion(), 1 } }, 42 },
      Entry{  100000043, 793, InteractionType::Nuclear, { "h(43)" }                                     , { { ParticleID::helion(), 1 } }, 43 },
      Entry{  100000044, 794, InteractionType::Nuclear, { "h(44)" }                                     , { { ParticleID::helion(), 1 } }, 44 },
      Entry{  100000045, 795, InteractionType::Nuclear, { "h(45)" }                                     , { { ParticleID::helion(), 1 } }, 45 },
      Entry{  100000046, 796, InteractionType::Nuclear, { "h(46)" }                                     , { { ParticleID::helion(), 1 } }, 46 },
      Entry{  100000047, 797, InteractionType::Nuclear, { "h(47)" }                                     , { { ParticleID::helion(), 1 } }, 47 },
      Entry{  100000048, 798, InteractionType::Nuclear, { "h(48)" }                                     , { { ParticleID::helion(), 1 } }, 48 },
      Entry{  100000049,      InteractionType::Nuclear, { "h(49)" }                                     , { { ParticleID::helion(), 1 } }, 49 },
      Entry{  100000050,      InteractionType::Nuclear, { "h(50)" }                                     , { { ParticleID::helion(), 1 } }, 50 },
      Entry{  100000051,      InteractionType::Nuclear, { "h(51)" }                                     , { { ParticleID::helion(), 1 } }, 51 },
      Entry{  100000052,      InteractionType::Nuclear, { "h(52)" }                                     , { { ParticleID::helion(), 1 } }, 52 },
      Entry{  100000053,      InteractionType::Nuclear, { "h(53)" }                                     , { { ParticleID::helion(), 1 } }, 53 },
      Entry{  100000054,      InteractionType::Nuclear, { "h(54)" }                                     , { { ParticleID::helion(), 1 } }, 54 },
      Entry{  100000055,      InteractionType::Nuclear, { "h(55)" }                                     , { { ParticleID::helion(), 1 } }, 55 },
      Entry{  100000056,      InteractionType::Nuclear, { "h(56)" }                                     , { { ParticleID::helion(), 1 } }, 56 },
      Entry{  100000057,      InteractionType::Nuclear, { "h(57)" }                                     , { { ParticleID::helion(), 1 } }, 57 },
      Entry{  100000058,      InteractionType::Nuclear, { "h(58)" }                                     , { { ParticleID::helion(), 1 } }, 58 },
      Entry{  100000059,      InteractionType::Nuclear, { "h(59)" }                                     , { { ParticleID::helion(), 1 } }, 59 },
      Entry{  100000060,      InteractionType::Nuclear, { "h(60)" }                                     , { { ParticleID::helion(), 1 } }, 60 },
      Entry{  100000061,      InteractionType::Nuclear, { "h(61)" }                                     , { { ParticleID::helion(), 1 } }, 61 },
      Entry{  100000062,      InteractionType::Nuclear, { "h(62)" }                                     , { { ParticleID::helion(), 1 } }, 62 },
      Entry{  100000063,      InteractionType::Nuclear, { "h(63)" }                                     , { { ParticleID::helion(), 1 } }, 63 },
      Entry{  100000064,      InteractionType::Nuclear, { "h(64)" }                                     , { { ParticleID::helion(), 1 } }, 64 },
      Entry{  100000065,      InteractionType::Nuclear, { "h(65)" }                                     , { { ParticleID::helion(), 1 } }, 65 },
      Entry{  100000066,      InteractionType::Nuclear, { "h(66)" }                                     , { { ParticleID::helion(), 1 } }, 66 },
      Entry{  100000067,      InteractionType::Nuclear, { "h(67)" }                                     , { { ParticleID::helion(), 1 } }, 67 },
      Entry{  100000068,      InteractionType::Nuclear, { "h(68)" }                                     , { { ParticleID::helion(), 1 } }, 68 },
      Entry{  100000069,      InteractionType::Nuclear, { "h(69)" }                                     , { { ParticleID::helion(), 1 } }, 69 },
      Entry{  100000070,      InteractionType::Nuclear, { "h(70)" }                                     , { { ParticleID::helion(), 1 } }, 70 },
      Entry{  100000071,      InteractionType::Nuclear, { "h(71)" }                                     , { { ParticleID::helion(), 1 } }, 71 },
      Entry{  100000072,      InteractionType::Nuclear, { "h(72)" }                                     , { { ParticleID::helion(), 1 } }, 72 },
      Entry{  100000073,      InteractionType::Nuclear, { "h(73)" }                                     , { { ParticleID::helion(), 1 } }, 73 },
      Entry{  100000074,      InteractionType::Nuclear, { "h(74)" }                                     , { { ParticleID::helion(), 1 } }, 74 },
      Entry{  100000075,      InteractionType::Nuclear, { "h(75)" }                                     , { { ParticleID::helion(), 1 } }, 75 },
      Entry{  100000076,      InteractionType::Nuclear, { "h(76)" }                                     , { { ParticleID::helion(), 1 } }, 76 },
      Entry{  100000077,      InteractionType::Nuclear, { "h(77)" }                                     , { { ParticleID::helion(), 1 } }, 77 },
      Entry{  100000078,      InteractionType::Nuclear, { "h(78)" }                                     , { { ParticleID::helion(), 1 } }, 78 },
      Entry{  100000079,      InteractionType::Nuclear, { "h(79)" }                                     , { { ParticleID::helion(), 1 } }, 79 },
      Entry{  100000080,      InteractionType::Nuclear, { "h(80)" }                                     , { { ParticleID::helion(), 1 } }, 80 },
      Entry{  100000081,      InteractionType::Nuclear, { "h(81)" }                                     , { { ParticleID::helion(), 1 } }, 81 },
      Entry{  100000082,      InteractionType::Nuclear, { "h(82)" }                                     , { { ParticleID::helion(), 1 } }, 82 },
      Entry{  100000083,      InteractionType::Nuclear, { "h(83)" }                                     , { { ParticleID::helion(), 1 } }, 83 },
      Entry{  100000084,      InteractionType::Nuclear, { "h(84)" }                                     , { { ParticleID::helion(), 1 } }, 84 },
      Entry{  100000085,      InteractionType::Nuclear, { "h(85)" }                                     , { { ParticleID::helion(), 1 } }, 85 },
      Entry{  100000086,      InteractionType::Nuclear, { "h(86)" }                                     , { { ParticleID::helion(), 1 } }, 86 },
      Entry{  100000087,      InteractionType::Nuclear, { "h(87)" }                                     , { { ParticleID::helion(), 1 } }, 87 },
      Entry{  100000088,      InteractionType::Nuclear, { "h(88)" }                                     , { { ParticleID::helion(), 1 } }, 88 },
      Entry{  100000089,      InteractionType::Nuclear, { "h(89)" }                                     , { { ParticleID::helion(), 1 } }, 89 },
      Entry{  100000090,      InteractionType::Nuclear, { "h(90)" }                                     , { { ParticleID::helion(), 1 } }, 90 },
      Entry{  100000091,      InteractionType::Nuclear, { "h(91)" }                                     , { { ParticleID::helion(), 1 } }, 91 },
      Entry{  100000092,      InteractionType::Nuclear, { "h(92)" }                                     , { { ParticleID::helion(), 1 } }, 92 },
      Entry{  100000093,      InteractionType::Nuclear, { "h(93)" }                                     , { { ParticleID::helion(), 1 } }, 93 },
      Entry{  100000094,      InteractionType::Nuclear, { "h(94)" }                                     , { { ParticleID::helion(), 1 } }, 94 },
      Entry{  100000095,      InteractionType::Nuclear, { "h(95)" }                                     , { { ParticleID::helion(), 1 } }, 95 },
      Entry{  100000096,      InteractionType::Nuclear, { "h(96)" }                                     , { { ParticleID::helion(), 1 } }, 96 },
      Entry{  100000097,      InteractionType::Nuclear, { "h(97)" }                                     , { { ParticleID::helion(), 1 } }, 97 },
      Entry{  100000098,      InteractionType::Nuclear, { "h(98)" }                                     , { { ParticleID::helion(), 1 } }, 98 },
      Entry{  100000099,      InteractionType::Nuclear, { "h(99)" }                                     , { { ParticleID::helion(), 1 } }, 99 },
      Entry{  100000150, 799, InteractionType::Nuclear, { "h(c)" }                                      , { { ParticleID::helion(), 1 } }, LevelID::continuum },
      Entry{  100000151, 106, InteractionType::Nuclear, { "h(t)", "h" }                                 , { { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  100010151,  34, InteractionType::Nuclear, { "nh(t)", "nh" , "n,h(t)", "n,h" }             , { { ParticleID::neutron(), 1 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  100020151, 176, InteractionType::Nuclear, { "2nh(t)", "2nh", "2n,h(t)", "2n,h" }          , { { ParticleID::neutron(), 2 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  100030151, 177, InteractionType::Nuclear, { "3nh(t)", "3nh", "3n,h(t)", "3n,h" }          , { { ParticleID::neutron(), 3 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  100040151, 178, InteractionType::Nuclear, { "4nh(t)", "4nh", "4n,h(t)", "4n,h" }          , { { ParticleID::neutron(), 4 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  100100151, 191, InteractionType::Nuclear, { "ph(t)", "ph" , "p,h(t)", "p,h" }             , { { ParticleID::proton(), 1 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  100110151, 186, InteractionType::Nuclear, { "nph(t)", "nph", "n,p,h(t)", "n,p,h" }        , { { ParticleID::neutron(), 1 }, { ParticleID::proton(), 1 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  101000151, 192, InteractionType::Nuclear, { "dh(t)", "dh" , "d,h(t)", "d,h" }             , { { ParticleID::deuteron(), 1 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  101010151, 187, InteractionType::Nuclear, { "ndh(t)", "ndh", "n,d,h(t)", "n,d,h" }        , { { ParticleID::neutron(), 1 }, { ParticleID::deuteron(), 1 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  110010151, 188, InteractionType::Nuclear, { "nth(t)", "nth", "n,t,h(t)", "n,t,h" }        , { { ParticleID::neutron(), 1 }, { ParticleID::triton(), 1 }, { ParticleID::helion(), 1 } }, LevelID::all },

      Entry{ 1000000000, 800, InteractionType::Nuclear, { "a(0)" }                                      , { { ParticleID::alpha(), 1 } }, 0 },
      Entry{ 1000000001, 801, InteractionType::Nuclear, { "a(1)" }                                      , { { ParticleID::alpha(), 1 } }, 1 },
      Entry{ 1000000002, 802, InteractionType::Nuclear, { "a(2)" }                                      , { { ParticleID::alpha(), 1 } }, 2 },
      Entry{ 1000000003, 803, InteractionType::Nuclear, { "a(3)" }                                      , { { ParticleID::alpha(), 1 } }, 3 },
      Entry{ 1000000004, 804, InteractionType::Nuclear, { "a(4)" }                                      , { { ParticleID::alpha(), 1 } }, 4 },
      Entry{ 1000000005, 805, InteractionType::Nuclear, { "a(5)" }                                      , { { ParticleID::alpha(), 1 } }, 5 },
      Entry{ 1000000006, 806, InteractionType::Nuclear, { "a(6)" }                                      , { { ParticleID::alpha(), 1 } }, 6 },
      Entry{ 1000000007, 807, InteractionType::Nuclear, { "a(7)" }                                      , { { ParticleID::alpha(), 1 } }, 7 },
      Entry{ 1000000008, 808, InteractionType::Nuclear, { "a(8)" }                                      , { { ParticleID::alpha(), 1 } }, 8 },
      Entry{ 1000000009, 809, InteractionType::Nuclear, { "a(9)" }                                      , { { ParticleID::alpha(), 1 } }, 9 },
      Entry{ 1000000010, 810, InteractionType::Nuclear, { "a(10)" }                                     , { { ParticleID::alpha(), 1 } }, 10 },
      Entry{ 1000000011, 811, InteractionType::Nuclear, { "a(11)" }                                     , { { ParticleID::alpha(), 1 } }, 11 },
      Entry{ 1000000012, 812, InteractionType::Nuclear, { "a(12)" }                                     , { { ParticleID::alpha(), 1 } }, 12 },
      Entry{ 1000000013, 813, InteractionType::Nuclear, { "a(13)" }                                     , { { ParticleID::alpha(), 1 } }, 13 },
      Entry{ 1000000014, 814, InteractionType::Nuclear, { "a(14)" }                                     , { { ParticleID::alpha(), 1 } }, 14 },
      Entry{ 1000000015, 815, InteractionType::Nuclear, { "a(15)" }                                     , { { ParticleID::alpha(), 1 } }, 15 },
      Entry{ 1000000016, 816, InteractionType::Nuclear, { "a(16)" }                                     , { { ParticleID::alpha(), 1 } }, 16 },
      Entry{ 1000000017, 817, InteractionType::Nuclear, { "a(17)" }                                     , { { ParticleID::alpha(), 1 } }, 17 },
      Entry{ 1000000018, 818, InteractionType::Nuclear, { "a(18)" }                                     , { { ParticleID::alpha(), 1 } }, 18 },
      Entry{ 1000000019, 819, InteractionType::Nuclear, { "a(19)" }                                     , { { ParticleID::alpha(), 1 } }, 19 },
      Entry{ 1000000020, 820, InteractionType::Nuclear, { "a(20)" }                                     , { { ParticleID::alpha(), 1 } }, 20 },
      Entry{ 1000000021, 821, InteractionType::Nuclear, { "a(21)" }                                     , { { ParticleID::alpha(), 1 } }, 21 },
      Entry{ 1000000022, 822, InteractionType::Nuclear, { "a(22)" }                                     , { { ParticleID::alpha(), 1 } }, 22 },
      Entry{ 1000000023, 823, InteractionType::Nuclear, { "a(23)" }                                     , { { ParticleID::alpha(), 1 } }, 23 },
      Entry{ 1000000024, 824, InteractionType::Nuclear, { "a(24)" }                                     , { { ParticleID::alpha(), 1 } }, 24 },
      Entry{ 1000000025, 825, InteractionType::Nuclear, { "a(25)" }                                     , { { ParticleID::alpha(), 1 } }, 25 },
      Entry{ 1000000026, 826, InteractionType::Nuclear, { "a(26)" }                                     , { { ParticleID::alpha(), 1 } }, 26 },
      Entry{ 1000000027, 827, InteractionType::Nuclear, { "a(27)" }                                     , { { ParticleID::alpha(), 1 } }, 27 },
      Entry{ 1000000028, 828, InteractionType::Nuclear, { "a(28)" }                                     , { { ParticleID::alpha(), 1 } }, 28 },
      Entry{ 1000000029, 829, InteractionType::Nuclear, { "a(29)" }                                     , { { ParticleID::alpha(), 1 } }, 29 },
      Entry{ 1000000030, 830, InteractionType::Nuclear, { "a(30)" }                                     , { { ParticleID::alpha(), 1 } }, 30 },
      Entry{ 1000000031, 831, InteractionType::Nuclear, { "a(31)" }                                     , { { ParticleID::alpha(), 1 } }, 31 },
      Entry{ 1000000032, 832, InteractionType::Nuclear, { "a(32)" }                                     , { { ParticleID::alpha(), 1 } }, 32 },
      Entry{ 1000000033, 833, InteractionType::Nuclear, { "a(33)" }                                     , { { ParticleID::alpha(), 1 } }, 33 },
      Entry{ 1000000034, 834, InteractionType::Nuclear, { "a(34)" }                                     , { { ParticleID::alpha(), 1 } }, 34 },
      Entry{ 1000000035, 835, InteractionType::Nuclear, { "a(35)" }                                     , { { ParticleID::alpha(), 1 } }, 35 },
      Entry{ 1000000036, 836, InteractionType::Nuclear, { "a(36)" }                                     , { { ParticleID::alpha(), 1 } }, 36 },
      Entry{ 1000000037, 837, InteractionType::Nuclear, { "a(37)" }                                     , { { ParticleID::alpha(), 1 } }, 37 },
      Entry{ 1000000038, 838, InteractionType::Nuclear, { "a(38)" }                                     , { { ParticleID::alpha(), 1 } }, 38 },
      Entry{ 1000000039, 839, InteractionType::Nuclear, { "a(39)" }                                     , { { ParticleID::alpha(), 1 } }, 39 },
      Entry{ 1000000040, 840, InteractionType::Nuclear, { "a(40)" }                                     , { { ParticleID::alpha(), 1 } }, 40 },
      Entry{ 1000000041, 841, InteractionType::Nuclear, { "a(41)" }                                     , { { ParticleID::alpha(), 1 } }, 41 },
      Entry{ 1000000042, 842, InteractionType::Nuclear, { "a(42)" }                                     , { { ParticleID::alpha(), 1 } }, 42 },
      Entry{ 1000000043, 843, InteractionType::Nuclear, { "a(43)" }                                     , { { ParticleID::alpha(), 1 } }, 43 },
      Entry{ 1000000044, 844, InteractionType::Nuclear, { "a(44)" }                                     , { { ParticleID::alpha(), 1 } }, 44 },
      Entry{ 1000000045, 845, InteractionType::Nuclear, { "a(45)" }                                     , { { ParticleID::alpha(), 1 } }, 45 },
      Entry{ 1000000046, 846, InteractionType::Nuclear, { "a(46)" }                                     , { { ParticleID::alpha(), 1 } }, 46 },
      Entry{ 1000000047, 847, InteractionType::Nuclear, { "a(47)" }                                     , { { ParticleID::alpha(), 1 } }, 47 },
      Entry{ 1000000048, 848, InteractionType::Nuclear, { "a(48)" }                                     , { { ParticleID::alpha(), 1 } }, 48 },
      Entry{ 1000000049,      InteractionType::Nuclear, { "a(49)" }                                     , { { ParticleID::alpha(), 1 } }, 49 },
      Entry{ 1000000050,      InteractionType::Nuclear, { "a(50)" }                                     , { { ParticleID::alpha(), 1 } }, 50 },
      Entry{ 1000000051,      InteractionType::Nuclear, { "a(51)" }                                     , { { ParticleID::alpha(), 1 } }, 51 },
      Entry{ 1000000052,      InteractionType::Nuclear, { "a(52)" }                                     , { { ParticleID::alpha(), 1 } }, 52 },
      Entry{ 1000000053,      InteractionType::Nuclear, { "a(53)" }                                     , { { ParticleID::alpha(), 1 } }, 53 },
      Entry{ 1000000054,      InteractionType::Nuclear, { "a(54)" }                                     , { { ParticleID::alpha(), 1 } }, 54 },
      Entry{ 1000000055,      InteractionType::Nuclear, { "a(55)" }                                     , { { ParticleID::alpha(), 1 } }, 55 },
      Entry{ 1000000056,      InteractionType::Nuclear, { "a(56)" }                                     , { { ParticleID::alpha(), 1 } }, 56 },
      Entry{ 1000000057,      InteractionType::Nuclear, { "a(57)" }                                     , { { ParticleID::alpha(), 1 } }, 57 },
      Entry{ 1000000058,      InteractionType::Nuclear, { "a(58)" }                                     , { { ParticleID::alpha(), 1 } }, 58 },
      Entry{ 1000000059,      InteractionType::Nuclear, { "a(59)" }                                     , { { ParticleID::alpha(), 1 } }, 59 },
      Entry{ 1000000060,      InteractionType::Nuclear, { "a(60)" }                                     , { { ParticleID::alpha(), 1 } }, 60 },
      Entry{ 1000000061,      InteractionType::Nuclear, { "a(61)" }                                     , { { ParticleID::alpha(), 1 } }, 61 },
      Entry{ 1000000062,      InteractionType::Nuclear, { "a(62)" }                                     , { { ParticleID::alpha(), 1 } }, 62 },
      Entry{ 1000000063,      InteractionType::Nuclear, { "a(63)" }                                     , { { ParticleID::alpha(), 1 } }, 63 },
      Entry{ 1000000064,      InteractionType::Nuclear, { "a(64)" }                                     , { { ParticleID::alpha(), 1 } }, 64 },
      Entry{ 1000000065,      InteractionType::Nuclear, { "a(65)" }                                     , { { ParticleID::alpha(), 1 } }, 65 },
      Entry{ 1000000066,      InteractionType::Nuclear, { "a(66)" }                                     , { { ParticleID::alpha(), 1 } }, 66 },
      Entry{ 1000000067,      InteractionType::Nuclear, { "a(67)" }                                     , { { ParticleID::alpha(), 1 } }, 67 },
      Entry{ 1000000068,      InteractionType::Nuclear, { "a(68)" }                                     , { { ParticleID::alpha(), 1 } }, 68 },
      Entry{ 1000000069,      InteractionType::Nuclear, { "a(69)" }                                     , { { ParticleID::alpha(), 1 } }, 69 },
      Entry{ 1000000070,      InteractionType::Nuclear, { "a(70)" }                                     , { { ParticleID::alpha(), 1 } }, 70 },
      Entry{ 1000000071,      InteractionType::Nuclear, { "a(71)" }                                     , { { ParticleID::alpha(), 1 } }, 71 },
      Entry{ 1000000072,      InteractionType::Nuclear, { "a(72)" }                                     , { { ParticleID::alpha(), 1 } }, 72 },
      Entry{ 1000000073,      InteractionType::Nuclear, { "a(73)" }                                     , { { ParticleID::alpha(), 1 } }, 73 },
      Entry{ 1000000074,      InteractionType::Nuclear, { "a(74)" }                                     , { { ParticleID::alpha(), 1 } }, 74 },
      Entry{ 1000000075,      InteractionType::Nuclear, { "a(75)" }                                     , { { ParticleID::alpha(), 1 } }, 75 },
      Entry{ 1000000076,      InteractionType::Nuclear, { "a(76)" }                                     , { { ParticleID::alpha(), 1 } }, 76 },
      Entry{ 1000000077,      InteractionType::Nuclear, { "a(77)" }                                     , { { ParticleID::alpha(), 1 } }, 77 },
      Entry{ 1000000078,      InteractionType::Nuclear, { "a(78)" }                                     , { { ParticleID::alpha(), 1 } }, 78 },
      Entry{ 1000000079,      InteractionType::Nuclear, { "a(79)" }                                     , { { ParticleID::alpha(), 1 } }, 79 },
      Entry{ 1000000080,      InteractionType::Nuclear, { "a(80)" }                                     , { { ParticleID::alpha(), 1 } }, 80 },
      Entry{ 1000000081,      InteractionType::Nuclear, { "a(81)" }                                     , { { ParticleID::alpha(), 1 } }, 81 },
      Entry{ 1000000082,      InteractionType::Nuclear, { "a(82)" }                                     , { { ParticleID::alpha(), 1 } }, 82 },
      Entry{ 1000000083,      InteractionType::Nuclear, { "a(83)" }                                     , { { ParticleID::alpha(), 1 } }, 83 },
      Entry{ 1000000084,      InteractionType::Nuclear, { "a(84)" }                                     , { { ParticleID::alpha(), 1 } }, 84 },
      Entry{ 1000000085,      InteractionType::Nuclear, { "a(85)" }                                     , { { ParticleID::alpha(), 1 } }, 85 },
      Entry{ 1000000086,      InteractionType::Nuclear, { "a(86)" }                                     , { { ParticleID::alpha(), 1 } }, 86 },
      Entry{ 1000000087,      InteractionType::Nuclear, { "a(87)" }                                     , { { ParticleID::alpha(), 1 } }, 87 },
      Entry{ 1000000088,      InteractionType::Nuclear, { "a(88)" }                                     , { { ParticleID::alpha(), 1 } }, 88 },
      Entry{ 1000000089,      InteractionType::Nuclear, { "a(89)" }                                     , { { ParticleID::alpha(), 1 } }, 89 },
      Entry{ 1000000090,      InteractionType::Nuclear, { "a(90)" }                                     , { { ParticleID::alpha(), 1 } }, 90 },
      Entry{ 1000000091,      InteractionType::Nuclear, { "a(91)" }                                     , { { ParticleID::alpha(), 1 } }, 91 },
      Entry{ 1000000092,      InteractionType::Nuclear, { "a(92)" }                                     , { { ParticleID::alpha(), 1 } }, 92 },
      Entry{ 1000000093,      InteractionType::Nuclear, { "a(93)" }                                     , { { ParticleID::alpha(), 1 } }, 93 },
      Entry{ 1000000094,      InteractionType::Nuclear, { "a(94)" }                                     , { { ParticleID::alpha(), 1 } }, 94 },
      Entry{ 1000000095,      InteractionType::Nuclear, { "a(95)" }                                     , { { ParticleID::alpha(), 1 } }, 95 },
      Entry{ 1000000096,      InteractionType::Nuclear, { "a(96)" }                                     , { { ParticleID::alpha(), 1 } }, 96 },
      Entry{ 1000000097,      InteractionType::Nuclear, { "a(97)" }                                     , { { ParticleID::alpha(), 1 } }, 97 },
      Entry{ 1000000098,      InteractionType::Nuclear, { "a(98)" }                                     , { { ParticleID::alpha(), 1 } }, 98 },
      Entry{ 1000000099,      InteractionType::Nuclear, { "a(99)" }                                     , { { ParticleID::alpha(), 1 } }, 99 },
      Entry{ 1000000150, 849, InteractionType::Nuclear, { "a(c)" }                                      , { { ParticleID::alpha(), 1 } }, LevelID::continuum },
      Entry{ 1000000151, 107, InteractionType::Nuclear, { "a(t)", "a" }                                 , { { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000010151,  22, InteractionType::Nuclear, { "na(t)", "na", "n,a(t)", "n,a" }              , { { ParticleID::neutron(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000020151,  24, InteractionType::Nuclear, { "2na(t)", "2na", "2n,a(t)", "2n,a" }          , { { ParticleID::neutron(), 2 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000030151,  25, InteractionType::Nuclear, { "3na(t)", "3na", "3n,a(t)", "3n,a" }          , { { ParticleID::neutron(), 3 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000040151, 165, InteractionType::Nuclear, { "4na(t)", "4na", "4n,a(t)", "4n,a" }          , { { ParticleID::neutron(), 4 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000050151, 166, InteractionType::Nuclear, { "5na(t)", "5na", "5n,a(t)", "5n,a" }          , { { ParticleID::neutron(), 5 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000060151, 167, InteractionType::Nuclear, { "6na(t)", "6na", "6n,a(t)", "6n,a" }          , { { ParticleID::neutron(), 6 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000070151, 168, InteractionType::Nuclear, { "7na(t)", "7na", "7n,a(t)", "7n,a" }          , { { ParticleID::neutron(), 7 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000100151, 112, InteractionType::Nuclear, { "pa(t)", "pa", "p,a(t)", "p,a" }              , { { ParticleID::proton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000110151,  45, InteractionType::Nuclear, { "npa(t)", "npa", "n,p,a(t)", "n,p,a" }        , { { ParticleID::neutron(), 1 }, { ParticleID::proton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000120151, 159, InteractionType::Nuclear, { "2npa(t)", "2npa", "2n,p,a(t)", "2n,p,a" }    , { { ParticleID::neutron(), 2 }, { ParticleID::proton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000130151, 181, InteractionType::Nuclear, { "3npa(t)", "3npa", "3n,p,a(t)", "3n,p,a" }    , { { ParticleID::neutron(), 3 }, { ParticleID::proton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000140151, 196, InteractionType::Nuclear, { "4npa(t)", "4npa", "4n,p,a(t)", "4n,p,a" }    , { { ParticleID::neutron(), 4 }, { ParticleID::proton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000230151, 199, InteractionType::Nuclear, { "3n2pa(t)", "3n2pa", "3n,2p,a(t)", "3n,2p,a" }, { { ParticleID::neutron(), 3 }, { ParticleID::proton(), 2 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1001000151, 117, InteractionType::Nuclear, { "da(t)", "da", "d,a(t)", "d,a" }              , { { ParticleID::deuteron(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1001010151, 158, InteractionType::Nuclear, { "nda(t)", "nda", "n,d,a(t)", "n,d,a" }        , { { ParticleID::neutron(), 1 }, { ParticleID::deuteron(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1010000151, 155, InteractionType::Nuclear, { "ta(t)", "ta", "t,a(t)", "t,a" }              , { { ParticleID::triton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1010010151, 189, InteractionType::Nuclear, { "nta(t)", "nta", "n,t,a(t)", "n,t,a" }        , { { ParticleID::neutron(), 1 }, { ParticleID::triton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1100000151, 193, InteractionType::Nuclear, { "ha(t)", "ha", "h,a(t)", "h,a" }              , { { ParticleID::helion(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 2000000151, 108, InteractionType::Nuclear, { "2a(t)", "2a" }                               , { { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2000010151,  29, InteractionType::Nuclear, { "n2a(t)", "n2a", "n,2a(t)", "n,2a" }          , { { ParticleID::neutron(), 1 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2000020151,  30, InteractionType::Nuclear, { "2n2a(t)", "2n2a", "2n,2a(t)", "2n,2a" }      , { { ParticleID::neutron(), 2 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2000030151, 180, InteractionType::Nuclear, { "3n2a(t)", "3n2a", "3n,2a(t)", "3n,2a" }      , { { ParticleID::neutron(), 3 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2000040151, 195, InteractionType::Nuclear, { "4n2a(t)", "4n2a", "4n,2a(t)", "4n,2a" }      , { { ParticleID::neutron(), 4 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2001000151, 114, InteractionType::Nuclear, { "d2a(t)", "d2a", "d,2a(t)", "d,2a" }          , { { ParticleID::deuteron(), 1 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2001010151,  35, InteractionType::Nuclear, { "nd2a(t)", "nd2a", "n,d,2a(t)", "n,d,2a" }    , { { ParticleID::neutron(), 1 }, { ParticleID::deuteron(), 1 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2010000151, 113, InteractionType::Nuclear, { "t2a(t)", "t2a", "t,2a(t)", "t,2a" }          , { { ParticleID::triton(), 1 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2010010151,  36, InteractionType::Nuclear, { "nt2a(t)", "nt2a", "n,t,2a(t)", "n,t,2a" }    , { { ParticleID::neutron(), 1 }, { ParticleID::triton(), 1 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 3000000151, 109, InteractionType::Nuclear, { "3a(t)", "3a" }                               , { { ParticleID::alpha(), 3 } }, LevelID::all },
      Entry{ 3000010151,  23, InteractionType::Nuclear, { "n3a(t)", "n3a", "n,3a(t)", "n,3a" }          , { { ParticleID::neutron(), 1 }, { ParticleID::alpha(), 3 } }, LevelID::all },

      // photoatomic only
      // check for what to do with 523 - is it used in evaluations?
      Entry{        502, 502, InteractionType::Atomic , { "coherent", "coherent-scattering" }            , {} },
      Entry{        504, 504, InteractionType::Atomic , { "incoherent", "incoherent-scattering" }        , {} },
      Entry{       1515, 515, InteractionType::Atomic , { "pair-production-electron", "2e-e+", "2e-,e+" }, { { ParticleID::electron(), 2 }, { ParticleID::positron(), 1 } } },
      Entry{       1517, 517, InteractionType::Atomic , { "pair-production-nuclear", "e-e+", "e-,e+" }   , { { ParticleID::electron(), 1 }, { ParticleID::positron(), 1 } } },
      Entry{       1518, 516, InteractionType::Atomic , { "pair-production" } },

      // electroatomic only
      Entry{       1524,      InteractionType::Atomic , { "deficit-scattering", "e-[deficit-scattering]" }        , { { ParticleID::electron(), 1 } } },
      Entry{       1525, 525, InteractionType::Atomic , { "large-angle-scattering", "e-[large-angle-scattering]" }, { { ParticleID::electron(), 1 } } },
      Entry{       1526, 526, InteractionType::Atomic , { "total-scattering", "e-[total-scattering]" }            , { { ParticleID::electron(), 1 } } },
      Entry{       1527, 527, InteractionType::Atomic , { "bremsstrahlung", "e-[bremsstrahlung]" }                , { { ParticleID::electron(), 1 } } },
      Entry{       1528, 528, InteractionType::Atomic , { "excitation", "e-[excitation]" }                        , { { ParticleID::electron(), 1 } } },

      // both photoatomic and electroatomic
      Entry{        501, 501, InteractionType::Atomic , { "total[atomic]" } },  // the symbol must be unique and total is already taken

      // only ionisation reactions have a subshell identifier
      // for photoionisation there is only one outgoing electron (the electron knocked off)
      // for electro-ionisation there are two outgoing electrons (the incident one and the electron knocked off)
      // mt numbers for these cannot be used for constructing a ReactionType
      Entry{       1534, 534, InteractionType::Atomic , { "photo-ionisation{1s1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::K  },
      Entry{       1535, 535, InteractionType::Atomic , { "photo-ionisation{2s1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::L1  },
      Entry{       1536, 536, InteractionType::Atomic , { "photo-ionisation{2p1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::L2  },
      Entry{       1537, 537, InteractionType::Atomic , { "photo-ionisation{2p3/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::L3  },
      Entry{       1538, 538, InteractionType::Atomic , { "photo-ionisation{3s1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::M1  },
      Entry{       1539, 539, InteractionType::Atomic , { "photo-ionisation{3p1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::M2  },
      Entry{       1540, 540, InteractionType::Atomic , { "photo-ionisation{3p3/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::M3  },
      Entry{       1541, 541, InteractionType::Atomic , { "photo-ionisation{3d3/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::M4  },
      Entry{       1542, 542, InteractionType::Atomic , { "photo-ionisation{3d5/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::M5  },
      Entry{       1543, 543, InteractionType::Atomic , { "photo-ionisation{4s1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::N1  },
      Entry{       1544, 544, InteractionType::Atomic , { "photo-ionisation{4p1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::N2  },
      Entry{       1545, 545, InteractionType::Atomic , { "photo-ionisation{4p3/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::N3  },
      Entry{       1546, 546, InteractionType::Atomic , { "photo-ionisation{4d3/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::N4  },
      Entry{       1547, 547, InteractionType::Atomic , { "photo-ionisation{4d5/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::N5  },
      Entry{       1548, 548, InteractionType::Atomic , { "photo-ionisation{4f5/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::N6  },
      Entry{       1549, 549, InteractionType::Atomic , { "photo-ionisation{4f7/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::N7  },
      Entry{       1550, 550, InteractionType::Atomic , { "photo-ionisation{5s1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::O1  },
      Entry{       1551, 551, InteractionType::Atomic , { "photo-ionisation{5p1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::O2  },
      Entry{       1552, 552, InteractionType::Atomic , { "photo-ionisation{5p3/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::O3  },
      Entry{       1553, 553, InteractionType::Atomic , { "photo-ionisation{5d3/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::O4  },
      Entry{       1554, 554, InteractionType::Atomic , { "photo-ionisation{5d5/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::O5  },
      Entry{       1555, 555, InteractionType::Atomic , { "photo-ionisation{5f5/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::O6  },
      Entry{       1556, 556, InteractionType::Atomic , { "photo-ionisation{5f7/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::O7  },
      Entry{       1557, 557, InteractionType::Atomic , { "photo-ionisation{5g7/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::O8  },
      Entry{       1558, 558, InteractionType::Atomic , { "photo-ionisation{5g9/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::O9  },
      Entry{       1559, 559, InteractionType::Atomic , { "photo-ionisation{6s1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::P1  },
      Entry{       1560, 560, InteractionType::Atomic , { "photo-ionisation{6p1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::P2  },
      Entry{       1561, 561, InteractionType::Atomic , { "photo-ionisation{6p3/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::P3  },
      Entry{       1562, 562, InteractionType::Atomic , { "photo-ionisation{6d3/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::P4  },
      Entry{       1563, 563, InteractionType::Atomic , { "photo-ionisation{6d5/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::P5  },
      Entry{       1564, 564, InteractionType::Atomic , { "photo-ionisation{6f5/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::P6  },
      Entry{       1565, 565, InteractionType::Atomic , { "photo-ionisation{6f7/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::P7  },
      Entry{       1566, 566, InteractionType::Atomic , { "photo-ionisation{6g7/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::P8  },
      Entry{       1567, 567, InteractionType::Atomic , { "photo-ionisation{6g9/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::P9  },
      Entry{       1568, 568, InteractionType::Atomic , { "photo-ionisation{6h9/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::P10 },
      Entry{       1569, 569, InteractionType::Atomic , { "photo-ionisation{6h11/2}" }  , { { ParticleID::electron(), 1 } }, ElectronSubshellID::P11 },
      Entry{       1570, 570, InteractionType::Atomic , { "photo-ionisation{7s1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q1  },
      Entry{       1571, 571, InteractionType::Atomic , { "photo-ionisation{7p1/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q2  },
      Entry{       1572, 572, InteractionType::Atomic , { "photo-ionisation{7p3/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q3  },
      Entry{       1573,      InteractionType::Atomic , { "photo-ionisation{7d3/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q4  },
      Entry{       1574,      InteractionType::Atomic , { "photo-ionisation{7d5/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q5  },
      Entry{       1575,      InteractionType::Atomic , { "photo-ionisation{7f5/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q6  },
      Entry{       1576,      InteractionType::Atomic , { "photo-ionisation{7f7/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q7  },
      Entry{       1577,      InteractionType::Atomic , { "photo-ionisation{7g7/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q8  },
      Entry{       1578,      InteractionType::Atomic , { "photo-ionisation{7g9/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q9  },
      Entry{       1579,      InteractionType::Atomic , { "photo-ionisation{7h9/2}" }   , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q10 },
      Entry{       1580,      InteractionType::Atomic , { "photo-ionisation{7h11/2}" }  , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q11 },
      Entry{       1581,      InteractionType::Atomic , { "photo-ionisation{7i11/2}" }  , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q12 },
      Entry{       1582,      InteractionType::Atomic , { "photo-ionisation{7i13/2}" }  , { { ParticleID::electron(), 1 } }, ElectronSubshellID::Q13 },
      Entry{       1583, 522, InteractionType::Atomic , { "photo-ionisation"          } , { { ParticleID::electron(), 1 } } },
      Entry{       2534, 534, InteractionType::Atomic , { "electro-ionisation{1s1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::K  },
      Entry{       2535, 535, InteractionType::Atomic , { "electro-ionisation{2s1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::L1  },
      Entry{       2536, 536, InteractionType::Atomic , { "electro-ionisation{2p1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::L2  },
      Entry{       2537, 537, InteractionType::Atomic , { "electro-ionisation{2p3/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::L3  },
      Entry{       2538, 538, InteractionType::Atomic , { "electro-ionisation{3s1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::M1  },
      Entry{       2539, 539, InteractionType::Atomic , { "electro-ionisation{3p1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::M2  },
      Entry{       2540, 540, InteractionType::Atomic , { "electro-ionisation{3p3/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::M3  },
      Entry{       2541, 541, InteractionType::Atomic , { "electro-ionisation{3d3/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::M4  },
      Entry{       2542, 542, InteractionType::Atomic , { "electro-ionisation{3d5/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::M5  },
      Entry{       2543, 543, InteractionType::Atomic , { "electro-ionisation{4s1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::N1  },
      Entry{       2544, 544, InteractionType::Atomic , { "electro-ionisation{4p1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::N2  },
      Entry{       2545, 545, InteractionType::Atomic , { "electro-ionisation{4p3/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::N3  },
      Entry{       2546, 546, InteractionType::Atomic , { "electro-ionisation{4d3/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::N4  },
      Entry{       2547, 547, InteractionType::Atomic , { "electro-ionisation{4d5/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::N5  },
      Entry{       2548, 548, InteractionType::Atomic , { "electro-ionisation{4f5/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::N6  },
      Entry{       2549, 549, InteractionType::Atomic , { "electro-ionisation{4f7/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::N7  },
      Entry{       2550, 550, InteractionType::Atomic , { "electro-ionisation{5s1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::O1  },
      Entry{       2551, 551, InteractionType::Atomic , { "electro-ionisation{5p1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::O2  },
      Entry{       2552, 552, InteractionType::Atomic , { "electro-ionisation{5p3/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::O3  },
      Entry{       2553, 553, InteractionType::Atomic , { "electro-ionisation{5d3/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::O4  },
      Entry{       2554, 554, InteractionType::Atomic , { "electro-ionisation{5d5/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::O5  },
      Entry{       2555, 555, InteractionType::Atomic , { "electro-ionisation{5f5/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::O6  },
      Entry{       2556, 556, InteractionType::Atomic , { "electro-ionisation{5f7/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::O7  },
      Entry{       2557, 557, InteractionType::Atomic , { "electro-ionisation{5g7/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::O8  },
      Entry{       2558, 558, InteractionType::Atomic , { "electro-ionisation{5g9/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::O9  },
      Entry{       2559, 559, InteractionType::Atomic , { "electro-ionisation{6s1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::P1  },
      Entry{       2560, 560, InteractionType::Atomic , { "electro-ionisation{6p1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::P2  },
      Entry{       2561, 561, InteractionType::Atomic , { "electro-ionisation{6p3/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::P3  },
      Entry{       2562, 562, InteractionType::Atomic , { "electro-ionisation{6d3/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::P4  },
      Entry{       2563, 563, InteractionType::Atomic , { "electro-ionisation{6d5/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::P5  },
      Entry{       2564, 564, InteractionType::Atomic , { "electro-ionisation{6f5/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::P6  },
      Entry{       2565, 565, InteractionType::Atomic , { "electro-ionisation{6f7/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::P7  },
      Entry{       2566, 566, InteractionType::Atomic , { "electro-ionisation{6g7/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::P8  },
      Entry{       2567, 567, InteractionType::Atomic , { "electro-ionisation{6g9/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::P9  },
      Entry{       2568, 568, InteractionType::Atomic , { "electro-ionisation{6h9/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::P10 },
      Entry{       2569, 569, InteractionType::Atomic , { "electro-ionisation{6h11/2}" }, { { ParticleID::electron(), 2 } }, ElectronSubshellID::P11 },
      Entry{       2570, 570, InteractionType::Atomic , { "electro-ionisation{7s1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q1  },
      Entry{       2571, 571, InteractionType::Atomic , { "electro-ionisation{7p1/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q2  },
      Entry{       2572, 572, InteractionType::Atomic , { "electro-ionisation{7p3/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q3  },
      Entry{       2573,      InteractionType::Atomic , { "electro-ionisation{7d3/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q4  },
      Entry{       2574,      InteractionType::Atomic , { "electro-ionisation{7d5/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q5  },
      Entry{       2575,      InteractionType::Atomic , { "electro-ionisation{7f5/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q6  },
      Entry{       2576,      InteractionType::Atomic , { "electro-ionisation{7f7/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q7  },
      Entry{       2577,      InteractionType::Atomic , { "electro-ionisation{7g7/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q8  },
      Entry{       2578,      InteractionType::Atomic , { "electro-ionisation{7g9/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q9  },
      Entry{       2579,      InteractionType::Atomic , { "electro-ionisation{7h9/2}" } , { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q10 },
      Entry{       2580,      InteractionType::Atomic , { "electro-ionisation{7h11/2}" }, { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q11 },
      Entry{       2581,      InteractionType::Atomic , { "electro-ionisation{7i11/2}" }, { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q12 },
      Entry{       2582,      InteractionType::Atomic , { "electro-ionisation{7i13/2}" }, { { ParticleID::electron(), 2 } }, ElectronSubshellID::Q13 },
      Entry{       2583, 522, InteractionType::Atomic , { "electro-ionisation" }        , { { ParticleID::electron(), 2 } } }
    };
    static inline std::unordered_map< std::string, std::size_t >
    string_conversion_dictionary = [] ( const auto& entries ) {

      std::unordered_map< std::string, std::size_t > conversion;
      for ( std::size_t index = 0; index < entries.size(); ++index ) {

        for ( const auto& symbol : entries[ index ].symbols() ) {

          conversion[ symbol ] = index;
        }
      }
      return conversion;
    }( entries );
    static inline std::unordered_map< std::int64_t, std::size_t >
    particles_conversion_dictionary = [] ( const auto& entries ) {

      std::unordered_map< std::int64_t, std::size_t > conversion;
      for ( std::size_t index = 0; index < entries.size(); ++index ) {

        auto number = entries[index].number();
        if ( number >= 1000  ) {

          conversion[ number ] = index;
        }
      }
      return conversion;
    }( entries );
    static inline std::unordered_map< short, std::size_t >
    mt_conversion_dictionary = [] ( const auto& entries ) {

      std::unordered_map< short, std::size_t > conversion;
      for ( std::size_t index = 0; index < entries.size(); ++index ) {

        auto mt = entries[ index ].mt();
        if ( mt.has_value() ) {

          // exclude ionisation since the mt number applies to both
          // photoatomic and electroatomic reactions
          if ( ( ( mt.value() < 534 ) || ( mt.value() > 572 ) ) && ( mt.value() != 522 ) ) {

            conversion[ mt.value() ] = index;
          }
        }
      }
      return conversion;
    }( entries );

    /* fields */
    std::size_t index_;

    /* auxiliary functions */
    #include "dryad/id/ReactionType/src/getIndex.hpp"

  public:

    /* constructor */
    #include "dryad/id/ReactionType/src/ctor.hpp"

    /* predefined identifiers */

    /**
     *  @brief Return the total reaction type
     *
     *  @param[in] type   the interaction type (nuclear or atomic)
     */
    static ReactionType
    total( const InteractionType& type = InteractionType::Nuclear ) {

      if ( type == InteractionType::Nuclear ) {

        return ReactionType( static_cast< std::size_t >( 0 ) );
      }
      else {

        return ReactionType( static_cast< std::size_t >( 848 ) );
      }
    };

    /**
     *  @brief Return the elastic reaction type
     *
     *  @param[in] projectile   the projectile
     *  @param[in] level.       the level number of the target (default = 0)
     */
    static ReactionType
    elastic( const ParticleID& projectile, int level = 0 ) {

      if ( level >= 0 && level < 100 ) {

        if ( projectile == ParticleID::neutron() ) {

          return ReactionType( static_cast< std::size_t >( 132 + level ) );
        }
        else if ( projectile == ParticleID::photon() ) {

          return ReactionType( static_cast< std::size_t >( 30 + level ) );
        }
        else if ( projectile == ParticleID::proton() ) {

          return ReactionType( static_cast< std::size_t >( 258 + level ) );
        }
        else if ( projectile == ParticleID::deuteron() ) {

          return ReactionType( static_cast< std::size_t >( 375 + level ) );
        }
        else if ( projectile == ParticleID::triton() ) {

          return ReactionType( static_cast< std::size_t >( 484 + level ) );
        }
        else if ( projectile == ParticleID::helion() ) {

          return ReactionType( static_cast< std::size_t >( 596 + level ) );
        }
        else if ( projectile == ParticleID::alpha() ) {

          return ReactionType( static_cast< std::size_t >( 707 + level ) );
        }
      }

      Log::error( "Elastic scattering for \'{}\' to level \'{}\' is not defined",
                  projectile.symbol(), level );
      throw std::exception();
    };

    /* static methods */

    /**
     *  @brief Return the number of currently registered identifiers
     */
    static std::size_t size() {

      return entries.size();
    }

    /**
     *  @brief Return whether or not the mt number corresponds to a registered reaction type
     *
     *  This function does not recognise any of the ionisation mt numbers
     *  (522 for total ionisation and 534 through 572 for subshell ionisation)
     *  because electro- and photoinionisation cannot be distinguished by the
     *  mt number alone.
     *
     *  @param[in] mt   the mt number
     */
    static bool isRegistered( int mt ) {

      return mt_conversion_dictionary.find( mt ) != mt_conversion_dictionary.end();
    }

    /**
     *  @brief Return whether or not the string corresponds to a registered reaction type
     *
     *  @param[in] string   the string
     */
    static bool isRegistered( const std::string& string ) {

      return string_conversion_dictionary.find( string ) != string_conversion_dictionary.end();
    }

    /* methods */

    /**
     *  @brief Return the number for this reaction type
     *
     *  Note: this imposes logical order to the identifiers. It is public
     *        for test purposes only.
     */
    std::int64_t number() const {

      return entries[ this->index_ ].number();
    }

    /**
     *  @brief Return the interaction type (nuclear or atomic) for this reaction type
     */
    const InteractionType& interactionType() const {

      return entries[ this->index_ ].type();
    }

    /**
     *  @brief Return the mt number for this reaction type
     */
    const std::optional< short >& mt() const {

      return entries[ this->index_ ].mt();
    }

    /**
     *  @brief Return the symbol for this reaction type
     */
    const std::string& symbol() const {

      return entries[ this->index_ ].symbol();
    }

    /**
     *  @brief Return the particles emitted for this reaction type
     */
    const std::optional< std::map< ParticleID, short > >& particles() const {

      return entries[ this->index_ ].particles();
    }

    /**
     *  @brief Return the level or subshell of the residual for this reaction type
     */
    const std::optional< short >& level() const {

      return entries[ this->index_ ].level();
    }

    /**
     *  @brief Return the partial designator for this reaction type
     *
     *  A partial designator is used for some atomic interactions when the
     *  reaction type cannot be completely characterised with outgoing particles
     *  only. For example: both coherent and incoherent scattering have an outgoing
     *  photon.
     */
    const std::optional< std::string >& partialDesignator() const noexcept {

      return entries[ this->index_ ].partialDesignator();
    }

    /**
     *  @brief Return the symbol and alternatives
     */
    const std::vector< std::string >& symbols() const noexcept {

      return entries[ this->index_ ].symbols();
    }

    /**
     *  @brief Return whether or not the reaction type is considered a special type
     *
     *  A special type is a reaction type for which no outgoing particles types can be
     *  defined because it is a summation reaction or because the outgoing particles
     *  are not known due to complexity (e.g. anything or fission)
     */
    bool isSpecial() const {

      return !this->particles().has_value();
    }

    /**
     *  @brief Return whether or not the reaction type has a partial designator
     *
     *  A partial designator is used for some atomic interactions when the
     *  reaction type cannot be completely characterised with outgoing particles
     *  only. For example: both coherent and incoherent scattering have an outgoing
     *  photon.
     */
    bool hasPartialDesignator() const noexcept {

      return this->partialDesignator().has_value();
    }

    /**
     *  @brief Return whether or not the reaction type is ENDF compatible
     */
    bool isCompatibleWithENDF() const {

      return this->mt().has_value();
    }

    /**
     *  @brief Return the residual produced by this reaction type
     *
     *  @param[in] projectile   the projectile
     *  @param[in] target       the target
     */
    ParticleID resolve( const ParticleID& projectile, const ParticleID& target ) const {

      if ( this->isSpecial() ) {

        Log::error( "\'{}\' is a special reaction and cannot be resolved", this->symbol() );
        throw std::exception();
      }

      if ( this->interactionType() == InteractionType::Nuclear ) {

        int za = projectile.za() + target.za() - entries[ this->index_ ].dza().value();
        return ParticleID( za, this->level().value() );
      }
      else {

        // atomic reactions only work on elemental identifiers
        if ( target.a() != 0 ) {

          Log::error( "\'{}\' is an atomic interaction and only elemental targets be resolved" );
          throw std::exception();
        }

        // assign the subshell ID for the ion if we need to, otherwise just return the target
        if ( this->level().has_value() ) {

          return ParticleID( target.za(), this->level().value() );
        }
        else {

          return target;
        }
      }
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator==( const ReactionType& left, const ReactionType& right ) {

      return left.number() == right.number();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator!=( const ReactionType& left, const ReactionType& right ) {

      return ! ( left == right );
    }

    /**
     *  @brief Less than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<( const ReactionType& left, const ReactionType& right ) {

      return left.number() < right.number();
    }

    /**
     *  @brief Greater than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>( const ReactionType& left, const ReactionType& right ) {

      return right < left;
    }

    /**
     *  @brief Less than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<=( const ReactionType& left, const ReactionType& right ) {

      return ! ( right < left );
    }

    /**
     *  @brief Greater than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>=( const ReactionType& left, const ReactionType& right ) {

      return ! ( left < right );
    }
  };

} // id namespace
} // dryad namespace
} // njoy namespace

namespace std {

  // std::hash override for the ReactionType class
  template <>
  struct hash< njoy::dryad::id::ReactionType > {

    size_t operator()( const njoy::dryad::id::ReactionType& key ) const {

      return key.number();
    }
  };

} // namespace std

#endif
