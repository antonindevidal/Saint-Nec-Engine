#pragma once
/**
 * @file GameObject.hpp
 * @brief Basic GameObject.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 3rd 2023.
 *
 */

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tracy/Tracy.hpp>

#include "Component.hpp"
#include "Vector3.hpp"

namespace sne
{
	/**
	* @class GameObject.
	* @brief Basic GameObject to be used in a scene.
	*/
	class GameObject
	{
	private:
		Vector3 position; //TODO: remove 
		Vector3 rotation; //TODO: remove - Radian
		
		/**
		 * Vector of components used by the GameObject.
		 */
		std::vector<Component*> components;

		/**
		 * 4*4 Matrix containing position and rotation of the GameObject.
		 */
 		glm::mat4 model;

		/**
		* Name for the GameObject
		*/
		std::string name;

	public:

		/**
		 * Default constructor of the GameObject.
		 */
		GameObject();

		/**
		 * Destructor of a GameObject instance.
		 */
		~GameObject();

		/**
		 * Update function of a GameObject instance.
		 * All the logic happens here.
		 */
		void update();

		/**
		 * Draw function of a GameObject instance.
		 * No logic should happen there.
		 */
		void draw() const;

		/**
		 * Add a component to the components vector.
		 * 
		 * @param component Component to add to the vector.
		 */
		void addComponent(Component* component);

		const std::vector<Component*> getComponent() const;

		/**
		 * Getter for the model matrix.
		 * 
		 * @return Model matrix .
		 */
		const glm::mat4& getModel() const;

		/**
		 * Setter for the model matrix.
		 * 
		 * @param newModel New model matrix to set.
		 */
		void setModel(const glm::mat4& newModel);

		/**
		 * Translate the model matrix.
		 * 
		 * @param translation Translation applied to the model matrix.
		 */
		void translate(const glm::vec3& translation);

		/**
		 * Rotate the model matrix.
		 * 
		 * @param angle Angle in degree to rotate the matrix.
		 * @param axis Axis of rotation.
		 */
		void rotate(const float angle, const glm::vec3& axis);

		/**
		*  Getter for the name of an instance of GamObject.
		*/
		const std::string& getName() const;

		/**
		* Setter for the name
		* 
		* @param newName Name to set.
		*/
		void setName(const std::string& newName);
	};
}