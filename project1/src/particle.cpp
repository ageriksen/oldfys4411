#include "particle.h"
#include <cassert>

Particle::Particle() {
}

void Particle::setPosition(const std::vector<double> &position) {
    assert((int)position.size() == m_numberOfDimensions);
    m_position = position;
}

void Particle::adjustPosition(double change, int dimension) {
    m_position.at(dimension) += change;
}

void Particle::setNumberOfDimensions(int numberOfDimensions) {
    m_numberOfDimensions = numberOfDimensions;
}

double Particle::lengthSquared()
{
    double rr = 0;
    for( int i = 0; i < m_numberOfDimensions; i++ )
    {
        rr += m_position[i]*m_position[i];
    }
    return rr;
}
