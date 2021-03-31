#include "..\Euler.h"
#include <iostream>

Euler::Euler()
{

}

void Euler::Update(ParticleSystem& ps, float dt)
{
	glm::vec3 iPos, iV, auxPos, auxV;

	// per cada partícula
	for (int i = 0; i < ps.currentParticles; i++)
	{
		iPos = ps.positions[i];
		iV = ps.celerities[i];

		ps.positions[i] = ps.positions[i] + ps.celerities[i] * dt;
		ps.celerities[i] = ps.celerities[i] + (gravity * dt);

		if (CheckCollisionSphere(ps.positions[i]))
		{
			glm::vec3 colPos = GetCollisionPoint(iPos, ps.positions[i]);
			glm::vec3 norm = GetCollisionNorm(colPos);
			ReboundPlane(ps.positions[i], ps.celerities[i], norm, GetDFromPlane(colPos, norm));
		}

		while (CheckCollisionBox(iPos, ps.positions[i]) < 6)
		{
			int collidedPlane = CheckCollisionBox(iPos, ps.positions[i]);
			ReboundPlane(ps.positions[i], ps.celerities[i], box.norms[collidedPlane], box.d[collidedPlane]);
		}
	}
}

float Euler::GetDFromPlane(glm::vec3 collisionPos, glm::vec3 normal)
{
	return -(collisionPos.x * normal.x) -
		(collisionPos.y * normal.y) -
		(collisionPos.z * normal.z);
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

glm::vec3 Euler::GetCollisionPoint(glm::vec3 iPos, glm::vec3 pos)
{
	float a = 0, b = 0, c = 0, delta = 0, lambda = 0;
	glm::vec3 vD = pos - iPos;
	glm::vec3 collisionPos;

	a = glm::pow(vD.x, 2) + glm::pow(vD.y, 2) + glm::pow(vD.z, 2);
	b = 2 * glm::dot(iPos - sphere.c, vD);
	c = glm::pow((iPos.x - sphere.c.x), 2) + glm::pow((iPos.y - sphere.c.y), 2) + glm::pow((iPos.z - sphere.c.z), 2) - glm::pow(sphere.r, 2);

	delta = glm::pow(b, 2) - (4 * a * c);
	if (delta == 0)
	{
		lambda = -b / (2 * a);
		collisionPos.x = iPos.x + lambda * vD.x;
		collisionPos.y = iPos.y + lambda * vD.y;
		collisionPos.z = iPos.z + lambda * vD.z;
	}
	else if (delta > 0)
	{
		lambda = (-b - glm::sqrt(delta)) / (2 * a);
		collisionPos.x = iPos.x + lambda * vD.x;
		collisionPos.y = iPos.y + lambda * vD.y;
		collisionPos.z = iPos.z + lambda * vD.z;

		if (glm::dot(collisionPos, iPos) < 0) // el angulo es agudo
		{
			lambda = (-b + glm::sqrt(delta)) / (2 * a);
			collisionPos.x = iPos.x + lambda * vD.x;
			collisionPos.y = iPos.y + lambda * vD.y;
			collisionPos.z = iPos.z + lambda * vD.z;
		}
	}

	return collisionPos;
}

glm::vec3 Euler::GetCollisionNorm(glm::vec3 collisionPos)
{
	return glm::normalize(collisionPos - sphere.c);
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