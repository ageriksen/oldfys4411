




double System::WaveFunction(r, alpha)
{
    return std::exp( -0.5*alpha*alpha*r*r );
}

double System::LocalEnergy(r, alpha)
{
    return 0.5*r*r*( 1 - alpha*alpha*alpha*alpha ) + 0.5*alpha*alpha;
}
