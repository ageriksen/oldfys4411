#pragma once
#include "wavefunction.h"

class SimpleGaussian : public WaveFunction {
public:
    SimpleGaussian(class System* system, double alpha);
    double evaluate(std::vector<class Particle*> particles);
    double exponent(std::vector<class Particle*> particles);
    double laplacian(std::vector<class Particle*> particles);
};
