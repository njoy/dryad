#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATECOMPLEXBREAKUPPARTICLES
#define NJOY_DRYAD_FORMAT_ENDF_CREATECOMPLEXBREAKUPPARTICLES

// system includes
#include <map>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create the complex breakup particles for a residual and
   *         breakup type
   *
   *  @param[in] residual          the residual particle
   *  @param[in] complex_breakup   the complex breakup flag
   */
  inline std::map< id::ParticleID, std::size_t >
  createComplexBreakUpParticles( const id::ParticleID residual,
                                 int complex_breakup ) {

    // create the complex breakup particles
    std::map< id::ParticleID, std::size_t > particles;
    switch ( complex_breakup ) {

      case 22 : {

        particles = { { id::ParticleID::alpha(), 1 } };
        break;
      }
      case 23 : {

        particles = { { id::ParticleID::alpha(), 3 } };
        break;
      }
      case 24 : {

        particles = { { id::ParticleID::neutron(), 1 },
                      { id::ParticleID::alpha(), 1 } };
        break;
      }
      case 25 : {

        particles = { { id::ParticleID::neutron(), 2 },
                      { id::ParticleID::alpha(), 1 } };
        break;
      }
      case 28 : {

        particles = { { id::ParticleID::proton(), 1 } };
        break;
      }
      case 29 : {

        particles = { { id::ParticleID::alpha(), 2 } };
        break;
      }
      case 30 : {

        particles = { { id::ParticleID::neutron(), 1 },
                      { id::ParticleID::alpha(), 2 } };
        break;
      }
      case 32 : {

        particles = { { id::ParticleID::deuteron(), 1 } };
        break;
      }
      case 33 : {

        particles = { { id::ParticleID::triton(), 1 } };
        break;
      }
      case 34 : {

        particles = { { id::ParticleID::helion(), 1 } };
        break;
      }
      case 35 : {

        particles = { { id::ParticleID::deuteron(), 1 },
                      { id::ParticleID::alpha(), 2 } };
        break;
      }
      case 36 : {

        particles = { { id::ParticleID::triton(), 1 },
                      { id::ParticleID::alpha(), 2 } };
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

            particles[ id::ParticleID::neutron() ] += 1;
            break;
          }
          case 1001 : {

            particles[ id::ParticleID::proton() ] += 1;
            break;
          }
          case 1002 : {

            particles[ id::ParticleID::deuteron() ] += 1;
            break;
          }
          case 1003 : {

            particles[ id::ParticleID::triton() ] += 1;
            break;
          }
          case 2003 : {

            particles[ id::ParticleID::helion() ] += 1;
            break;
          }
          case 2004 : {

            particles[ id::ParticleID::alpha() ] += 1;
            break;
          }
          default : {

            particles[ id::ParticleID::nuclide( remainder, id::LevelID::all ) ] += 1;
            break;
          }
        }
      }
    }

    return particles;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
