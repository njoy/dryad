// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/medic/curateComptonProfiles.hpp"

// namespace aliases
namespace python = pybind11;

namespace medic {

  void wrapCurateComptonProfiles( python::module& module ) {

    // type aliases

    // wrap the function
    module
    .def(

      "curate_compton_profiles",
      &njoy::medic::curateComptonProfiles,
      python::arg( "photoatomic" ),
      python::arg( "relaxation" ),
      "Curate the Compton profile data\n\n"
      "When the Compton profile data contains a subshell that is not present\n"
      "in the atomic relaxation data, that profile is removed.\n\n"
      "When the atomic relaxation data contains subshells that are not present\n"
      "in the Compton profiles, then an appropriate Compton profile for the\n"
      "missing subshell is selected based on the available subshells. That\n"
      "subshell is selected based on the quantum numbers of the missing subshell\n"
      "(n, l, l + m with m = +1/2 or -1/2), whichever is found first:\n"
      "  - the shell with the same n and l but the other m\n"
      "  - the shell with the same n, l - 1 and the same m\n"
      "  - the shell with the same n, l - 1 and the other m\n\n"
       "Parameters\n"
      "----------\n"
      "    photoatomic : njoy.dryad.ProjectileTarget\n"
      "        the photoatomic projectile-target data to be curated\n"
      "    relaxation : njoy.dryad.AtomicRelaxation\n"
      "        the atomic relaxation data"
    );
  }

} // medic namespace
