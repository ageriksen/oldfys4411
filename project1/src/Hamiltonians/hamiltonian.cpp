#include "hamiltonian.h"


Hamiltonian::Hamiltonian(System* system) {
    m_system = system;
}

double Hamiltonian::numeric() 
{
    //std::cout << "--------------------------------" << std::endl;
    //std::cout << "starting numeric differentiation" << std::endl;
    //std::cout << "--------------------------------" << std::endl;
    double h = 0.001;
    double h2 = 1e6;
    std::vector<class Particle*> r = m_system->getParticles();
    std::vector<class Particle*> rplus;
    std::vector<class Particle*> rminus;
    for( int i=0; i<m_system->getNumberOfParticles(); i++ )
    {
        rplus.push_back(new Particle());
        rplus.at(i)->setNumberOfDimensions(m_system->getNumberOfDimensions());
        rplus.at(i)->setPosition(r[i]->getPosition());
        rminus.push_back(new Particle());
        rminus.at(i)->setNumberOfDimensions(m_system->getNumberOfDimensions());
        rminus.at(i)->setPosition(r[i]->getPosition());
    }
    double psiplus = 0; double psiminus = 0;
    double psicurrent = m_system->getWaveFunction()->evaluate(r);
    double kinetic = 0; 
    for( int part=0; part < m_system->getNumberOfParticles(); part++ )
    {
        for( int dim=0; dim < m_system->getNumberOfDimensions(); dim++ )
        {
            rplus[part]->adjustPosition(h, dim);
            rminus[part]->adjustPosition(-h, dim);
            psiplus = m_system->getWaveFunction()->evaluate(rplus);
            psiminus = m_system->getWaveFunction()->evaluate(rminus);
            kinetic -= ( psiminus + psiplus - 2*psicurrent );
            rplus[part]->adjustPosition(-h, dim);
            rminus[part]->adjustPosition(h, dim);
        }//dimensions
    }//particles
    //std::cout << "finished numeric differentiation" << std::endl;
    //std::cout << "--------------------------------" << std::endl;
    //rplus.clear(); 
    std::vector<class Particle*>().swap( rplus );
    //rminus.clear();
    std::vector<class Particle*>().swap( rminus );
    return 0.5*h2*kinetic/psicurrent;
}
