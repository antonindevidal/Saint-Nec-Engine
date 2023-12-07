#include "Time.hpp"


Time* Time::instance = nullptr;
float Time::deltaTime = 0.0f;


Time::Time() : lastFrame(0.0f)
{

}

Time::~Time()
{
}

Time* Time::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Time();
	}
	return instance;
}

void Time::calculateDeltaTime()
{
	float currentFrame = glfwGetTime();
	Time::deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

float Time::getDeltaTime()
{
	return deltaTime;
}

float Time::getTimeSinceStart()
{
	return glfwGetTime();
}
