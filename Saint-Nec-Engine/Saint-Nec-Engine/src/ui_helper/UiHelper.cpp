#include "UiHelper.hpp"


void UiHelper::WindowSceneManagerTree(sne::SceneManager* manager)
{
	ImGui::Begin("Scene Managment");


	for (const sne::Scene* s : manager->getScenes())
	{
		if (ImGui::Button(s->getName().c_str(), ImVec2(300,30)))
		{
			manager->changeScene(s->getName());
		}
	}

	SceneHelper(manager->getCurrentScene());

	ImGui::End();

}


void UiHelper::SceneManagerHelper(const sne::SceneManager& sceneManager)
{
}

void UiHelper::SceneHelper(const sne::Scene& scene)
{

	ImGui::Text("Camera:");
	ImGui::Text("Position: %f %f %f", scene.getCamera().getPosition().x, scene.getCamera().getPosition().y, scene.getCamera().getPosition().z);
	ImGui::Separator();

	const std::vector<sne::GameObject*> list = scene.getGameObjects();
	for (sne::GameObject* g : list)
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
