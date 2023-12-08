#pragma once
#include "Utils.h"

class Vector
{
public:
	double x;
	double y;

public:
	Vector();
	Vector(double x, double y);
	Vector(const Vector& p);
	bool operator==(const Vector& p) const
	{
		return Utils::IsDoubleEqual(x, p.x) && Utils::IsDoubleEqual(y, p.y);
	}

	Vector operator+(const Vector& p) const
	{
		return Vector(x + p.x, y + p.y);
	}

	Vector operator-(const Vector& p) const
	{
		return Vector(x - p.x, y - p.y);
	}

	double GetLength() const;
	Vector Normalize() const;

	static double Cross(const Vector& v1, const Vector& v2);
};

