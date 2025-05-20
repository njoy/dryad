#ifndef NJOY_DRYAD_ID_REACTIONTYPE
#define NJOY_DRYAD_ID_REACTIONTYPE

// system includes
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

// other includes
#include "dryad/InteractionType.hpp"
#include "dryad/id/LevelID.hpp"
#include "dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace id {

  class ReactionType {

    /* helper class */
    #include "dryad/id/ReactionType/Entry.hpp"

    static inline std::vector< Entry > entries{

      // nuclear reaction types

      // special types: reactions without ejectiles, unknown number and/or types of ejectiles, or with
      // ejectiles that depend on the projectile
      Entry{          1,   1, InteractionType::Nuclear, "total"        , { "nuclear total" } },
      Entry{          3,   3, InteractionType::Nuclear, "non-elastic"  , {} },
      Entry{          5,   5, InteractionType::Nuclear, "anything"     , {} },
      Entry{         18,  18, InteractionType::Nuclear, "fission(t)"   , {} },
      Entry{         19,  19, InteractionType::Nuclear, "fission"      , { "fission1" } },
      Entry{         20,  20, InteractionType::Nuclear, "fission[n]"   , { "fission2" } },
      Entry{         21,  21, InteractionType::Nuclear, "fission[2n]"  , { "fission3" } },
      Entry{         38,  38, InteractionType::Nuclear, "fission[3n]"  , { "fission4" } },
      Entry{         27,  27, InteractionType::Nuclear, "absorption"   , {} },
      Entry{        101, 101, InteractionType::Nuclear, "disappearance", {} },

      // ENDF normal reactions: reactions with ejectiles (not counting photons and residual)
      Entry{       1000,      InteractionType::Nuclear, "g(0)"         , {}                 , {}, 0 },
      Entry{       1001,      InteractionType::Nuclear, "g(1)"         , {}                 , {}, 1 },
      Entry{       1002,      InteractionType::Nuclear, "g(2)"         , {}                 , {}, 2 },
      Entry{       1003,      InteractionType::Nuclear, "g(3)"         , {}                 , {}, 3 },
      Entry{       1004,      InteractionType::Nuclear, "g(4)"         , {}                 , {}, 4 },
      Entry{       1005,      InteractionType::Nuclear, "g(5)"         , {}                 , {}, 5 },
      Entry{       1006,      InteractionType::Nuclear, "g(6)"         , {}                 , {}, 6 },
      Entry{       1007,      InteractionType::Nuclear, "g(7)"         , {}                 , {}, 7 },
      Entry{       1008,      InteractionType::Nuclear, "g(8)"         , {}                 , {}, 8 },
      Entry{       1009,      InteractionType::Nuclear, "g(9)"         , {}                 , {}, 9 },
      Entry{       1010,      InteractionType::Nuclear, "g(10)"        , {}                 , {}, 10 },
      Entry{       1011,      InteractionType::Nuclear, "g(11)"        , {}                 , {}, 11 },
      Entry{       1012,      InteractionType::Nuclear, "g(12)"        , {}                 , {}, 12 },
      Entry{       1013,      InteractionType::Nuclear, "g(13)"        , {}                 , {}, 13 },
      Entry{       1014,      InteractionType::Nuclear, "g(14)"        , {}                 , {}, 14 },
      Entry{       1015,      InteractionType::Nuclear, "g(15)"        , {}                 , {}, 15 },
      Entry{       1016,      InteractionType::Nuclear, "g(16)"        , {}                 , {}, 16 },
      Entry{       1017,      InteractionType::Nuclear, "g(17)"        , {}                 , {}, 17 },
      Entry{       1018,      InteractionType::Nuclear, "g(18)"        , {}                 , {}, 18 },
      Entry{       1019,      InteractionType::Nuclear, "g(19)"        , {}                 , {}, 19 },
      Entry{       1020,      InteractionType::Nuclear, "g(20)"        , {}                 , {}, 20 },
      Entry{       1021,      InteractionType::Nuclear, "g(21)"        , {}                 , {}, 21 },
      Entry{       1022,      InteractionType::Nuclear, "g(22)"        , {}                 , {}, 22 },
      Entry{       1023,      InteractionType::Nuclear, "g(23)"        , {}                 , {}, 23 },
      Entry{       1024,      InteractionType::Nuclear, "g(24)"        , {}                 , {}, 24 },
      Entry{       1025,      InteractionType::Nuclear, "g(25)"        , {}                 , {}, 25 },
      Entry{       1026,      InteractionType::Nuclear, "g(26)"        , {}                 , {}, 26 },
      Entry{       1027,      InteractionType::Nuclear, "g(27)"        , {}                 , {}, 27 },
      Entry{       1028,      InteractionType::Nuclear, "g(28)"        , {}                 , {}, 28 },
      Entry{       1029,      InteractionType::Nuclear, "g(29)"        , {}                 , {}, 29 },
      Entry{       1030,      InteractionType::Nuclear, "g(30)"        , {}                 , {}, 30 },
      Entry{       1031,      InteractionType::Nuclear, "g(31)"        , {}                 , {}, 31 },
      Entry{       1032,      InteractionType::Nuclear, "g(32)"        , {}                 , {}, 32 },
      Entry{       1033,      InteractionType::Nuclear, "g(33)"        , {}                 , {}, 33 },
      Entry{       1034,      InteractionType::Nuclear, "g(34)"        , {}                 , {}, 34 },
      Entry{       1035,      InteractionType::Nuclear, "g(35)"        , {}                 , {}, 35 },
      Entry{       1036,      InteractionType::Nuclear, "g(36)"        , {}                 , {}, 36 },
      Entry{       1037,      InteractionType::Nuclear, "g(37)"        , {}                 , {}, 37 },
      Entry{       1038,      InteractionType::Nuclear, "g(38)"        , {}                 , {}, 38 },
      Entry{       1039,      InteractionType::Nuclear, "g(39)"        , {}                 , {}, 39 },
      Entry{       1040,      InteractionType::Nuclear, "g(40)"        , {}                 , {}, 40 },
      Entry{       1041,      InteractionType::Nuclear, "g(41)"        , {}                 , {}, 41 },
      Entry{       1042,      InteractionType::Nuclear, "g(42)"        , {}                 , {}, 42 },
      Entry{       1043,      InteractionType::Nuclear, "g(43)"        , {}                 , {}, 43 },
      Entry{       1044,      InteractionType::Nuclear, "g(44)"        , {}                 , {}, 44 },
      Entry{       1045,      InteractionType::Nuclear, "g(45)"        , {}                 , {}, 45 },
      Entry{       1046,      InteractionType::Nuclear, "g(46)"        , {}                 , {}, 46 },
      Entry{       1047,      InteractionType::Nuclear, "g(47)"        , {}                 , {}, 47 },
      Entry{       1048,      InteractionType::Nuclear, "g(48)"        , {}                 , {}, 48 },
      Entry{       1049,      InteractionType::Nuclear, "g(49)"        , {}                 , {}, 49 },
      Entry{       1050,      InteractionType::Nuclear, "g(50)"        , {}                 , {}, 50 },
      Entry{       1051,      InteractionType::Nuclear, "g(51)"        , {}                 , {}, 51 },
      Entry{       1052,      InteractionType::Nuclear, "g(52)"        , {}                 , {}, 52 },
      Entry{       1053,      InteractionType::Nuclear, "g(53)"        , {}                 , {}, 53 },
      Entry{       1054,      InteractionType::Nuclear, "g(54)"        , {}                 , {}, 54 },
      Entry{       1055,      InteractionType::Nuclear, "g(55)"        , {}                 , {}, 55 },
      Entry{       1056,      InteractionType::Nuclear, "g(56)"        , {}                 , {}, 56 },
      Entry{       1057,      InteractionType::Nuclear, "g(57)"        , {}                 , {}, 57 },
      Entry{       1058,      InteractionType::Nuclear, "g(58)"        , {}                 , {}, 58 },
      Entry{       1059,      InteractionType::Nuclear, "g(59)"        , {}                 , {}, 59 },
      Entry{       1060,      InteractionType::Nuclear, "g(60)"        , {}                 , {}, 60 },
      Entry{       1061,      InteractionType::Nuclear, "g(61)"        , {}                 , {}, 61 },
      Entry{       1062,      InteractionType::Nuclear, "g(62)"        , {}                 , {}, 62 },
      Entry{       1063,      InteractionType::Nuclear, "g(63)"        , {}                 , {}, 63 },
      Entry{       1064,      InteractionType::Nuclear, "g(64)"        , {}                 , {}, 64 },
      Entry{       1065,      InteractionType::Nuclear, "g(65)"        , {}                 , {}, 65 },
      Entry{       1066,      InteractionType::Nuclear, "g(66)"        , {}                 , {}, 66 },
      Entry{       1067,      InteractionType::Nuclear, "g(67)"        , {}                 , {}, 67 },
      Entry{       1068,      InteractionType::Nuclear, "g(68)"        , {}                 , {}, 68 },
      Entry{       1069,      InteractionType::Nuclear, "g(69)"        , {}                 , {}, 69 },
      Entry{       1070,      InteractionType::Nuclear, "g(70)"        , {}                 , {}, 70 },
      Entry{       1071,      InteractionType::Nuclear, "g(71)"        , {}                 , {}, 71 },
      Entry{       1072,      InteractionType::Nuclear, "g(72)"        , {}                 , {}, 72 },
      Entry{       1073,      InteractionType::Nuclear, "g(73)"        , {}                 , {}, 73 },
      Entry{       1074,      InteractionType::Nuclear, "g(74)"        , {}                 , {}, 74 },
      Entry{       1075,      InteractionType::Nuclear, "g(75)"        , {}                 , {}, 75 },
      Entry{       1076,      InteractionType::Nuclear, "g(76)"        , {}                 , {}, 76 },
      Entry{       1077,      InteractionType::Nuclear, "g(77)"        , {}                 , {}, 77 },
      Entry{       1078,      InteractionType::Nuclear, "g(78)"        , {}                 , {}, 78 },
      Entry{       1079,      InteractionType::Nuclear, "g(79)"        , {}                 , {}, 79 },
      Entry{       1080,      InteractionType::Nuclear, "g(80)"        , {}                 , {}, 80 },
      Entry{       1081,      InteractionType::Nuclear, "g(81)"        , {}                 , {}, 81 },
      Entry{       1082,      InteractionType::Nuclear, "g(82)"        , {}                 , {}, 82 },
      Entry{       1083,      InteractionType::Nuclear, "g(83)"        , {}                 , {}, 83 },
      Entry{       1084,      InteractionType::Nuclear, "g(84)"        , {}                 , {}, 84 },
      Entry{       1085,      InteractionType::Nuclear, "g(85)"        , {}                 , {}, 85 },
      Entry{       1086,      InteractionType::Nuclear, "g(86)"        , {}                 , {}, 86 },
      Entry{       1087,      InteractionType::Nuclear, "g(87)"        , {}                 , {}, 87 },
      Entry{       1088,      InteractionType::Nuclear, "g(88)"        , {}                 , {}, 88 },
      Entry{       1089,      InteractionType::Nuclear, "g(89)"        , {}                 , {}, 89 },
      Entry{       1090,      InteractionType::Nuclear, "g(90)"        , {}                 , {}, 90 },
      Entry{       1091,      InteractionType::Nuclear, "g(91)"        , {}                 , {}, 91 },
      Entry{       1092,      InteractionType::Nuclear, "g(92)"        , {}                 , {}, 92 },
      Entry{       1093,      InteractionType::Nuclear, "g(93)"        , {}                 , {}, 93 },
      Entry{       1094,      InteractionType::Nuclear, "g(94)"        , {}                 , {}, 94 },
      Entry{       1095,      InteractionType::Nuclear, "g(95)"        , {}                 , {}, 95 },
      Entry{       1096,      InteractionType::Nuclear, "g(96)"        , {}                 , {}, 96 },
      Entry{       1097,      InteractionType::Nuclear, "g(97)"        , {}                 , {}, 97 },
      Entry{       1098,      InteractionType::Nuclear, "g(98)"        , {}                 , {}, 98 },
      Entry{       1150,      InteractionType::Nuclear, "g(c)"         , {}                 , {}, LevelID::continuum },
      Entry{       1151, 102, InteractionType::Nuclear, "g(t)"         , { "capture", "g" } , {}, LevelID::all },

      Entry{      10000,  50, InteractionType::Nuclear, "n(0)"         , {}                 , { { ParticleID::neutron(), 1 } }, 0 },
      Entry{      10001,  51, InteractionType::Nuclear, "n(1)"         , {}                 , { { ParticleID::neutron(), 1 } }, 1 },
      Entry{      10002,  52, InteractionType::Nuclear, "n(2)"         , {}                 , { { ParticleID::neutron(), 1 } }, 2 },
      Entry{      10003,  53, InteractionType::Nuclear, "n(3)"         , {}                 , { { ParticleID::neutron(), 1 } }, 3 },
      Entry{      10004,  54, InteractionType::Nuclear, "n(4)"         , {}                 , { { ParticleID::neutron(), 1 } }, 4 },
      Entry{      10005,  55, InteractionType::Nuclear, "n(5)"         , {}                 , { { ParticleID::neutron(), 1 } }, 5 },
      Entry{      10006,  56, InteractionType::Nuclear, "n(6)"         , {}                 , { { ParticleID::neutron(), 1 } }, 6 },
      Entry{      10007,  57, InteractionType::Nuclear, "n(7)"         , {}                 , { { ParticleID::neutron(), 1 } }, 7 },
      Entry{      10008,  58, InteractionType::Nuclear, "n(8)"         , {}                 , { { ParticleID::neutron(), 1 } }, 8 },
      Entry{      10009,  59, InteractionType::Nuclear, "n(9)"         , {}                 , { { ParticleID::neutron(), 1 } }, 9 },
      Entry{      10010,  60, InteractionType::Nuclear, "n(10)"        , {}                 , { { ParticleID::neutron(), 1 } }, 10 },
      Entry{      10011,  61, InteractionType::Nuclear, "n(11)"        , {}                 , { { ParticleID::neutron(), 1 } }, 11 },
      Entry{      10012,  62, InteractionType::Nuclear, "n(12)"        , {}                 , { { ParticleID::neutron(), 1 } }, 12 },
      Entry{      10013,  63, InteractionType::Nuclear, "n(13)"        , {}                 , { { ParticleID::neutron(), 1 } }, 13 },
      Entry{      10014,  64, InteractionType::Nuclear, "n(14)"        , {}                 , { { ParticleID::neutron(), 1 } }, 14 },
      Entry{      10015,  65, InteractionType::Nuclear, "n(15)"        , {}                 , { { ParticleID::neutron(), 1 } }, 15 },
      Entry{      10016,  66, InteractionType::Nuclear, "n(16)"        , {}                 , { { ParticleID::neutron(), 1 } }, 16 },
      Entry{      10017,  67, InteractionType::Nuclear, "n(17)"        , {}                 , { { ParticleID::neutron(), 1 } }, 17 },
      Entry{      10018,  68, InteractionType::Nuclear, "n(18)"        , {}                 , { { ParticleID::neutron(), 1 } }, 18 },
      Entry{      10019,  69, InteractionType::Nuclear, "n(19)"        , {}                 , { { ParticleID::neutron(), 1 } }, 19 },
      Entry{      10020,  70, InteractionType::Nuclear, "n(20)"        , {}                 , { { ParticleID::neutron(), 1 } }, 20 },
      Entry{      10021,  71, InteractionType::Nuclear, "n(21)"        , {}                 , { { ParticleID::neutron(), 1 } }, 21 },
      Entry{      10022,  72, InteractionType::Nuclear, "n(22)"        , {}                 , { { ParticleID::neutron(), 1 } }, 22 },
      Entry{      10023,  73, InteractionType::Nuclear, "n(23)"        , {}                 , { { ParticleID::neutron(), 1 } }, 23 },
      Entry{      10024,  74, InteractionType::Nuclear, "n(24)"        , {}                 , { { ParticleID::neutron(), 1 } }, 24 },
      Entry{      10025,  75, InteractionType::Nuclear, "n(25)"        , {}                 , { { ParticleID::neutron(), 1 } }, 25 },
      Entry{      10026,  76, InteractionType::Nuclear, "n(26)"        , {}                 , { { ParticleID::neutron(), 1 } }, 26 },
      Entry{      10027,  77, InteractionType::Nuclear, "n(27)"        , {}                 , { { ParticleID::neutron(), 1 } }, 27 },
      Entry{      10028,  78, InteractionType::Nuclear, "n(28)"        , {}                 , { { ParticleID::neutron(), 1 } }, 28 },
      Entry{      10029,  79, InteractionType::Nuclear, "n(29)"        , {}                 , { { ParticleID::neutron(), 1 } }, 29 },
      Entry{      10030,  80, InteractionType::Nuclear, "n(30)"        , {}                 , { { ParticleID::neutron(), 1 } }, 30 },
      Entry{      10031,  81, InteractionType::Nuclear, "n(31)"        , {}                 , { { ParticleID::neutron(), 1 } }, 31 },
      Entry{      10032,  82, InteractionType::Nuclear, "n(32)"        , {}                 , { { ParticleID::neutron(), 1 } }, 32 },
      Entry{      10033,  83, InteractionType::Nuclear, "n(33)"        , {}                 , { { ParticleID::neutron(), 1 } }, 33 },
      Entry{      10034,  84, InteractionType::Nuclear, "n(34)"        , {}                 , { { ParticleID::neutron(), 1 } }, 34 },
      Entry{      10035,  85, InteractionType::Nuclear, "n(35)"        , {}                 , { { ParticleID::neutron(), 1 } }, 35 },
      Entry{      10036,  86, InteractionType::Nuclear, "n(36)"        , {}                 , { { ParticleID::neutron(), 1 } }, 36 },
      Entry{      10037,  87, InteractionType::Nuclear, "n(37)"        , {}                 , { { ParticleID::neutron(), 1 } }, 37 },
      Entry{      10038,  88, InteractionType::Nuclear, "n(38)"        , {}                 , { { ParticleID::neutron(), 1 } }, 38 },
      Entry{      10039,  89, InteractionType::Nuclear, "n(39)"        , {}                 , { { ParticleID::neutron(), 1 } }, 39 },
      Entry{      10040,  90, InteractionType::Nuclear, "n(40)"        , {}                 , { { ParticleID::neutron(), 1 } }, 40 },
      Entry{      10150,  91, InteractionType::Nuclear, "n(c)"         , {}                 , { { ParticleID::neutron(), 1 } }, LevelID::continuum },
      Entry{      10151,   4, InteractionType::Nuclear, "n(t)"         , { "n" }            , { { ParticleID::neutron(), 1 } }, LevelID::all },

      Entry{      20000, 875, InteractionType::Nuclear, "2n(0)"        , {}                 , { { ParticleID::neutron(), 2 } }, 0 },
      Entry{      20001, 876, InteractionType::Nuclear, "2n(1)"        , {}                 , { { ParticleID::neutron(), 2 } }, 1 },
      Entry{      20002, 877, InteractionType::Nuclear, "2n(2)"        , {}                 , { { ParticleID::neutron(), 2 } }, 2 },
      Entry{      20003, 878, InteractionType::Nuclear, "2n(3)"        , {}                 , { { ParticleID::neutron(), 2 } }, 3 },
      Entry{      20004, 879, InteractionType::Nuclear, "2n(4)"        , {}                 , { { ParticleID::neutron(), 2 } }, 4 },
      Entry{      20005, 880, InteractionType::Nuclear, "2n(5)"        , {}                 , { { ParticleID::neutron(), 2 } }, 5 },
      Entry{      20006, 881, InteractionType::Nuclear, "2n(6)"        , {}                 , { { ParticleID::neutron(), 2 } }, 6 },
      Entry{      20007, 882, InteractionType::Nuclear, "2n(7)"        , {}                 , { { ParticleID::neutron(), 2 } }, 7 },
      Entry{      20008, 883, InteractionType::Nuclear, "2n(8)"        , {}                 , { { ParticleID::neutron(), 2 } }, 8 },
      Entry{      20009, 884, InteractionType::Nuclear, "2n(9)"        , {}                 , { { ParticleID::neutron(), 2 } }, 9 },
      Entry{      20010, 885, InteractionType::Nuclear, "2n(10)"       , {}                 , { { ParticleID::neutron(), 2 } }, 10 },
      Entry{      20011, 886, InteractionType::Nuclear, "2n(11)"       , {}                 , { { ParticleID::neutron(), 2 } }, 11 },
      Entry{      20012, 887, InteractionType::Nuclear, "2n(12)"       , {}                 , { { ParticleID::neutron(), 2 } }, 12 },
      Entry{      20013, 888, InteractionType::Nuclear, "2n(13)"       , {}                 , { { ParticleID::neutron(), 2 } }, 13 },
      Entry{      20014, 889, InteractionType::Nuclear, "2n(14)"       , {}                 , { { ParticleID::neutron(), 2 } }, 14 },
      Entry{      20015, 890, InteractionType::Nuclear, "2n(15)"       , {}                 , { { ParticleID::neutron(), 2 } }, 15 },
      Entry{      20150, 891, InteractionType::Nuclear, "2n(c)"        , {}                 , { { ParticleID::neutron(), 2 } }, LevelID::continuum },
      Entry{      20151,  16, InteractionType::Nuclear, "2n(t)"        , { "2n" }           , { { ParticleID::neutron(), 2 } }, LevelID::all },
      Entry{      30151,  17, InteractionType::Nuclear, "3n(t)"        , { "3n" }           , { { ParticleID::neutron(), 3 } }, LevelID::all },
      Entry{      40151,  37, InteractionType::Nuclear, "4n(t)"        , { "4n" }           , { { ParticleID::neutron(), 4 } }, LevelID::all },
      Entry{      50151, 152, InteractionType::Nuclear, "5n(t)"        , { "5n" }           , { { ParticleID::neutron(), 5 } }, LevelID::all },
      Entry{      60151, 153, InteractionType::Nuclear, "6n(t)"        , { "6n" }           , { { ParticleID::neutron(), 6 } }, LevelID::all },
      Entry{      70151, 160, InteractionType::Nuclear, "7n(t)"        , { "7n" }           , { { ParticleID::neutron(), 7 } }, LevelID::all },
      Entry{      80151, 161, InteractionType::Nuclear, "8n(t)"        , { "8n" }           , { { ParticleID::neutron(), 8 } }, LevelID::all },

      Entry{     100000, 600, InteractionType::Nuclear, "p(0)"         , {}                 , { { ParticleID::proton(), 1 } }, 0 },
      Entry{     100001, 601, InteractionType::Nuclear, "p(1)"         , {}                 , { { ParticleID::proton(), 1 } }, 1 },
      Entry{     100002, 602, InteractionType::Nuclear, "p(2)"         , {}                 , { { ParticleID::proton(), 1 } }, 2 },
      Entry{     100003, 603, InteractionType::Nuclear, "p(3)"         , {}                 , { { ParticleID::proton(), 1 } }, 3 },
      Entry{     100004, 604, InteractionType::Nuclear, "p(4)"         , {}                 , { { ParticleID::proton(), 1 } }, 4 },
      Entry{     100005, 605, InteractionType::Nuclear, "p(5)"         , {}                 , { { ParticleID::proton(), 1 } }, 5 },
      Entry{     100006, 606, InteractionType::Nuclear, "p(6)"         , {}                 , { { ParticleID::proton(), 1 } }, 6 },
      Entry{     100007, 607, InteractionType::Nuclear, "p(7)"         , {}                 , { { ParticleID::proton(), 1 } }, 7 },
      Entry{     100008, 608, InteractionType::Nuclear, "p(8)"         , {}                 , { { ParticleID::proton(), 1 } }, 8 },
      Entry{     100009, 609, InteractionType::Nuclear, "p(9)"         , {}                 , { { ParticleID::proton(), 1 } }, 9 },
      Entry{     100010, 610, InteractionType::Nuclear, "p(10)"        , {}                 , { { ParticleID::proton(), 1 } }, 10 },
      Entry{     100011, 611, InteractionType::Nuclear, "p(11)"        , {}                 , { { ParticleID::proton(), 1 } }, 11 },
      Entry{     100012, 612, InteractionType::Nuclear, "p(12)"        , {}                 , { { ParticleID::proton(), 1 } }, 12 },
      Entry{     100013, 613, InteractionType::Nuclear, "p(13)"        , {}                 , { { ParticleID::proton(), 1 } }, 13 },
      Entry{     100014, 614, InteractionType::Nuclear, "p(14)"        , {}                 , { { ParticleID::proton(), 1 } }, 14 },
      Entry{     100015, 615, InteractionType::Nuclear, "p(15)"        , {}                 , { { ParticleID::proton(), 1 } }, 15 },
      Entry{     100016, 616, InteractionType::Nuclear, "p(16)"        , {}                 , { { ParticleID::proton(), 1 } }, 16 },
      Entry{     100017, 617, InteractionType::Nuclear, "p(17)"        , {}                 , { { ParticleID::proton(), 1 } }, 17 },
      Entry{     100018, 618, InteractionType::Nuclear, "p(18)"        , {}                 , { { ParticleID::proton(), 1 } }, 18 },
      Entry{     100019, 619, InteractionType::Nuclear, "p(19)"        , {}                 , { { ParticleID::proton(), 1 } }, 19 },
      Entry{     100020, 620, InteractionType::Nuclear, "p(20)"        , {}                 , { { ParticleID::proton(), 1 } }, 20 },
      Entry{     100021, 621, InteractionType::Nuclear, "p(21)"        , {}                 , { { ParticleID::proton(), 1 } }, 21 },
      Entry{     100022, 622, InteractionType::Nuclear, "p(22)"        , {}                 , { { ParticleID::proton(), 1 } }, 22 },
      Entry{     100023, 623, InteractionType::Nuclear, "p(23)"        , {}                 , { { ParticleID::proton(), 1 } }, 23 },
      Entry{     100024, 624, InteractionType::Nuclear, "p(24)"        , {}                 , { { ParticleID::proton(), 1 } }, 24 },
      Entry{     100025, 625, InteractionType::Nuclear, "p(25)"        , {}                 , { { ParticleID::proton(), 1 } }, 25 },
      Entry{     100026, 626, InteractionType::Nuclear, "p(26)"        , {}                 , { { ParticleID::proton(), 1 } }, 26 },
      Entry{     100027, 627, InteractionType::Nuclear, "p(27)"        , {}                 , { { ParticleID::proton(), 1 } }, 27 },
      Entry{     100028, 628, InteractionType::Nuclear, "p(28)"        , {}                 , { { ParticleID::proton(), 1 } }, 28 },
      Entry{     100029, 629, InteractionType::Nuclear, "p(29)"        , {}                 , { { ParticleID::proton(), 1 } }, 29 },
      Entry{     100030, 630, InteractionType::Nuclear, "p(30)"        , {}                 , { { ParticleID::proton(), 1 } }, 30 },
      Entry{     100031, 631, InteractionType::Nuclear, "p(31)"        , {}                 , { { ParticleID::proton(), 1 } }, 31 },
      Entry{     100032, 632, InteractionType::Nuclear, "p(32)"        , {}                 , { { ParticleID::proton(), 1 } }, 32 },
      Entry{     100033, 633, InteractionType::Nuclear, "p(33)"        , {}                 , { { ParticleID::proton(), 1 } }, 33 },
      Entry{     100034, 634, InteractionType::Nuclear, "p(34)"        , {}                 , { { ParticleID::proton(), 1 } }, 34 },
      Entry{     100035, 635, InteractionType::Nuclear, "p(35)"        , {}                 , { { ParticleID::proton(), 1 } }, 35 },
      Entry{     100036, 636, InteractionType::Nuclear, "p(36)"        , {}                 , { { ParticleID::proton(), 1 } }, 36 },
      Entry{     100037, 637, InteractionType::Nuclear, "p(37)"        , {}                 , { { ParticleID::proton(), 1 } }, 37 },
      Entry{     100038, 638, InteractionType::Nuclear, "p(38)"        , {}                 , { { ParticleID::proton(), 1 } }, 38 },
      Entry{     100039, 639, InteractionType::Nuclear, "p(39)"        , {}                 , { { ParticleID::proton(), 1 } }, 39 },
      Entry{     100040, 640, InteractionType::Nuclear, "p(40)"        , {}                 , { { ParticleID::proton(), 1 } }, 40 },
      Entry{     100041, 641, InteractionType::Nuclear, "p(41)"        , {}                 , { { ParticleID::proton(), 1 } }, 41 },
      Entry{     100042, 642, InteractionType::Nuclear, "p(42)"        , {}                 , { { ParticleID::proton(), 1 } }, 42 },
      Entry{     100043, 643, InteractionType::Nuclear, "p(43)"        , {}                 , { { ParticleID::proton(), 1 } }, 43 },
      Entry{     100044, 644, InteractionType::Nuclear, "p(44)"        , {}                 , { { ParticleID::proton(), 1 } }, 44 },
      Entry{     100045, 645, InteractionType::Nuclear, "p(45)"        , {}                 , { { ParticleID::proton(), 1 } }, 45 },
      Entry{     100046, 646, InteractionType::Nuclear, "p(46)"        , {}                 , { { ParticleID::proton(), 1 } }, 46 },
      Entry{     100047, 647, InteractionType::Nuclear, "p(47)"        , {}                 , { { ParticleID::proton(), 1 } }, 47 },
      Entry{     100048, 648, InteractionType::Nuclear, "p(48)"        , {}                 , { { ParticleID::proton(), 1 } }, 48 },
      Entry{     100150, 649, InteractionType::Nuclear, "p(c)"         , {}                 , { { ParticleID::proton(), 1 } }, LevelID::continuum },
      Entry{     100151, 103, InteractionType::Nuclear, "p(t)"         , { "p" }            , { { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     110151,  28, InteractionType::Nuclear, "np(t)"        , { "np" }           , { { ParticleID::neutron(), 1 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     120151,  41, InteractionType::Nuclear, "2np(t)"       , { "2np" }          , { { ParticleID::neutron(), 2 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     130151,  42, InteractionType::Nuclear, "3np(t)"       , { "3np" }          , { { ParticleID::neutron(), 3 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     210151,  43, InteractionType::Nuclear, "n2p(t)"       , { "n2p" }          , { { ParticleID::neutron(), 1 }, { ParticleID::proton(), 2 } }, LevelID::all },
      Entry{     140151, 156, InteractionType::Nuclear, "4np(t)"       , { "4np" }          , { { ParticleID::neutron(), 4 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     150151, 162, InteractionType::Nuclear, "5np(t)"       , { "5np" }          , { { ParticleID::neutron(), 5 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     160151, 163, InteractionType::Nuclear, "6np(t)"       , { "6np" }          , { { ParticleID::neutron(), 6 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     170151, 164, InteractionType::Nuclear, "7np(t)"       , { "7np" }          , { { ParticleID::neutron(), 7 }, { ParticleID::proton(), 1 } }, LevelID::all },
      Entry{     200151, 111, InteractionType::Nuclear, "2p(t)"        , { "2p" }           , { { ParticleID::proton(), 2 } }, LevelID::all },
      Entry{     220151, 190, InteractionType::Nuclear, "2n2p(t)"      , { "2n2p" }         , { { ParticleID::neutron(), 2 }, { ParticleID::proton(), 2 } }, LevelID::all },
      Entry{     230151, 179, InteractionType::Nuclear, "3n2p(t)"      , { "3n2p" }         , { { ParticleID::neutron(), 3 }, { ParticleID::proton(), 2 } }, LevelID::all },
      Entry{     240151, 194, InteractionType::Nuclear, "4n2p(t)"      , { "4n2p" }         , { { ParticleID::neutron(), 4 }, { ParticleID::proton(), 2 } }, LevelID::all },
      Entry{     250151, 200, InteractionType::Nuclear, "5n2p(t)"      , { "5n2p" }         , { { ParticleID::neutron(), 5 }, { ParticleID::proton(), 2 } }, LevelID::all },
      Entry{     300151, 197, InteractionType::Nuclear, "3p(t)"        , { "3p" }           , { { ParticleID::proton(), 3 } }, LevelID::all },
      Entry{     310151, 198, InteractionType::Nuclear, "n3p(t)"       , { "n3p" }          , { { ParticleID::neutron(), 1 }, { ParticleID::proton(), 3 } }, LevelID::all },

      Entry{    1000000, 650, InteractionType::Nuclear, "d(0)"         , {}                 , { { ParticleID::deuteron(), 1 } }, 0 },
      Entry{    1000001, 651, InteractionType::Nuclear, "d(1)"         , {}                 , { { ParticleID::deuteron(), 1 } }, 1 },
      Entry{    1000002, 652, InteractionType::Nuclear, "d(2)"         , {}                 , { { ParticleID::deuteron(), 1 } }, 2 },
      Entry{    1000003, 653, InteractionType::Nuclear, "d(3)"         , {}                 , { { ParticleID::deuteron(), 1 } }, 3 },
      Entry{    1000004, 654, InteractionType::Nuclear, "d(4)"         , {}                 , { { ParticleID::deuteron(), 1 } }, 4 },
      Entry{    1000005, 655, InteractionType::Nuclear, "d(5)"         , {}                 , { { ParticleID::deuteron(), 1 } }, 5 },
      Entry{    1000006, 656, InteractionType::Nuclear, "d(6)"         , {}                 , { { ParticleID::deuteron(), 1 } }, 6 },
      Entry{    1000007, 657, InteractionType::Nuclear, "d(7)"         , {}                 , { { ParticleID::deuteron(), 1 } }, 7 },
      Entry{    1000008, 658, InteractionType::Nuclear, "d(8)"         , {}                 , { { ParticleID::deuteron(), 1 } }, 8 },
      Entry{    1000009, 659, InteractionType::Nuclear, "d(9)"         , {}                 , { { ParticleID::deuteron(), 1 } }, 9 },
      Entry{    1000010, 660, InteractionType::Nuclear, "d(10)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 10 },
      Entry{    1000011, 661, InteractionType::Nuclear, "d(11)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 11 },
      Entry{    1000012, 662, InteractionType::Nuclear, "d(12)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 12 },
      Entry{    1000013, 663, InteractionType::Nuclear, "d(13)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 13 },
      Entry{    1000014, 664, InteractionType::Nuclear, "d(14)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 14 },
      Entry{    1000015, 665, InteractionType::Nuclear, "d(15)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 15 },
      Entry{    1000016, 666, InteractionType::Nuclear, "d(16)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 16 },
      Entry{    1000017, 667, InteractionType::Nuclear, "d(17)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 17 },
      Entry{    1000018, 668, InteractionType::Nuclear, "d(18)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 18 },
      Entry{    1000019, 669, InteractionType::Nuclear, "d(19)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 19 },
      Entry{    1000020, 670, InteractionType::Nuclear, "d(20)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 20 },
      Entry{    1000021, 671, InteractionType::Nuclear, "d(21)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 21 },
      Entry{    1000022, 672, InteractionType::Nuclear, "d(22)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 22 },
      Entry{    1000023, 673, InteractionType::Nuclear, "d(23)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 23 },
      Entry{    1000024, 674, InteractionType::Nuclear, "d(24)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 24 },
      Entry{    1000025, 675, InteractionType::Nuclear, "d(25)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 25 },
      Entry{    1000026, 676, InteractionType::Nuclear, "d(26)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 26 },
      Entry{    1000027, 677, InteractionType::Nuclear, "d(27)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 27 },
      Entry{    1000028, 678, InteractionType::Nuclear, "d(28)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 28 },
      Entry{    1000029, 679, InteractionType::Nuclear, "d(29)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 29 },
      Entry{    1000030, 680, InteractionType::Nuclear, "d(30)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 30 },
      Entry{    1000031, 681, InteractionType::Nuclear, "d(31)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 31 },
      Entry{    1000032, 682, InteractionType::Nuclear, "d(32)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 32 },
      Entry{    1000033, 683, InteractionType::Nuclear, "d(33)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 33 },
      Entry{    1000034, 684, InteractionType::Nuclear, "d(34)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 34 },
      Entry{    1000035, 685, InteractionType::Nuclear, "d(35)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 35 },
      Entry{    1000036, 686, InteractionType::Nuclear, "d(36)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 36 },
      Entry{    1000037, 687, InteractionType::Nuclear, "d(37)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 37 },
      Entry{    1000038, 688, InteractionType::Nuclear, "d(38)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 38 },
      Entry{    1000039, 689, InteractionType::Nuclear, "d(39)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 39 },
      Entry{    1000040, 690, InteractionType::Nuclear, "d(40)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 40 },
      Entry{    1000041, 691, InteractionType::Nuclear, "d(41)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 41 },
      Entry{    1000042, 692, InteractionType::Nuclear, "d(42)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 42 },
      Entry{    1000043, 693, InteractionType::Nuclear, "d(43)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 43 },
      Entry{    1000044, 694, InteractionType::Nuclear, "d(44)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 44 },
      Entry{    1000045, 695, InteractionType::Nuclear, "d(45)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 45 },
      Entry{    1000046, 696, InteractionType::Nuclear, "d(46)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 46 },
      Entry{    1000047, 697, InteractionType::Nuclear, "d(47)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 47 },
      Entry{    1000048, 698, InteractionType::Nuclear, "d(48)"        , {}                 , { { ParticleID::deuteron(), 1 } }, 48 },
      Entry{    1000150, 699, InteractionType::Nuclear, "d(c)"         , {}                 , { { ParticleID::deuteron(), 1 } }, LevelID::continuum },
      Entry{    1000151, 104, InteractionType::Nuclear, "d(t)"         , { "d" }            , { { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1010151,  32, InteractionType::Nuclear, "nd(t)"        , { "nd" }           , { { ParticleID::neutron(), 1 }, { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1020151,  11, InteractionType::Nuclear, "2nd(t)"       , { "2nd" }          , { { ParticleID::neutron(), 2 }, { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1030151, 157, InteractionType::Nuclear, "3nd(t)"       , { "3nd" }          , { { ParticleID::neutron(), 3 }, { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1040151, 169, InteractionType::Nuclear, "4nd(t)"       , { "4nd" }          , { { ParticleID::neutron(), 4 }, { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1050151, 170, InteractionType::Nuclear, "5nd(t)"       , { "5nd" }          , { { ParticleID::neutron(), 5 }, { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1060151, 171, InteractionType::Nuclear, "6nd(t)"       , { "6nd" }          , { { ParticleID::neutron(), 6 }, { ParticleID::deuteron(), 1 } }, LevelID::all },
      Entry{    1100151, 115, InteractionType::Nuclear, "pd(t)"        , { "pd" }           , { { ParticleID::proton(), 1 }, { ParticleID::deuteron(), 1 } }, LevelID::all },

      Entry{   10000000, 700, InteractionType::Nuclear, "t(0)"         , {}                 , { { ParticleID::triton(), 1 } }, 0 },
      Entry{   10000001, 701, InteractionType::Nuclear, "t(1)"         , {}                 , { { ParticleID::triton(), 1 } }, 1 },
      Entry{   10000002, 702, InteractionType::Nuclear, "t(2)"         , {}                 , { { ParticleID::triton(), 1 } }, 2 },
      Entry{   10000003, 703, InteractionType::Nuclear, "t(3)"         , {}                 , { { ParticleID::triton(), 1 } }, 3 },
      Entry{   10000004, 704, InteractionType::Nuclear, "t(4)"         , {}                 , { { ParticleID::triton(), 1 } }, 4 },
      Entry{   10000005, 705, InteractionType::Nuclear, "t(5)"         , {}                 , { { ParticleID::triton(), 1 } }, 5 },
      Entry{   10000006, 706, InteractionType::Nuclear, "t(6)"         , {}                 , { { ParticleID::triton(), 1 } }, 6 },
      Entry{   10000007, 707, InteractionType::Nuclear, "t(7)"         , {}                 , { { ParticleID::triton(), 1 } }, 7 },
      Entry{   10000008, 708, InteractionType::Nuclear, "t(8)"         , {}                 , { { ParticleID::triton(), 1 } }, 8 },
      Entry{   10000009, 709, InteractionType::Nuclear, "t(9)"         , {}                 , { { ParticleID::triton(), 1 } }, 9 },
      Entry{   10000010, 710, InteractionType::Nuclear, "t(10)"        , {}                 , { { ParticleID::triton(), 1 } }, 10 },
      Entry{   10000011, 711, InteractionType::Nuclear, "t(11)"        , {}                 , { { ParticleID::triton(), 1 } }, 11 },
      Entry{   10000012, 712, InteractionType::Nuclear, "t(12)"        , {}                 , { { ParticleID::triton(), 1 } }, 12 },
      Entry{   10000013, 713, InteractionType::Nuclear, "t(13)"        , {}                 , { { ParticleID::triton(), 1 } }, 13 },
      Entry{   10000014, 714, InteractionType::Nuclear, "t(14)"        , {}                 , { { ParticleID::triton(), 1 } }, 14 },
      Entry{   10000015, 715, InteractionType::Nuclear, "t(15)"        , {}                 , { { ParticleID::triton(), 1 } }, 15 },
      Entry{   10000016, 716, InteractionType::Nuclear, "t(16)"        , {}                 , { { ParticleID::triton(), 1 } }, 16 },
      Entry{   10000017, 717, InteractionType::Nuclear, "t(17)"        , {}                 , { { ParticleID::triton(), 1 } }, 17 },
      Entry{   10000018, 718, InteractionType::Nuclear, "t(18)"        , {}                 , { { ParticleID::triton(), 1 } }, 18 },
      Entry{   10000019, 719, InteractionType::Nuclear, "t(19)"        , {}                 , { { ParticleID::triton(), 1 } }, 19 },
      Entry{   10000020, 720, InteractionType::Nuclear, "t(20)"        , {}                 , { { ParticleID::triton(), 1 } }, 20 },
      Entry{   10000021, 721, InteractionType::Nuclear, "t(21)"        , {}                 , { { ParticleID::triton(), 1 } }, 21 },
      Entry{   10000022, 722, InteractionType::Nuclear, "t(22)"        , {}                 , { { ParticleID::triton(), 1 } }, 22 },
      Entry{   10000023, 723, InteractionType::Nuclear, "t(23)"        , {}                 , { { ParticleID::triton(), 1 } }, 23 },
      Entry{   10000024, 724, InteractionType::Nuclear, "t(24)"        , {}                 , { { ParticleID::triton(), 1 } }, 24 },
      Entry{   10000025, 725, InteractionType::Nuclear, "t(25)"        , {}                 , { { ParticleID::triton(), 1 } }, 25 },
      Entry{   10000026, 726, InteractionType::Nuclear, "t(26)"        , {}                 , { { ParticleID::triton(), 1 } }, 26 },
      Entry{   10000027, 727, InteractionType::Nuclear, "t(27)"        , {}                 , { { ParticleID::triton(), 1 } }, 27 },
      Entry{   10000028, 728, InteractionType::Nuclear, "t(28)"        , {}                 , { { ParticleID::triton(), 1 } }, 28 },
      Entry{   10000029, 729, InteractionType::Nuclear, "t(29)"        , {}                 , { { ParticleID::triton(), 1 } }, 29 },
      Entry{   10000030, 730, InteractionType::Nuclear, "t(30)"        , {}                 , { { ParticleID::triton(), 1 } }, 30 },
      Entry{   10000031, 731, InteractionType::Nuclear, "t(31)"        , {}                 , { { ParticleID::triton(), 1 } }, 31 },
      Entry{   10000032, 732, InteractionType::Nuclear, "t(32)"        , {}                 , { { ParticleID::triton(), 1 } }, 32 },
      Entry{   10000033, 733, InteractionType::Nuclear, "t(33)"        , {}                 , { { ParticleID::triton(), 1 } }, 33 },
      Entry{   10000034, 734, InteractionType::Nuclear, "t(34)"        , {}                 , { { ParticleID::triton(), 1 } }, 34 },
      Entry{   10000035, 735, InteractionType::Nuclear, "t(35)"        , {}                 , { { ParticleID::triton(), 1 } }, 35 },
      Entry{   10000036, 736, InteractionType::Nuclear, "t(36)"        , {}                 , { { ParticleID::triton(), 1 } }, 36 },
      Entry{   10000037, 737, InteractionType::Nuclear, "t(37)"        , {}                 , { { ParticleID::triton(), 1 } }, 37 },
      Entry{   10000038, 738, InteractionType::Nuclear, "t(38)"        , {}                 , { { ParticleID::triton(), 1 } }, 38 },
      Entry{   10000039, 739, InteractionType::Nuclear, "t(39)"        , {}                 , { { ParticleID::triton(), 1 } }, 39 },
      Entry{   10000040, 740, InteractionType::Nuclear, "t(40)"        , {}                 , { { ParticleID::triton(), 1 } }, 40 },
      Entry{   10000041, 741, InteractionType::Nuclear, "t(41)"        , {}                 , { { ParticleID::triton(), 1 } }, 41 },
      Entry{   10000042, 742, InteractionType::Nuclear, "t(42)"        , {}                 , { { ParticleID::triton(), 1 } }, 42 },
      Entry{   10000043, 743, InteractionType::Nuclear, "t(43)"        , {}                 , { { ParticleID::triton(), 1 } }, 43 },
      Entry{   10000044, 744, InteractionType::Nuclear, "t(44)"        , {}                 , { { ParticleID::triton(), 1 } }, 44 },
      Entry{   10000045, 745, InteractionType::Nuclear, "t(45)"        , {}                 , { { ParticleID::triton(), 1 } }, 45 },
      Entry{   10000046, 746, InteractionType::Nuclear, "t(46)"        , {}                 , { { ParticleID::triton(), 1 } }, 46 },
      Entry{   10000047, 747, InteractionType::Nuclear, "t(47)"        , {}                 , { { ParticleID::triton(), 1 } }, 47 },
      Entry{   10000048, 748, InteractionType::Nuclear, "t(48)"        , {}                 , { { ParticleID::triton(), 1 } }, 48 },
      Entry{   10000150, 749, InteractionType::Nuclear, "t(c)"         , {}                 , { { ParticleID::triton(), 1 } }, LevelID::continuum },
      Entry{   10000151, 105, InteractionType::Nuclear, "t(t)"         , { "t" }            , { { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10010151,  33, InteractionType::Nuclear, "nt(t)"        , { "nt" }           , { { ParticleID::neutron(), 1 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10020151, 154, InteractionType::Nuclear, "2nt(t)"       , { "2nt" }          , { { ParticleID::neutron(), 2 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10030151, 172, InteractionType::Nuclear, "3nt(t)"       , { "3nt" }          , { { ParticleID::neutron(), 3 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10040151, 173, InteractionType::Nuclear, "4nt(t)"       , { "4nt" }          , { { ParticleID::neutron(), 4 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10050151, 174, InteractionType::Nuclear, "5nt(t)"       , { "5nt" }          , { { ParticleID::neutron(), 5 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10060151, 175, InteractionType::Nuclear, "6nt(t)"       , { "6nt" }          , { { ParticleID::neutron(), 6 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10100151, 116, InteractionType::Nuclear, "pt(t)"        , { "pt" }           , { { ParticleID::proton(), 1 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   10110151, 184, InteractionType::Nuclear, "npt(t)"       , { "npt" }          , { { ParticleID::neutron(), 1 }, { ParticleID::proton(), 1 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   11000151, 182, InteractionType::Nuclear, "dt(t)"        , { "dt" }           , { { ParticleID::deuteron(), 1 }, { ParticleID::triton(), 1 } }, LevelID::all },
      Entry{   11010151, 185, InteractionType::Nuclear, "ndt(t)"       , { "ndt" }          , { { ParticleID::neutron(), 1 }, { ParticleID::deuteron(), 1 }, { ParticleID::triton(), 1 } }, LevelID::all },

      Entry{  100000000, 750, InteractionType::Nuclear, "h(0)"         , {}                 , { { ParticleID::helion(), 1 } }, 0 },
      Entry{  100000001, 751, InteractionType::Nuclear, "h(1)"         , {}                 , { { ParticleID::helion(), 1 } }, 1 },
      Entry{  100000002, 752, InteractionType::Nuclear, "h(2)"         , {}                 , { { ParticleID::helion(), 1 } }, 2 },
      Entry{  100000003, 753, InteractionType::Nuclear, "h(3)"         , {}                 , { { ParticleID::helion(), 1 } }, 3 },
      Entry{  100000004, 754, InteractionType::Nuclear, "h(4)"         , {}                 , { { ParticleID::helion(), 1 } }, 4 },
      Entry{  100000005, 755, InteractionType::Nuclear, "h(5)"         , {}                 , { { ParticleID::helion(), 1 } }, 5 },
      Entry{  100000006, 756, InteractionType::Nuclear, "h(6)"         , {}                 , { { ParticleID::helion(), 1 } }, 6 },
      Entry{  100000007, 757, InteractionType::Nuclear, "h(7)"         , {}                 , { { ParticleID::helion(), 1 } }, 7 },
      Entry{  100000008, 758, InteractionType::Nuclear, "h(8)"         , {}                 , { { ParticleID::helion(), 1 } }, 8 },
      Entry{  100000009, 759, InteractionType::Nuclear, "h(9)"         , {}                 , { { ParticleID::helion(), 1 } }, 9 },
      Entry{  100000010, 760, InteractionType::Nuclear, "h(10)"        , {}                 , { { ParticleID::helion(), 1 } }, 10 },
      Entry{  100000011, 761, InteractionType::Nuclear, "h(11)"        , {}                 , { { ParticleID::helion(), 1 } }, 11 },
      Entry{  100000012, 762, InteractionType::Nuclear, "h(12)"        , {}                 , { { ParticleID::helion(), 1 } }, 12 },
      Entry{  100000013, 763, InteractionType::Nuclear, "h(13)"        , {}                 , { { ParticleID::helion(), 1 } }, 13 },
      Entry{  100000014, 764, InteractionType::Nuclear, "h(14)"        , {}                 , { { ParticleID::helion(), 1 } }, 14 },
      Entry{  100000015, 765, InteractionType::Nuclear, "h(15)"        , {}                 , { { ParticleID::helion(), 1 } }, 15 },
      Entry{  100000016, 766, InteractionType::Nuclear, "h(16)"        , {}                 , { { ParticleID::helion(), 1 } }, 16 },
      Entry{  100000017, 767, InteractionType::Nuclear, "h(17)"        , {}                 , { { ParticleID::helion(), 1 } }, 17 },
      Entry{  100000018, 768, InteractionType::Nuclear, "h(18)"        , {}                 , { { ParticleID::helion(), 1 } }, 18 },
      Entry{  100000019, 769, InteractionType::Nuclear, "h(19)"        , {}                 , { { ParticleID::helion(), 1 } }, 19 },
      Entry{  100000020, 770, InteractionType::Nuclear, "h(20)"        , {}                 , { { ParticleID::helion(), 1 } }, 20 },
      Entry{  100000021, 771, InteractionType::Nuclear, "h(21)"        , {}                 , { { ParticleID::helion(), 1 } }, 21 },
      Entry{  100000022, 772, InteractionType::Nuclear, "h(22)"        , {}                 , { { ParticleID::helion(), 1 } }, 22 },
      Entry{  100000023, 773, InteractionType::Nuclear, "h(23)"        , {}                 , { { ParticleID::helion(), 1 } }, 23 },
      Entry{  100000024, 774, InteractionType::Nuclear, "h(24)"        , {}                 , { { ParticleID::helion(), 1 } }, 24 },
      Entry{  100000025, 775, InteractionType::Nuclear, "h(25)"        , {}                 , { { ParticleID::helion(), 1 } }, 25 },
      Entry{  100000026, 776, InteractionType::Nuclear, "h(26)"        , {}                 , { { ParticleID::helion(), 1 } }, 26 },
      Entry{  100000027, 777, InteractionType::Nuclear, "h(27)"        , {}                 , { { ParticleID::helion(), 1 } }, 27 },
      Entry{  100000028, 778, InteractionType::Nuclear, "h(28)"        , {}                 , { { ParticleID::helion(), 1 } }, 28 },
      Entry{  100000029, 779, InteractionType::Nuclear, "h(29)"        , {}                 , { { ParticleID::helion(), 1 } }, 29 },
      Entry{  100000030, 780, InteractionType::Nuclear, "h(30)"        , {}                 , { { ParticleID::helion(), 1 } }, 30 },
      Entry{  100000031, 781, InteractionType::Nuclear, "h(31)"        , {}                 , { { ParticleID::helion(), 1 } }, 31 },
      Entry{  100000032, 782, InteractionType::Nuclear, "h(32)"        , {}                 , { { ParticleID::helion(), 1 } }, 32 },
      Entry{  100000033, 783, InteractionType::Nuclear, "h(33)"        , {}                 , { { ParticleID::helion(), 1 } }, 33 },
      Entry{  100000034, 784, InteractionType::Nuclear, "h(34)"        , {}                 , { { ParticleID::helion(), 1 } }, 34 },
      Entry{  100000035, 785, InteractionType::Nuclear, "h(35)"        , {}                 , { { ParticleID::helion(), 1 } }, 35 },
      Entry{  100000036, 786, InteractionType::Nuclear, "h(36)"        , {}                 , { { ParticleID::helion(), 1 } }, 36 },
      Entry{  100000037, 787, InteractionType::Nuclear, "h(37)"        , {}                 , { { ParticleID::helion(), 1 } }, 37 },
      Entry{  100000038, 788, InteractionType::Nuclear, "h(38)"        , {}                 , { { ParticleID::helion(), 1 } }, 38 },
      Entry{  100000039, 789, InteractionType::Nuclear, "h(39)"        , {}                 , { { ParticleID::helion(), 1 } }, 39 },
      Entry{  100000040, 790, InteractionType::Nuclear, "h(40)"        , {}                 , { { ParticleID::helion(), 1 } }, 40 },
      Entry{  100000041, 791, InteractionType::Nuclear, "h(41)"        , {}                 , { { ParticleID::helion(), 1 } }, 41 },
      Entry{  100000042, 792, InteractionType::Nuclear, "h(42)"        , {}                 , { { ParticleID::helion(), 1 } }, 42 },
      Entry{  100000043, 793, InteractionType::Nuclear, "h(43)"        , {}                 , { { ParticleID::helion(), 1 } }, 43 },
      Entry{  100000044, 794, InteractionType::Nuclear, "h(44)"        , {}                 , { { ParticleID::helion(), 1 } }, 44 },
      Entry{  100000045, 795, InteractionType::Nuclear, "h(45)"        , {}                 , { { ParticleID::helion(), 1 } }, 45 },
      Entry{  100000046, 796, InteractionType::Nuclear, "h(46)"        , {}                 , { { ParticleID::helion(), 1 } }, 46 },
      Entry{  100000047, 797, InteractionType::Nuclear, "h(47)"        , {}                 , { { ParticleID::helion(), 1 } }, 47 },
      Entry{  100000048, 798, InteractionType::Nuclear, "h(48)"        , {}                 , { { ParticleID::helion(), 1 } }, 48 },
      Entry{  100000150, 799, InteractionType::Nuclear, "h(c)"         , {}                 , { { ParticleID::helion(), 1 } }, LevelID::continuum },
      Entry{  100000151, 106, InteractionType::Nuclear, "h(t)"         , { "h" }            , { { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  100010151,  34, InteractionType::Nuclear, "nh(t)"        , { "nh" }           , { { ParticleID::neutron(), 1 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  100020151, 176, InteractionType::Nuclear, "2nh(t)"       , { "2nh" }          , { { ParticleID::neutron(), 2 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  100030151, 177, InteractionType::Nuclear, "3nh(t)"       , { "3nh" }          , { { ParticleID::neutron(), 3 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  100040151, 178, InteractionType::Nuclear, "4nh(t)"       , { "4nh" }          , { { ParticleID::neutron(), 4 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  100100151, 191, InteractionType::Nuclear, "ph(t)"        , { "ph" }           , { { ParticleID::proton(), 1 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  100110151, 186, InteractionType::Nuclear, "nph(t)"       , { "nph" }          , { { ParticleID::neutron(), 1 }, { ParticleID::proton(), 1 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  101000151, 192, InteractionType::Nuclear, "dh(t)"        , { "dh" }           , { { ParticleID::deuteron(), 1 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  101010151, 187, InteractionType::Nuclear, "ndh(t)"       , { "ndh" }          , { { ParticleID::neutron(), 1 }, { ParticleID::deuteron(), 1 }, { ParticleID::helion(), 1 } }, LevelID::all },
      Entry{  110010151, 188, InteractionType::Nuclear, "nth(t)"       , { "nth" }          , { { ParticleID::neutron(), 1 }, { ParticleID::triton(), 1 }, { ParticleID::helion(), 1 } }, LevelID::all },

      Entry{ 1000000000, 800, InteractionType::Nuclear, "a(0)"         , {}                 , { { ParticleID::alpha(), 1 } }, 0 },
      Entry{ 1000000001, 801, InteractionType::Nuclear, "a(1)"         , {}                 , { { ParticleID::alpha(), 1 } }, 1 },
      Entry{ 1000000002, 802, InteractionType::Nuclear, "a(2)"         , {}                 , { { ParticleID::alpha(), 1 } }, 2 },
      Entry{ 1000000003, 803, InteractionType::Nuclear, "a(3)"         , {}                 , { { ParticleID::alpha(), 1 } }, 3 },
      Entry{ 1000000004, 804, InteractionType::Nuclear, "a(4)"         , {}                 , { { ParticleID::alpha(), 1 } }, 4 },
      Entry{ 1000000005, 805, InteractionType::Nuclear, "a(5)"         , {}                 , { { ParticleID::alpha(), 1 } }, 5 },
      Entry{ 1000000006, 806, InteractionType::Nuclear, "a(6)"         , {}                 , { { ParticleID::alpha(), 1 } }, 6 },
      Entry{ 1000000007, 807, InteractionType::Nuclear, "a(7)"         , {}                 , { { ParticleID::alpha(), 1 } }, 7 },
      Entry{ 1000000008, 808, InteractionType::Nuclear, "a(8)"         , {}                 , { { ParticleID::alpha(), 1 } }, 8 },
      Entry{ 1000000009, 809, InteractionType::Nuclear, "a(9)"         , {}                 , { { ParticleID::alpha(), 1 } }, 9 },
      Entry{ 1000000010, 810, InteractionType::Nuclear, "a(10)"        , {}                 , { { ParticleID::alpha(), 1 } }, 10 },
      Entry{ 1000000011, 811, InteractionType::Nuclear, "a(11)"        , {}                 , { { ParticleID::alpha(), 1 } }, 11 },
      Entry{ 1000000012, 812, InteractionType::Nuclear, "a(12)"        , {}                 , { { ParticleID::alpha(), 1 } }, 12 },
      Entry{ 1000000013, 813, InteractionType::Nuclear, "a(13)"        , {}                 , { { ParticleID::alpha(), 1 } }, 13 },
      Entry{ 1000000014, 814, InteractionType::Nuclear, "a(14)"        , {}                 , { { ParticleID::alpha(), 1 } }, 14 },
      Entry{ 1000000015, 815, InteractionType::Nuclear, "a(15)"        , {}                 , { { ParticleID::alpha(), 1 } }, 15 },
      Entry{ 1000000016, 816, InteractionType::Nuclear, "a(16)"        , {}                 , { { ParticleID::alpha(), 1 } }, 16 },
      Entry{ 1000000017, 817, InteractionType::Nuclear, "a(17)"        , {}                 , { { ParticleID::alpha(), 1 } }, 17 },
      Entry{ 1000000018, 818, InteractionType::Nuclear, "a(18)"        , {}                 , { { ParticleID::alpha(), 1 } }, 18 },
      Entry{ 1000000019, 819, InteractionType::Nuclear, "a(19)"        , {}                 , { { ParticleID::alpha(), 1 } }, 19 },
      Entry{ 1000000020, 820, InteractionType::Nuclear, "a(20)"        , {}                 , { { ParticleID::alpha(), 1 } }, 20 },
      Entry{ 1000000021, 821, InteractionType::Nuclear, "a(21)"        , {}                 , { { ParticleID::alpha(), 1 } }, 21 },
      Entry{ 1000000022, 822, InteractionType::Nuclear, "a(22)"        , {}                 , { { ParticleID::alpha(), 1 } }, 22 },
      Entry{ 1000000023, 823, InteractionType::Nuclear, "a(23)"        , {}                 , { { ParticleID::alpha(), 1 } }, 23 },
      Entry{ 1000000024, 824, InteractionType::Nuclear, "a(24)"        , {}                 , { { ParticleID::alpha(), 1 } }, 24 },
      Entry{ 1000000025, 825, InteractionType::Nuclear, "a(25)"        , {}                 , { { ParticleID::alpha(), 1 } }, 25 },
      Entry{ 1000000026, 826, InteractionType::Nuclear, "a(26)"        , {}                 , { { ParticleID::alpha(), 1 } }, 26 },
      Entry{ 1000000027, 827, InteractionType::Nuclear, "a(27)"        , {}                 , { { ParticleID::alpha(), 1 } }, 27 },
      Entry{ 1000000028, 828, InteractionType::Nuclear, "a(28)"        , {}                 , { { ParticleID::alpha(), 1 } }, 28 },
      Entry{ 1000000029, 829, InteractionType::Nuclear, "a(29)"        , {}                 , { { ParticleID::alpha(), 1 } }, 29 },
      Entry{ 1000000030, 830, InteractionType::Nuclear, "a(30)"        , {}                 , { { ParticleID::alpha(), 1 } }, 30 },
      Entry{ 1000000031, 831, InteractionType::Nuclear, "a(31)"        , {}                 , { { ParticleID::alpha(), 1 } }, 31 },
      Entry{ 1000000032, 832, InteractionType::Nuclear, "a(32)"        , {}                 , { { ParticleID::alpha(), 1 } }, 32 },
      Entry{ 1000000033, 833, InteractionType::Nuclear, "a(33)"        , {}                 , { { ParticleID::alpha(), 1 } }, 33 },
      Entry{ 1000000034, 834, InteractionType::Nuclear, "a(34)"        , {}                 , { { ParticleID::alpha(), 1 } }, 34 },
      Entry{ 1000000035, 835, InteractionType::Nuclear, "a(35)"        , {}                 , { { ParticleID::alpha(), 1 } }, 35 },
      Entry{ 1000000036, 836, InteractionType::Nuclear, "a(36)"        , {}                 , { { ParticleID::alpha(), 1 } }, 36 },
      Entry{ 1000000037, 837, InteractionType::Nuclear, "a(37)"        , {}                 , { { ParticleID::alpha(), 1 } }, 37 },
      Entry{ 1000000038, 838, InteractionType::Nuclear, "a(38)"        , {}                 , { { ParticleID::alpha(), 1 } }, 38 },
      Entry{ 1000000039, 839, InteractionType::Nuclear, "a(39)"        , {}                 , { { ParticleID::alpha(), 1 } }, 39 },
      Entry{ 1000000040, 840, InteractionType::Nuclear, "a(40)"        , {}                 , { { ParticleID::alpha(), 1 } }, 40 },
      Entry{ 1000000041, 841, InteractionType::Nuclear, "a(41)"        , {}                 , { { ParticleID::alpha(), 1 } }, 41 },
      Entry{ 1000000042, 842, InteractionType::Nuclear, "a(42)"        , {}                 , { { ParticleID::alpha(), 1 } }, 42 },
      Entry{ 1000000043, 843, InteractionType::Nuclear, "a(43)"        , {}                 , { { ParticleID::alpha(), 1 } }, 43 },
      Entry{ 1000000044, 844, InteractionType::Nuclear, "a(44)"        , {}                 , { { ParticleID::alpha(), 1 } }, 44 },
      Entry{ 1000000045, 845, InteractionType::Nuclear, "a(45)"        , {}                 , { { ParticleID::alpha(), 1 } }, 45 },
      Entry{ 1000000046, 846, InteractionType::Nuclear, "a(46)"        , {}                 , { { ParticleID::alpha(), 1 } }, 46 },
      Entry{ 1000000047, 847, InteractionType::Nuclear, "a(47)"        , {}                 , { { ParticleID::alpha(), 1 } }, 47 },
      Entry{ 1000000048, 848, InteractionType::Nuclear, "a(48)"        , {}                 , { { ParticleID::alpha(), 1 } }, 48 },
      Entry{ 1000000150, 849, InteractionType::Nuclear, "a(c)"         , {}                 , { { ParticleID::alpha(), 1 } }, LevelID::continuum },
      Entry{ 1000000151, 107, InteractionType::Nuclear, "a(t)"         , { "a" }            , { { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000010151,  22, InteractionType::Nuclear, "na(t)"        , { "na" }           , { { ParticleID::neutron(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000020151,  24, InteractionType::Nuclear, "2na(t)"       , { "2na" }          , { { ParticleID::neutron(), 2 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000030151,  25, InteractionType::Nuclear, "3na(t)"       , { "3na" }          , { { ParticleID::neutron(), 3 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000040151, 165, InteractionType::Nuclear, "4na(t)"       , { "4na" }          , { { ParticleID::neutron(), 4 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000050151, 166, InteractionType::Nuclear, "5na(t)"       , { "5na" }          , { { ParticleID::neutron(), 5 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000060151, 167, InteractionType::Nuclear, "6na(t)"       , { "6na" }          , { { ParticleID::neutron(), 6 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000070151, 168, InteractionType::Nuclear, "7na(t)"       , { "7na" }          , { { ParticleID::neutron(), 7 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000100151, 112, InteractionType::Nuclear, "pa(t)"        , { "pa" }           , { { ParticleID::proton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000110151,  45, InteractionType::Nuclear, "npa(t)"       , { "npa" }          , { { ParticleID::neutron(), 1 }, { ParticleID::proton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000120151, 159, InteractionType::Nuclear, "2npa(t)"      , { "2npa" }         , { { ParticleID::neutron(), 2 }, { ParticleID::proton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000130151, 181, InteractionType::Nuclear, "3npa(t)"      , { "3npa" }         , { { ParticleID::neutron(), 3 }, { ParticleID::proton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000140151, 196, InteractionType::Nuclear, "4npa(t)"      , { "4npa" }         , { { ParticleID::neutron(), 4 }, { ParticleID::proton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1000230151, 199, InteractionType::Nuclear, "3n2pa(t)"     , { "3n2pa" }        , { { ParticleID::neutron(), 3 }, { ParticleID::proton(), 2 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1001000151, 117, InteractionType::Nuclear, "da(t)"        , { "da" }           , { { ParticleID::proton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1001010151, 158, InteractionType::Nuclear, "nda(t)"       , { "nda" }          , { { ParticleID::neutron(), 1 }, { ParticleID::deuteron(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1010000151, 155, InteractionType::Nuclear, "ta(t)"        , { "ta" }           , { { ParticleID::triton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1010010151, 189, InteractionType::Nuclear, "nta(t)"       , { "nta" }          , { { ParticleID::neutron(), 1 }, { ParticleID::triton(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 1100000151, 193, InteractionType::Nuclear, "ha(t)"        , { "ha" }           , { { ParticleID::helion(), 1 }, { ParticleID::alpha(), 1 } }, LevelID::all },
      Entry{ 2000000151, 108, InteractionType::Nuclear, "2a(t)"        , { "2a" }           , { { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2000010151,  29, InteractionType::Nuclear, "n2a(t)"       , { "n2a" }          , { { ParticleID::neutron(), 1 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2000020151,  30, InteractionType::Nuclear, "2n2a(t)"      , { "2n2a" }         , { { ParticleID::neutron(), 2 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2000030151, 180, InteractionType::Nuclear, "3n2a(t)"      , { "3n2a" }         , { { ParticleID::neutron(), 3 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2000040151, 195, InteractionType::Nuclear, "4n2a(t)"      , { "4n2a" }         , { { ParticleID::neutron(), 4 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2001000151, 114, InteractionType::Nuclear, "d2a(t)"       , { "d2a" }          , { { ParticleID::deuteron(), 1 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2001010151,  35, InteractionType::Nuclear, "nd2a(t)"      , { "nd2a" }         , { { ParticleID::neutron(), 1 }, { ParticleID::deuteron(), 1 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2010000151, 113, InteractionType::Nuclear, "t2a(t)"       , { "t2a" }          , { { ParticleID::triton(), 1 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 2010010151,  36, InteractionType::Nuclear, "nt2a(t)"      , { "nt2a" }         , { { ParticleID::neutron(), 1 }, { ParticleID::triton(), 1 }, { ParticleID::alpha(), 2 } }, LevelID::all },
      Entry{ 3000000151, 109, InteractionType::Nuclear, "3a(t)"        , { "3a" }           , { { ParticleID::alpha(), 3 } }, LevelID::all },
      Entry{ 3000010151,  23, InteractionType::Nuclear, "n3a(t)"       , { "n3a" }          , { { ParticleID::neutron(), 1 }, { ParticleID::alpha(), 3 } }, LevelID::all },

      // atomic reaction types

//      Entry{ 501, InteractionType::Atomic , "atomic total", {} },  // the symbol must be unique and total is already taken
//      Entry{ 502, InteractionType::Atomic , "coherent"    , { "coherent scattering" } },
//      Entry{ 504, InteractionType::Atomic , "incoherent"  , { "incoherent scattering" } }
    };
    static inline std::unordered_map< std::string, std::size_t >
    string_conversion_dictionary = [] ( const auto& entries ) {

      std::unordered_map< std::string, std::size_t > conversion;
      for ( std::size_t index = 0; index < entries.size(); ++index ) {

        conversion[ entries[ index ].symbol() ] = index;
        for ( const auto& alternative : entries[ index ].alternatives() ) {

          conversion[ alternative ] = index;
        }
      }
      return conversion;
    }( entries );
    static inline std::unordered_map< int, std::size_t >
    mt_conversion_dictionary = [] ( const auto& entries ) {

      std::unordered_map< int, std::size_t > conversion;
      for ( std::size_t index = 0; index < entries.size(); ++index ) {

        if ( entries[ index ].mt().has_value() ) {

          conversion[ entries[ index ].mt().value() ] = index;
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

    /* static methods */

    /**
     *  @brief Return the number of currently registered identifiers
     *
     *  Note: this imposes logical order to the reaction types. It is public
     *        for test purposes only.
     */
    static std::size_t size() noexcept {

      return entries.size();
    }

    /**
     *  @brief Return whether or not the mt number corresponds to a registered reaction type
     *
     *  @param[in] mt   the mt number
     */
    static bool isRegistered( int mt ) noexcept {

      return mt_conversion_dictionary.find( mt ) != mt_conversion_dictionary.end();
    }

    /**
     *  @brief Return whether or not the string corresponds to a registered reaction type
     *
     *  @param[in] string   the string
     */
    static bool isRegistered( const std::string& string ) noexcept {

      return string_conversion_dictionary.find( string ) != string_conversion_dictionary.end();
    }

    /* methods */

    /**
     *  @brief Return the number for this reaction type
     *
     *  Note: this imposes logical order to the identifiers. It is public
     *        for test purposes only.
     */
    long number() const noexcept {

      return entries[ this->index_ ].number();
    }

    /**
     *  @brief Return the symbol for this reaction type
     */
    const std::string& symbol() const noexcept {

      return entries[ this->index_ ].symbol();
    }

    /**
     *  @brief Return the particles emitted for this reaction type
     */
    const std::optional< std::vector< std::pair< ParticleID, char > > >& particles() const noexcept {

      return entries[ this->index_ ].particles();
    }

    /**
     *  @brief Return whether or not the reaction type is ENDF compatible
     */
    bool isCompatibleWithENDF() const noexcept {

      return entries[ this->index_ ].mt().has_value();
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

    size_t operator()( const njoy::dryad::id::ReactionType& key ) const noexcept {

      return key.number();
    }
  };

} // namespace std

#endif
