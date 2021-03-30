#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include "../ParticleSystem.h"
#include "../Emitter.h"
#include "../Euler.h"
#include <glm/glm.hpp>
#include <ctime>

//Exemple
extern void Exemple_GUI();
extern void Exemple_PhysicsInit();
extern void Exemple_PhysicsUpdate(float dt);
extern void Exemple_PhysicsCleanup();

namespace LilSpheres {
	extern const int maxParticles;
}


extern bool renderParticles;
extern bool renderSphere;;

bool show_test_window = false;

ParticleSystem ps;
Emitter emitter;
Euler euler;
//float initialAngle = 0.0f;
float angle = 0.f;
int nextParticleIdx = 0.f;
float timer = 0;
float emissionRate = 500.f; // Particles/second
float maxAge = 5.f; // Seconds

void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 0);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate

	ImGui::InputFloat("Emission rate", &emissionRate, 1.f);	
	ImGui::DragFloat("Max age", &maxAge, 0.05f, 0.5f, 10.f);	
	ImGui::InputInt("Max Particles", &ps.maxParticles);
	ImGui::DragFloat("Speed", &emitter.speed, 0.05f, 0.f, 20.f);

	ImGui::DragFloat3("Direction", (float*)&emitter.direction, 0.05f, -1.f, 1.f);
	switch(emitter.type)
	{
	case Emitter::Type::FOUNTAIN:
		if (ImGui::Button("Cascade")) { emitter.type = Emitter::Type::CASCADE; }
	

		break;
	case Emitter::Type::CASCADE:
		if (ImGui::Button("Fountain")) { emitter.type = Emitter::Type::FOUNTAIN; }
		ImGui::DragFloat3("Position Cascade", (float*)&emitter.endCascadePos, 0.05f, -4.5f, 4.5f);
		break;
	}
	ImGui::DragFloat3("Position", (float*)&emitter.position, 0.05f, -4.5f, 4.5f);
	ImGui::DragFloat3("Gravedad", (float*)&euler.gravity, 0.05f, -9.8f, 9.8f);

	ImGui::DragFloat("Elasticidad", &euler.reboundCoefficient, 0.005f, 0.01f, 1.f);

	ImGui::End();
}

void PhysicsInit() {
	//srand(static_cast<unsigned>(time(nullptr)));
	renderParticles = true;
	//renderSphere = true;
	ps = ParticleSystem(1000);
	emitter = Emitter(Emitter::Type::FOUNTAIN);
	euler = Euler();
}

void PhysicsUpdate(float dt)
{
	ps.DestroyOldParticles(maxAge);
	timer += dt;
	if (timer >= 1 / emissionRate)
	{
		while (timer > 0)
		{
			timer -= 1 / emissionRate;
			emitter.spawn(ps);
		}
		//nextParticleIdx = (nextParticleIdx + 1) % ps.maxParticles;

		timer = 0;
	}
	euler.Update(ps, dt);
	ps.UpdateLilSpheres();
	ps.UpdateAge(dt);
}

void PhysicsCleanup() {
}