//#include "Math/random.h"
#include <random>
#include <iostream>

#include "wavefunction.h"

int main()
{   
    int     ndims       =   1           ;
    int     nparticles  =   1           ;
    int     nsteps      =   (int) 1e6   ;
    
    //double  omega       =   1.0         ;   // oscillator freq
    double  alpha       =   0.5         ;   // variational param
    double  stepsize    =   0.00001       ;   // metropolis steplength
    double  equilibr    =   0.1         ;   // amount total steps
                                            // for equilibration
    double oldr, newr;
    double oldWf, newWf;
    double E, EE, DE; // local energy, energy squared and change in energy
    int accepted;

    WaveFunction wf;

    std::random_device rd;
    std::mt19937_64 engine(rd());
    std::uniform_real_distribution<double> uniformDistribution(-1, 1);
    std::uniform_real_distribution<double> acceptanceDistribution(0, 1);


    //oldr = stepsize*( Random::nextDouble() - 0.5 );
    oldr = stepsize*( uniformDistribution(engine)- 0.5 );
    oldWf = wf.psi(oldr, alpha);
    for( int mc = 0; mc < nsteps; mc++ )
    {
        if( mc > nsteps*equilibr)
        {
            newr = oldr + stepsize*( uniformDistribution(engine)- 0.5 );
            newWf = wf.psi(newr, alpha);
            if( uniformDistribution(engine) <= (newWf*newWf)/(oldWf*oldWf) )
            {
                oldr = newr;
                oldWf = newWf;
                accepted ++;
            }
            DE = wf.LocalEnergy(oldr, alpha);
            E += DE;
            EE += DE*DE;
        }
    }
    E /= nsteps;
    EE /= nsteps;
    double variance = EE - E*E;
    double acceptratio = accepted/nsteps;
    double error = std::sqrt( variance/nsteps );

    //  ==========================================  \\
    std::cout << std::endl;
    std::cout << "  -- System info -- " << std::endl;
    std::cout << " Number of particles  : " << nparticles << std::endl;
    std::cout << " Number of dimensions : " << ndims << std::endl;
    std::cout << " Number of Metropolis steps run : 10^" << std::log10(nsteps) << std::endl;
    std::cout << " Number of equilibration steps  : 10^" << std::log10(std::round(nsteps*equilibr)) << std::endl;
    std::cout << std::endl;
    std::cout << "  -- Wave function parameters -- " << std::endl;
    std::cout << " Parameter alpha: " << alpha << std::endl;
    std::cout    <<  std::endl;
    std::cout    <<  "  ---- Reults -----    "   << std::endl;
    //std::cout    <<  " values scaled by  :   "   <<  m_N                <<  std::endl; 
    std::cout    <<  " Energy            :   "   <<  E           <<  std::endl;
    std::cout    <<  " variance          :   "   <<  variance         <<  std::endl;
    //std::cout    <<  " accepted steps    :   "   <<  m_acceptedsteps    <<  std::endl;
    std::cout    <<  " acceptance ratio  :   "   <<  acceptratio    <<  std::endl;
    std::cout    <<  " error             :   "   <<  error    <<  std::endl;
    std::cout    <<  std::endl;


    return 0;
}

