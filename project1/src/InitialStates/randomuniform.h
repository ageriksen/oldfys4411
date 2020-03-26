#pragma once
#include "initialstate.h"

class RandomUniform : public InitialState {
public:
    RandomUniform(System* system, int numberOfDimensions, int numberOfParticles, double steplength);
    void setupInitialState();
};

