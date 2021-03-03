#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <glm/glm.hpp>

//Exemple
extern void Exemple_GUI();
extern void Exemple_PhysicsInit();
extern void Exemple_PhysicsUpdate(float dt);
extern void Exemple_PhysicsCleanup();

namespace LilSpheres {
	extern int firstParticleIdx, particleCount;
	extern const int maxParticles;
	extern void updateParticles(int startIdx, int count, float* array_data);
}
extern bool renderParticles;

bool show_test_window = false;
void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);

	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		Exemple_GUI();
	}
	
	ImGui::End();
}


//class Particle
//{
//public:
//	Particle() : position(glm::vec3(0.f, 0.f, 0.f)) {};
//	Particle(glm::vec3 _position) : position(_position) {};
//	glm::vec3 position;
//};

class ParticleSystem
{
public:
	ParticleSystem(int numParticles /*, (posicions opcionals)*/) {};

	void updateParticle(int idx, glm::vec3 newPos)
	{

	}

	void updateLilSpheres()
	{

	}

private:

};

ParticleSystem ps;

void PhysicsInit() {
	//Exemple_PhysicsInit();
	renderParticles = true;
	ps = ParticleSystem(1);

	ps.updateParticle(0, glm::vec3(4.f, 3.f, 2.f));

	LilSpheres::firstParticleIdx = 0;
	LilSpheres::particleCount = 1;
}

void PhysicsUpdate(float dt) {
	//Exemple_PhysicsUpdate(dt);

	//int startParticle = 0;
	//int numParticles = 1;
	//float* particlesPositionVector = &(p1.position.x);

	//LilSpheres::updateParticles(startParticle, numParticles, particlesPositionVector);
}

void PhysicsCleanup() {
	//Exemple_PhysicsCleanup();
}