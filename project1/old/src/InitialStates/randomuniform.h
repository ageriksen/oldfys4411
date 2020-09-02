#pragma once
#include <iostream>
#include <cassert>
#include "Math/random.h"
//#include <random>
#include "../particle.h"
#include "../system.h"
#include "initialstate.h"

class RandomUniform : public InitialState {
public:
    RandomUniform(System* system, int numberOfDimensions, int numberOfParticles, double steplength);
    void setupInitialState();
};

