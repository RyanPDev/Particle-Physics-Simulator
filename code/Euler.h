#pragma once
#include "ParticleSystem.h"
#include <vector>
#include <glm/glm.hpp> 

class Euler
{
private:
	struct BoxCollider
	{
		glm::vec3 pos[2] = { glm::vec3(-5.f, 0.f, -5.f), glm::vec3{5.f, 10.f, 5.f} };

		glm::vec3 norms[6] = {
	glm::vec3(0.f,  1.f,  0.f),
	glm::vec3(1.f,  0.f,  0.f),
	glm::vec3(0.f,  0.f,  1.f),
	glm::vec3(0.f, -1.f,  0.f),
	glm::vec3(-1.f,  0.f,  0.f),
	glm::vec3(0.f,  0.f, -1.f)
		};
		float d[6] = { 0.f, 5.f, 5.f, 10.f, 5.f, 5.f };
	}box;

	struct SphereCollider
	{

	};

	struct CapsuleCollider
	{

	};

	int CheckCollisionBox(glm::vec3, glm::vec3);
	void ReboundPlane(glm::vec3&, glm::vec3&, glm::vec3, float);
	float GetDistanceFromPlane(int, glm::vec3);
public:
	Euler();
	float reboundCoefficient = 1.f;
	glm::vec3 gravity = { 0, -9.8f, 0 };
	void Update(ParticleSystem& ps, float dt);
};