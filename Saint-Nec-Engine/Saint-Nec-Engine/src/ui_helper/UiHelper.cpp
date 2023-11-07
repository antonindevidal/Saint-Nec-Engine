#include "UiHelper.hpp"

void UiHelper::WindowSceneTree(const sne::Scene& scene)
{
	ImGui::Begin("Scene tree");
	SceneHelper(scene);
	ImGui::End();
}

void UiHelper::SceneManagerHelper(const sne::SceneManager& sceneManager)
{
}

void UiHelper::SceneHelper(const sne::Scene& scene)
{
	const std::vector<sne::GameObject*> list = scene.getGameObjects();
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
