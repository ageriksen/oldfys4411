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

    double alpha = m_parameters[0];
    double rr = 0;
    for( int i = 0; i < m_system->getNumberOfDimensions(); i++ )
    {
        rr += particles[i]->lengthSquared();
    }
    return std::exp( -alpha*rr );
    //double r = particles[0]->getPosition()[0];
    //return std::exp( -0.5*alpha*alpha*r*r );
}

//double SimpleGaussian::exponent(std::vector<class Particle*> particles)
//{
//    /*in a lot of cases, probably uneccessary to find the result. Just change the exponent*/
//    double alpha = m_parameters[0];
//    double exponent = 0;
//    for( int i = 0; i < particles.size(); i++ )
//    {
//        double rr = particles[i]->lengthSquared();
//        exponent -= alpha*rr;
//    }
//    return exponent;
//}

double SimpleGaussian::laplacian(std::vector<class Particle*> particles) {
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
    double alpha = m_parameters[0];
    double dimensions = particles[0]->getPosition().size();
    double derivative = 0;
    double rr = 0;
    for( int i = 0; i < m_system->getNumberOfDimensions(); i++ )
    {
        rr += particles[i]->lengthSquared();
    }
    derivative = ( -2*alpha*dimensions*particles.size() + 4*alpha*alpha*rr );       
    return derivative;
}
// energy per particle and energy per particle per dimension should be spot on for the non-interacting case. 
// variational principle, ch. 7 -> 1st example <- answer here you can check your answer
