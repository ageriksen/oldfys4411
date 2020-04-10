#pragma once


#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>

class Sampler {
public:
    Sampler(class System* system);
    void setNumberOfMetropolisSteps(int steps);
    void sample(bool acceptedStep);
    void printOutputToTerminal();
    void computeAverages();
    double getEnergy()          { return m_energy; }

    void writeResults();
    void writeTime(double time);
    bool fileexists( const std::string& );

private:
    int     m_numberOfMetropolisSteps = 0;
    int     m_stepNumber = 0;

    double  m_acceptedSteps = 0;
    double  m_cumulativeEnergy = 0;
    double  m_cumulativeEnergy2 = 0;

    double  m_energy = 0;
    double  m_energy2 = 0;
    double  m_acceptRatio = 0;
    double  m_variance = 0;
    double  m_meanEnergy = 0;

    class System* m_system = nullptr;
    double m_N = 0;
};
