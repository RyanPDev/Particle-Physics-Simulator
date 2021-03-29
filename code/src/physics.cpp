#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include "../ParticleSystem.h"
#include "../Emitter.h"
#include "../Euler.h"
#include <glm/glm.hpp>


//Exemple
extern void Exemple_GUI();
extern void Exemple_PhysicsInit();
extern void Exemple_PhysicsUpdate(float dt);
extern void Exemple_PhysicsCleanup();

namespace LilSpheres {
	extern const int maxParticles;
}
extern bool renderParticles;

bool show_test_window = false;


ParticleSystem ps;
Emitter emitter;
Euler euler;
//float initialAngle = 0.0f;
float angle = 0.f;
int nextParticleIdx = 0.f;
float time = 0;
float emissionRate = 1.f; // Particles/second
float maxAge = 5.f; // Seconds

void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);

	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		ImGui::InputFloat("Emission rate", &emissionRate, 1.f);
		ImGui::InputFloat("Max age", &maxAge);
		ImGui::InputInt("Max Particles", &ps.maxParticles);
	}

	ImGui::End();
}

void PhysicsInit() {

	renderParticles = true;
	ps = ParticleSystem(100);
	emitter = Emitter(Emitter::Type::FOUNTAIN);
	euler = Euler();
}


void PhysicsUpdate(float dt) 
{
	ps.DestroyOldParticles(maxAge);
	time += dt;
	if (time >= 1 / emissionRate)
	{
		time = 0;
		emitter.spawn(ps);
		nextParticleIdx = (nextParticleIdx + 1) % ps.maxParticles;
	}
	euler.Update(ps,dt);
	ps.UpdateLilSpheres();
	ps.UpdateAge(dt);
}

void PhysicsCleanup() {
}