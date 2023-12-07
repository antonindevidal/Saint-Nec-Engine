#pragma once
/**
 * @file Time.hpp
 * @brief Time class definition.
 * @author Antonin DEVIDAL.
 * @date november 8 2023.
 *
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * @class Time.
 * @brief Manage time and calculate delta time for update in the game.
 * 
 * This class is a singleton.
 */
class Time
{
public:
	/**
	 * Instance of the singleton.
	 */
	static Time* instance;

	/**
	 * Default constructor.
	 */
	Time();

	/**
	 * Destructor.
	 */
	~Time();

	/**
	 * Return the instance of the singleton.
	 * If the instance is nullptr, it creates the instance
	 */
	static Time* getInstance();

	/**
	 * Calculate the delta time.
	 * This must be called in the main loop of the Application!
	 */
	void calculateDeltaTime();

	/**
	 * Return delta time.
	 */
	static float getDeltaTime();

	/**
	 * Return OpenGL time.
	 */
	static float getTimeSinceStart();
private:
	/**
	 * Last frame time.
	 */
	float lastFrame;

	/**
	 * Last delta time calculated.
	 */
	static float deltaTime;

};


