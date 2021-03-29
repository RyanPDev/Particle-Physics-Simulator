#pragma once
#include <glm/vec3.hpp>

class ParticleSystem
{
public:
	ParticleSystem(int maxParticles = 100);

	void UpdateParticle(int idx, glm::vec3 newPos);
	void UpdateLilSpheres();

	void SpawnParticle(glm::vec3 _position);

	void UpdateAge(float _dt);
	void DestroyOldParticles(float _maxAge);

	int maxParticles;
	glm::vec3* positions;
	glm::vec3* velocities;

private:
	float* age;

	int currentParticles;
};