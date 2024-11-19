#ifndef NJOY_DRYAD_FORMAT_GNDS_ATOMIC_CREATEELECTRONSUBSHELLID
#define NJOY_DRYAD_FORMAT_GNDS_ATOMIC_CREATEELECTRONSUBSHELLID

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ElectronSubshellID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace atomic {

  /**
   *  @brief Create an ElectronSubshellID
   */
  id::ElectronSubshellID createElectronSubshellID( std::string subshell ) {

    return id::ElectronSubshellID( std::move( subshell ) );
  }

  /**
   *  @brief Create an ElectronSubshellID from a vacancy for
   *         a radiative transition
   */
  id::ElectronSubshellID createRadiativeTransitionElectronSubshellID( std::string vacancy ) {

    return id::ElectronSubshellID( std::string( vacancy.begin() + 2, vacancy.end() - 1 ) );
  }

  /**
   *  @brief Create ElectronSubshellIDs from vacancy for a non-radiative transition
   */
  std::pair< id::ElectronSubshellID, id::ElectronSubshellID >
  createNonRadiativeTransitionElectronSubshellID( std::string vacancies ) {

    auto iter = std::find( vacancies.begin(), vacancies.end(), ',' );
    return std::make_pair( id::ElectronSubshellID( std::string( vacancies.begin() + 2, iter ) ),
                           id::ElectronSubshellID( std::string( iter + 1, vacancies.end() -1 ) ) );
  }

} // atomic namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
