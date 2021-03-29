#include "..\Euler.h"

Euler::Euler(){}
void Euler::Update(ParticleSystem &ps, float dt)
{
	// per cada particula
	for (int i = 0; i < ps.currentParticles; i++)
	{
		ps.positions[i] = ps.positions[i] + ps.celerities[i] * dt;
		ps.celerities[i] = ps.celerities[i] + (gravity * dt);
	}
}
