#ifndef HONUMERIC_H
#define HONUMERIC_H

#include "hamiltonian.h"
#include <vector>
#include <cassert>
#include <iostream>
#include "../system.h"
#include "../particle.h"
#include "../WaveFunctions/wavefunction.h"

class HOnumeric : public Hamiltonian {
public:
    HOnumeric(System* system, double omega);
    double computeLocalEnergy(std::vector<Particle*> particles);
    double exactEnergy();

private:
    double m_omega = 0;
};

#endif //!HONUMERIC_H
