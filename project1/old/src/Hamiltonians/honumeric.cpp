#include "honumeric.h"


HOnumeric::HOnumeric(System* system, double omega) :
        Hamiltonian(system) {
    assert(omega > 0);
    m_omega  = omega;
    m_name = "HO_numeric";
}

double HOnumeric::computeLocalEnergy(std::vector<class Particle*> particles) {
    /* when using numerical differentiation, the computation of the kinetic
     * energy becomes the same for all Hamiltonians, and thus the code for
     * doing this is in the hamiltonian superclass under numerical.
     *
     * You may access the wave function currently used through the
     * getWaveFunction method in the m_system object in the super-class, i.e.
     * m_system->getWaveFunction()...
     */

    double rr = 0;
    for( int i=0; i < m_system->getNumberOfParticles(); i++ )
    {
        rr += particles[i]->lengthSquared();
    } // move kinetic out off loop

    double potential = 0.5 * m_omega * m_omega * rr;

    //double kinetic = -0.5*m_system->getWaveFunction()->laplacian(m_system->getParticles());
    double kinetic = numeric();
    return kinetic + potential;
}
