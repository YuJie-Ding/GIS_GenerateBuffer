#include "Vector.h"

Vector::Vector()
{
	x = y = 0;
}

Vector::Vector(double x, double y)
{
	this->x = x;
	this->y = y;
}

Vector::Vector(const Vector& p)
{
	this->x = p.x;
	this->y = p.y;
}

double Vector::GetLength() const
{
	return sqrt(x * x + y * y);
}

Vector Vector::Normalize() const
{
	double length = GetLength();
	return Vector(x / length, y / length);
}

double Vector::Cross(const Vector& v1, const Vector& v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}
