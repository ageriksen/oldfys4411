#pragma once
#include <vector>
#include <string>
#include "../system.h"
#include "../particle.h"

class Hamiltonian {
public:
    Hamiltonian(class System* system);
    virtual double computeLocalEnergy(std::vector<class Particle*> particles) = 0;
    //virtual double exactEnergy() = 0;
    std::string getName() {return m_name;}

    double numeric();

protected:
    class System* m_system = nullptr;
    std::string m_name ="";
};

