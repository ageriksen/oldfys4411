#include "wavefunction.h"

double WaveFunction::psi(double r, double alpha)
{
    return std::exp( -0.5*alpha*alpha*r*r );
}

double WaveFunction::LocalEnergy(double r, double alpha)
{
    return 0.5*r*r*( 1 - alpha*alpha*alpha*alpha ) + 0.5*alpha*alpha;
}
