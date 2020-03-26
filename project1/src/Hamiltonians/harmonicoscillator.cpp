#include "harmonicoscillator.h"
#include <cassert>
#include <iostream>
#include "../system.h"
#include "../particle.h"
#include "../WaveFunctions/wavefunction.h"

using std::cout;
using std::endl;

HarmonicOscillator::HarmonicOscillator(System* system, double omega) :
        Hamiltonian(system) {
    assert(omega > 0);
    m_omega  = omega;
}

double HarmonicOscillator::computeLocalEnergy(std::vector<class Particle*> particles) {
    /* Here, you need to compute the kinetic and potential energies. Note that
     * when using numerical differentiation, the computation of the kinetic
     * energy becomes the same for all Hamiltonians, and thus the code for
     * doing this should be moved up to the super-class, Hamiltonian.
     *
     * You may access the wave function currently used through the
     * getWaveFunction method in the m_system object in the super-class, i.e.
     * m_system->getWaveFunction()...
     */

    double localEnergy = 0;
    for( int i=0; i < particles.size(); i++ )
    {
        double rr = particles[i]->lengthSquared();
        double potential = 0.5 * m_omega * m_omega * rr;
        double kinetic = m_system->getWaveFunction()->laplacian(m_system->getParticles());
        localEnergy += kinetic + potential;
    } // move kinetic out off loop
    return localEnergy;

    //double r = particles[0]->getPosition()[0];
    //double alpha = m_system->getWaveFunction()->getParameters()[0];
    //return 0.5*r*r*( 1 - alpha*alpha*alpha*alpha ) + 0.5*alpha*alpha;
}

