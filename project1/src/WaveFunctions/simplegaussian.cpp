#include "simplegaussian.h"
#include <cmath>
#include <cassert>
#include "wavefunction.h"
#include "../system.h"
#include "../particle.h"

SimpleGaussian::SimpleGaussian(System* system, double alpha) :
        WaveFunction(system) {
    assert(alpha >= 0);
    m_numberOfParameters = 1;
    m_parameters.reserve(1);
    m_parameters.push_back(alpha);
}

double SimpleGaussian::evaluate(std::vector<class Particle*> particles) {
    /* You need to implement a Gaussian wave function here. The positions of
     * the particles are accessible through the particle[i].getPosition()
     * function.
     *
     * For the actual expression, use exp(-alpha * r^2), with alpha being the
     * (only) variational parameter.
     */
    //return 0;

    //following specifically for 1 particle, 1 dimension. to avoid errors in evaluating sqrt(x^2)
    double r = particles[0]->getPosition()[0];
    return std::exp( -m_parameters[0]*r*r); //gaussian function, in 1 dim and 1 particle
}

double SimpleGaussian::exponent(std::vector<class Particle*> particles)
{
    /*in a lot of cases, probably uneccessary to find the result. Just change the exponent*/
    double r = particles[0]->getPosition()[0];
    return -m_parameters[0]*r*r;
}

double SimpleGaussian::computeDoubleDerivative(std::vector<class Particle*> particles) {
    /* All wave functions need to implement this function, so you need to
     * find the double derivative analytically. Note that by double derivative,
     * we actually mean the sum of the Laplacians with respect to the
     * coordinates of each particle.
     *
     * This quantity is needed to compute the (local) energy (consider the
     * Schrödinger equation to see how the two are related).
     *  
     * ( 2*a^2*r^2 - 2*a )*e^( -ar^2 )
     */

    //return 0;

    double r = particles[0]->getPosition()[0];
    double alpha = m_parameters[0];
    return ( 4*alpha*alpha*r*r - 2*alpha );//*std::exp( -alpha*r*r );
}
