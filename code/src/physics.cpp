#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <glm/glm.hpp>
#include "../ParticleSystem.h"

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
//float initialAngle = 0.0f;
float angle = 0.f;
int nextParticleIdx = 0.f;

float emissionRate = 1.f; // Particles/second
float maxAge = 5.f; // Seconds

void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);

	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		ImGui::InputFloat("Emission rate", &emissionRate, 1.f);
		ImGui::InputFloat("Max age", &maxAge);
	}

	ImGui::End();
}

void PhysicsInit() {
	renderParticles = true;
	ps = ParticleSystem(1000);
}

void spawn()
{
	float x = nextParticleIdx * cos(angle) / 20.f;
	float y = nextParticleIdx / 10.f;
	float z = nextParticleIdx * sin(angle) / 20.f;

	angle += 0.1f;

	ps.SpawnParticle(glm::vec3(x, y, z));

	//nextParticleIdx++;
	nextParticleIdx = (nextParticleIdx + 1) % ps.maxParticles;
}

void PhysicsUpdate(float dt) {
	ps.DestroyOldParticles(maxAge);

	//if (nextParticleIdx < ps.maxParticles)
	{
		spawn();
	}
	//initialAngle += 0.1f;

	ps.UpdateLilSpheres();
	ps.UpdateAge(dt);
}

void PhysicsCleanup() {
}