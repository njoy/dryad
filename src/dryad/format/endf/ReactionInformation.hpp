#ifndef NJOY_DRYAD_FORMAT_ENDF_REACTIONINFORMATION
#define NJOY_DRYAD_FORMAT_ENDF_REACTIONINFORMATION

// system includes
#include <map>
#include <unordered_set>

// other includes
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief A class related to ENDF reaction information
   */
  class ReactionInformation {

    inline static const std::unordered_set< int > derived_ = {

      203, 204, 205, 206, 207, 251, 252, 253
    };
    inline static const std::unordered_set< int > summation_or_primary_ = {

       16,  18, 103, 104, 105, 106, 107, 526
    };
    inline static const std::unordered_set< int > summation_ = {

        1,   3,   4,  27, 101, 501, 516, 522
    };
    inline static const std::unordered_set< int > primary_ = {

        2,   5,  11,  17,  19,  20,  21,  22,  23,  24,  25,
       28,  29,  30,  32,  33,  34,  35,  36,  37,  38,
       41,  42,  44,  45,  50,  51,  52,  53,  54,  55,
       56,  57,  58,  59,  60,  61,  62,  63,  64,  65,
       66,  67,  68,  69,  70,  71,  72,  73,  74,  75,
       76,  77,  78,  79,  80,  81,  82,  83,  84,  85,
       86,  87,  88,  89,  90,  91, 102, 108, 109, 111,
      112, 113, 114, 115, 116, 117, 152, 153, 154, 155,
      156, 157, 158, 159, 160, 161, 162, 163, 164, 165,
      166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
      176, 177, 178, 179, 180, 181, 182, 183, 184, 185,
      186, 187, 188, 189, 190, 191, 192, 193, 194, 195,
      196, 197, 198, 199, 200, 502, 504, 505, 506, 515,
      517, 523, 525, 527, 528, 534, 535, 536, 537, 538,
      539, 540, 541, 542, 543, 544, 545, 546, 547, 548,
      549, 550, 551, 552, 553, 554, 555, 556, 557, 558,
      559, 560, 561, 562, 563, 564, 565, 566, 567, 568,
      569, 570, 571, 572,
      600, 601, 602, 603, 604, 605, 606, 607, 608, 609,
      610, 611, 612, 613, 614, 615, 616, 617, 618, 619,
      620, 621, 622, 623, 624, 625, 626, 627, 628, 629,
      630, 631, 632, 633, 634, 635, 636, 637, 638, 639,
      640, 641, 642, 643, 644, 645, 646, 647, 648, 649,
      650, 651, 652, 653, 654, 655, 656, 657, 658, 659,
      660, 661, 662, 663, 664, 665, 666, 667, 668, 669,
      670, 671, 672, 673, 674, 675, 676, 677, 678, 679,
      680, 681, 682, 683, 684, 685, 686, 687, 688, 689,
      690, 691, 692, 693, 694, 695, 696, 697, 698, 699,
      700, 701, 702, 703, 704, 705, 706, 707, 708, 709,
      710, 711, 712, 713, 714, 715, 716, 717, 718, 719,
      720, 721, 722, 723, 724, 725, 726, 727, 728, 729,
      730, 731, 732, 733, 734, 735, 736, 737, 738, 739,
      740, 741, 742, 743, 744, 745, 746, 747, 748, 749,
      750, 751, 752, 753, 754, 755, 756, 757, 758, 759,
      760, 761, 762, 763, 764, 765, 766, 767, 768, 769,
      770, 771, 772, 773, 774, 775, 776, 777, 778, 779,
      780, 781, 782, 783, 784, 785, 786, 787, 788, 789,
      790, 791, 792, 793, 794, 795, 796, 797, 798, 799,
      800, 801, 802, 803, 804, 805, 806, 807, 808, 809,
      810, 811, 812, 813, 814, 815, 816, 817, 818, 819,
      820, 821, 822, 823, 824, 825, 826, 827, 828, 829,
      830, 831, 832, 833, 834, 835, 836, 837, 838, 839,
      840, 841, 842, 843, 844, 845, 846, 847, 848, 849,
      875, 876, 877, 878, 879, 880, 881, 882, 883, 884,
      885, 886, 887, 888, 889, 890, 891
    };
    inline static const std::map< int, std::vector< int > > partials_ = {

      {   1, {  } },
      {   3, {  } },
      {   4, {  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,
                61,  62,  63,  64,  65,  66,  67,  68,  69,  70,
                71,  72,  73,  74,  75,  76,  77,  78,  79,  80,
                81,  82,  83,  84,  85,  86,  87,  88,  89,  90,
                91 } },
      {  16, { 875, 876, 877, 878, 879, 880, 881, 882, 883, 884,
               885, 886, 887, 888, 889, 890, 891 } },
      {  18, {  19,  20,  21,  38 } },
      {  27, {  } },
      { 101, {  } },
      { 103, { 600, 601, 602, 603, 604, 605, 606, 607, 608, 609,
               610, 611, 612, 613, 614, 615, 616, 617, 618, 619,
               620, 621, 622, 623, 624, 625, 626, 627, 628, 629,
               630, 631, 632, 633, 634, 635, 636, 637, 638, 639,
               640, 641, 642, 643, 644, 645, 646, 647, 648, 649 } },
      { 104, { 650, 651, 652, 653, 654, 655, 656, 657, 658, 659,
               660, 661, 662, 663, 664, 665, 666, 667, 668, 669,
               670, 671, 672, 673, 674, 675, 676, 677, 678, 679,
               680, 681, 682, 683, 684, 685, 686, 687, 688, 689,
               690, 691, 692, 693, 694, 695, 696, 697, 698, 699 } },
      { 105, { 700, 701, 702, 703, 704, 705, 706, 707, 708, 709,
               710, 711, 712, 713, 714, 715, 716, 717, 718, 719,
               720, 721, 722, 723, 724, 725, 726, 727, 728, 729,
               730, 731, 732, 733, 734, 735, 736, 737, 738, 739,
               740, 741, 742, 743, 744, 745, 746, 747, 748, 749 } },
      { 106, { 750, 751, 752, 753, 754, 755, 756, 757, 758, 759,
               760, 761, 762, 763, 764, 765, 766, 767, 768, 769,
               770, 771, 772, 773, 774, 775, 776, 777, 778, 779,
               780, 781, 782, 783, 784, 785, 786, 787, 788, 789,
               790, 791, 792, 793, 794, 795, 796, 797, 798, 799 } },
      { 107, { 800, 801, 802, 803, 804, 805, 806, 807, 808, 809,
               810, 811, 812, 813, 814, 815, 816, 817, 818, 819,
               820, 821, 822, 823, 824, 825, 826, 827, 828, 829,
               830, 831, 832, 833, 834, 835, 836, 837, 838, 839,
               840, 841, 842, 843, 844, 845, 846, 847, 848, 849 } },
      { 501, { 502, 504, 515, 517, 525,      527, 528, 534, 535,
               536, 537, 538, 539, 540, 541, 542, 543, 544, 545,
               546, 547, 548, 549, 550, 551, 552, 553, 554, 555,
               556, 557, 558, 559, 560, 561, 562, 563, 564, 565,
               566, 567, 568, 569, 570, 571, 572 } },
      { 516, { 515, 517 } },
      { 522, { 534, 535, 536, 537, 538, 539, 540, 541, 542, 543,
               544, 545, 546, 547, 548, 549, 550, 551, 552, 553,
               554, 555, 556, 557, 558, 559, 560, 561, 562, 563,
               564, 565, 566, 567, 568, 569, 570, 571, 572 } },
      { 526, { 525 } }
    };

  public:

    /**
     *  @brief Return whether or not the MT number is valid
     *
     *  @param[in] material   the ENDF material
     *  @param[in] mt         the MT number
     */
    static bool isValid( const ENDFtk::tree::Material&, int mt ) {

      if ( ( mt > 0 ) && ( mt < 1000 ) ) {

        if ( ( primary_.find( mt ) == primary_.end() ) &&
             ( summation_.find( mt ) == summation_.end() ) &&
             ( summation_or_primary_.find( mt ) == summation_or_primary_.end() ) &&
             ( derived_.find( mt ) == derived_.end() ) ) {

          return false;
        }

        return true;
      }

      return false;
    }

    /**
     *  @brief Return whether or not the MT number is for a derived reaction
     *
     *  @param[in] material   the ENDF material
     *  @param[in] mt         the MT number
     */
    static bool isDerived( const ENDFtk::tree::Material&, int mt ) {

      return derived_.find( mt ) != derived_.end();
    }

    /**
     *  @brief Return whether or not the MT number is for a summation reaction
     *
     *  @param[in] material   the ENDF material
     *  @param[in] mt         the MT number
     */
    static bool isSummation( const ENDFtk::tree::Material& material, int mt ) {

      switch ( mt ) {

        case  16 : return material.hasSection( 3, 875 ) ? true : false;
        case  18 : return material.hasSection( 3, 19 )  ? true : false;
        case 103 : return material.hasSection( 3, 600 ) ? true : false;
        case 104 : return material.hasSection( 3, 650 ) ? true : false;
        case 105 : return material.hasSection( 3, 700 ) ? true : false;
        case 106 : return material.hasSection( 3, 750 ) ? true : false;
        case 107 : return material.hasSection( 3, 800 ) ? true : false;
        case 526 : return material.hasSection( 23, 525 ) ? true : false;
        default : {

          return summation_.find( mt ) != summation_.end();
        }
      }
    }

    /**
     *  @brief Return whether or not the MT number is for a primary reaction
     *
     *  @param[in] material   the ENDF material
     *  @param[in] mt         the MT number
     */
    static bool isPrimary( const ENDFtk::tree::Material& material, int mt ) {

      switch ( mt ) {

        case  16 : return material.hasSection( 3, 875 ) ? false : true;
        case  18 : return material.hasSection( 3, 19 )  ? false : true;
        case 103 : return material.hasSection( 3, 600 ) ? false : true;
        case 104 : return material.hasSection( 3, 650 ) ? false : true;
        case 105 : return material.hasSection( 3, 700 ) ? false : true;
        case 106 : return material.hasSection( 3, 750 ) ? false : true;
        case 107 : return material.hasSection( 3, 800 ) ? false : true;
        case 526 : return material.hasSection( 23, 525 ) ? false : true;
        default : {

          return primary_.find( mt ) != primary_.end();
        }
      }
    }

    /**
     *  @brief Return the partial mt numbers for a summation mt number
     *
     *  @param[in] material   the ENDF material
     *  @param[in] mt         the MT number
     */
    static std::vector< int > partials( const ENDFtk::tree::Material& material,
                                        int mf, int mt ) {

      std::vector< int > partials;
      if ( mf == 3 && mt == 1 ) {

        auto sections = material.file( mf ).sectionNumbers();
        std::copy_if( sections.begin(), sections.end(),
                      std::back_inserter( partials ),
                      [&material] ( auto&& value ) { return isPrimary( material, value ); } );
      }
      else if ( isSummation( material, mt ) ) {

        // create a vector of partial mt numbers that are present
        std::copy_if( partials_.at( mt ).begin(), partials_.at( mt ).end(),
                      std::back_inserter( partials ),
                      [&material, mf] ( auto&& value ) { return material.hasSection( mf, value ); } );

        // add deficiency mt number for total elastic in electro-atomic data
        auto iter = std::lower_bound( partials.begin(), partials.end(), 525 );
        if ( iter != partials.end() ) {

          if ( *iter == 525 ) {

            partials.insert( iter + 1, -526 );
          }
        }
      }
      return partials;
    }
  };

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
