#include "hamiltonian.h"

#include <iostream>
#include <string>

Hamiltonian::Hamiltonian(System* system) {
    m_system = system;
}

double Hamiltonian::numeric() 
{
    double h = 0.001;
    double h2 = 1e6;
    std::vector<class Particle*> r = m_system->getParticles();
    std::vector<class Particle*> rpluss;
    std::vector<class Particle*> rminus;
    for( int i=0; i<m_system->getNumberOfParticles(); i++ )
    {
        rpluss.push_back(new Particle());
        rpluss.at(i)->setNumberOfDimensions(m_system->getNumberOfDimensions());
        rpluss.at(i)->setPosition(r[i]->getPosition());
        rminus.push_back(new Particle());
        rminus.at(i)->setNumberOfDimensions(m_system->getNumberOfDimensions());
        rminus.at(i)->setPosition(r[i]->getPosition());
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
            rpluss[part]->adjustPosition(-h, dim);
            rminus[part]->adjustPosition(h, dim);
        }//dimensions
    }//particles
    return 0.5*h2*kinetic/psicurrent;
}
