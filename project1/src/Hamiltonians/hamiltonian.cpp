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

    double psiplus = 0; double psiminus = 0;
    double psicurrent = m_system->getWaveFunction()->evaluate(r);
    double kinetic = 0; 

    for( int part=0; part < m_system->getNumberOfParticles(); part++ )
    {
        for( int dim=0; dim < m_system->getNumberOfDimensions(); dim++ )
        {
            r[part]->adjustPosition(h, dim); 
            psiplus = m_system->getWaveFunction()->evaluate(r);
            r[part]->adjustPosition(-h,dim);

            r[part]->adjustPosition(-h, dim); 
            psiminus = m_system->getWaveFunction()->evaluate(r);
            r[part]->adjustPosition(h,dim);

            kinetic -= ( psiminus + psiplus - 2*psicurrent );
        }//dimensions
    }//particles
    //std::cout << "finished numeric differentiation" << std::endl;
    //std::cout << "--------------------------------" << std::endl;
    return 0.5*h2*kinetic/psicurrent;
}
