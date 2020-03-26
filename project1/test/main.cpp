//#include "Math/random.h"
#include <random>
#include <iostream>
#include <vector>

#include "wavefunction.h"

int main()
{   
    int     ndims       =   1           ;
    int     nparticles  =   1           ;
    int     nsteps      =   (int) 1e6   ;
    
    //double  omega       =   1.0         ;   // oscillator freq
    double  alpha       =   0.4         ;   // variational param
    double  stepsize    =   0.0001       ;   // metropolis steplength
    double  equilibr    =   0.1         ;   // amount total steps
                                            // for equilibration
    double oldr, newr;
    double oldWf, newWf;
    double bestE=10; double bestVar=10;
    int accepted;

    WaveFunction wf;
    std::vector<double> alphas, energies, variances;

    std::random_device rd;
    std::mt19937_64 engine(rd());
    std::uniform_real_distribution<double> uniformDistribution(-1, 1);
    std::uniform_real_distribution<double> acceptanceDistribution(0, 1);

    //  ||==========================================||
    std::cout << std::endl;
    std::cout << "  -- System info -- " << std::endl;
    std::cout << " Number of particles  : " << nparticles << std::endl;
    std::cout << " Number of dimensions : " << ndims << std::endl;
    std::cout << " Number of Metropolis steps run : 10^" << std::log10(nsteps) << std::endl;
    std::cout << " Number of equilibration steps  : 10^" << std::log10(std::round(nsteps*equilibr)) << std::endl;
    //  ||==========================================||

    int maxVariations = 20;

    for( int i = 0; i < maxVariations; i++ )
    {
        alpha += 0.05;
        alphas.push_back(alpha);
        double energy=0;
        double energy2=0;
        double delta=0; // local energy, energy squared and change in energy
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
                delta = wf.LocalEnergy(oldr, alpha);
                energy += delta;
                energy2 += delta*delta;
            }
        }
        energy /= nsteps;
        energy2 /= nsteps;
        double variance = energy2 - energy*energy;
        double acceptratio = (double)accepted/(double)nsteps;
        double error = std::sqrt( variance/nsteps );
        energies.push_back(energy);
        variances.push_back(variance);
        if( energy<bestE && variance<bestVar )
        {
            //std::cout << "---------------------------------------" << std::endl;
            //std::cout << "new best.\n previous best:\n" << std::endl;
            //std::cout << "energy: " << bestE << ", variance: " << bestVar << std::endl;
            //std::cout << "new:" << std::endl;
            //std::cout << "energy: " << energy << ", variance: " << variance << std::endl;
            //std::cout << "---------------------------------------" << std::endl;
            bestE=energy; bestVar=variance;
        }
        //std::cout << std::endl;
        //std::cout << "  -- Wave function parameters -- " << std::endl;
        //std::cout << " Parameter alpha: " << alpha << std::endl;
        std::cout   << "-----alpha="    <<  alpha   << std::endl;
        //std::cout   <<  "  ---- Reults -----    "   << std::endl;
        std::cout   <<  " Energy            :   "   << energy         <<  std::endl;
        std::cout   <<  " variance          :   "   << variance       <<  std::endl;
        //std::cout   <<  " accepted steps    :   "   << accepted       <<  std::endl;
        std::cout   <<  " acceptance ratio  :   "   << acceptratio    <<  std::endl;
        std::cout   <<  " error             :   "   << error          <<  std::endl;
        //std::cout    <<  " Best energy       :   "   << bestE   <<  std::endl;
        //std::cout    <<  " Best variance     :   "   << bestVar <<  std::endl;
        //std::cout    <<  std::endl;
    }



    return 0;
}

