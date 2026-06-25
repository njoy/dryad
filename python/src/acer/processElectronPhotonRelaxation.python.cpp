// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/acer/processElectronPhotonRelaxation.hpp"

// namespace aliases
namespace python = pybind11;

namespace acer {

  void wrapProcessElectronPhotonRelaxation( python::module& module ) {

    // type aliases

    // wrap the function
    module
    .def(

      "process_electron_photon_relaxation",
      &njoy::acer::processElectronPhotonRelaxation,
      python::arg( "photoatomic" ),
      python::arg( "electroatomic" ),
      python::arg( "relaxation" ),
      python::arg( "filename" ),
      python::arg( "number" ),
      python::arg( "date" ),
      python::arg( "title" ),
      "Process data into an epr ace file\n\n"
      "Parameters\n"
      "----------\n"
      "    z : int\n"
      "        the cosine values\n"
      "    photoatomic : njoy.dryad.ProjectileTarget\n"
      "        the photoatomic projectile-target data\n"
      "    electroatomic : njoy.dryad.ProjectileTarget\n"
      "        the electroatomic projectile-target data\n"
      "    relaxation : njoy.dryad.AtomicRelaxation\n"
      "        the atomic relaxation data\n"
      "    filename : str\n"
      "        the filename for the ace file\n"
      "    number : int\n"
      "        the extension number (above 0, less than 100)\n"
      "    date : str\n"
      "        the processing date\n"
      "    title : str\n"
      "        the ace file title"
    );
  }

} // acer namespace
