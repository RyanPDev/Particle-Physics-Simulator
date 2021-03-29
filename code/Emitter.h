#pragma once
#include "ParticleSystem.h"
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
static class Emitter
{
private:
	glm::vec3 CalcPos();
	glm::vec3 CalcDir(int _angle);
	
public:
	enum class Type {FOUNTAIN, CASCADE,COUNT};
	glm::vec3 position;
	glm::vec3 direction;
	float speed;
	int angle;

	Type type;
	Emitter();
	Emitter(Type _type);
	void spawn(ParticleSystem& _ps);
};

