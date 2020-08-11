#pragma once
#include <iostream>
#include "Math/Matrix3x3.h"

namespace nc
{
	struct Transform
	{
		Vector2 position;
		float scale;
		float angle;

		Matrix3x3 matrix;

		Transform() : position{ 0,0 }, scale{ 1 }, angle{ 0 } {}
		Transform(const Vector2& position, float scale = 1, float angle = 0) : position{ position }, scale{ scale }, angle{ angle } {}

		void Update();
		void Update(const Matrix3x3& mx);

		friend std::istream& operator >> (std::istream& stream, Transform& t);

	};
}
