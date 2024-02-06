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
		Minkowski(const glm::vec3& pointA, const glm::vec3& pointB, bool isDiff=true)
		{
			_pointA = pointA;
			_pointB = pointB;
			
			if(isDiff)
				_coordinate = _pointA - _pointB;
			else
				_coordinate = _pointA + _pointB;

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