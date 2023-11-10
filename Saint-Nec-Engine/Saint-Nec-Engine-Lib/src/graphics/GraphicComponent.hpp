
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <stb_image.h>
#include "Shader.hpp"
#include "../architecture/Component.hpp"
#include "../architecture/SceneManager.hpp"
#include "../architecture/GameObject.hpp"
namespace sne::graphics
{
	enum VertexDataType
	{
		SNE_VERTICES, // 3 floats
		SNE_VERTICES_TEXTURE, // 3 floats + 2 floats
		SNE_VERTICES_COLOR, //3 floats + 3 floats
		SNE_VERTICES_COLOR_TEXTURE //3 floats + 3 floats + 2 floats
	};

	/**
	 * 
	 * Use triangles as primitives.
	 */
	class GraphicComponent: public sne::Component
	{
	public:
		GraphicComponent(const char* vertexShaderPath, const char* fragmentShaderPath);

		void setGeometry(const std::vector<float>& vertices, const VertexDataType& vertexDataType, const std::vector<int>& indices);
		void setTexture(const char* texturePath, const char* name);

		void draw() const override;

	private:
		/**
		* Vertex Buffer Object.
		*/
		unsigned int VBO;

		/**
		* Vertex Array Object.
		*/
		unsigned int VAO;

		/**
		* Element Buffer Object.
		*/
		unsigned int EBO;

		/**
		 * Number of elements to be rendered (points).
		 */
		unsigned int renderedElementCount;

		/**
		 * Shader object for graphic component.
		 */
		Shader shader;

		/**
		 * Texture ID.
		 */
		unsigned int textureID; // For now, only one texture per graphic component is suppported

		bool hasTexture;
		bool hasGeometry;
	};
}

