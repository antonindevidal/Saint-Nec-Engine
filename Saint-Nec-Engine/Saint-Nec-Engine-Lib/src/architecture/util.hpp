#pragma once

/**
 * @file util.hpp
 * @brief file that contains usefull and mixed functions.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 6rd 2023.
 *
 */

#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace glm
{
	bool operator==(const glm::vec3 &v1, const glm::vec3 &v2);
	bool operator<(const glm::vec3 &v1, const glm::vec3 &v2);
	bool operator>(const glm::vec3 &v1, const glm::vec3 &v2);
	bool operator<=(const glm::vec3 &v1, const glm::vec3 &v2);
	bool operator>=(const glm::vec3 &v1, const glm::vec3 &v2);
	glm::vec3 operator-(const glm::vec3 &v, float &eps);
	glm::vec3 operator+(const glm::vec3 &v, float &eps);
	std::ostream &operator<<(std::ostream &oss, const glm::vec3 &v);
}

namespace sne
{
	/**
	 * @brief evalute the norm of the vector
	 *
	 * @param v
	 * @return double
	 */
	double norm(const glm::vec3 &v);

	/**
	 * @brief build matrix for rotation
	 *
	 * @param rx x angle
	 * @param ry y angle
	 * @param rz z angle
	 * @return rotation matrix
	 */
	glm::mat3 buildRotationMatrix(float rx, float ry, float rz);

	/**
	 * @brief build matrix for rotation
	 *
	 * @param rotation
	 * @return glm::mat3
	 */
	glm::mat3 buildRotationMatrix(const glm::vec3 &rotation);

	/**
	 * @brief pretty print for rotation matrix
	 *
	 * @param R rotation matrix
	 * @param rx
	 * @param ry
	 * @param rz
	 */
	void displayRotationMatrix(glm::mat3 &R, float rx, float ry, float rz);

	/**
	 * @brief update point after a rotation
	 *
	 * @param rotationMatrix matrix that built whith the corresponding angles of rotation
	 * @param point point to rotate
	 * @param center rotation center
	 */
	void rotate(const glm::mat3 &rotationMatrix, glm::vec3 &point, const glm::vec3 &center);
}