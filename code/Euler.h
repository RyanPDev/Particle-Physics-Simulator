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
		glm::vec3 c = { -4.f, 9.f, 3.f };
		float r = 1.f;
	}sphere;

	struct CapsuleCollider
	{
		glm::vec3 pos[2];
		float r;
	}capsule;

	int CheckCollisionBox(glm::vec3, glm::vec3);
	bool CheckCollisionSphere(glm::vec3);
	int CheckCollisionCapsule(glm::vec3, glm::vec3);
	void ReboundPlane(glm::vec3&, glm::vec3&, glm::vec3, float);
	float GetDistanceFromPlane(int, glm::vec3);
	float GetDFromPlane(glm::vec3, glm::vec3);
	glm::vec3 GetCollisionPoint(glm::vec3, glm::vec3);
	glm::vec3 Euler::GetCollisionNorm(glm::vec3);
public:
	float reboundCoefficient = 1.f;
	Euler();
	glm::vec3 gravity = { 0, -9.8f, 0 };
	void Update(ParticleSystem& ps, float dt);
};