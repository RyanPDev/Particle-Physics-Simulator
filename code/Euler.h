#pragma once
#include "ParticleSystem.h"
class Euler
{
private:
public:
	glm::vec3 gravity = { 0,0,0 };
	Euler();
	void Update(ParticleSystem &ps, float dt);
};

