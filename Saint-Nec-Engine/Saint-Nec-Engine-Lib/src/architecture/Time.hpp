#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Time
{
public:

	static Time* instance;

	Time();

	~Time();

	static Time* getInstance();

	void calculateDeltaTime();

	static float getDeltaTime();
private:
	float lastFrame;
	static float deltaTime;

};


