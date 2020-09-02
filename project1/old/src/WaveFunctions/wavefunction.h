#pragma once
#include <vector>


class WaveFunction {
public:
    WaveFunction(class System* system);

    int     getNumberOfParameters() { return m_numberOfParameters; }
    std::vector<double> getParameters() { return m_parameters; }

    void setParameter(double value){m_parameters[0]=value;}
    void changeParameter(double value){m_parameters[0]+=value;}

    virtual double evaluate(std::vector<class Particle*> particles) = 0;
    virtual double laplacian(std::vector<class Particle*> particles) = 0;
    //virtual double exponent(std::vector<class Particle*> particles) = 0;

protected:
    int     m_numberOfParameters = 0;
    std::vector<double> m_parameters = std::vector<double>();
    class System* m_system = nullptr;
};

