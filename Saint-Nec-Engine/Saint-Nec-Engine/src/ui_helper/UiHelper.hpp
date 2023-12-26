#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <typeinfo>

#include <architecture/Scene.hpp>
#include <architecture/SceneManager.hpp>
#include <architecture/GameObject.hpp>


class UiHelper
{

public:

	static void WindowSceneManagerTree(sne::SceneManager* manager);

private:
	static void SceneManagerHelper(const sne::SceneManager& sceneManager);
	static void SceneHelper(const sne::Scene& scene);
	static void GameObjectHelper(const sne::GameObject& gameObject);
};