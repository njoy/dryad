#ifndef NJOY_FORMAT_ENDF_READ_CREATECOMPLEXBREAKUPPARTICLES
#define NJOY_FORMAT_ENDF_READ_CREATECOMPLEXBREAKUPPARTICLES

// system includes
#include <map>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create the complex breakup particles for a residual and
   *         breakup type
   *
   *  @param[in] residual          the residual particle
   *  @param[in] complex_breakup   the complex breakup flag
   */
  inline std::map< dryad::id::ParticleID, std::size_t >
  createComplexBreakUpParticles( const dryad::id::ParticleID residual,
                                 int complex_breakup ) {

    // create the complex breakup particles
    std::map< dryad::id::ParticleID, std::size_t > particles;
    switch ( complex_breakup ) {

      case 22 : {

        particles = { { dryad::id::ParticleID::alpha(), 1 } };
        break;
      }
      case 23 : {

        particles = { { dryad::id::ParticleID::alpha(), 3 } };
        break;
      }
      case 24 : {

        particles = { { dryad::id::ParticleID::neutron(), 1 },
                      { dryad::id::ParticleID::alpha(), 1 } };
        break;
      }
      case 25 : {

        particles = { { dryad::id::ParticleID::neutron(), 2 },
                      { dryad::id::ParticleID::alpha(), 1 } };
        break;
      }
      case 28 : {

        particles = { { dryad::id::ParticleID::proton(), 1 } };
        break;
      }
      case 29 : {

        particles = { { dryad::id::ParticleID::alpha(), 2 } };
        break;
      }
      case 30 : {

        particles = { { dryad::id::ParticleID::neutron(), 1 },
                      { dryad::id::ParticleID::alpha(), 2 } };
        break;
      }
      case 32 : {

        particles = { { dryad::id::ParticleID::deuteron(), 1 } };
        break;
      }
      case 33 : {

        particles = { { dryad::id::ParticleID::triton(), 1 } };
        break;
      }
      case 34 : {

        particles = { { dryad::id::ParticleID::helion(), 1 } };
        break;
      }
      case 35 : {

        particles = { { dryad::id::ParticleID::deuteron(), 1 },
                      { dryad::id::ParticleID::alpha(), 2 } };
        break;
      }
      case 36 : {

        particles = { { dryad::id::ParticleID::triton(), 1 },
                      { dryad::id::ParticleID::alpha(), 2 } };
        break;
      }
      default : {

        Log::error( "Complex breakup flag \'{}\' has not been implemented yet",
                    complex_breakup );
        throw std::exception();
      }
    }

    // calculate the za of the emitted particles
    int delta = 0;
    for ( const auto& [id, multiplicity] : particles ) {

      delta += multiplicity * id.za();
    }

    // calculate and add residual
    if ( delta != residual.za()  ) {

      auto remainder = residual.za() - delta;
      if ( remainder < 0 ) {

        Log::error( "Complex breakup flag \'{}\' is not compatible with residual \'{}\'",
                    complex_breakup, residual.symbol() );
        throw std::exception();
      }
      else {

        switch ( remainder ) {

          case 1 : {

            particles[ dryad::id::ParticleID::neutron() ] += 1;
            break;
          }
          case 1001 : {

            particles[ dryad::id::ParticleID::proton() ] += 1;
            break;
          }
          case 1002 : {

            particles[ dryad::id::ParticleID::deuteron() ] += 1;
            break;
          }
          case 1003 : {

            particles[ dryad::id::ParticleID::triton() ] += 1;
            break;
          }
          case 2003 : {

            particles[ dryad::id::ParticleID::helion() ] += 1;
            break;
          }
          case 2004 : {

            particles[ dryad::id::ParticleID::alpha() ] += 1;
            break;
          }
          default : {

            particles[ dryad::id::ParticleID::nuclide( remainder, dryad::id::LevelID::all ) ] += 1;
            break;
          }
        }
      }
    }

    return particles;
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
