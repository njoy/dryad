#include "njoy/dryad/resonances/CompoundSystem.hpp"

// convenience typedefs
using namespace njoy;
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

 // This file creates a dryad compound object used in unit tests for ENDF-6 writting a MF2 file using a R-Matrix formalism.
 // It contains 2 spin groups, each of them with 3 channels : (n,n), (n,g), (n,a) and (n,f)
 // Four particle pairs are used to assess the correct numbering, called PPI in ENDF-6 format.
 // A background is set on the third channel of the second spin group.


 id::ParticleID projectileID = id::ParticleID::neutron();
 id::ParticleID targetID = id::ParticleID( "Cu63" );
                 
 dryad::resonances::ParticlePair neutron_cu63(dryad::resonances::Particle(id::ParticleID::neutron(),  1.0 * constants::neutron_mass, 0.5, 1), // ID, mass, spin, parity 
                                              dryad::resonances::Particle(targetID                 , 20.0 * constants::neutron_mass, 1.5, 1));
  
 dryad::resonances::ParticlePair incident_ppair = neutron_cu63;

 dryad::resonances::ParticlePair photon_residual(dryad::resonances::Particle(id::ParticleID::photon(), 0.0                          , 1, 1), // ID, mass, spin, parity 
                                                 dryad::resonances::Particle(targetID                , 2.0 * constants::neutron_mass, 3, 1) );

 dryad::resonances::ParticlePair alpha_residual(dryad::resonances::Particle(id::ParticleID::alpha(), 7.0 * constants::neutron_mass, 9, 1), // ID, mass, spin, parity 
                                                 dryad::resonances::Particle(targetID              , 8.0 * constants::neutron_mass, 10, 1) );

/**
 *  @brief Create a dummy dryad spin group object, using for testing ENDF writter
 */
SpinGroup create_dryad_spingroup_1() {
  
  double J = 1;
  short parity = -1;

  Kinematics kinematics = dryad::resonances::Kinematics::NonRelativistic;
        
  auto capture_id = id::ChannelID( id::ReactionID( projectileID, targetID, 102 ), 
                                   ChannelQuantumNumbers(1, 2, J, parity), // l s J Pi
                                   1 );
                                   
  Channel capture_channel( capture_id,
                           incident_ppair,
                           photon_residual,
                           8.0, // Q value
                           11.0, // Boundary
                           dryad::resonances::ChannelRadii(0.61, 0.62),
                           kinematics,
                           std::nullopt, // No background
                           -1.,     // penetrability
                           0.,     // shiftFactor  
                           0.,     // phaseShift   
                           0. );   // difference   

  auto elast_id = id::ChannelID( id::ReactionID( projectileID, targetID, 50 ), 
                                 ChannelQuantumNumbers(3, 4, J, parity), // l s J Pi
                                 2 );


  Channel elast_channel( elast_id,
                         incident_ppair,
                         neutron_cu63,
                         8.0, // Q value
                         12.0,
                         ChannelRadii(0.63, 0.64),
                         kinematics,
                         std::nullopt, // No background
                         1.,     // penetrability
                         0.,     // shiftFactor  
                         0.,     // phaseShift   
                         0. );   // difference  

                   
  auto nalpha_id = id::ChannelID( id::ReactionID( projectileID, targetID, 600 ), 
                                  ChannelQuantumNumbers(3, 4, J, parity), // l s J Pi
                                  4 );


  Channel nalpha_channel(  nalpha_id,
                           incident_ppair,
                           alpha_residual, // no outgoing pp for fission
                           45.0, // Q_value
                           46.0, // boundary condition
                           dryad::resonances::ChannelRadii(0.65, 0.66),
                           dryad::resonances::Kinematics::NonRelativistic,
                           std::nullopt, // No background
                           1.,     // penetrability
                           0.,     // shiftFactor  
                           0.,     // phaseShift   
                           0. );   // difference

  std::vector< Channel > channels = {capture_channel, elast_channel, nalpha_channel};
  
  ResonanceTable resonances( {capture_id, elast_id, nalpha_id},
                             {10, 20},
                             {{2, 3},     // First channel
                              {4, 5},     // Second
                              {6, 7}} );  // Third

  


  return njoy::dryad::resonances::SpinGroup(channels, 
              resonances, 
              Formalism::ReichMoore, 
              BoundaryCondition::Constant);
}


/**
 *  @brief Create a dummy dryad spin group object, using for testing ENDF writter
 */
SpinGroup create_dryad_spingroup_2() {
  
  double J = 2;
  short parity = -1;
    
  auto capture_id = id::ChannelID( id::ReactionID( projectileID, targetID, 102 ), 
                                   ChannelQuantumNumbers(1, 2, J, parity), // l s J Pi
                                   1 );
                                   
  Channel capture_channel(  capture_id,
                            incident_ppair,
                            photon_residual,
                            9.0, // Q_value
                            11.0, // boundary condition
                            dryad::resonances::ChannelRadii(0.61, 0.62),
                            dryad::resonances::Kinematics::NonRelativistic,
                            std::nullopt, // No background
                            -1.,     // penetrability
                            0.,     // shiftFactor  
                            0.,     // phaseShift   
                            0. );   // difference

  auto elast_id = id::ChannelID( id::ReactionID( projectileID, targetID, 50 ), 
                                 ChannelQuantumNumbers(3, 4, J, parity), // l s J Pi
                                 2 );


  Channel elastic_channel(  elast_id,
                            incident_ppair,
                            neutron_cu63,
                            18.0, // Q_value
                            12.0, // boundary condition
                            dryad::resonances::ChannelRadii(0.63, 0.64),
                            dryad::resonances::Kinematics::NonRelativistic,
                            std::nullopt, // No background
                            1.,     // penetrability
                            0.,     // shiftFactor  
                            0.,     // phaseShift   
                            0. );   // difference

  auto fission_id = id::ChannelID( id::ReactionID( projectileID, targetID, 18 ), 
                                   ChannelQuantumNumbers(3, 4, J, parity), // l s J Pi
                                   3 );

  int index = 1;
  double lower_energy = 1.;
  double upper_energy = 2.;
  double r0 = 3.;
  double r1 = 4.;
  double r2 = 5.;
  double s0 = 6.;
  double s1 = 7.;

  dryad::resonances::SammyBackground background( std::array< double, 3 >{r0, r1, r2}, 
                                                 std::array< double, 2 >{s0, s1}, 
                                                 lower_energy, 
                                                 upper_energy );

  Channel fission_channel(  fission_id,
                            incident_ppair,
                            std::nullopt, // no outgoing pp for fission
                            23.0, // Q_value
                            12.0, // boundary condition
                            dryad::resonances::ChannelRadii(0.63, 0.64),
                            dryad::resonances::Kinematics::NonRelativistic,
                            std::move( background ),
                            -1.,     // penetrability
                            0.,     // shiftFactor  
                            0.,     // phaseShift   
                            0. );   // difference


  std::vector< Channel > channels = {capture_channel, elastic_channel, fission_channel};
  
  ResonanceTable resonances( {capture_id, elast_id, fission_id},
                             {10, 20},
                             {{2, 3}, 
                              {4, 5},
                              {6, 7} } );

  return njoy::dryad::resonances::SpinGroup(channels, 
              resonances, 
              Formalism::ReichMoore, 
              BoundaryCondition::Constant);
}

CompoundSystem create_dryad_compound() {
  double EL(1e-5), EH(1e5);
  std::vector<SpinGroup> spingroups = { create_dryad_spingroup_1(), create_dryad_spingroup_2() };

  return CompoundSystem(EL, EH, spingroups);
}