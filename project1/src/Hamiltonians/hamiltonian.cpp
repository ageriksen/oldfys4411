#include "hamiltonian.h"

Hamiltonian::Hamiltonian(System* system) {
    m_system = system;
}

double Hamiltonian::numeric() 
{
    //return 0.0;
    double h = 0.001;
    double h2 = 1e6;
    std::vector<class Particle*> r = m_system->getParticles();
    std::vector<class Particle*> rpluss(m_system->getNumberOfParticles());
    std::vector<class Particle*> rminus(m_system->getNumberOfParticles());
    for( int i=0; i<m_system->getNumberOfParticles(); i++ )
    {
        rpluss[i]->setPosition(r[i]->getPosition());
        rminus[i]->setPosition(r[i]->getPosition());
    }
    double psipluss = 0; double psiminus = 0;
    double psicurrent = m_system->getWaveFunction()->evaluate(r);
    double kinetic = 0; 
    for( int part=0; part < m_system->getNumberOfParticles(); part++ )
    {
        for( int dim=0; dim < m_system->getNumberOfDimensions(); dim++ )
        {
            rpluss[part]->adjustPosition(h, dim);
            rminus[part]->adjustPosition(-h, dim);
            psipluss = m_system->getWaveFunction()->evaluate(rpluss);
            psiminus = m_system->getWaveFunction()->evaluate(rminus);
            kinetic -= ( psiminus + psipluss - 2*psicurrent );
            rpluss[part]->setPosition(r[part]->getPosition());
            rminus[part]->setPosition(r[part]->getPosition());
        }//dimensions
    }//particles
    return 0.5*h2*kinetic/psicurrent;
}
