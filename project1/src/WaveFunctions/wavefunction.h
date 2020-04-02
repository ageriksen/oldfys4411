#pragma once
#include <vector>


class WaveFunction {
public:
    WaveFunction(class System* system);

    int     getNumberOfParameters() { return m_numberOfParameters; }
    std::vector<double> getParameters() { return m_parameters; }

    virtual double evaluate(std::vector<class Particle*> particles) = 0;
    virtual double laplacian(std::vector<class Particle*> particles) = 0;
    //virtual double exponent(std::vector<class Particle*> particles) = 0;

    void changeParameter(int parameter, double change){m_parameters[parameter]+=change;}

protected:
    int     m_numberOfParameters = 0;
    std::vector<double> m_parameters = std::vector<double>();
    class System* m_system = nullptr;
};

