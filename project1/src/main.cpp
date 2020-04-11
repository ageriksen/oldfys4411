#include <iostream>
#include <chrono>
#include "system.h"
#include "particle.h"
#include "WaveFunctions/wavefunction.h"
#include "WaveFunctions/simplegaussian.h"
#include "Hamiltonians/hamiltonian.h"
#include "Hamiltonians/harmonicoscillator.h"
#include "InitialStates/initialstate.h"
#include "InitialStates/randomuniform.h"
#include "Math/random.h"

using namespace std;


int main() {
    int numberOfDimensions  = 1;
    int numberOfParticles   = 1;
    int numberOfSteps       = (int) 1e4;
    double omega            = 1.0;          // Oscillator frequency.
    double alpha            = 0.1;          // Variational parameter.
    double stepLength       = 0.5;          // Metropolis step length.
    double equilibration    = 0.1;          // Amount of the total steps used
    double spread = 1;
    // for equilibration.
    int maxVar              = 12;

    Timer* timer = new Timer();

    System* system = new System(maxVar, timer);
    system->setHamiltonian              (new HarmonicOscillator(system, omega));
    system->setWaveFunction             (new SimpleGaussian(system, alpha));
    system->setInitialState             (new RandomUniform(system, numberOfDimensions, numberOfParticles, spread));
    system->setEquilibrationFraction    (equilibration);
    system->setStepLength               (stepLength);

    system->runMetropolisSteps          (numberOfSteps);
    return 0;
}
