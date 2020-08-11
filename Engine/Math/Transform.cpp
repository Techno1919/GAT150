#include "pch.h"
#include "Transform.h"

namespace nc
{
	std::istream& operator>>(std::istream& stream, Transform& t)
	{
		stream >> t.position;

		std::string line;
		std::getline(stream, line);
		t.scale = stof(line);

		std::getline(stream, line);
		t.angle = stof(line);

		return stream;
	}
	void Transform::Update()
	{
		Matrix3x3 mxScale;
		mxScale.Scale(scale);

		Matrix3x3 mxRotate;
		mxRotate.Rotate(angle);

		Matrix3x3 mxTrans;
		mxTrans.Translate(position);

		matrix = mxScale * mxRotate * mxTrans;
	}
	void Transform::Update(const Matrix3x3& mx)
	{
		Update();
		matrix = matrix * mx;
	}
}

