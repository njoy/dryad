// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace resonances {

  // declarations - enums
  void wrapBoundaryCondition( python::module& );
  void wrapFormalism( python::module& );

  // declarations - components
  void wrapParticle( python::module& );
  void wrapParticlePair( python::module& );
  void wrapChannelQuantumNumbers( python::module& );
  void wrapTabulatedRadius( python::module& );
  void wrapChannelRadii( python::module& );
  void wrapHardSpherePenetrability( python::module& );
  void wrapHardSphereShiftFactor( python::module& );
  void wrapHardSpherePhaseShift( python::module& );
  void wrapCoulombPenetrability( python::module& );
  void wrapCoulombShiftFactor( python::module& );
  void wrapCoulombPhaseShift( python::module& );
  void wrapCoulombPhaseShiftDifference( python::module& );
  void wrapTabulatedWaveFunction( python::module& );
  void wrapChannel( python::module& );
  void wrapResonanceTable( python::module& );
  void wrapSpinGroup( python::module& );
  void wrapCompoundSystem( python::module& );

  void wrapResonanceParameters( python::module& );
}

void wrapResonances( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "resonances",
    "Resonance data"
  );

  // enums
  resonances::wrapBoundaryCondition( submodule );
  resonances::wrapFormalism( submodule );

  // components
  resonances::wrapParticle( submodule );
  resonances::wrapParticlePair( submodule );
  resonances::wrapChannelQuantumNumbers( submodule );
  resonances::wrapTabulatedRadius( submodule );
  resonances::wrapChannelRadii( submodule );
  resonances::wrapHardSpherePenetrability( submodule );
  resonances::wrapHardSphereShiftFactor( submodule );
  resonances::wrapHardSpherePhaseShift( submodule );
  resonances::wrapCoulombPenetrability( submodule );
  resonances::wrapCoulombShiftFactor( submodule );
  resonances::wrapCoulombPhaseShift( submodule );
  resonances::wrapCoulombPhaseShiftDifference( submodule );
  resonances::wrapTabulatedWaveFunction( submodule );
  resonances::wrapChannel( submodule );
  resonances::wrapResonanceTable( submodule );
  resonances::wrapSpinGroup( submodule );
  resonances::wrapCompoundSystem( submodule );

  resonances::wrapResonanceParameters( submodule );
}
