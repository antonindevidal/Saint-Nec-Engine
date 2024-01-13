#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <architecture/util.hpp>

namespace sne::physics
{
	class Minkowski {
		glm::vec3 _pointA,
			_pointB,
			_coordinate;
		float _distance; 

	public:
		Minkowski(const glm::vec3& pointA, const glm::vec3& pointB)
		{
			_pointA = pointA;
			_pointB = pointB;
			_coordinate = _pointA - _pointB;
			_distance = norm(_coordinate);
		}

		float getDistance() const
		{
			return _distance;
		}

		glm::vec3 getPointA() const
		{
			return _pointA;
		}

		glm::vec3 getPointB() const
		{
			return _pointB;
		}
	};

}