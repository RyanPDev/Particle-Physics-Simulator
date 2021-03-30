#include "..\Emitter.h"

Emitter::Emitter(){}
Emitter::Emitter(Type _type):type(_type)
{
	type = Type::CASCADE;
	position = glm::vec3(0, 1, 0);
	endCascadePos = glm::vec3(4, 2, 4);
	direction = glm::vec3(1, 1, 0);
	speed = 5;
	angle = 30;
}
void Emitter::spawn(ParticleSystem &_ps)
{
	if (_ps.currentParticles < _ps.maxParticles)
	{
		_ps.SpawnParticle(CalcPos(),CalcDir(angle));
	}
}
glm::vec3 Emitter::CalcPos() {
	switch(type)
	{
	case Type::FOUNTAIN:
		break;
	case Type::CASCADE:
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		return position + (glm::vec3(endCascadePos - position)* r);
		break;
	}
	return position;
}
glm::vec3 Emitter::CalcDir(int _angle) {
	//float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	//return glm::normalize(glm::cos());
	//glm::dot()
	switch(type)
	{
	case Type::FOUNTAIN:
		break;
	case Type::CASCADE:
		break;
	}
	return glm::normalize(direction) * speed;
}