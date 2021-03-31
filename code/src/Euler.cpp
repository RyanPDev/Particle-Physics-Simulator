#include "..\Euler.h"

Euler::Euler()
{

}

void Euler::Update(ParticleSystem& ps, float dt)
{
	glm::vec3 iPos, iV;

	// per cada partícula
	for (int i = 0; i < ps.currentParticles; i++)
	{
		iPos = ps.positions[i];
		iV = ps.celerities[i];

		ps.positions[i] = ps.positions[i] + ps.celerities[i] * dt;
		ps.celerities[i] = ps.celerities[i] + (gravity * dt);

		while (CheckCollisionBox(iPos, ps.positions[i]) < 6)
		{
			int collidedPlane = CheckCollisionBox(iPos, ps.positions[i]);
			ReboundPlane(ps.positions[i], ps.celerities[i], box.norms[collidedPlane], box.d[collidedPlane]);
		}

		if (CheckCollisionSphere(ps.positions[i]))
		{

		}
	}
}

int Euler::CheckCollisionBox(glm::vec3 iPos, glm::vec3 pos)
{
	int collidedPlane = 6;
	for (int i = 0; i < 6; i++)
	{
		if ((glm::dot(box.norms[i], iPos) + box.d[i]) * (glm::dot(box.norms[i], pos) + box.d[i]) <= 0 && GetDistanceFromPlane(i, iPos) != 0)
		{
			collidedPlane = i;
			break;
		}
	}
	return collidedPlane;
}

bool Euler::CheckCollisionSphere(glm::vec3 pos)
{
	return (glm::abs(glm::distance(sphere.c, pos)) - sphere.r <= 0);
}

int Euler::CheckCollisionCapsule(glm::vec3, glm::vec3)
{
	return 0;
}

float Euler::GetDistanceFromPlane(int plane, glm::vec3 pos)
{
	float distance = 0;
	distance = (glm::abs((box.norms[plane].x * pos.x) + (box.norms[plane].y * pos.y) + (box.norms[plane].z * pos.z) + box.d[plane])) /
		(glm::sqrt(glm::pow(box.norms[plane].x, 2) + glm::pow(box.norms[plane].y, 2) + glm::pow(box.norms[plane].z, 2)));

	return distance;
}

void Euler::ReboundPlane(glm::vec3& p, glm::vec3& v, glm::vec3 n, float d)
{
	p = p - (1 + reboundCoefficient) * (glm::dot(n, p) + d) * n;
	v = v - (1 + reboundCoefficient) * (glm::dot(n, v)) * n;
}