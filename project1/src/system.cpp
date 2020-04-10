#include "system.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include "sampler.h"
#include "particle.h"
#include "WaveFunctions/wavefunction.h"
#include "Hamiltonians/hamiltonian.h"
#include "InitialStates/initialstate.h"
#include "Math/random.h"

bool System::metropolisStep(int particle) 
{
    /* Perform the actual Metropolis step: Choose a particle at random and
     * change it's position by a random amount, and check if the step is
     * accepted by the Metropolis test (compare the wave function evaluated
     * at this new position with the one at the old position).
     */
        
    //double oldWave = m_waveFunction->exponent(m_particles);
    double oldWave = m_waveFunction->evaluate(m_particles);


    std::vector<double> testStep(m_numberOfDimensions);

    for (int dim = 0; dim < m_numberOfDimensions; dim++)
    {
        double step = 2*(Random::nextDouble() - 0.5)*m_stepLength;
        testStep[dim] = step;
        m_particles[particle]->adjustPosition( testStep[dim], dim );
    }
    //double newWave = m_waveFunction->exponent(m_particles);
    double newWave = m_waveFunction->evaluate(m_particles);
    
    //double ratio = std::exp( 2.*newWave - 2.*oldWave );
    //if (Random::nextDouble() <= ratio) 
    double ratio = (newWave*newWave)/(oldWave*oldWave);
    if( Random::nextDouble() <= ratio )
    {
        return true;
    }
    else
    {
        for (int dim = 0; dim <m_numberOfDimensions; dim++)
        {
            m_particles[particle]->adjustPosition( -1*testStep[dim], dim );
        }
        return false;
    }
}

void System::runMetropolisSteps(int numberOfMetropolisSteps) 
{
    
    for( int variation = 0; variation < m_maxVar; variation++ )
    {
        m_particles                 = m_initialState->getParticles();
        m_numberOfMetropolisSteps   = numberOfMetropolisSteps;
        m_sampler                   = new Sampler(this);
        m_sampler->setNumberOfMetropolisSteps(numberOfMetropolisSteps);

        m_waveFunction->changeParameter((double)0.05);
        for (int i=0; i < numberOfMetropolisSteps; i++) 
        {
            for (int particle = 0; particle < m_numberOfParticles; particle++) 
            {
                bool acceptedStep = metropolisStep(particle);
                if( i > numberOfMetropolisSteps*m_equilibrationFraction )
                {
                    m_sampler->sample(acceptedStep);
                }
            }// particles
        }//Metropolis steps
        //m_timer->newTime();
        m_sampler->computeAverages();
        m_sampler->printOutputToTerminal();
        m_sampler->writeResults();
        
    }//variable variations
    
    m_timer->newTime();
    std::chrono::duration<double> time = m_timer->timeDifference(0, 1);
    std::cout    <<  "   ------   VMC finished    ------"   << std::endl;
    std::cout    <<  " time spent:   "   <<  (double)time.count()<<"s"<<  std::endl;
    m_sampler->writeTime((double)time.count());
}

void System::setNumberOfParticles(int numberOfParticles) {
    m_numberOfParticles = numberOfParticles;
}

void System::setNumberOfDimensions(int numberOfDimensions) {
    m_numberOfDimensions = numberOfDimensions;
}

void System::setStepLength(double stepLength) {
    assert(stepLength >= 0);
    m_stepLength = stepLength;
}

void System::setEquilibrationFraction(double equilibrationFraction) {
    assert(equilibrationFraction >= 0);
    m_equilibrationFraction = equilibrationFraction;
}

void System::setHamiltonian(Hamiltonian* hamiltonian) {
    m_hamiltonian = hamiltonian;
}

void System::setWaveFunction(WaveFunction* waveFunction) {
    m_waveFunction = waveFunction;
}

void System::setInitialState(InitialState* initialState) {
    m_initialState = initialState;
}


