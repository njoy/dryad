#ifndef NJOY_DRYAD_FORMAT_GNDS_ATOMIC_CREATEELECTRONSUBSHELLID
#define NJOY_DRYAD_FORMAT_GNDS_ATOMIC_CREATEELECTRONSUBSHELLID

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ElementID.hpp"
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
  id::ElectronSubshellID
  createRadiativeTransitionElectronSubshellID( const id::ElementID& element,
                                               std::string vacancy ) {

    auto size = element.symbol().size();
    return id::ElectronSubshellID( std::string( vacancy.begin() + size + 1, vacancy.end() - 1 ) );
  }

  /**
   *  @brief Create ElectronSubshellIDs from vacancy for a non-radiative transition
   */
  std::pair< id::ElectronSubshellID, id::ElectronSubshellID >
  createNonRadiativeTransitionElectronSubshellID( const id::ElementID& element,
                                                  std::string vacancies ) {

    auto size = element.symbol().size();
    auto iter = std::find( vacancies.begin(), vacancies.end(), ',' );
    return std::make_pair( id::ElectronSubshellID( std::string( vacancies.begin() + size + 1, iter ) ),
                           id::ElectronSubshellID( std::string( iter + 1, vacancies.end() -1 ) ) );
  }

} // atomic namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
