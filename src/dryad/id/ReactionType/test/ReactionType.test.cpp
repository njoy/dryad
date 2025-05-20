// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "dryad/id/ReactionType.hpp"

// other includes
#include <map>
#include <unordered_map>

// convenience typedefs
using ReactionType = njoy::dryad::id::ReactionType;

SCENARIO( "ReactionType" ) {

  GIVEN( "valid data for a ReactionType" ) {

    std::vector< int > mt = {

        1,        3,   4,   5,  18,  19,  20,  21,  38,
       27, 101, 102,  11,  16,  17,  22,  23,  24,  25,
       28,  29,  30,  32,  33,  34,  35,  36,  37,  41,
       42,  44,  45,  50,  51,  52,  53,  54,  55,  56,
       57,  58,  59,  60,  61,  62,  63,  64,  65,  66,
       67,  68,  69,  70,  71,  72,  73,  74,  75,  76,
       77,  78,  79,  80,  81,  82,  83,  84,  85,  86,
       87,  88,  89,  90,  91, 103, 104, 105, 106, 107,
      108, 109, 111, 112, 113, 114, 115, 116, 117, 152,
      153, 154, 155, 156, 157, 158, 159, 160, 161, 162,
      163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
      173, 174, 175, 176, 177, 178, 179, 180, 181, 182,
      183, 184, 185, 186, 187, 188, 189, 190, 191, 192,
      193, 194, 195, 196, 197, 198, 199, 200, 600, 601,
      602, 603, 604, 605, 606, 607, 608, 609, 610, 611,
      612, 613, 614, 615, 616, 617, 618, 619, 620, 621,
      622, 623, 624, 625, 626, 627, 628, 629, 630, 631,
      632, 633, 634, 635, 636, 637, 638, 639, 640, 641,
      642, 643, 644, 645, 646, 647, 648, 649, 650, 651,
      652, 653, 654, 655, 656, 657, 658, 659, 660, 661,
      662, 663, 664, 665, 666, 667, 668, 669, 670, 671,
      672, 673, 674, 675, 676, 677, 678, 679, 680, 681,
      682, 683, 684, 685, 686, 687, 688, 689, 690, 691,
      692, 693, 694, 695, 696, 697, 698, 699, 700, 701,
      702, 703, 704, 705, 706, 707, 708, 709, 710, 711,
      712, 713, 714, 715, 716, 717, 718, 719, 720, 721,
      722, 723, 724, 725, 726, 727, 728, 729, 730, 731,
      732, 733, 734, 735, 736, 737, 738, 739, 740, 741,
      742, 743, 744, 745, 746, 747, 748, 749, 750, 751,
      752, 753, 754, 755, 756, 757, 758, 759, 760, 761,
      762, 763, 764, 765, 766, 767, 768, 769, 770, 771,
      772, 773, 774, 775, 776, 777, 778, 779, 780, 781,
      782, 783, 784, 785, 786, 787, 788, 789, 790, 791,
      792, 793, 794, 795, 796, 797, 798, 799, 800, 801,
      802, 803, 804, 805, 806, 807, 808, 809, 810, 811,
      812, 813, 814, 815, 816, 817, 818, 819, 820, 821,
      822, 823, 824, 825, 826, 827, 828, 829, 830, 831,
      832, 833, 834, 835, 836, 837, 838, 839, 840, 841,
      842, 843, 844, 845, 846, 847, 848, 849, 875, 876,
      877, 878, 879, 880, 881, 882, 883, 884, 885, 886,
      887, 888, 889, 890, 891,
    };

    THEN( "an ReactionType can be created using mt numbers" ) {

      ReactionType id( 1 );
      CHECK( 1 == id.number() );
      CHECK( "total" == id.symbol() );
      CHECK( std::nullopt == id.particles() );
      CHECK( true == id.isCompatibleWithENDF() );


    } // THEN
  } // GIVEN

  GIVEN( "valid ReactionType instances" ) {

    ReactionType id1( 50 );
    ReactionType id2( 600 );

    THEN( "instances can be compared" ) {

      CHECK( ( id1 <  id1 ) == false );
      CHECK( ( id1 <= id1 ) == true );
      CHECK( ( id1 >  id1 ) == false );
      CHECK( ( id1 >= id1 ) == true );
      CHECK( ( id1 == id1 ) == true );
      CHECK( ( id1 != id1 ) == false );
      CHECK( ( id1 <  id2 ) == true );
      CHECK( ( id1 <= id2 ) == true );
      CHECK( ( id1 >  id2 ) == false );
      CHECK( ( id1 >= id2 ) == false );
      CHECK( ( id1 == id2 ) == false );
      CHECK( ( id1 != id2 ) == true );
      CHECK( ( id2 <  id1 ) == false );
      CHECK( ( id2 <= id1 ) == false );
      CHECK( ( id2 >  id1 ) == true );
      CHECK( ( id2 >= id1 ) == true );
      CHECK( ( id2 == id1 ) == false );
      CHECK( ( id2 != id1 ) == true );
    } // THEN

    THEN( "instances can be used as keys in a std::map" ) {

      std::map< ReactionType, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ReactionType( 50 ) ] == "1" );
      CHECK( map[ ReactionType( 600 ) ] == "2" );
    } // THEN

    THEN( "instances can be used as keys in a std::unordered_map" ) {

      std::unordered_map< ReactionType, std::string > map{

        { id1, "1" }, { id2, "2" }
      };

      CHECK( map[ id1 ] == "1" );
      CHECK( map[ id2 ] == "2" );
      CHECK( map[ ReactionType( 50 ) ] == "1" );
      CHECK( map[ ReactionType( 600 ) ] == "2" );
    } // THEN
  } // GIVEN

//  GIVEN( "invalid data for an ReactionType" ) {
//
//    THEN( "an exception is thrown" ) {
//
//      CHECK_THROWS( ReactionType( "not a particle symbol" ) );
//      CHECK_THROWS( ReactionType( -1000 ) );
//      CHECK_THROWS( ReactionType( 1000, 1 ) );
//      CHECK_THROWS( ReactionType( 1000, njoy::dryad::id::LevelID::continuum ) );
//      CHECK_THROWS( ReactionType( 1000, njoy::dryad::id::LevelID::all ) );
//      CHECK_THROWS( ReactionType( 1000, 152 ) );
//      CHECK_THROWS( ReactionType( 1001, 152 ) );
//      CHECK_THROWS( ReactionType( "H_e0" ) );
//      CHECK_THROWS( ReactionType( "H_e1" ) );
//      CHECK_THROWS( ReactionType( "H1_e152" ) );
//      CHECK_THROWS( ReactionType( 1000, 533 ) );
//      CHECK_THROWS( ReactionType( 1000, 581 ) );
//    } // THEN
//  } // GIVEN
} // SCENARIO
