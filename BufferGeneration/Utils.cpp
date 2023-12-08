#include <stdexcept>

#include "Utils.h"
#include "Vector.h"
#include "SimpleLine.h"
#include "StraightLine.h"

const double Utils::threshold = 1e-11;
const double Utils::PI = 3.1415926535;

bool Utils::IsDoubleEqual(double a, double b)
{
	return abs(a - b) < threshold ? true : false;
}


Vector Utils::Intersect(SimpleLine l1, SimpleLine l2)
{
	return Intersect(l1.ToStraightLine(), l2.ToStraightLine());
}

Vector Utils::Intersect(StraightLine l1, StraightLine l2)
{
	if (StraightLine::IsParallel(l1, l2))
		throw std::logic_error("The tow lines are parallel");
	double D = l1.A * l2.B - l1.B * l2.A;
	double Dx = -l1.C * l2.B + l2.C * l1.B;
	double Dy = -l1.A * l2.C + l2.A * l1.C;
	return Vector(Dx / D, Dy / D);
}

double Utils::Angle2Radians(double angle)
{
	return angle * PI / 180.0;
}

double Utils::Radians2Angle(double radians)
{
	return radians * 180.0 / PI;
}
