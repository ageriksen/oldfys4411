#pragma once
#include <vector>
#include "../parameter.h"


class WaveFunction {
public:
    WaveFunction(class System* system);

    int     getNumberOfParameters() { return m_numberOfParameters; }
    std::vector<class Parameter> getParameters() { return m_parameters; }

    void changeParameter(int i, double change) { m_parameters[i].step(change);}
    void setParameter(int i, double parameter) { if(i<m_numberOfParameters) m_parameters[i].setValue(parameter);}

    virtual double evaluate(std::vector<class Particle*> particles) = 0;
    //virtual double exponent(std::vector<class Particle*> particles) = 0;
    virtual double laplacian(std::vector<class Particle*> particles) = 0;

protected:
    int     m_numberOfParameters = 0;
    std::vector<class Parameter> m_parameters = std::vector<class Parameter>();
    class System* m_system = nullptr;
};

