#include "UiHelper.hpp"

void UiHelper::WindowSceneTree(const sne::Scene* scene)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Begin("Scene tree");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::Separator();
	ImGui::Text("Camera:");
	ImGui::Text("Position: %f %f %f", scene->getCamera().getPosition().x, scene->getCamera().getPosition().y, scene->getCamera().getPosition().z);
	ImGui::Text("Front: %f %f %f", scene->getCamera().getFront().x, scene->getCamera().getFront().y, scene->getCamera().getFront().z);
	ImGui::Separator();

	SceneHelper(scene);
	ImGui::End();
}

void UiHelper::SceneManagerHelper(const sne::SceneManager& sceneManager)
{
}

void UiHelper::SceneHelper(const sne::Scene* scene)
{
	const std::vector<sne::GameObject*> list = scene->getGameObjects();
	for (sne::GameObject *g : list)
	{
		GameObjectHelper(*g);
	}
}

void UiHelper::GameObjectHelper(const sne::GameObject& gameObject)
{
	ImGui::Separator();
	ImGui::Text(gameObject.getName().c_str());
	ImGui::Text("Coordinates: %f %f %f", gameObject.getModel()[3].x, gameObject.getModel()[3].y, gameObject.getModel()[3].z);

	for (sne::Component* c : gameObject.getComponent())
	{
		ImGui::Text(typeid(*c).name()); // Using reflection because only for debug purpose
	}
}
