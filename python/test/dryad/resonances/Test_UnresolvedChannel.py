# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import Particle
from njoy.dryad.resonances import Channel
from njoy.dryad.resonances import UnresolvedChannel
from njoy.dryad.resonances import ChannelRadii
from njoy.dryad.resonances import ParticlePair
from njoy.dryad.resonances import Kinematics
from njoy.dryad.resonances import TabulatedRadius
from njoy.dryad.id import ChannelID
from njoy.dryad.id import ReactionID
from njoy.dryad.id import ParticleID

class Test_UnresolvedChannel( unittest.TestCase ) :
    """Unit test for the UnresolvedChannel class."""

    def test_component( self ):

        elasticID = ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' )
        captureID = ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' )

        elasticRID = ReactionID( 'n,Cl35->n,Cl35' )
        captureRID = ReactionID( 'n,Cl35->g,Cl36[all]' )

        g = Particle( ParticleID.photon(), 0, 1, +1 )
        n = Particle( ParticleID.neutron(), 1.00866491574, 0.5, +1 )
        cl36 = Particle( ParticleID( 'Cl36' ), 35.9683050031, 0, +1 )
        cl35 = Particle( ParticleID( 'Cl35' ), 34.9688491981, 1.5, +1 )

        elasticPair = ParticlePair( n, cl35 )
        capturePair = ParticlePair( g, cl36 )

        elasticPair = ParticlePair( n, cl35 )
        capturePair = ParticlePair( g, cl36 )

        elasticQ = 0.0
        captureQ = 0.0

        elasticBoundary = None
        captureBoundary = None

        elasticRadii = ChannelRadii( 4.822220, 3.667980 )
        captureRadii = ChannelRadii( 0. )

        reference_energy = 1.

        chunk = UnresolvedChannel( elasticID, elasticPair, elasticPair,
                                   elasticQ, elasticBoundary, elasticRadii,
                                   True, reference_energy )

        self.assertEqual( elasticID, chunk.identifier )
        self.assertEqual( elasticRID, chunk.reaction )
        self.assertEqual( elasticPair, chunk.outgoing_particle_pair )
        self.assertEqual( elasticRadii, chunk.channel_radii )
        self.assertAlmostEqual( reference_energy, chunk.reference_energy )

        self.assertAlmostEqual( 3.1622776601683794e-3, chunk.width_conversion_factor( 1e-5 ) )
        self.assertAlmostEqual( 1.,                    chunk.width_conversion_factor( 1. ) )
        self.assertAlmostEqual( 10.,                   chunk.width_conversion_factor( 100. ) )


        chunk = UnresolvedChannel( captureID, elasticPair, capturePair,
                                   captureQ, captureBoundary, captureRadii,
                                   False, reference_energy )

        self.assertEqual( captureID, chunk.identifier )
        self.assertEqual( captureRID, chunk.reaction )
        self.assertEqual( capturePair, chunk.outgoing_particle_pair )
        self.assertEqual( captureRadii, chunk.channel_radii )
        self.assertAlmostEqual( reference_energy, chunk.reference_energy )

        self.assertAlmostEqual( 1., chunk.width_conversion_factor( 1e-5 ) )
        self.assertAlmostEqual( 1., chunk.width_conversion_factor( 1. ) )
        self.assertAlmostEqual( 1., chunk.width_conversion_factor( 100. ) )

    def test_curation( self ) :

        identifier = ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' )
        pair = ParticlePair( Particle( ParticleID.neutron(), 1.00866491574, 0.5, +1 ),
                             Particle( ParticleID( 'Cl35' ), 34.9688491981, 1.5, +1 ) )

        # the data is given explicitly
        chunk = UnresolvedChannel( identifier, pair, pair, 0., None,
                                   ChannelRadii( TabulatedRadius( [ 1e-5, 1., 1., 1., 2e+7 ],
                                                                  [ 4., 4., 4.5, 5., 5. ] ),
                                                 TabulatedRadius( [ 1e-5, 2., 2., 2., 2e+7 ],
                                                                  [ 3., 3., 3.5, 4., 4. ] ),
                                                 TabulatedRadius( [ 1e-5, 3., 3., 3., 2e+7 ],
                                                                  [ 2., 2., 2.5, 3., 3. ] ) ) )

        # the tabulated data is not curated
        radii = chunk.channel_radii
        self.assertEqual( False, radii.penetrability_radius.is_curated )
        self.assertEqual( False, radii.shift_factor_radius.is_curated )
        self.assertEqual( False, radii.phase_shift_radius.is_curated )

        # the tabulated data can be curated
        chunk.curate()

        radii = chunk.channel_radii
        self.assertEqual( True, radii.penetrability_radius.is_curated )
        self.assertEqual( True, radii.shift_factor_radius.is_curated )
        self.assertEqual( True, radii.phase_shift_radius.is_curated )

    def test_comparison( self ) :

        elasticID = ChannelID( 'n,Cl35->n,Cl35{0,1,1+}' )
        captureID = ChannelID( 'n,Cl35->g,Cl36[all]{0,0,1+}' )

        g = Particle( ParticleID.photon(), 0, 1, +1 )
        n = Particle( ParticleID.neutron(), 1.00866491574, 0.5, +1 )
        cl36 = Particle( ParticleID( 'Cl36' ), 35.9683050031, 0, +1 )
        cl35 = Particle( ParticleID( 'Cl35' ), 34.9688491981, 1.5, +1 )

        elasticPair = ParticlePair( n, cl35 )
        capturePair = ParticlePair( g, cl36 )

        elasticQ = 0.0
        captureQ = 0.0

        elasticBoundary = None
        captureBoundary = None

        elasticRadii = ChannelRadii( 4.822220, 3.667980 )
        captureRadii = ChannelRadii( 0. )

        left = UnresolvedChannel( elasticID, elasticPair, elasticPair,
                                  elasticQ, elasticBoundary, elasticRadii, True, 1. )
        equal = UnresolvedChannel( elasticID, elasticPair, elasticPair,
                                   elasticQ, elasticBoundary, elasticRadii, True, 1. )
        differentChannel = UnresolvedChannel( captureID, elasticPair, capturePair,
                                              captureQ, captureBoundary, captureRadii, False, 1. )
        differentReference = UnresolvedChannel( elasticID, elasticPair, elasticPair,
                                                elasticQ, elasticBoundary, elasticRadii, False, 2. )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == differentChannel ) )
        self.assertEqual( False, ( left == differentReference ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != differentChannel ) )
        self.assertEqual( True, ( left != differentReference ) )

if __name__ == "__main__":
    unittest.main()
