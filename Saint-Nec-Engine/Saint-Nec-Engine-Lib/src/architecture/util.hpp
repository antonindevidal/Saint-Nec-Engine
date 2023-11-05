#pragma once
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace sne
{

	bool operator==(const glm::vec3 &v1, const glm::vec3 &v2);
	bool operator<(const glm::vec3 &v1, const glm::vec3 &v2);
	bool operator>(const glm::vec3 &v1, const glm::vec3 &v2);
	bool operator<=(const glm::vec3 &v1, const glm::vec3 &v2);
	bool operator>=(const glm::vec3 &v1, const glm::vec3 &v2);
	glm::vec3 operator-(const glm::vec3 &v, float &eps);
	glm::vec3 operator+(const glm::vec3 &v, float &eps);
	// 	glm::vec3 operator*(double) const;
	std::ostream &operator<<(std::ostream &oss, const glm::vec3 &v);

	// template <typename GLMVect>
	// double norm(const GLMVect &v)
	// {
	// 	float res = 0;
	// 	for (auto elt : v)
	// 		res += elt * elt;

	// 	return sqrt(res);
	// }

	double norm(const glm::vec3 &v);
	// glm::vec3 operator-(const glm::vec3 &p, double eps);
	// glm::vec3 operator+(const glm::vec3 &p, double eps);
	glm::mat3 buildRotationMatrix(float alpha, float beta, float gamma);
	void displayRotationMatrix(glm::mat3 &R, float alpha, float beta, float gamma);
}